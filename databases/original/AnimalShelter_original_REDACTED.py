from pymongo import MongoClient
from pymongo.errors import PyMongoError


class AnimalShelter:
    """CRUD operations for the animals collection in MongoDB."""

    def __init__(
        self,
        user="REDACTED_USERNAME",
        password="REDACTED_PASSWORD",
        host="localhost",
        port=27017,
        db_name="aac",
        collection_name="animals",
        auth_source="admin",
    ):
        uri = f"mongodb://{user}:{password}@{host}:{port}/{db_name}?authSource={auth_source}"
        self.client = MongoClient(uri)
        self.database = self.client[db_name]
        self.collection = self.database[collection_name]

    def create(self, data):
        if not isinstance(data, dict) or not data:
            return False
        try:
            result = self.collection.insert_one(data)
            return result.acknowledged
        except PyMongoError as e:
            print("Create error:", e)
            return False

    def read(self, query, projection=None):
        if query is None or not isinstance(query, dict):
            return []
        try:
            return list(self.collection.find(query, projection))
        except PyMongoError as e:
            print("Read error:", e)
            return []

    def update(self, query, new_values, many=False):
        if not isinstance(query, dict) or not query:
            return 0
        if not isinstance(new_values, dict) or not new_values:
            return 0
        try:
            update_values = {"$set": new_values}
            if many:
                result = self.collection.update_many(query, update_values)
            else:
                result = self.collection.update_one(query, update_values)
            return result.modified_count
        except PyMongoError as e:
            print("Update error:", e)
            return 0

    def delete(self, query, many=False):
        if not isinstance(query, dict) or not query:
            return 0
        try:
            if many:
                result = self.collection.delete_many(query)
            else:
                result = self.collection.delete_one(query)
            return result.deleted_count
        except PyMongoError as e:
            print("Delete error:", e)
            return 0
