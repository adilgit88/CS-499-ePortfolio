from __future__ import annotations

import logging

import pytest

from animal_shelter import (
    AnimalShelter,
    ConfigurationError,
    DatabaseConfig,
    DatabaseConnectionError,
    ValidationError,
)


@pytest.fixture
def config():
    return DatabaseConfig(user="test user", password="p@ss word")


@pytest.fixture
def shelter(config, fake_client):
    return AnimalShelter(config, client=fake_client)


def sample_animal(animal_id="A1001", animal_type="dog", **extra):
    document = {
        "animal_id": animal_id,
        "animal_type": animal_type,
        "breed": "Labrador Retriever Mix",
        "name": "Scout",
        "sex_upon_outcome": "Neutered Male",
    }
    document.update(extra)
    return document


def test_environment_requires_credentials(monkeypatch):
    monkeypatch.delenv("MONGODB_USER", raising=False)
    monkeypatch.delenv("MONGODB_PASSWORD", raising=False)
    with pytest.raises(ConfigurationError):
        DatabaseConfig.from_environment()


def test_environment_rejects_invalid_port(monkeypatch):
    monkeypatch.setenv("MONGODB_USER", "user")
    monkeypatch.setenv("MONGODB_PASSWORD", "password")
    monkeypatch.setenv("MONGODB_PORT", "not-a-number")
    with pytest.raises(ConfigurationError):
        DatabaseConfig.from_environment()


def test_uri_encodes_special_characters(config):
    uri = config.build_uri()
    assert "test+user" in uri
    assert "p%40ss+word" in uri
    assert "p@ss word" not in uri


def test_constructor_verifies_connection(config, fake_client):
    AnimalShelter(config, client=fake_client, create_indexes=False)
    assert fake_client.ping_count == 1


def test_constructor_reports_connection_failure(config, fake_client):
    fake_client.fail_ping = True
    with pytest.raises(DatabaseConnectionError):
        AnimalShelter(config, client=fake_client)
    assert fake_client.close_count == 1


def test_expected_indexes_are_created(shelter):
    assert set(shelter.collection.indexes) == {
        "uq_animal_id",
        "ix_animal_type",
        "ix_breed",
        "ix_sex_upon_outcome",
        "ix_rescue_filters",
    }
    assert shelter.collection.indexes["uq_animal_id"]["unique"] is True


def test_create_normalizes_and_returns_inserted_id(shelter):
    result = shelter.create(sample_animal(animal_id=" a1001 ", animal_type="dog"))
    assert result.success is True
    assert result.inserted_id == "fake-1"
    stored = shelter.read({"animal_id": "A1001"})[0]
    assert stored["animal_type"] == "Dog"


def test_create_rejects_missing_required_field(shelter):
    with pytest.raises(ValidationError):
        shelter.create({"animal_id": "A1001", "breed": "Mix"})


def test_create_rejects_unknown_field(shelter):
    with pytest.raises(ValidationError):
        shelter.create(sample_animal(secret_note="not allowed"))


def test_duplicate_animal_id_returns_safe_failure(shelter, caplog):
    shelter.create(sample_animal())
    with caplog.at_level(logging.ERROR):
        result = shelter.create(sample_animal(name="Second Name"))
    assert result.success is False
    assert "could not be created" in result.message
    assert "Create operation failed" in caplog.text


def test_read_allows_safe_empty_query_projection_sort_and_limit(shelter):
    shelter.create(sample_animal("A1002", name="Zulu"))
    shelter.create(sample_animal("A1001", name="Alpha"))
    records = shelter.read(
        {},
        {"_id": 0, "animal_id": 1, "name": 1},
        sort=[("name", 1)],
        limit=1,
    )
    assert records == [{"animal_id": "A1001", "name": "Alpha"}]


def test_read_rejects_negative_limit(shelter):
    with pytest.raises(ValidationError):
        shelter.read({}, limit=-1)


def test_update_reports_matched_and_modified_counts(shelter):
    shelter.create(sample_animal())
    changed = shelter.update({"animal_id": "A1001"}, {"name": "Ranger"})
    unchanged = shelter.update({"animal_id": "A1001"}, {"name": "Ranger"})
    assert changed.success is True
    assert (changed.matched_count, changed.modified_count) == (1, 1)
    assert (unchanged.matched_count, unchanged.modified_count) == (1, 0)


def test_update_many_changes_all_matches(shelter):
    shelter.create(sample_animal("A1001"))
    shelter.create(sample_animal("A1002"))
    result = shelter.update(
        {"animal_type": "Dog"}, {"outcome_type": "Transfer"}, many=True
    )
    assert (result.matched_count, result.modified_count) == (2, 2)


def test_update_blocks_empty_filter(shelter):
    with pytest.raises(ValidationError):
        shelter.update({}, {"name": "Unsafe"})


def test_update_rejects_raw_mongodb_operator(shelter):
    with pytest.raises(ValidationError):
        shelter.update({"animal_id": "A1001"}, {"$set": {"name": "Unsafe"}})


def test_update_rejects_protected_identifier(shelter):
    with pytest.raises(ValidationError):
        shelter.update({"animal_id": "A1001"}, {"animal_id": "A9999"})


def test_delete_one_and_many_report_counts(shelter):
    shelter.create(sample_animal("A1001"))
    shelter.create(sample_animal("A1002"))
    shelter.create(sample_animal("C1001", animal_type="cat"))

    one = shelter.delete({"animal_id": "A1001"})
    many = shelter.delete({"animal_type": "Dog"}, many=True)

    assert one.deleted_count == 1
    assert many.deleted_count == 1
    assert len(shelter.read({})) == 1


def test_delete_blocks_empty_filter(shelter):
    with pytest.raises(ValidationError):
        shelter.delete({})


def test_health_check_reports_success_and_failure(shelter, fake_client):
    assert shelter.health_check() is True
    fake_client.fail_ping = True
    assert shelter.health_check() is False


def test_context_manager_closes_client(config, fake_client):
    with AnimalShelter(config, client=fake_client) as managed:
        assert managed.is_closed is False
    assert managed.is_closed is True
    assert fake_client.close_count == 1


def test_close_is_idempotent(shelter, fake_client):
    shelter.close()
    shelter.close()
    assert fake_client.close_count == 1


def test_operations_after_close_are_blocked(shelter):
    shelter.close()
    with pytest.raises(DatabaseConnectionError):
        shelter.read({})
