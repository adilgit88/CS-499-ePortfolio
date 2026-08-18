# Algorithms and Data Structures Narrative

**Adil Patel**  
Computer Science Capstone

## Artifact Description

The artifact I selected for this enhancement is the **ABCU Course Planner**, a C++ application I originally developed in my Data Structures and Algorithms coursework.

The application reads a course catalog from a CSV file and stores information such as the course number, course name, and prerequisites. A user can load the catalog, display all courses in alphanumeric order, search for a specific course, and view its prerequisite information.

Before beginning this enhancement, I had already improved the software design of the application by separating responsibilities into smaller components, replacing raw owning pointers with `std::unique_ptr`, improving input validation, and adding automated tests.

For this enhancement, I focused specifically on the program's main data structure.

The earlier version used a standard binary search tree. Although the tree produced correct results, its performance depended heavily on the order in which course records were inserted.

I replaced the ordinary binary search tree with a **self-balancing AVL tree** to provide more predictable search and insertion performance.

## Why I Selected This Artifact

I selected this artifact because it demonstrates an important difference between a program that is functionally correct and one that is designed to perform reliably under different conditions.

The original binary search tree correctly stored and searched course records.

The problem was its shape.

A normal binary search tree does not automatically keep itself balanced. If values are inserted in a favorable order, the tree may remain reasonably balanced and provide good performance.

However, if course numbers are inserted in sorted or nearly sorted order, each new node can be added to the same side of the tree.

The tree can then become a long chain rather than a balanced structure.

In this worst-case situation, insertion and search can degrade to **O(n)** performance.

This means that as the amount of data grows, the program may need to examine many or even all nodes to find a record.

The application may still return the correct answer, but its performance becomes dependent on the order of the input data.

That weakness made the project a strong choice for demonstrating growth in algorithm analysis and data-structure selection.

## AVL Tree Enhancement

To address the weakness of the original structure, I implemented an AVL tree.

An AVL tree is a binary search tree that automatically maintains its balance.

Each node stores its current height.

After a successful insertion, the tree updates the height of the affected nodes and calculates a balance factor based on the difference between the left and right subtree heights.

A balanced AVL node has a balance factor between negative one and positive one.

When that range is exceeded, the tree performs rotations to restore balance.

I implemented all four AVL rotation cases:

Left-left, right-right, left-right, and right-left.

The rotations change the structure of the tree while preserving the binary-search ordering rule.

Smaller course numbers remain on the left side of a node, and larger course numbers remain on the right.

The difference is that the tree actively prevents one side from becoming significantly taller than the other.

## Working With Modern C++ Ownership

One of the more challenging parts of this enhancement was implementing rotations while continuing to use `std::unique_ptr`.

Many basic AVL examples use raw pointers.

My implementation required moving ownership of nodes and subtrees safely during each rotation.

For example, during a right rotation, the left child becomes the new root of that section of the tree.

The previous root must move below it, and the subtree between them must be preserved and reattached correctly.

Using `std::unique_ptr` meant I could not simply copy pointer relationships.

I had to think carefully about which object owned each node before and after the rotation.

This made the implementation more challenging, but it also gave me a stronger understanding of what each rotation is actually doing.

## Maintaining Tree Heights

Correct height management was another important part of the implementation.

After inserting a node or performing a rotation, the program must update heights in the correct order.

The lower node must be updated before the new root because the new root's height depends on the corrected height of its children.

A tree can appear visually balanced while still storing incorrect height information.

To detect this type of problem, I added an `isBalanced()` function.

This function recursively evaluates the actual height of each subtree, checks the difference between the left and right sides, and verifies that the stored node heights match the calculated values.

This provides stronger validation than simply checking whether the root appears correct.

## Using the Right Structure for the Right Task

The enhanced application does not rely on one data structure for every operation.

The AVL tree is used for ordered storage, searching, and alphanumeric traversal.

The CSV-loading process also uses an `unordered_set` to quickly verify whether prerequisite course numbers exist.

This was an important design decision.

The AVL tree provides predictable search performance while maintaining sorted data.

The `unordered_set` provides fast average-case membership checks.

Using both structures demonstrates that choosing a data structure is not about selecting one structure and forcing it to handle every requirement.

Different structures are useful for different operations.

A professional solution should use each structure where it provides the most value.

## Performance Comparison

The strongest evidence for this enhancement comes from testing the AVL tree under the same conditions that create problems for the original binary search tree.

I created a performance comparison using **1,000 sorted values**.

Sorted input represents a worst-case situation for an ordinary binary search tree because each new node can be placed on the same side.

With 1,000 sorted values, the unbalanced binary search tree reached a height of:

**1,000**

The AVL tree using the same values reached a height of:

**10**

The AVL balance validation also passed.

This difference demonstrates why the enhancement matters.

The ordinary tree becomes a one-sided structure whose height grows directly with the number of records.

The AVL tree remains compact because it continuously rebalances itself.

The result turns the algorithm discussion into measurable evidence instead of relying only on theory.

## Complexity and Trade-Offs

The enhancement improves worst-case search and insertion from **O(n)** in the ordinary binary search tree to **O(log n)** in the AVL tree.

However, this improvement is not free.

Each AVL node stores an additional height value.

Insertion requires balance calculations.

Some insertions also require one or more rotations.

The implementation is more complex than a standard binary search tree.

For this application, I consider that trade-off worthwhile.

The Course Planner loads a catalog and then performs searches against that data. Predictable search performance is more valuable than the small memory savings and simpler implementation of an unbalanced tree.

This experience reinforced an important lesson about algorithm design.

The most advanced or complicated structure is not automatically the best choice.

The correct choice depends on the needs of the application and the trade-offs involved.

## Automated Testing

Testing was an important part of verifying the enhancement.

I created focused tests for all four AVL rotation patterns.

The test sequences were selected specifically to trigger the different cases and confirm that the tree rebalanced correctly.

I also tested large sorted and reverse-sorted datasets.

These tests are more meaningful than random input because they intentionally create conditions that expose the weakness of the original binary search tree.

In addition to the new AVL tests, I kept the earlier tests for duplicate detection, sorted traversal, CSV validation, missing files, invalid prerequisites, and reload behavior.

Maintaining these tests was important because improving the data structure should not break existing functionality.

The enhanced program should still behave correctly from the user's point of view even though the internal structure has changed significantly.

## Observability and Maintainability

Another improvement was making the internal state of the tree easier to evaluate.

The enhanced application can report information such as the number of nodes, tree height, root value, and balance status.

These details improve observability.

Instead of only checking whether the program prints the expected course, I can inspect important properties of the structure itself.

This is valuable during development and testing because an algorithm may appear to work while still violating an internal rule.

Clear diagnostics, automated tests, and modular code also make the implementation easier for another developer to understand and maintain.

## Design Decisions

One design decision I made was not to implement AVL deletion.

The Course Planner is designed primarily to load a course catalog, display course information, and search for records.

Interactive deletion is not part of the application's current requirements.

Adding AVL deletion would have increased the size and complexity of the implementation and would have required additional testing without solving a real problem for the current application.

I chose to focus on insertion, search, traversal, and balance because those operations directly support the intended use of the software.

This decision reflects an important professional lesson: adding more features does not automatically create a better solution.

The goal should be to solve the actual problem completely and clearly.

## Professional Skills Demonstrated

This enhancement demonstrates my ability to analyze an existing computing solution rather than simply rewrite it.

I identified a specific performance weakness.

I evaluated why that weakness could occur.

I selected an appropriate data structure to address it.

I implemented the balancing algorithm.

I created tests for both correctness and structural behavior.

I measured the difference between the original and enhanced solutions.

I also evaluated the cost of the enhancement rather than presenting the AVL tree as automatically better in every situation.

These are skills that apply beyond this particular project.

Professional software development requires understanding not only how an algorithm works, but also why it is appropriate for a particular problem.

## Course Outcome Alignment

This enhancement strongly supports the program outcome focused on designing and evaluating computing solutions using algorithmic principles while managing design trade-offs.

I did not simply replace one tree with another.

I identified a worst-case performance weakness, selected a self-balancing structure, implemented the required rotations, verified structural invariants, and measured the resulting improvement.

The work also supports the outcome focused on using well-founded computing techniques and tools.

The project uses modern C++ ownership, recursive algorithms, CMake, automated testing, strict compiler practices, and performance comparison tools to create a solution that can be verified and maintained.

Professional communication is demonstrated through documentation, readable interfaces, test results, and the explanation of the algorithm and its trade-offs.

The artifact also supports collaboration because another developer can examine the tree metrics, tests, and documentation to understand both how the implementation works and why the design was selected.

Security is not the main focus of this artifact, but safe memory ownership, controlled input handling, and testing help reduce the risk of unstable or unexpected behavior.

## Incorporating Feedback

The feedback I received on this enhancement emphasized that successful software involves more than passing functional tests.

Performance, observability, maintainability, and other software-quality characteristics also matter.

That feedback reinforced the reason I included more than basic correctness testing.

The performance comparison demonstrates how the data structure behaves under a difficult input pattern.

The tree-height and balance functions improve observability.

The modular structure and automated tests improve maintainability.

For the final portfolio, I kept these elements because they show that the enhancement is not simply an AVL tree implementation.

It is an evaluation of how a data-structure choice affects the overall quality of a software solution.

## Reflection

The biggest lesson I learned from this enhancement is that correct output does not necessarily mean that the underlying solution is strong.

The original binary search tree worked.

It passed its basic tests.

It could load course information and return the correct records.

If I had only looked at the final output, there would have been little reason to change it.

Algorithm analysis revealed the weakness.

The performance of the tree could change dramatically depending on the order of the input.

That helped me understand the difference between asking:

Does the program work?

and asking:

How will the program behave when the input changes or grows?

Both questions are important.

Implementing rotations with `std::unique_ptr` also strengthened my understanding of data structures.

I had to think about tree balance, node height, ownership, and ordering at the same time.

Testing sorted input showed me why test data should be chosen intentionally.

Random input might make the original tree appear acceptable.

Sorted input directly exposes the problem I was trying to solve.

Overall, this enhancement represents growth in the way I evaluate algorithms.

I now think more carefully about worst-case behavior, scalability, structural guarantees, implementation complexity, testing, and the needs of the application.

The enhanced Course Planner still provides the same familiar functionality to the user.

Internally, however, it now uses a data structure whose performance is predictable, measurable, and supported by automated evidence.

That is why this artifact is an important part of my professional ePortfolio.
