# CS 499 Code Review Video Script

**Adil Patel**  
**CS 499: Computer Science Capstone**

## Opening

Hello everyone.

My name is Adil Patel, and this is my CS 499 code review.

In this video, I will review the artifacts I selected for my Computer Science capstone.

I selected two main projects.

The first project is my **ABCU Course Planner** from CS 300. I will use this project for two enhancement areas: **Software Design and Engineering**, and **Algorithms and Data Structures**.

My second project is the **Grazioso Salvare AnimalShelter database module** from CS 340. I will use this project for my **Database enhancement**.

During this review, I will first explain what the original programs do. Then I will look at areas that can be improved. After that, I will explain the enhancements I plan to make and how they connect to the five Computer Science program outcomes.

My main goal is not to completely replace these projects. Both projects already work. My goal is to take working student projects and improve them using the skills I developed throughout the Computer Science program.

## Part One: ABCU Course Planner

**[Open the original ProjectTwo.cpp file.]**

The first artifact is the ABCU Course Planner. I originally created this program in CS 300, Data Structures and Algorithms. It is written in C++.

The program reads course information from a CSV file. Each course has a course number, a course name, and possibly one or more prerequisites. The program stores this information in a binary search tree.

The user can load the course data, print all courses in alphanumeric order, or search for one course and see its prerequisites. From a functional point of view, the program does what it was designed to do.

### Software Design Problem: One Large File

**[Scroll through ProjectTwo.cpp.]**

The first issue is that almost everything is inside one large C++ file. The course model, tree, CSV loading, menu, validation, and main program are all together.

For my software engineering enhancement, I plan to separate these responsibilities. I will create separate files for the course model, binary search tree, CSV loading, and user interface. This will make the code easier to understand and test.

### Memory Management

**[Show the Node structure.]**

The original tree uses raw pointers. Nodes are created and deleted manually. This can create memory leaks or invalid pointer problems if cleanup is not handled correctly.

For the enhanced version, I plan to use `std::unique_ptr`. A unique pointer clearly defines ownership and automatically cleans up memory when the owning object is destroyed.

### Reloading the Tree

**[Show the tree reset code.]**

The original program manually calls the destructor and uses placement new to rebuild the tree. This is more complicated than necessary.

I plan to replace this with a normal `clear()` method. If I want to clear the tree, I should simply call `clear()`.

### CSV Loading and Error Messages

**[Show the CSV loading code.]**

The loading logic prints messages directly to the console. This connects the loader too closely with the user interface.

I plan to return a structured result instead. The result can include whether loading succeeded, how many records were loaded or skipped, and any validation messages. This also makes automated testing easier.

### User Input

The original program uses normal `cin` input for the file path. That can fail when a path contains spaces. I plan to use `getline` so the full path can be read correctly.

### Testing

The original project does not have a repeatable automated test suite. I plan to add tests for insertion, duplicate course numbers, sorted traversal, safe clearing, valid CSV loading, malformed rows, missing files, invalid prerequisites, and reloading data.

## Algorithms and Data Structures Review

Now I want to look at the same course planner from an algorithms and data structures point of view.

The original program uses a normal binary search tree. The tree works correctly, but its shape depends on insertion order.

If course numbers are inserted in sorted order, the tree can become one long chain. Search and insertion can then become O of n in the worst case.

For my algorithms enhancement, I plan to replace the normal BST with an **AVL tree**.

An AVL tree keeps itself balanced. Each node stores its height. After insertion, the program checks the balance factor and performs rotations when needed.

There are four main cases: left-left, right-right, left-right, and right-left.

The main reason for choosing AVL is predictable performance. The original BST can become O of n. A balanced AVL tree keeps search and insertion at O of log n.

There is a trade-off. The AVL tree stores extra height information and the code becomes more complex because of rotations. I think this is a good trade-off for a course planner that loads data and searches it repeatedly.

I also plan to test all four rotation cases and compare sorted and reverse-sorted input. I want to compare the height of an unbalanced tree with the AVL tree so the improvement is measurable.

## Part Two: Grazioso Salvare AnimalShelter

**[Open the original AnimalShelter Python file.]**

My second artifact comes from CS 340. It is the AnimalShelter data-access class from the Grazioso Salvare project. It uses Python and MongoDB and provides create, read, update, and delete operations.

### Hard-Coded Credentials

**[Show the constructor.]**

The biggest security problem is that the database username and password are stored directly in the source code. If the code is shared or uploaded to GitHub, those credentials can be exposed.

For my enhancement, I plan to move credentials into environment variables. I will provide an example configuration file without real secrets.

### Connection Handling

The original class creates a MongoDB client but does not immediately verify the connection. I plan to add a short timeout and perform a ping when the class starts so connection problems fail early.

### Error Handling

The original version uses `print()` when database errors occur. I plan to use structured logging instead and make sure passwords and complete connection strings are not written to logs.

### Resource Cleanup

The original class does not have a clear way to close the MongoDB client. I plan to add a `close()` method and support Python context management with `__enter__` and `__exit__`.

### Validation and Safety

The original class already blocks empty update and delete filters, and I want to keep that protection. I also plan to define allowed fields, require important values, reject blank identifiers, protect fields that should not change, and prevent outside code from sending raw MongoDB update operators directly.

### Better Return Values

The original CRUD methods often return a Boolean or one count. I plan to return more useful information. Updates will return matched and modified counts. Create operations will return the inserted ID. Delete operations will return clear deletion information.

### Indexes

The original class does not define an indexing strategy. I plan to add focused indexes for important fields such as animal ID and fields used often for filtering. I will not index every field because indexes use storage and add work to writes.

### Database Testing

I plan to make the database client injectable so tests can use an isolated client instead of changing a real database. I want tests for connection behavior, indexes, CRUD operations, validation, duplicate handling, safety checks, logging, and cleanup.

## Course Outcomes

The first outcome focuses on collaboration. Modular code, documentation, and automated tests make these projects easier for another developer to understand and change. The code review itself also supports collaboration because I am explaining my decisions to a technical audience.

The second outcome focuses on communication. This video is oral communication. My narratives provide written communication. README files and the final GitHub Pages ePortfolio provide technical and visual communication.

The third outcome focuses on algorithms and design trade-offs. The strongest example is changing the normal BST into an AVL tree and comparing O of n worst-case behavior with O of log n balanced behavior.

The fourth outcome focuses on well-founded computing techniques and tools. Across the enhancements I plan to use modern C++ ownership, modular design, CMake, automated tests, MongoDB indexing, environment configuration, structured logging, dependency injection, and resource management.

The fifth outcome focuses on security. The C++ enhancement improves memory safety and input handling. The database enhancement removes hard-coded credentials, keeps safety checks around destructive operations, protects fields, restricts raw update operators, and avoids exposing sensitive connection information in logs.

## Final Summary

To summarize, the original artifacts are functional, but they contain areas that can be improved.

For Software Design and Engineering, I plan to improve the structure of the ABCU Course Planner, memory ownership, input handling, result handling, and testing.

For Algorithms and Data Structures, I plan to replace the unbalanced BST with a self-balancing AVL tree to provide predictable performance.

For Databases, I plan to improve the AnimalShelter MongoDB class through secure configuration, validation, indexes, better error handling, better results, connection management, and automated testing.

The main lesson I have learned is that working software is only the starting point. Professional software also needs to be understandable, maintainable, tested, efficient, and secure.

Thank you for watching my code review.
