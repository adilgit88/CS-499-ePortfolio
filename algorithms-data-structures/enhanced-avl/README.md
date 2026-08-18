# Enhanced Course Planner - AVL Tree

## Overview

This is the Algorithms and Data Structures enhancement of the Course Planner. It starts from the modular BST baseline and replaces the ordinary binary search tree with a self-balancing AVL tree.

## Algorithm enhancement

An ordinary binary search tree performs well when records arrive in a helpful order, but sorted input can turn it into a one-sided chain. In that case, insertion and search can degrade from O(log n) to O(n).

The enhanced `AVLTree` stores a height value in every node. After each insertion, it computes the node's balance factor and performs one of four rotation patterns when needed: left-left, right-right, left-right, or right-left. The ordering rule remains unchanged, so in-order traversal still returns the course catalog in alphanumeric order.

## Measurable evidence

- `height()` reports the current tree height.
- `isBalanced()` validates every AVL balance rule and stored height value.
- `rootCourse()` supports focused rotation tests.
- Automated tests cover all four rotations, duplicate handling, ordered traversal, CSV validation, clearing, and reload behavior.
- Sorted and reverse-sorted tests insert 1,000 courses and confirm that the AVL tree height remains at most 11.
- `performance_demo.cpp` compares sorted insertion into an unbalanced BST probe and the AVL implementation. The measured heights are 1,000 and 10, respectively.

## Complexity

| Operation | Ordinary BST worst case | AVL tree worst case |
|---|---:|---:|
| Insert | O(n) | O(log n) |
| Search | O(n) | O(log n) |
| In-order traversal | O(n) | O(n) |
| Stored height | Up to n | O(log n) |

The AVL design uses one integer height field per node and may perform rotations during insertion. This is a reasonable trade-off for predictable lookup performance.

## Build with CMake

```bash
cmake -S . -B build
cmake --build build
```

## Run the application

```bash
./build/course_planner
```

On Windows with a Visual Studio generator, executables may be inside `build/Debug`.

## Run automated tests

```bash
ctest --test-dir build --output-on-failure
```

## Run the comparison

```bash
./build/course_planner_comparison
```

## Direct g++ build

```bash
g++ -std=c++17 -Wall -Wextra -pedantic AVLTree.cpp CourseLoader.cpp main.cpp -o course_planner
g++ -std=c++17 -Wall -Wextra -pedantic -I. AVLTree.cpp CourseLoader.cpp tests/tests.cpp -o course_planner_tests
g++ -std=c++17 -Wall -Wextra -pedantic -I. AVLTree.cpp CourseLoader.cpp performance_demo.cpp -o course_planner_comparison
```
