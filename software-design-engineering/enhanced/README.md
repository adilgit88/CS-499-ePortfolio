# Enhanced Course Planner - Software Design and Engineering

## Overview

This C++ Course Planner is the software design and engineering enhancement of the original single-file application. The user-facing functionality remains familiar while the internal design is more modular, maintainable, testable, and explicit about memory ownership.

## Main improvements

- Split the original single-file program into focused model, tree, loader, user-interface, and test files.
- Replaced raw owning pointers with `std::unique_ptr` for automatic memory management.
- Added a safe `clear()` operation instead of manually calling the destructor and placement `new`.
- Changed traversal to return an ordered `std::vector<Course>` instead of printing from the tree class.
- Changed CSV loading to return a structured `LoadResult` with counts and messages.
- Added full-line path input with `std::getline`, including support for spaces.
- Removed global `using namespace std` and strengthened const-correctness.
- Added duplicate reporting, malformed-row handling, missing-file handling, reload testing, and unit-style assertions.

## Build with CMake

```bash
cmake -S . -B build
cmake --build build
```

## Run the program

```bash
./build/course_planner
```

On Windows with Visual Studio generators, the executable may be inside `build/Debug`.

## Run tests

```bash
ctest --test-dir build --output-on-failure
```

## Direct g++ build

```bash
g++ -std=c++17 -Wall -Wextra -pedantic BinarySearchTree.cpp CourseLoader.cpp main.cpp -o course_planner
g++ -std=c++17 -Wall -Wextra -pedantic -I. BinarySearchTree.cpp CourseLoader.cpp tests/tests.cpp -o course_planner_tests
./course_planner_tests
```
