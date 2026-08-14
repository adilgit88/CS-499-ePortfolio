# CS 499 Database Enhancement

## Artifact

This project enhances the CS 340 Grazioso Salvare `AnimalShelter` MongoDB CRUD class for the CS 499 database category.

## Improvements

- Removes database credentials from source code and loads them from environment variables.
- URL-encodes credentials before building the MongoDB connection string.
- Uses a short server-selection timeout and an immediate `ping` to detect connection or authentication problems early.
- Replaces `print()` error output with Python logging.
- Adds `close()`, `__enter__()`, and `__exit__()` for deterministic cleanup.
- Blocks empty update and delete filters.
- Accepts plain update fields and creates the MongoDB `$set` document internally.
- Rejects unsupported fields, protected identifier changes, and raw update operators.
- Returns inserted identifiers and separate matched/modified/deleted counts.
- Creates indexes for `animal_id`, `animal_type`, `breed`, `sex_upon_outcome`, and the common rescue-filter combination.
- Includes repeatable unit tests using an in-memory fake MongoDB client, so tests do not touch production data.

## Setup

1. Create and activate a Python virtual environment.
2. Install dependencies:

   ```bash
   pip install -r requirements.txt
   ```

3. Copy `.env.example` to `.env` and replace the example values. Export the variables into the shell before running the program. The `.env` file is excluded by `.gitignore`.

## Example

```python
from animal_shelter import AnimalShelter

with AnimalShelter() as shelter:
    result = shelter.create(
        {
            "animal_id": "A1001",
            "animal_type": "Dog",
            "breed": "Labrador Retriever Mix",
            "name": "Scout",
        }
    )
    print(result)
```

## Run Tests

From the `enhanced` folder:

```bash
pytest -q
```

The tests cover configuration validation, encoded credentials, connection verification, index creation, create/read/update/delete behavior, dangerous empty-filter protection, update-operator rejection, detailed operation results, health checks, and connection cleanup.

## Design Trade-Offs

The class validates a known set of animal fields to improve data quality. This is safer than accepting any document shape, but the allowed-field list must be updated when the application introduces a legitimate new field. The indexes improve common dashboard reads, but they also use storage and add a small cost to writes. For that reason, the enhancement creates a focused set of indexes that match the rescue dashboard's filter patterns rather than indexing every field.
