"""Test doubles for PyMongo.

The production module still requires the real PyMongo package. These unit tests
install a small in-memory substitute before importing the module, which keeps
the test suite isolated from a live database.
"""

from __future__ import annotations

import copy
import sys
import types
from dataclasses import dataclass
from pathlib import Path
from typing import Any

import pytest


class FakePyMongoError(Exception):
    pass


@dataclass
class InsertOneResult:
    acknowledged: bool
    inserted_id: str


@dataclass
class UpdateResult:
    matched_count: int
    modified_count: int


@dataclass
class DeleteResult:
    deleted_count: int


class FakeCursor:
    def __init__(self, documents: list[dict[str, Any]]):
        self._documents = documents

    def sort(self, fields: list[tuple[str, int]]) -> "FakeCursor":
        for field, direction in reversed(fields):
            self._documents.sort(
                key=lambda document: (document.get(field) is None, document.get(field)),
                reverse=direction < 0,
            )
        return self

    def limit(self, count: int) -> "FakeCursor":
        self._documents = self._documents[:count]
        return self

    def __iter__(self):
        return iter(copy.deepcopy(self._documents))


class FakeCollection:
    def __init__(self):
        self.documents: list[dict[str, Any]] = []
        self.indexes: dict[str, dict[str, Any]] = {}
        self._next_id = 1

    def create_index(self, fields, *, unique=False, name=None):
        index_name = name or "_".join(field for field, _ in fields)
        self.indexes[index_name] = {
            "fields": tuple(fields),
            "unique": unique,
        }
        return index_name

    def insert_one(self, document):
        new_document = copy.deepcopy(document)
        for index in self.indexes.values():
            if not index["unique"]:
                continue
            fields = [field for field, _ in index["fields"]]
            for existing in self.documents:
                if all(existing.get(field) == new_document.get(field) for field in fields):
                    raise FakePyMongoError("duplicate key")

        inserted_id = f"fake-{self._next_id}"
        self._next_id += 1
        new_document.setdefault("_id", inserted_id)
        self.documents.append(new_document)
        return InsertOneResult(True, inserted_id)

    def find(self, query, projection=None):
        matches = [
            copy.deepcopy(document)
            for document in self.documents
            if self._matches(document, query)
        ]
        if projection is not None:
            matches = [self._project(document, projection) for document in matches]
        return FakeCursor(matches)

    def update_one(self, query, update_document):
        return self._update(query, update_document, many=False)

    def update_many(self, query, update_document):
        return self._update(query, update_document, many=True)

    def delete_one(self, query):
        return self._delete(query, many=False)

    def delete_many(self, query):
        return self._delete(query, many=True)

    def _update(self, query, update_document, *, many):
        matched = 0
        modified = 0
        for document in self.documents:
            if not self._matches(document, query):
                continue
            matched += 1
            before = copy.deepcopy(document)
            document.update(update_document.get("$set", {}))
            if document != before:
                modified += 1
            if not many:
                break
        return UpdateResult(matched, modified)

    def _delete(self, query, *, many):
        deleted = 0
        kept = []
        for document in self.documents:
            should_delete = self._matches(document, query) and (many or deleted == 0)
            if should_delete:
                deleted += 1
            else:
                kept.append(document)
        self.documents = kept
        return DeleteResult(deleted)

    @staticmethod
    def _matches(document, query):
        for field, expected in query.items():
            actual = document.get(field)
            if isinstance(expected, dict) and "$in" in expected:
                if actual not in expected["$in"]:
                    return False
            elif actual != expected:
                return False
        return True

    @staticmethod
    def _project(document, projection):
        included = {key for key, value in projection.items() if value}
        excluded = {key for key, value in projection.items() if not value}
        if included:
            result = {key: document[key] for key in included if key in document}
            if projection.get("_id", 1) and "_id" in document:
                result["_id"] = document["_id"]
            return result
        return {key: value for key, value in document.items() if key not in excluded}


class FakeDatabase:
    def __init__(self):
        self.collections: dict[str, FakeCollection] = {}

    def __getitem__(self, collection_name):
        return self.collections.setdefault(collection_name, FakeCollection())


class FakeAdmin:
    def __init__(self, client):
        self.client = client

    def command(self, name):
        if name != "ping":
            raise FakePyMongoError("unsupported command")
        self.client.ping_count += 1
        if self.client.fail_ping:
            raise FakePyMongoError("server unavailable")
        return {"ok": 1}


class FakeMongoClient:
    def __init__(self, *args, fail_ping=False, **kwargs):
        self.args = args
        self.kwargs = kwargs
        self.fail_ping = fail_ping
        self.ping_count = 0
        self.close_count = 0
        self.databases: dict[str, FakeDatabase] = {}
        self.admin = FakeAdmin(self)

    def __getitem__(self, database_name):
        return self.databases.setdefault(database_name, FakeDatabase())

    def close(self):
        self.close_count += 1


# Install fake modules before animal_shelter.py is imported during collection.
pymongo_module = types.ModuleType("pymongo")
pymongo_module.ASCENDING = 1
pymongo_module.MongoClient = FakeMongoClient
errors_module = types.ModuleType("pymongo.errors")
errors_module.PyMongoError = FakePyMongoError
pymongo_module.errors = errors_module
sys.modules.setdefault("pymongo", pymongo_module)
sys.modules.setdefault("pymongo.errors", errors_module)

ENHANCED_DIR = Path(__file__).resolve().parents[1]
if str(ENHANCED_DIR) not in sys.path:
    sys.path.insert(0, str(ENHANCED_DIR))


@pytest.fixture
def fake_client():
    return FakeMongoClient()
