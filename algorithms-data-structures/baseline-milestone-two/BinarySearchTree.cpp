#include "BinarySearchTree.h"

BinarySearchTree::InsertResult BinarySearchTree::insert(const Course& course) {
    const InsertResult result = insertNode(root_, course);
    if (result == InsertResult::Inserted) {
        ++size_;
    }
    return result;
}

BinarySearchTree::InsertResult BinarySearchTree::insertNode(
    std::unique_ptr<Node>& node,
    const Course& course) {

    if (!node) {
        node = std::make_unique<Node>(course);
        return InsertResult::Inserted;
    }

    if (course.courseNumber < node->course.courseNumber) {
        return insertNode(node->left, course);
    }

    if (course.courseNumber > node->course.courseNumber) {
        return insertNode(node->right, course);
    }

    return InsertResult::Duplicate;
}

const Course* BinarySearchTree::search(const std::string& courseNumber) const {
    const Node* current = root_.get();

    while (current != nullptr) {
        if (courseNumber == current->course.courseNumber) {
            return &current->course;
        }

        current = courseNumber < current->course.courseNumber
            ? current->left.get()
            : current->right.get();
    }

    return nullptr;
}

std::vector<Course> BinarySearchTree::inOrderCourses() const {
    std::vector<Course> courses;
    courses.reserve(size_);
    collectInOrder(root_.get(), courses);
    return courses;
}

void BinarySearchTree::collectInOrder(
    const Node* node,
    std::vector<Course>& courses) {

    if (node == nullptr) {
        return;
    }

    collectInOrder(node->left.get(), courses);
    courses.push_back(node->course);
    collectInOrder(node->right.get(), courses);
}

void BinarySearchTree::clear() noexcept {
    root_.reset();
    size_ = 0;
}

bool BinarySearchTree::empty() const noexcept {
    return size_ == 0;
}

std::size_t BinarySearchTree::size() const noexcept {
    return size_;
}
