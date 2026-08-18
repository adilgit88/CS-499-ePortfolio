# Modular BST Baseline

## Overview

This folder contains the modular binary-search-tree version of the Course Planner used as the baseline for the Algorithms and Data Structures enhancement. It already includes the software-engineering improvements such as separated responsibilities, `std::unique_ptr` ownership, structured loading results, and automated tests.

The algorithm enhancement replaces this ordinary binary search tree with a self-balancing AVL tree so performance no longer depends heavily on insertion order.

## Build

```bash
cmake -S . -B build
cmake --build build
```

## Run

```bash
./build/course_planner
```

On Windows with Visual Studio generators, the executable may be inside `build/Debug`.

## Test

```bash
ctest --test-dir build --output-on-failure
```

[View the enhanced AVL version](../enhanced-avl/)
