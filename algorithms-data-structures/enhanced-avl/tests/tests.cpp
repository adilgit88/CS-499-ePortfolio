#include "AVLTree.h"
#include "CourseLoader.h"

#include <cassert>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

namespace {

Course makeCourse(
    const std::string& number,
    const std::string& name = "Test Course",
    std::vector<std::string> prerequisites = {}) {

    return Course{number, name, std::move(prerequisites)};
}

std::string numberedCourse(int number) {
    std::ostringstream stream;
    stream << "CSCI" << std::setw(4) << std::setfill('0') << number;
    return stream.str();
}

void requireBalanced(const AVLTree& tree) {
    assert(tree.isBalanced());
}

void testInsertSearchAndDuplicate() {
    AVLTree tree;

    assert(tree.insert(makeCourse("CSCI300", "Data Structures")) ==
           AVLTree::InsertResult::Inserted);
    assert(tree.insert(makeCourse("MATH201", "Discrete Mathematics")) ==
           AVLTree::InsertResult::Inserted);
    assert(tree.insert(makeCourse("CSCI300", "Duplicate")) ==
           AVLTree::InsertResult::Duplicate);

    assert(tree.size() == 2);
    assert(tree.search("CSCI300") != nullptr);
    assert(tree.search("CSCI999") == nullptr);
    requireBalanced(tree);
}

void testInOrderAndClear() {
    AVLTree tree;
    tree.insert(makeCourse("CSCI400", "Software Engineering"));
    tree.insert(makeCourse("CSCI200", "Programming II"));
    tree.insert(makeCourse("CSCI300", "Data Structures"));

    const std::vector<Course> courses = tree.inOrderCourses();
    assert(courses.size() == 3);
    assert(courses[0].courseNumber == "CSCI200");
    assert(courses[1].courseNumber == "CSCI300");
    assert(courses[2].courseNumber == "CSCI400");
    requireBalanced(tree);

    tree.clear();
    assert(tree.empty());
    assert(tree.size() == 0);
    assert(tree.height() == 0);
    assert(tree.search("CSCI300") == nullptr);
    requireBalanced(tree);
}

void verifyThreeNodeRotation(
    const std::string& first,
    const std::string& second,
    const std::string& third) {

    AVLTree tree;
    tree.insert(makeCourse(first));
    tree.insert(makeCourse(second));
    tree.insert(makeCourse(third));

    assert(tree.size() == 3);
    assert(tree.height() == 2);
    assert(tree.rootCourse() != nullptr);
    assert(tree.rootCourse()->courseNumber == "CSCI200");
    requireBalanced(tree);
}

void testAllFourRotationCases() {
    verifyThreeNodeRotation("CSCI300", "CSCI200", "CSCI100");  // Left-left
    verifyThreeNodeRotation("CSCI100", "CSCI200", "CSCI300");  // Right-right
    verifyThreeNodeRotation("CSCI300", "CSCI100", "CSCI200");  // Left-right
    verifyThreeNodeRotation("CSCI100", "CSCI300", "CSCI200");  // Right-left
}

void testSortedAndReverseSortedInsertion() {
    constexpr int courseCount = 1000;

    AVLTree sortedTree;
    for (int number = 1; number <= courseCount; ++number) {
        assert(sortedTree.insert(makeCourse(numberedCourse(number))) ==
               AVLTree::InsertResult::Inserted);
    }

    assert(sortedTree.size() == courseCount);
    assert(sortedTree.height() <= 11);
    assert(sortedTree.search(numberedCourse(1)) != nullptr);
    assert(sortedTree.search(numberedCourse(courseCount)) != nullptr);
    requireBalanced(sortedTree);

    AVLTree reverseTree;
    for (int number = courseCount; number >= 1; --number) {
        assert(reverseTree.insert(makeCourse(numberedCourse(number))) ==
               AVLTree::InsertResult::Inserted);
    }

    assert(reverseTree.size() == courseCount);
    assert(reverseTree.height() <= 11);
    requireBalanced(reverseTree);
}

void testLoaderValidationAndReload() {
    const std::filesystem::path filePath =
        std::filesystem::temp_directory_path() / "cs499_avl_loader_test.csv";

    {
        std::ofstream file(filePath);
        file << "CSCI300,Data Structures,CSCI200\n";
        file << "CSCI200,Programming II\n";
        file << "CSCI300,Duplicate Course\n";
        file << "BADROW\n";
        file << "CSCI400,Software Engineering,DOESNOTEXIST\n";
    }

    AVLTree tree;
    tree.insert(makeCourse("OLD100", "Old Data"));

    const LoadResult result = CourseLoader::loadCsv(filePath.string(), tree);
    assert(result.success);
    assert(result.loadedCount == 3);
    assert(result.skippedCount == 2);
    assert(tree.size() == 3);
    assert(tree.search("OLD100") == nullptr);
    assert(tree.search("CSCI300") != nullptr);
    assert(tree.search("CSCI400") != nullptr);
    assert(tree.search("CSCI400")->prerequisites.empty());
    requireBalanced(tree);

    std::filesystem::remove(filePath);
}

void testMissingFile() {
    AVLTree tree;
    const LoadResult result = CourseLoader::loadCsv(
        "this_file_should_not_exist_499.csv", tree);

    assert(!result.success);
    assert(result.loadedCount == 0);
    assert(!result.messages.empty());
}

}  // namespace

int main() {
    testInsertSearchAndDuplicate();
    testInOrderAndClear();
    testAllFourRotationCases();
    testSortedAndReverseSortedInsertion();
    testLoaderValidationAndReload();
    testMissingFile();

    std::cout << "All AVL Course Planner tests passed.\n";
    return 0;
}
