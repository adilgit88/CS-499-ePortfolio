# Professional Self-Assessment

**Adil Patel**  
Southern New Hampshire University  
CS 499: Computer Science Capstone

## Introduction

Completing the Computer Science program at Southern New Hampshire University changed the way I approach technology and problem solving. When I began the program, much of my attention was focused on learning how to write code that produced the correct result. As I progressed, I learned that professional software development requires more than functional code. A strong computing solution also needs to be maintainable, secure, efficient, understandable, testable, and appropriate for the people who will use or support it.

Developing this ePortfolio made that growth especially visible. Returning to earlier projects allowed me to compare the decisions I made when I first learned a concept with the decisions I would make now. Instead of replacing earlier projects with completely new work, I improved them using the skills I developed throughout the program. The difference can be seen directly in the structure, quality, security, performance, and testing of the enhanced artifacts.

My professional interests are centered on software engineering and cybersecurity. I enjoy building practical applications, but I also want to understand how software, data, users, and systems can be protected. The program helped me see that these areas are closely connected. Security should influence architecture, data handling, input validation, authentication, error handling, testing, and other design decisions from the beginning.

## Developing as a Computer Science Professional

One of the most important lessons I gained is that computer science is not only about knowing a programming language. Languages, frameworks, databases, and tools change, but the ability to analyze a problem, break it into smaller parts, evaluate solutions, and explain technical decisions continues to be valuable.

CS 300 introduced data structures and algorithms through the ABCU Course Planner and helped me understand insertion, traversal, search, and complexity. CS 340 introduced Python and MongoDB through the Grazioso Salvare project and expanded my understanding of persistent data and CRUD operations. CS 360 introduced Android development, interface state, local storage, and mobile hardware features. CS 465 gave me full-stack experience across client, server, APIs, authentication, and persistent data. CS 305 strengthened my understanding of secure software development, vulnerability analysis, dependencies, and secure communications. CS 370 introduced neural networks and reinforcement learning, where experimentation, training behavior, and performance measurement become part of the development process.

Together, these experiences gave me a much broader view of computer science than I had when I entered the program.

## Collaboration and Working With Others

Computer science work rarely exists in isolation. Even when one developer writes most of the code, software normally has users, stakeholders, reviewers, administrators, or other developers who depend on it.

The CS 499 code review required me to explain existing code and planned improvements as if I were speaking to peers or a manager. That experience showed me that understanding my own code is not enough. I also need to explain why a design was selected, where weaknesses exist, what trade-offs are involved, and what another developer should know before making changes.

Instructor feedback throughout the capstone provided another form of collaboration. Feedback on my algorithms enhancement emphasized that functional correctness is only one measure of software quality. Performance, maintainability, observability, and other qualities also matter. That reinforced the value of performance comparisons, metrics, and automated tests.

I have also learned that collaboration is easier when software itself is designed for collaboration. Modular components, clear method names, documentation, version control, automated tests, and predictable interfaces reduce the amount of knowledge another developer needs before working with a project.

## Communicating With Stakeholders

Communication became more important to me as I progressed through the program. A technically correct solution can still fail if the developer cannot explain what it does or if it does not address the needs of the intended user.

Programming assignments required readable code and documentation. Written reports required me to explain technical decisions without relying entirely on source code. Presentations and the CS 499 code review required oral communication. User-facing applications required thinking about visual communication and interface design.

My full-stack and mobile coursework also taught me the difference between what a developer sees and what a user sees. A developer may think about API requests, database objects, classes, and state. A user expects understandable screens, useful feedback, clear navigation, and predictable behavior.

The ePortfolio itself is another communication exercise. Rather than presenting unexplained source files, I am presenting the original work, the enhanced work, the reasons for the changes, measurable results, and what I learned from the process.

## Data Structures and Algorithms

My understanding of algorithms developed considerably during the program. Earlier, I tended to judge an algorithm mainly by whether it produced the correct output. CS 300 introduced complexity analysis and showed that two solutions can produce the same result while behaving very differently as data grows or arrives in a different order.

The course planner artifact demonstrates that growth. The original implementation used an ordinary BST. During the capstone I enhanced it into an AVL tree that automatically maintains balance. When 1,000 sorted records were inserted during testing, the unbalanced BST reached a height of 1,000 while the AVL tree remained at a height of 10.

I also learned that the most advanced data structure is not automatically the best one. Every structure introduces trade-offs involving memory, implementation complexity, expected operations, and performance. The important skill is selecting a solution that matches the real requirements.

## Software Engineering

The program changed how I think about software engineering. When I first began programming, I often thought of a program as one unit: write the code, run it, and verify the output. Later coursework taught me to think in components and responsibilities.

The software design enhancement demonstrates that transition. The original CS 300 project placed most of the program inside one source file and relied on raw pointer ownership. During CS 499, I separated the data model, tree logic, CSV loading, user interface, and tests. I replaced manual ownership with `std::unique_ptr`, improved input handling, introduced structured loading results, and added automated tests.

These improvements taught me that software design decisions affect future development. A class that prints errors directly to the console is harder to reuse. A function with a clear return contract is easier to test. A component with one responsibility is easier to change without affecting unrelated behavior.

## Database Development

Database coursework helped me understand that data is not simply something an application stores. The structure, validation, security, performance, and lifecycle of data affect the quality of the entire system.

My CS 340 work introduced MongoDB and document-oriented databases. During the capstone, I revisited the AnimalShelter class from a more experienced perspective. I removed hard-coded credentials, introduced environment-based configuration, added connection verification, strengthened validation, protected important fields, added indexes based on expected query patterns, improved operation results, added structured logging, and introduced explicit client cleanup. I also added 23 automated tests.

This work helped me understand database trade-offs. MongoDB provides flexibility, but applications still need boundaries for data quality. Indexes improve reads but require storage and increase write costs. More detailed results require slightly more code but allow other parts of the application to make better decisions.

## Developing a Security Mindset

Security became increasingly important to me throughout the program. CS 305 provided direct experience with secure coding concepts, vulnerability analysis, dependency checking, and protecting communications. It helped me understand that software security requires thinking about what could go wrong rather than testing only the expected path.

That mindset became part of how I approached later projects. Input validation is not only about usability. It can prevent unexpected or malicious data from reaching sensitive parts of an application. Memory ownership is not only a software-quality concern. Unsafe memory handling can cause crashes or vulnerabilities. Database credentials are secrets and should not be stored directly in source code.

My database enhancement demonstrates this mindset most directly. Hard-coded credentials were removed, destructive operations require meaningful filters, protected identifiers cannot be changed freely, raw MongoDB update operators are restricted, and failure conditions are tested.

I understand that security is an ongoing process. New dependencies, features, configuration changes, and attack techniques can introduce risk over time. Professionally, I want security to remain part of how I evaluate every computing solution.

## Professional Goals and Values

Completing the program helped clarify the kind of professional I want to become. I am interested in software engineering because I enjoy turning an idea or requirement into a working system. At the same time, I have a strong interest in cybersecurity and secure software because building a useful application also creates a responsibility to protect the people and information that depend on it.

The values I want to carry into my professional work are reliability, continuous learning, security, clarity, and practical problem solving. I do not expect to know every technology before beginning a role. One of the most valuable abilities I developed during this degree is becoming comfortable learning unfamiliar tools and solving problems systematically.

## How the ePortfolio Artifacts Fit Together

The three enhancements demonstrate different areas of computer science while showing a progression in how I approach computing problems.

The first enhancement focuses on **Software Design and Engineering**. The ABCU Course Planner was reorganized from a single-file student project into a modular C++ application with safer memory ownership, improved interfaces, validation, and automated testing.

The second enhancement builds on the same artifact from an **Algorithms and Data Structures** perspective. The ordinary BST was replaced with a self-balancing AVL tree. This demonstrates algorithm analysis, rotations, complexity trade-offs, structural testing, and measurable performance improvement.

The third enhancement focuses on **Databases** through the CS 340 Grazioso Salvare AnimalShelter module. The CRUD layer was improved with secure configuration, stronger validation, indexing, structured results, logging, lifecycle management, and automated testing.

Together, the artifacts demonstrate three connected levels of computing: how code is organized and maintained, how data is structured and processed efficiently, and how persistent data is accessed, protected, validated, and optimized. Security, testing, communication, and trade-off evaluation appear across all three rather than existing as isolated topics.

## Conclusion

Looking back at my earlier work through this capstone made my progress easier to recognize. The original artifacts show where I started. The enhanced versions show that my standards have changed.

I now ask more questions before considering software complete. Is the design understandable? Can another developer maintain it? How will the solution behave as the data grows? What happens when unexpected input is provided? How will failures be diagnosed? What data needs protection? How can I prove that the solution works instead of assuming that it does?

Those questions represent the most important growth I experienced throughout the Computer Science program. My ePortfolio demonstrates technical abilities in software engineering, algorithms and data structures, databases, security, testing, and communication, but it also represents a change in how I think as a computer science professional.
