"""Secure and testable MongoDB data-access layer for animal records.

The enhanced class keeps the small CRUD-focused design of the original CS 340
artifact while adding configuration validation, connection verification,
structured logging, lifecycle management, safer update rules, useful indexes,
and more informative operation results.
"""

from __future__ import annotations

import logging
import os
from dataclasses import dataclass
from typing import Any, Iterable, Mapping, Optional, Sequence
from urllib.parse import quote_plus

from pymongo import ASCENDING, MongoClient
from pymongo.errors import PyMongoError

LOGGER = logging.getLogger(__name__)


class ConfigurationError(ValueError):
    """Raised when required database settings are missing or invalid."""


class DatabaseConnectionError(ConnectionError):
    """Raised when MongoDB cannot be reached or authentication fails."""


class ValidationError(ValueError):
    """Raised when a CRUD request could damage data or violates the contract."""


@dataclass(frozen=True)
class DatabaseConfig:
    """MongoDB settings loaded from environment variables."""

    user: str
    password: str
    host: str = "localhost"
    port: int = 27017
    database: str = "aac"
    collection: str = "animals"
    auth_source: str = "admin"
    server_selection_timeout_ms: int = 5000

    @classmethod
    def from_environment(cls) -> "DatabaseConfig":
        user = os.getenv("MONGODB_USER", "").strip()
        password = os.getenv("MONGODB_PASSWORD", "").strip()

        if not user or not password:
            raise ConfigurationError(
                "MONGODB_USER and MONGODB_PASSWORD must be set before connecting."
            )

        try:
            port = int(os.getenv("MONGODB_PORT", "27017"))
            timeout = int(os.getenv("MONGODB_TIMEOUT_MS", "5000"))
        except ValueError as exc:
            raise ConfigurationError(
                "MONGODB_PORT and MONGODB_TIMEOUT_MS must be whole numbers."
            ) from exc

        if not 1 <= port <= 65535:
            raise ConfigurationError("MONGODB_PORT must be between 1 and 65535.")
        if timeout < 100:
            raise ConfigurationError("MONGODB_TIMEOUT_MS must be at least 100.")

        return cls(
            user=user,
            password=password,
            host=os.getenv("MONGODB_HOST", "localhost").strip() or "localhost",
            port=port,
            database=os.getenv("MONGODB_DATABASE", "aac").strip() or "aac",
            collection=os.getenv("MONGODB_COLLECTION", "animals").strip()
            or "animals",
            auth_source=os.getenv("MONGODB_AUTH_SOURCE", "admin").strip()
            or "admin",
            server_selection_timeout_ms=timeout,
        )

    def build_uri(self) -> str:
        """Build a safe MongoDB connection string with encoded credentials."""
        user = quote_plus(self.user)
        password = quote_plus(self.password)
        auth_source = quote_plus(self.auth_source)
        return (
            f"mongodb://{user}:{password}@{self.host}:{self.port}/"
            f"{self.database}?authSource={auth_source}"
        )


@dataclass(frozen=True)
class CreateResult:
    success: bool
    inserted_id: Optional[str] = None
    message: str = ""


@dataclass(frozen=True)
class UpdateResult:
    success: bool
    matched_count: int = 0
    modified_count: int = 0
    message: str = ""


@dataclass(frozen=True)
class DeleteResult:
    success: bool
    deleted_count: int = 0
    message: str = ""


class AnimalShelter:
    """CRUD operations and index management for a MongoDB animal collection."""

    ALLOWED_FIELDS = frozenset(
        {
            "rec_num",
            "age_upon_outcome",
            "animal_id",
            "animal_type",
            "breed",
            "color",
            "date_of_birth",
            "datetime",
            "monthyear",
            "name",
            "outcome_subtype",
            "outcome_type",
            "sex_upon_outcome",
            "location_lat",
            "location_long",
            "age_upon_outcome_in_weeks",
        }
    )
    REQUIRED_CREATE_FIELDS = frozenset({"animal_id", "animal_type"})
    PROTECTED_UPDATE_FIELDS = frozenset({"_id", "animal_id"})

    def __init__(
        self,
        config: Optional[DatabaseConfig] = None,
        *,
        client: Optional[Any] = None,
        verify_connection: bool = True,
        create_indexes: bool = True,
    ) -> None:
        self.config = config or DatabaseConfig.from_environment()
        self._closed = False

        try:
            self.client = client or MongoClient(
                self.config.build_uri(),
                serverSelectionTimeoutMS=self.config.server_selection_timeout_ms,
            )
            self.database = self.client[self.config.database]
            self.collection = self.database[self.config.collection]

            if verify_connection:
                self.client.admin.command("ping")
            if create_indexes:
                self.ensure_indexes()
        except PyMongoError as exc:
            LOGGER.exception("MongoDB initialization failed")
            self._safe_close()
            raise DatabaseConnectionError(
                "Unable to connect to MongoDB. Check the server and credentials."
            ) from exc

    def __enter__(self) -> "AnimalShelter":
        return self

    def __exit__(self, exc_type: Any, exc: Any, traceback: Any) -> None:
        self.close()

    @property
    def is_closed(self) -> bool:
        return self._closed

    def health_check(self) -> bool:
        """Return True when the current client can reach MongoDB."""
        self._require_open()
        try:
            self.client.admin.command("ping")
            return True
        except PyMongoError:
            LOGGER.exception("MongoDB health check failed")
            return False

    def ensure_indexes(self) -> tuple[str, ...]:
        """Create indexes that match the dashboard's common filter patterns."""
        self._require_open()
        created = (
            self.collection.create_index(
                [("animal_id", ASCENDING)], unique=True, name="uq_animal_id"
            ),
            self.collection.create_index(
                [("animal_type", ASCENDING)], name="ix_animal_type"
            ),
            self.collection.create_index(
                [("breed", ASCENDING)], name="ix_breed"
            ),
            self.collection.create_index(
                [("sex_upon_outcome", ASCENDING)], name="ix_sex_upon_outcome"
            ),
            self.collection.create_index(
                [
                    ("animal_type", ASCENDING),
                    ("breed", ASCENDING),
                    ("sex_upon_outcome", ASCENDING),
                ],
                name="ix_rescue_filters",
            ),
        )
        LOGGER.info("Verified %d MongoDB indexes", len(created))
        return created

    def create(self, data: Mapping[str, Any]) -> CreateResult:
        """Insert one validated animal document and return its identifier."""
        self._require_open()
        document = self._validate_create_document(data)

        try:
            result = self.collection.insert_one(document)
            if not result.acknowledged:
                return CreateResult(False, message="MongoDB did not acknowledge the insert.")
            return CreateResult(True, inserted_id=str(result.inserted_id))
        except PyMongoError:
            LOGGER.exception("Create operation failed")
            return CreateResult(False, message="The animal record could not be created.")

    def read(
        self,
        query: Optional[Mapping[str, Any]] = None,
        projection: Optional[Mapping[str, int]] = None,
        *,
        sort: Optional[Sequence[tuple[str, int]]] = None,
        limit: int = 0,
    ) -> list[dict[str, Any]]:
        """Return matching documents with optional projection, sorting, and limit."""
        self._require_open()
        filter_document = self._validate_query(query, allow_empty=True)

        if projection is not None and not isinstance(projection, Mapping):
            raise ValidationError("projection must be a mapping or None.")
        if not isinstance(limit, int) or limit < 0:
            raise ValidationError("limit must be a nonnegative integer.")

        try:
            cursor = self.collection.find(filter_document, projection)
            if sort:
                cursor = cursor.sort(list(sort))
            if limit:
                cursor = cursor.limit(limit)
            return list(cursor)
        except PyMongoError:
            LOGGER.exception("Read operation failed")
            return []

    def update(
        self,
        query: Mapping[str, Any],
        changes: Mapping[str, Any],
        *,
        many: bool = False,
    ) -> UpdateResult:
        """Apply a controlled $set update and report matched and modified counts."""
        self._require_open()
        filter_document = self._validate_query(query, allow_empty=False)
        update_fields = self._validate_update_fields(changes)

        try:
            update_document = {"$set": update_fields}
            result = (
                self.collection.update_many(filter_document, update_document)
                if many
                else self.collection.update_one(filter_document, update_document)
            )
            return UpdateResult(
                True,
                matched_count=result.matched_count,
                modified_count=result.modified_count,
            )
        except PyMongoError:
            LOGGER.exception("Update operation failed")
            return UpdateResult(False, message="The animal record could not be updated.")

    def delete(
        self, query: Mapping[str, Any], *, many: bool = False
    ) -> DeleteResult:
        """Delete one or many documents, while blocking an empty filter."""
        self._require_open()
        filter_document = self._validate_query(query, allow_empty=False)

        try:
            result = (
                self.collection.delete_many(filter_document)
                if many
                else self.collection.delete_one(filter_document)
            )
            return DeleteResult(True, deleted_count=result.deleted_count)
        except PyMongoError:
            LOGGER.exception("Delete operation failed")
            return DeleteResult(False, message="The animal record could not be deleted.")

    def close(self) -> None:
        """Close the MongoDB client exactly once."""
        if not self._closed:
            self._safe_close()
            self._closed = True
            LOGGER.info("MongoDB client closed")

    def _safe_close(self) -> None:
        client = getattr(self, "client", None)
        if client is not None:
            try:
                client.close()
            except Exception:
                LOGGER.exception("MongoDB client cleanup failed")

    def _require_open(self) -> None:
        if self._closed:
            raise DatabaseConnectionError("The MongoDB client has already been closed.")

    @classmethod
    def _validate_create_document(
        cls, data: Mapping[str, Any]
    ) -> dict[str, Any]:
        if not isinstance(data, Mapping) or not data:
            raise ValidationError("create data must be a nonempty mapping.")

        document = dict(data)
        unknown = set(document) - cls.ALLOWED_FIELDS
        missing = cls.REQUIRED_CREATE_FIELDS - set(document)

        if unknown:
            raise ValidationError(
                f"Unsupported animal fields: {', '.join(sorted(unknown))}."
            )
        if missing:
            raise ValidationError(
                f"Missing required fields: {', '.join(sorted(missing))}."
            )
        if not str(document["animal_id"]).strip():
            raise ValidationError("animal_id cannot be blank.")
        if not str(document["animal_type"]).strip():
            raise ValidationError("animal_type cannot be blank.")

        document["animal_id"] = str(document["animal_id"]).strip().upper()
        document["animal_type"] = str(document["animal_type"]).strip().title()
        return document

    @classmethod
    def _validate_update_fields(
        cls, changes: Mapping[str, Any]
    ) -> dict[str, Any]:
        if not isinstance(changes, Mapping) or not changes:
            raise ValidationError("changes must be a nonempty mapping.")

        update_fields = dict(changes)
        if any(str(key).startswith("$") for key in update_fields):
            raise ValidationError(
                "MongoDB update operators are not accepted; provide plain field values."
            )

        unknown = set(update_fields) - cls.ALLOWED_FIELDS
        protected = set(update_fields) & cls.PROTECTED_UPDATE_FIELDS
        if unknown:
            raise ValidationError(
                f"Unsupported update fields: {', '.join(sorted(unknown))}."
            )
        if protected:
            raise ValidationError(
                f"Protected fields cannot be updated: {', '.join(sorted(protected))}."
            )
        return update_fields

    @staticmethod
    def _validate_query(
        query: Optional[Mapping[str, Any]], *, allow_empty: bool
    ) -> dict[str, Any]:
        if query is None:
            if allow_empty:
                return {}
            raise ValidationError("A nonempty query is required for this operation.")
        if not isinstance(query, Mapping):
            raise ValidationError("query must be a mapping.")
        if not query and not allow_empty:
            raise ValidationError(
                "An empty query is blocked to prevent a full-collection change."
            )
        return dict(query)
