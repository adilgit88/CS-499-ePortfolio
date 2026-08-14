# CS 499 Artifact Narrative: Databases

**Adil Patel**  
Southern New Hampshire University  
CS 499: Computer Science Capstone  

**Artifact:** CS 340 Grazioso Salvare AnimalShelter MongoDB CRUD Module  
**Enhancement Focus:** Secure Configuration, Validation, Indexing, Lifecycle Management, Detailed Results, and Automated Testing  
**Enhancement Completed:** August 2026

## Artifact Description

The artifact I selected for my database enhancement is the `AnimalShelter` data-access class from my CS 340 Grazioso Salvare project. The application uses Python and MongoDB. The class connects to the `aac` database and `animals` collection and provides create, read, update, and delete operations.

The original artifact demonstrated basic MongoDB integration and included some useful checks, including blocking empty update and delete filters. However, it still reflected a classroom project. Credentials were embedded in the constructor, failures were printed to the console, the connection was not verified during initialization, there was no explicit cleanup method, indexes were not managed by the class, and result values often provided limited information.

For CS 499, I preserved the purpose of the artifact while redesigning the database layer around stronger configuration, validation, error handling, lifecycle management, indexing, security, and automated testing.

## Why I Selected This Artifact

I selected this artifact because the data layer protects one of an application's most important resources: its data. A user interface can look correct while the underlying database layer still contains serious weaknesses involving exposed credentials, poor validation, unsafe updates, weak error reporting, or inefficient queries.

One of the strongest improvements was removing hard-coded credentials. The enhanced class loads database settings from environment variables and fails clearly when required values are missing. Credentials are URL-encoded before building the MongoDB URI so special characters do not break the connection string.

The enhanced class also uses a short server-selection timeout and immediately performs a `ping`, allowing connection or authentication failures to appear during initialization rather than later during the first CRUD operation.

## Enhancement Comparison

| Area | Original Artifact | Enhanced Artifact |
|---|---|---|
| Credentials | Username/password in source | Environment variables and encoded URI values |
| Connection | No immediate verification | Timeout and ping during initialization |
| Errors | `print()` | Structured logging and controlled results |
| Lifecycle | No explicit cleanup | `close()`, `__enter__()`, and `__exit__()` |
| Data quality | Basic dictionary checks | Required/allowed fields, normalization, protected identifiers |
| Updates | Limited validation | Plain values only; raw operators and unsafe fields rejected |
| Results | Boolean or one count | Inserted ID, matched, modified, and deleted counts |
| Performance | No index plan | Focused single-field and compound indexes |
| Testing | No repeatable suite | 23 passing automated tests |

## Validation and Data Quality

MongoDB is intentionally flexible, but the application still benefits from clear boundaries. The enhanced class defines accepted fields, protects important identifiers, rejects blank identifiers and unknown fields, and keeps only a small set of fields required for a valid new animal record. Update callers provide normal values while the class builds the MongoDB update operation itself. Empty update and delete filters remain blocked.

## More Informative Results

The enhanced return values make database behavior easier for the calling application to understand. Updates return both `matched_count` and `modified_count`. This matters because a record can match a filter but remain unchanged when the new value is identical to the current value. Create operations return the inserted identifier, and delete operations return clear deletion information.

## Indexing and Performance

The enhanced class creates a unique index on `animal_id`, single-field indexes on commonly filtered fields such as `animal_type`, `breed`, and `sex_upon_outcome`, and a compound index that supports rescue-related filtering. I intentionally did not index every field because indexes consume storage and add work to inserts and updates.

## Lifecycle Management and Error Handling

The class now provides a `close()` method and Python context-manager support through `__enter__()` and `__exit__()`. Failures are handled through structured logging, with care taken not to intentionally include passwords or complete connection strings in logs.

## Automated Testing

To test the class without requiring a live MongoDB server or changing the course database, I allowed a client to be injected into the constructor. The test suite uses an isolated in-memory client that follows the small part of the PyMongo interface needed by the artifact. The tests cover configuration, connection behavior, indexes, CRUD operations, validation, duplicate handling, safety checks, health checks, logging, and cleanup. **All 23 tests pass.**

## Course Outcome Alignment

This enhancement strongly supports the fourth program outcome through environment-based configuration, typed result objects, MongoDB indexing, dependency injection, structured logging, validation, resource cleanup, and automated testing.

It also directly supports the fifth outcome. Removing hard-coded credentials reduces the chance of exposing database access through source control. Empty update and delete filters help prevent accidental mass changes. Raw update operators and protected identifier changes are restricted, and failure paths are tested instead of only successful requests.

The third outcome is supported through trade-off evaluation, including MongoDB flexibility versus application-level validation and faster indexed reads versus the storage and write costs of indexes. The second outcome is supported by documentation and clear result contracts. The first outcome is supported more fully across the portfolio, while clear interfaces and repeatable tests make this component easier for another developer to integrate.

## Reflection on the Enhancement Process

The main lesson from this enhancement was that database security begins before a query is executed. Configuration, connection strings, connection checks, logging, validation, results, indexes, and client cleanup all affect whether the database layer is reliable and safe.

I also learned that a simple return value can hide important states. Returning only `modified_count` made a successful match with no change look similar to a query that matched nothing. Separating matched and modified counts created a better contract.

A major design challenge was improving validation without making MongoDB behave like a rigid relational table. I selected a controlled field list while requiring only essential identifiers. The trade-off is that the allowed field list must be updated when the application introduces a legitimate new field.

Testing without a real database was another challenge. Dependency injection allowed me to use an isolated test client and verify class behavior safely. A larger production system could add integration tests against a temporary MongoDB instance, but the unit suite already gives fast evidence that the class rules work.

## Incorporating Instructor Feedback

My instructor gave this milestone full credit and said the narrative clearly explained the changes and development process. The instructor also noted that my original plan had included the possibility of adding a Users table, but that the final artifact did not implement it. Importantly, the narrative did not claim that it did. I kept that consistency in the final portfolio. The final scope focuses on the database improvements that were actually completed rather than adding a feature only because it appeared in an earlier plan.

## Overall Reflection

The original artifact demonstrated that I could connect Python to MongoDB and perform CRUD operations. The enhanced artifact demonstrates a broader understanding of how a database layer fits into a complete software system: protect configuration, validate boundaries, make failure visible, manage resources, plan query performance, return useful information, and provide repeatable evidence through tests.
