# Original Course Planner

This folder preserves the original C++ Course Planner created during my Data Structures and Algorithms coursework. The application reads course data from a CSV file, stores the records in a binary search tree, and allows the user to display the catalog or search for an individual course and its prerequisites.

The source is preserved as the comparison point for the Software Design and Engineering enhancement. The enhanced version improves modularity, memory ownership, validation, interfaces, and automated testing.

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

[View the enhanced version](../enhanced/)
