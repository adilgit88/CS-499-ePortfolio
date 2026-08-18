# Software Design and Engineering Narrative

**Adil Patel**  
Computer Science Capstone

## Artifact Description

The artifact I selected for this enhancement is the **ABCU Course Planner**, a C++ application I originally created in my Data Structures and Algorithms coursework.

The program was designed as a command-line advising tool for a fictional university. It reads course information from a CSV file, stores each course number, course name, and prerequisite list in a binary search tree, and allows a user to print the complete course catalog in alphanumeric order or search for an individual course and view its prerequisites.

The original application worked correctly and demonstrated my understanding of binary search trees, insertion, searching, and in-order traversal. However, when I reviewed the project later, I could see several areas where the software design could be improved.

Most of the application was contained in one large source file. Memory was managed with raw owning pointers. The program also reset its tree by manually calling a destructor and reconstructing the object with placement new. Error reporting was closely tied to console output, and the application did not include repeatable automated tests.

For this enhancement, I kept the original functionality while reorganizing the program into a more modular, maintainable, and testable application. My focus was not on adding unnecessary features. Instead, I concentrated on software structure, memory ownership, reusable interfaces, input handling, validation, and testing.

## Why I Selected This Artifact

I selected this artifact because it shows a clear difference between writing code that works and engineering software that is easier to maintain and extend.

When I first created the application, my main goal was to correctly implement the binary search tree and meet the functional requirements. That was appropriate for where I was in my development at the time.

Revisiting the same project later allowed me to evaluate it with a different set of priorities.

I began asking questions such as:

How easy would this code be for another developer to understand?

Could one part of the program be changed without affecting unrelated code?

Is memory ownership clear?

Can important behavior be tested automatically?

Could the loading logic be reused by another type of interface?

Those questions became the basis for the enhancement.

## Separation of Responsibilities

One of the largest improvements was separating the original single-file application into focused components.

The enhanced project includes a `Course.h` file for the course data model, separate header and source files for the binary search tree, separate files for CSV loading and validation, and a smaller `main.cpp` responsible primarily for user interaction.

The course model is simple enough that it only requires `Course.h`; there is no unnecessary `Course.cpp` file.

This structure gives each part of the application a clear responsibility.

The tree is responsible for storing and searching course records.

The loader is responsible for reading and validating external data.

The user interface is responsible for interacting with the user.

This makes the code easier to navigate and lowers the risk that a change in one area will unintentionally affect another.

It also makes the application easier for another developer to review because the purpose of each file is immediately clearer.

## Safer Memory Ownership

The original tree relied on raw owning pointers and manual cleanup.

For the enhanced version, I replaced those owning pointers with `std::unique_ptr`.

This was an important improvement because ownership is now expressed directly in the code. A node has a clear owner, and memory is released automatically when that ownership ends.

Using `std::unique_ptr` reduces the amount of manual memory management required and helps prevent problems such as memory leaks and incorrect cleanup.

This change also reflects a broader lesson I learned about modern C++ development. Memory management should not only work; it should be designed so that ownership is easy to understand.

## Improving Tree Reloading

The original program reset its binary search tree by manually calling the destructor and then using placement new to reconstruct the object.

Although the approach worked for the original assignment, it was more complicated than necessary and made the lifetime of the object harder to reason about.

I replaced this behavior with a dedicated `clear()` method.

The enhanced program can now remove the existing tree contents without manually destroying and recreating the entire object.

This is a relatively small change in terms of code size, but it significantly improves clarity and reduces the risk associated with manually controlling object lifetime.

## Structured Loading Results

The CSV-loading logic was also redesigned.

In the original version, the loader directly printed messages to the console when a file contained invalid data or other problems.

This tightly connected the loading logic to the command-line interface.

In the enhanced version, the loader returns a structured `LoadResult`.

This result can report whether the operation succeeded, how many records were loaded, how many were skipped, and what validation problems occurred.

The user interface can then decide how that information should be presented.

This makes the loader more reusable. The same loading logic could later support a graphical interface, web service, or another type of application without being rewritten simply because the method of displaying information changed.

It also improves testability because automated tests can directly inspect the returned values rather than trying to capture and interpret console output.

## Input Handling and Validation

I also improved several smaller areas that affect reliability.

The original program used standard `cin` input for the file path, which could cause problems when a path contained spaces.

The enhanced application uses `std::getline()` so the complete path can be read correctly.

I also removed the global `using namespace std`, improved const-correctness where appropriate, and strengthened validation for malformed CSV rows and invalid prerequisite references.

These are not large features, but together they make the application more predictable and easier to maintain.

## Automated Testing

The original artifact did not contain a repeatable automated test suite.

Most verification was performed manually by running the program and checking its output.

For the enhanced version, I added automated tests covering important behaviors such as course insertion, duplicate detection, sorted traversal, clearing the tree, valid CSV loading, malformed records, missing files, invalid prerequisites, and reload behavior.

Testing became more than a final check.

It influenced the way I designed the application.

For example, returning a structured `LoadResult` made the loading logic much easier to test than printing messages directly from inside the loader.

This helped me understand that testability is part of software design rather than something that should be added only after the implementation is finished.

## Professional Skills Demonstrated

This enhancement demonstrates several skills that are important in professional software development.

The modular structure improves maintainability and makes collaboration easier.

Modern C++ ownership reduces the risk associated with manual memory management.

Clear interfaces make components easier to reuse.

Validation improves reliability when working with external data.

Automated testing provides repeatable evidence that important functionality still behaves correctly after changes are made.

The enhancement also demonstrates restraint.

I considered adding several additional features, including a self-balancing tree during this stage. I decided not to combine every possible improvement into one enhancement.

Instead, I kept this work focused on software engineering and addressed the tree's algorithmic performance separately in my Algorithms and Data Structures enhancement.

That decision made the purpose of each enhancement easier to explain and evaluate.

## Course Outcome Alignment

This artifact provides strong evidence for the program outcome focused on using well-founded computing techniques and tools to create solutions that deliver practical value.

The modular architecture, `std::unique_ptr`, structured loading results, CMake configuration, and automated tests are all examples of established software engineering practices applied to improve an existing application.

The artifact also supports the security-focused outcome.

This is not my strongest security example, but replacing fragile manual memory ownership and improving validation reduces the opportunity for memory-related failures and unexpected behavior.

The design also supports the outcome related to evaluating computing solutions and trade-offs. I deliberately chose not to introduce the AVL tree during this enhancement because the purpose here was to improve software structure and engineering quality. The algorithmic limitation of the ordinary binary search tree was addressed separately and measured in the next enhancement.

Professional communication is demonstrated through clearer code organization, documentation, naming, testing information, and this narrative.

The work also supports collaboration because another developer can more easily understand individual components, make focused changes, and use the automated tests to verify that existing behavior has not been broken.

## Incorporating Feedback

The feedback I received on this enhancement reinforced the direction of the work.

My instructor noted that the code changes were strong and specifically commented on my decision to avoid over-engineering. The feedback also pointed out that testing often leads to better refactoring and better code.

That matched my experience during this enhancement.

Once I started thinking seriously about how the application would be tested, several design weaknesses became more obvious.

The loader became easier to test after it stopped printing directly to the console.

The modular structure made it easier to isolate behavior.

Clear ownership made the tree easier to reason about.

For the final version, I kept the enhancement focused rather than adding features simply to make the project look more complex.

## Reflection

The most important lesson I learned from this enhancement was that professional software development involves more than producing the correct output.

The original project worked.

It could load course information, store it in a binary search tree, print the catalog, and search for courses.

The enhancement did not change the main purpose of the application.

What changed was the quality of the internal design.

The enhanced version is easier to understand, safer to maintain, easier to test, and better prepared for future changes.

Working with `std::unique_ptr` also changed the way I think about ownership in C++. Instead of simply thinking about where a node exists in memory, I now think about which object owns it and when that ownership should end.

The structured loading result changed the way I think about interfaces. A function should provide useful information to its caller without deciding how that information must be displayed.

Automated testing changed the way I think about design. Code that is difficult to test is often giving a warning that its responsibilities are too tightly connected.

Overall, this enhancement represents an important shift in my development as a software engineer.

The original artifact shows that I could implement the required functionality.

The enhanced version shows that I now think more carefully about maintainability, ownership, testing, reuse, validation, and the needs of other developers who may work with the code later.

That growth is the main reason this artifact belongs in my professional ePortfolio.
