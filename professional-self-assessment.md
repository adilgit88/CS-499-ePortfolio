# Professional Self-Assessment

**Adil Patel**  
Computer Science Capstone

## Introduction

Completing my Computer Science degree has changed the way I approach software development and problem solving.

When I began the program, my main goal was usually simple: write code that works and produces the correct result. As I moved through more advanced projects, I learned that working software is only one part of professional development.

Software also needs to be understandable, maintainable, secure, efficient, testable, and useful to the people who depend on it.

Building this ePortfolio gave me an opportunity to see that growth clearly. Instead of only presenting newer projects, I returned to applications I created earlier in my education and evaluated them using the skills and standards I have developed since then.

That process showed me how much my thinking has changed.

Today, when I evaluate a solution, I think about more than whether the program runs. I think about how the code is organized, how data is protected, how performance may change as the application grows, how failures are handled, how another developer will understand the project, and how I can prove through testing that the software behaves correctly.

My professional interests are in software engineering and cybersecurity. I enjoy building practical applications, but I also want to understand how those applications can be made safer, more reliable, and easier to maintain.

These interests have shaped the way I approach the work presented in this portfolio.

## Developing as a Computer Science Professional

My coursework exposed me to many different areas of computer science.

I worked with C++, Python, JavaScript, databases, mobile applications, full-stack web development, secure software development, and artificial intelligence.

Each area required me to think about problems differently.

My Data Structures and Algorithms coursework taught me that the way information is organized can have a major effect on performance. I learned how structures such as trees and hash-based collections support different types of operations and why complexity matters when the size or order of the data changes.

Database programming taught me how applications communicate with persistent data and how decisions involving queries, indexes, validation, and database structure affect the complete application.

Mobile development required me to think about user interaction, local data, application state, and device features.

Full-stack web development helped me understand how user interfaces, APIs, authentication, server-side logic, and databases work together as parts of one system.

Secure software development taught me to look beyond expected behavior and ask what could go wrong. I gained experience thinking about software vulnerabilities, dependency risks, secure communication, and the importance of protecting data and resources throughout the development process.

My work with artificial intelligence and reinforcement learning added another perspective. Instead of only working with programs that follow a fixed set of instructions, I had to evaluate learning behavior, performance, experimentation, and results.

Together, these experiences gave me a well-rounded technical foundation and helped me understand that professional software development involves many connected areas.

## Collaboration and Working With Others

Software development is rarely an individual activity, even when one person writes most of the code.

Applications have users, stakeholders, developers, reviewers, administrators, and other people who depend on the system.

One area where I have grown is understanding that code itself should support collaboration.

If a project contains one large file with unclear responsibilities, another developer has to spend more time understanding the entire application before making even a small change.

A modular project with clear naming, documentation, predictable interfaces, and automated tests is much easier for another person to work with.

My capstone code review strengthened this skill by requiring me to explain existing code, identify weaknesses, discuss design choices, and communicate my enhancement plans as if I were speaking to another developer or manager.

Instructor feedback throughout the capstone also helped me think more carefully about professional software quality.

For example, one important lesson was that passing functional tests is not the only goal. Performance, maintainability, observability, security, and other qualities also affect whether software is ready for professional use.

I expect collaboration to remain an area of continuous growth in my career. Working on larger development teams will require skills such as code review, issue tracking, technical documentation, version control, communicating disagreements, and balancing the needs of different stakeholders.

The foundation I have developed gives me a strong starting point for those environments.

## Communicating With Stakeholders

Technical ability is important, but software developers also need to communicate clearly.

A developer may understand classes, database objects, algorithms, APIs, and application state. A stakeholder may care more about whether the application solves the correct problem, protects important information, and gives users clear results.

The ability to communicate between those perspectives is an important professional skill.

Throughout my education, I practiced technical communication through written reports, project documentation, presentations, code reviews, user interfaces, and software demonstrations.

The capstone brought those skills together.

My code review requires me to explain technical problems in spoken language.

My narratives explain the reasoning behind each enhancement.

My README files are designed to help another developer understand how to build, run, and test the software.

My ePortfolio presents the work in a way that allows an employer to understand the purpose and value of the projects without reading every source file.

I have also learned that technical design can affect communication with users.

For example, a database update that reports only whether it succeeded may not provide enough information for the user interface.

If the database reports both how many records matched and how many were actually modified, the application can give the user a much clearer result.

Small technical choices like this can have a direct effect on the user's experience.

## Data Structures and Algorithms

My understanding of algorithms has changed significantly.

Earlier in my education, I often evaluated a solution by asking whether it produced the correct answer.

I now understand that correctness is only one part of evaluating an algorithm.

A solution can return the correct result and still perform poorly when the data grows or arrives in an unexpected order.

The Course Planner artifact in this portfolio demonstrates that growth.

The original application used an ordinary binary search tree.

The tree worked correctly, but its shape depended on insertion order. Sorted input could create a one-sided tree, causing search and insertion to fall to linear performance in the worst case.

For my enhancement, I replaced the ordinary binary search tree with a self-balancing AVL tree.

The AVL implementation maintains its balance using node heights and rotations.

I did not only implement the algorithm. I also tested its behavior under difficult input conditions.

When 1,000 sorted values were inserted, the unbalanced binary search tree reached a height of 1,000.

The AVL tree reached a height of only 10.

That comparison made the importance of algorithm analysis very clear.

It showed me that choosing a data structure should be based on application requirements, expected operations, performance guarantees, memory costs, and implementation complexity rather than simply choosing the structure that is easiest to write.

## Software Engineering

Software engineering has become one of the strongest areas of growth for me.

When I first started programming, I often treated an application as one complete unit.

I would write the code, run it, fix errors, and consider the project finished once the expected output appeared.

More advanced projects taught me to think in terms of components, responsibilities, interfaces, testing, maintainability, and future change.

My Course Planner enhancement demonstrates this shift.

The original version placed most of the application inside one source file and relied on raw pointers for memory ownership.

I reorganized the application into focused components for the course model, tree logic, data loading, user interaction, and testing.

I also replaced owning raw pointers with `std::unique_ptr`, improved input handling, introduced structured loading results, and added automated tests.

These changes did not dramatically change what the user sees.

The application still loads courses, displays the catalog, and searches for course information.

The major improvement is how the program is built internally.

That is an important lesson I have taken from my education.

A professional enhancement does not always need to introduce a new visible feature.

Improving maintainability, reliability, testing, security, and clarity can provide just as much value.

## Database Development

My database experience taught me to think of data as a central part of the application rather than simply something stored in the background.

The database layer affects security, performance, reliability, data quality, and the information available to the rest of the software.

The AnimalShelter artifact in this portfolio originally provided basic MongoDB create, read, update, and delete operations.

It worked, but it also contained several weaknesses that are common in small learning projects.

Credentials were stored directly in the source code.

Connection problems were not checked immediately.

Validation was limited.

The class did not clearly manage the lifetime of the database connection.

Indexes were not part of the design.

Database results sometimes provided only limited information.

For my enhancement, I addressed these issues through environment-based configuration, stronger validation, connection verification, indexing, structured logging, clearer database results, resource cleanup, and automated testing.

I also added a suite of 23 tests.

One of the biggest lessons from this work was that database design involves trade-offs.

MongoDB provides flexible documents, but an application still needs rules to protect data quality.

Indexes can improve read performance, but they also require storage and increase the cost of writes.

Detailed result objects require slightly more design work, but they allow the rest of the application to make better decisions.

These trade-offs are part of building a database solution that supports the complete application.

## Developing a Security Mindset

Security is an area I want to continue developing professionally.

My secure software development coursework taught me that security should not be treated as something added after the application is completed.

Security decisions exist throughout the software.

They appear in authentication, configuration, input validation, dependency management, memory ownership, database access, error handling, logging, and data protection.

That mindset influenced the enhancements in this portfolio.

In the C++ application, safer memory ownership reduces the risk associated with incorrect manual memory management.

Improved validation helps prevent unexpected data from moving through the program.

The database artifact provides even stronger examples.

Hard-coded credentials were removed from the source code.

Database configuration was moved to environment variables.

Empty update and delete filters are rejected.

Protected fields have stronger rules.

Raw update operators are restricted at the class boundary.

Sensitive information is not intentionally placed in log messages.

Failure conditions are also included in automated testing.

These improvements reflect an important change in the way I approach software.

I do not only ask whether the normal path works.

I also ask what happens when input is incorrect, a service is unavailable, a developer makes a mistake, or someone attempts to use the system in an unexpected way.

That way of thinking is one of the skills I want to continue strengthening throughout my career.

## Professional Goals and Values

My education helped clarify the kind of developer I want to become.

I am interested in software engineering because I enjoy taking an idea or requirement and turning it into a working application.

I am also interested in cybersecurity because useful software creates a responsibility to protect the people, systems, and information that depend on it.

The professional values I want to bring to my work are reliability, security, clarity, responsibility, and continuous learning.

I understand that entering the technology field does not mean I will already know every language, framework, or tool an employer uses.

Technology changes too quickly for that.

What I have developed is the ability to learn unfamiliar technologies, break problems into smaller parts, research solutions, test my assumptions, and continue working through technical problems until I understand them.

During my education, I worked across several different development environments and programming languages.

Moving between those environments helped me become more comfortable learning new tools instead of depending on one specific technology.

That adaptability is something I expect to rely on throughout my career.

## How the Portfolio Fits Together

The artifacts in this portfolio demonstrate different areas of computer science, but they also support one larger story about my development as a software professional.

The first enhancement focuses on **software design and engineering**.

The original Course Planner was reorganized from a single-file C++ application into a more modular structure with clearer responsibilities, safer memory ownership, improved validation, reusable interfaces, and automated tests.

The second enhancement examines the same application from an **algorithms and data structures** perspective.

The ordinary binary search tree was replaced with a self-balancing AVL tree.

This enhancement demonstrates algorithm analysis, tree balancing, rotations, complexity, testing, and measurable performance improvement.

Using the same application for these two categories demonstrates an important point.

Clean software design does not automatically guarantee an efficient algorithm.

An efficient algorithm also does not automatically create maintainable software.

Both areas need to be considered.

The third enhancement focuses on **databases**.

The AnimalShelter MongoDB data-access layer was improved through secure configuration, stronger validation, indexes, structured results, logging, lifecycle management, and automated testing.

Together, the three enhancements demonstrate how different parts of computer science connect.

Software engineering affects how the application is organized and maintained.

Algorithms affect how efficiently information can be processed.

Databases affect how persistent information is stored, retrieved, protected, and managed.

Security, testing, communication, and trade-off analysis appear throughout all three areas.

## Conclusion

Looking back at my earlier work through this capstone made my progress easier to recognize.

The original projects are valuable because they show the foundation I developed earlier in my education.

The enhanced projects show how my standards have changed.

Today, before I consider software complete, I ask more questions.

Is the design understandable?

Can another developer maintain it?

How will the solution behave as the amount of data increases?

What happens when unexpected input is provided?

How are important resources protected?

How will failures be diagnosed?

Can I test the behavior repeatedly?

Can I explain the technical decisions to someone who did not build the system?

Those questions represent the biggest change in how I think as a computer science professional.

This ePortfolio demonstrates my experience with software engineering, algorithms and data structures, databases, security, testing, and professional communication.

More importantly, it demonstrates that I understand the difference between simply making software work and building software that is prepared to be used, reviewed, maintained, and improved by others.

I am completing my Computer Science degree with a stronger technical foundation, a clearer understanding of professional software development, and the ability to continue learning as I begin the next stage of my career.
