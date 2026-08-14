#include "BinarySearchTree.h"
#include "CourseLoader.h"

#include <cassert>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace {

Course makeCourse(
    const std::string& number,
    const std::string& name,
    std::vector<std::string> prerequisites = {}) {

    return Course{number, name, std::move(prerequisites)};
}

void testInsertSearchAndDuplicate() {
    BinarySearchTree tree;

    assert(tree.insert(makeCourse("CSCI300", "Data Structures")) ==
           BinarySearchTree::InsertResult::Inserted);
    assert(tree.insert(makeCourse("MATH201", "Discrete Mathematics")) ==
           BinarySearchTree::InsertResult::Inserted);
    assert(tree.insert(makeCourse("CSCI300", "Duplicate")) ==
           BinarySearchTree::InsertResult::Duplicate);

    assert(tree.size() == 2);
    assert(tree.search("CSCI300") != nullptr);
    assert(tree.search("CSCI999") == nullptr);
}

void testInOrderAndClear() {
    BinarySearchTree tree;
    tree.insert(makeCourse("CSCI400", "Software Engineering"));
    tree.insert(makeCourse("CSCI200", "Programming II"));
    tree.insert(makeCourse("CSCI300", "Data Structures"));

    const std::vector<Course> courses = tree.inOrderCourses();
    assert(courses.size() == 3);
    assert(courses[0].courseNumber == "CSCI200");
    assert(courses[1].courseNumber == "CSCI300");
    assert(courses[2].courseNumber == "CSCI400");

    tree.clear();
    assert(tree.empty());
    assert(tree.size() == 0);
    assert(tree.search("CSCI300") == nullptr);
}

void testLoaderValidationAndReload() {
    const std::filesystem::path filePath =
        std::filesystem::temp_directory_path() / "cs499_course_loader_test.csv";

    {
        std::ofstream file(filePath);
        file << "CSCI300,Data Structures,CSCI200\n";
        file << "CSCI200,Programming II\n";
        file << "CSCI300,Duplicate Course\n";
        file << "BADROW\n";
        file << "CSCI400,Software Engineering,DOESNOTEXIST\n";
    }

    BinarySearchTree tree;
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

    std::filesystem::remove(filePath);
}

void testMissingFile() {
    BinarySearchTree tree;
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
    testLoaderValidationAndReload();
    testMissingFile();

    std::cout << "All Course Planner tests passed.\n";
    return 0;
}
