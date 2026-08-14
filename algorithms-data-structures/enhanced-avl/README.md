# CS 499 Milestone Three - AVL Course Planner

## Artifact
This project is the algorithms and data structures enhancement of the CS 300 ABCU Course Planner. It starts from the modular Milestone Two version and replaces the ordinary binary search tree with a self-balancing AVL tree.

## Algorithm enhancement
An ordinary binary search tree performs well when records arrive in a helpful order, but sorted input can make it become a one-sided chain. In that case, insertion and search can degrade from O(log n) to O(n).

The enhanced `AVLTree` stores a height value in every node. After each insertion, it computes the node's balance factor and performs one of four rotation patterns when needed:

- Left-left: single right rotation
- Right-right: single left rotation
- Left-right: left rotation followed by right rotation
- Right-left: right rotation followed by left rotation

The tree keeps its ordering rule, so in-order traversal still returns the course catalog in alphanumeric order. Duplicate course numbers are still rejected.

## Added evidence
- `height()` reports the current tree height.
- `isBalanced()` validates every AVL balance rule and stored height value.
- `rootCourse()` supports focused rotation tests.
- Automated tests cover all four rotations, duplicate handling, ordered traversal, CSV validation, clearing, and reload behavior.
- Sorted and reverse-sorted tests insert 1,000 courses and confirm that the AVL tree height remains at most 11.
- `performance_demo.cpp` compares sorted insertion into an unbalanced BST probe and the AVL implementation. The expected heights are 1,000 and about 10, respectively.

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
