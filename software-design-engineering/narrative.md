# CS 499 Artifact Narrative: Software Design and Engineering

**Adil Patel**  
Southern New Hampshire University  
CS 499: Computer Science Capstone  

**Artifact:** CS 300 ABCU Course Planner  
**Original Artifact:** C++ Course Planner Using a Binary Search Tree  
**Enhancement Focus:** Software Design, Modularity, Memory Safety, Error Handling, and Testing  
**Enhancement Completed:** July 2026

## Artifact Description

The artifact I selected for this enhancement is the ABCU Course Planner that I originally created in CS 300, Data Structures and Algorithms. The program was developed as a command-line advising tool for a fictional university. It reads course information from a CSV file, stores course numbers, course names, and prerequisite information in a binary search tree, and allows the user to print the complete course list in alphanumeric order or search for an individual course and view its prerequisites.

The original artifact successfully demonstrated the fundamental concepts I was learning in CS 300, including binary search tree construction, insertion, search, and in-order traversal. However, it also reflected my level of experience at the time. The complete program was contained in one large source file, memory was managed with raw pointers, program components were tightly coupled, input handling was limited, and the program reset its tree by manually calling a destructor and reconstructing the object with placement new.

For my CS 499 software design and engineering enhancement, I preserved the original functionality while reorganizing the program into a more modular, maintainable, and testable application. The enhancement focused on software structure, memory ownership, input validation, error handling, reusable interfaces, and automated testing rather than adding unnecessary features.

## Justification for Inclusion

I selected this artifact because it clearly demonstrates growth in my approach to software development. The original program worked and met the requirements of CS 300, but the enhanced version reflects what I have learned about designing software that other developers could realistically understand, maintain, test, and extend.

One of the most important improvements was separating responsibilities that had previously existed in one source file. The enhanced application is divided into focused components: `Course.h` defines the data model, `BinarySearchTree.h/.cpp` manage the tree, `CourseLoader.h/.cpp` handle CSV parsing and validation, `main.cpp` manages the console interface, and automated tests verify important behaviors. This separation makes each responsibility easier to understand and reduces unnecessary coupling.

I also replaced raw owning pointers with `std::unique_ptr`. This applies RAII-based ownership and reduces the risk of memory leaks, dangling pointers, and incorrect cleanup. The unsafe destructor-and-placement-new reload pattern from the original version was replaced with a dedicated `clear()` method.

The CSV-loading process was redesigned so it returns a structured `LoadResult` instead of printing directly from deep inside the loading logic. The result includes success information, loaded and skipped record counts, and validation messages. This improves reuse and makes the component easier to test.

Input handling was improved with `std::getline()` so file paths containing spaces can be read correctly. The global `using namespace std` statement was removed, methods were made const-correct where appropriate, and malformed CSV records and invalid prerequisite references are detected rather than silently accepted.

Finally, I added automated tests for insertion, duplicate detection, sorted traversal, safe clearing, valid CSV loading, malformed rows, missing files, invalid prerequisites, and reload behavior. The original artifact relied mainly on manual testing. The enhanced artifact provides repeatable evidence that its major behaviors continue to work after refactoring.

## Course Outcome Alignment

This enhancement most strongly supports the fourth program outcome by applying well-founded computing practices to improve a real solution. Modular architecture, `std::unique_ptr`, RAII, structured result objects, CMake, and automated tests make the application safer and easier to maintain.

The enhancement also supports the fifth outcome through safer memory ownership and stronger input validation. I do not consider this artifact my strongest cybersecurity example, but removing fragile memory-management patterns and validating external input are part of a security mindset.

The third outcome is supported through design trade-offs. I considered implementing a self-balancing tree during this milestone but intentionally kept the algorithm unchanged so this enhancement could remain focused on software engineering. The tree's algorithmic weakness was then addressed directly in the Algorithms and Data Structures enhancement.

The second outcome is supported by clearer interfaces, documentation, naming, build instructions, and test results. The first outcome is supported more indirectly because modular code, documentation, and repeatable tests make collaboration easier for other developers.

## Reflection on the Enhancement Process

The most important lesson I learned was how much good C++ engineering depends on understanding ownership. When I created the original artifact, I focused mainly on whether insert, search, and traversal worked. Rewriting the tree with `std::unique_ptr` forced me to think about which object owns each node and when that ownership should end.

I also learned the value of returning structured information instead of printing results directly from application logic. At first, creating a `LoadResult` structure seemed more complicated than printing warnings. Once I began writing automated tests, the advantage became clear because tests could verify exact values instead of trying to capture console output.

Another challenge was deciding how much to change. I considered a self-balancing tree, expanded logging, and other additions, but those changes would have distracted from the software engineering goals. Keeping the scope focused allowed me to make a smaller set of improvements and support each one with a clear reason.

## Incorporating Instructor Feedback

My instructor said the code changes were strong and specifically commented positively on avoiding over-engineering. The instructor also noted that testing often leads to better refactoring and better code. That feedback reinforced what I experienced during the enhancement: testing did more than verify the program. It influenced how I designed the loader, structured result objects, and separated responsibilities.

For the final ePortfolio, I kept the enhancement focused instead of adding extra features only to make the project appear more complex.

## Overall Reflection

The original artifact shows that I could implement a binary search tree and satisfy functional requirements. The enhanced artifact shows that I now consider how software is structured, how resources are owned, how input is validated, how components can be reused, and how behavior can be verified through automated testing. The user-facing functionality remains familiar, but the internal design is significantly stronger and better suited for professional review.
