# Original Course Planner

This folder preserves the original C++ Course Planner before the later software engineering and algorithm enhancements. It uses a standard binary search tree to store and search course records.

The original implementation is included to show the starting point and the progression toward the modular BST baseline and the self-balancing AVL implementation.

## Build

From this folder, compile the original single-file application with a C++17 compiler:

```bash
g++ -std=c++17 ProjectTwo.cpp -o course_planner
```

## Run

```bash
./course_planner
```

On Windows, run `course_planner.exe` after compiling. Choose the load option and enter `Input.csv` when prompted. A sample `Input.csv` is included in this folder.

[View the modular BST baseline](../baseline-modular-bst/)

[View the enhanced AVL version](../enhanced-avl/)
