#include "BinarySearchTree.h"
#include "CourseLoader.h"

#include <algorithm>
#include <cctype>
#include <iostream>
#include <limits>
#include <string>

namespace {

std::string toUpper(std::string value) {
    std::transform(
        value.begin(),
        value.end(),
        value.begin(),
        [](unsigned char character) {
            return static_cast<char>(std::toupper(character));
        });
    return value;
}

void printMenu() {
    std::cout << "\n   1. Load Data Structure.\n"
              << "   2. Print Course List.\n"
              << "   3. Print Course.\n"
              << "   9. Exit\n"
              << "\nWhat would you like to do? ";
}

void printCourseList(const BinarySearchTree& tree) {
    if (tree.empty()) {
        std::cout << "Please load the data structure first (Option 1).\n";
        return;
    }

    std::cout << "\nHere is a sample schedule:\n\n";
    for (const Course& course : tree.inOrderCourses()) {
        std::cout << course.courseNumber << ", " << course.name << '\n';
    }
}

void printCourseInfo(const BinarySearchTree& tree) {
    if (tree.empty()) {
        std::cout << "Please load the data structure first (Option 1).\n";
        return;
    }

    std::cout << "What course do you want to know about? ";
    std::string courseNumber;
    std::getline(std::cin, courseNumber);
    courseNumber = toUpper(courseNumber);

    const Course* course = tree.search(courseNumber);
    if (course == nullptr) {
        std::cout << "Course '" << courseNumber << "' not found.\n";
        return;
    }

    std::cout << course->courseNumber << ", " << course->name << '\n';
    std::cout << "Prerequisites: ";

    if (course->prerequisites.empty()) {
        std::cout << "None\n";
        return;
    }

    for (std::size_t index = 0; index < course->prerequisites.size(); ++index) {
        if (index > 0) {
            std::cout << ", ";
        }
        std::cout << course->prerequisites[index];
    }
    std::cout << '\n';
}

}  // namespace

int main() {
    BinarySearchTree tree;
    int choice = 0;

    std::cout << "Welcome to the course planner.\n";

    while (choice != 9) {
        printMenu();

        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
        case 1: {
            std::cout << "Enter the file name or path to load: ";
            std::string filename;
            std::getline(std::cin, filename);

            const LoadResult result = CourseLoader::loadCsv(filename, tree);
            for (const std::string& message : result.messages) {
                std::cout << message << '\n';
            }

            if (result.success) {
                std::cout << result.loadedCount << " course(s) loaded successfully";
                if (result.skippedCount > 0) {
                    std::cout << "; " << result.skippedCount << " row(s) skipped";
                }
                std::cout << ".\n";
            }
            break;
        }

        case 2:
            printCourseList(tree);
            break;

        case 3:
            printCourseInfo(tree);
            break;

        case 9:
            std::cout << "Thank you for using the course planner!\n";
            break;

        default:
            std::cout << choice << " is not a valid option.\n";
            break;
        }
    }

    return 0;
}
