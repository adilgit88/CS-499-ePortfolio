# CS 499 Artifact Narrative: Algorithms and Data Structures

**Adil Patel**  
Southern New Hampshire University  
CS 499: Computer Science Capstone  

**Artifact:** CS 300 ABCU Course Planner  
**Original Data Structure:** Binary Search Tree  
**Enhanced Data Structure:** Self-Balancing AVL Tree  
**Enhancement Focus:** Algorithmic Efficiency, Worst-Case Performance, Testing, and Design Trade-Offs  
**Enhancement Completed:** July 2026

## Artifact Description

The artifact I selected for my Algorithms and Data Structures enhancement is the ABCU Course Planner that I originally created in CS 300. The application is written in C++ and reads a university course catalog from a CSV file. Each course contains a course number, course name, and prerequisite list. The program allows a user to load the catalog, print courses in alphanumeric order, search for an individual course, and view its prerequisites.

Before this enhancement, I had already improved the artifact for Software Design and Engineering by separating the program into focused components, replacing raw owning pointers with `std::unique_ptr`, improving input handling, and adding tests. For this enhancement, I preserved those improvements while changing the central data structure from an ordinary binary search tree to a self-balancing AVL tree.

## Why I Selected This Artifact

I selected this artifact because it provides a clear example of how a data-structure decision affects performance. The original BST can perform well when its shape is reasonably balanced, but it does not control that shape. If course numbers arrive in sorted order, the tree can become a long one-sided chain and search or insertion can degrade to O(n).

The AVL tree addresses that weakness by maintaining a height difference of no more than one between the left and right subtrees. Each node stores its height. After insertion, the algorithm updates heights, calculates the balance factor, and performs one of four rotation cases when needed: left-left, right-right, left-right, or right-left.

The enhanced implementation also uses `std::unique_ptr`, so rotations required careful movement of node ownership while preserving the binary-search ordering rule.

## Multiple Data Structures

The program also retains an `unordered_set` during CSV validation. The AVL tree is used for ordered storage and predictable search, while the `unordered_set` provides fast average membership checks when validating prerequisite course numbers. Using each structure for the job it handles well is better than forcing one structure to solve every requirement.

## Performance Improvement

| Area | Milestone Two BST | Milestone Three AVL |
|---|---|---|
| Tree shape | Depends on insertion order | Automatically rebalanced |
| Worst-case search | O(n) | O(log n) |
| Worst-case insertion | O(n) | O(log n) |
| Node information | Course and child pointers | Course, child pointers, and height |
| Balance control | None | AVL rotations |
| Diagnostics | Size and empty checks | Size, height, root, and balance validation |

There is a trade-off. The AVL tree stores one additional height value per node and may perform rotations during insertion. The implementation is also more complex. I accepted that cost because the course planner is mainly used for loading, ordering, and repeated searching. Predictable O(log n) behavior is more valuable for this use case.

## Testing and Measurable Evidence

I added focused tests for all four rotation patterns using short insertion sequences. I also created stress tests with 1,000 sorted records and 1,000 reverse-sorted records. These patterns are important because they represent the worst situation for the ordinary BST.

A direct comparison program inserts 1,000 sorted keys into both an unbalanced BST probe and the AVL implementation. The measured results were:

- Unbalanced BST height: **1,000**
- AVL tree height: **10**
- AVL balance validation: **passed**

This makes the benefit of the enhancement measurable rather than purely theoretical. I also retained earlier tests for duplicate detection, sorted traversal, CSV validation, missing files, invalid prerequisites, and reload behavior so the algorithm change would not break existing features.

## Course Outcome Alignment

This enhancement most directly supports the third program outcome. I identified a worst-case weakness, selected an AVL tree to address it, implemented the balancing rules, preserved ordering behavior, and tested correctness and tree height. The work demonstrates algorithm analysis and management of trade-offs.

It also strongly supports the fourth outcome through modern C++ ownership, recursive algorithms, CMake, automated tests, strict compiler warnings, sanitizer checks, and a dedicated performance comparison executable.

The second outcome is supported by documentation that explains the AVL algorithm, rotation cases, complexity differences, build process, testing process, and design trade-offs. The fifth outcome is supported more indirectly through safe memory ownership and controlled input handling. Collaboration is demonstrated more fully across the complete ePortfolio, but clear documentation, tests, and observable tree metrics make this artifact easier for another developer to understand.

## Reflection on the Enhancement Process

The biggest lesson was that a data structure can return correct results and still be a weak choice under certain conditions. The earlier BST produced correct output, but complexity analysis showed that its performance depended too heavily on input order.

The most difficult technical challenge was implementing AVL rotations while using `std::unique_ptr`. A rotation changes ownership relationships among several nodes, so I had to move nodes and saved subtrees carefully rather than copying raw-pointer examples.

Updating node heights in the correct order was another challenge. To verify the structure more deeply, I added `isBalanced()`, which recursively calculates actual subtree heights and checks that stored height values and balance factors are correct.

I also learned that performance testing should target the risk being discussed. Random insertion might make both trees look acceptable, so sorted insertion was the meaningful comparison. The difference between height 1,000 and height 10 showed exactly why the AVL enhancement matters.

I deliberately did not add AVL deletion because the application's actual requirements do not include interactive course deletion. Adding it would increase complexity and testing burden without solving a real use case.

## Incorporating Instructor Feedback

My instructor specifically praised the test design and noted that software quality includes more than passing functional tests. Performance, observability, maintainability, and other qualities also matter. That feedback reinforced the value of the performance comparison, tree metrics, balance validation, modular design, and automated tests.

## Overall Reflection

This enhancement changed how I evaluate algorithms. I now look beyond whether a data structure works and consider how it behaves under different inputs, what guarantees it provides, what implementation costs it introduces, and whether those trade-offs fit the application. The course planner still looks familiar to the user, but internally it now has a tested and measurable performance guarantee.
