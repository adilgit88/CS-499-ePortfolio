# Original AnimalShelter Database Module

This folder preserves the original Python `AnimalShelter` MongoDB CRUD module created during my database programming coursework.

**Public portfolio safety note:** the original source contained hard-coded MongoDB credentials. The public copy redacts only the default username and password values. The program structure and CRUD logic are otherwise preserved for comparison with the enhanced artifact.

## Requirements for the original module

The original code requires Python, PyMongo, a reachable MongoDB server, and valid database credentials. Those credentials are intentionally not included in this public repository. To execute the original module, replace the redacted credential placeholders with credentials for a database you control and install PyMongo in your environment.

The enhanced version is the recommended implementation for review and testing because it removes credentials from source code and includes repeatable automated tests.

[View the enhanced database module](../enhanced/)
