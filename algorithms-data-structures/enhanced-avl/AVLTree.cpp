#include "AVLTree.h"

#include <algorithm>
#include <utility>

AVLTree::InsertResult AVLTree::insert(const Course& course) {
    InsertResult result = InsertResult::Duplicate;
    root_ = insertNode(std::move(root_), course, result);

    if (result == InsertResult::Inserted) {
        ++size_;
    }

    return result;
}

std::unique_ptr<AVLTree::Node> AVLTree::insertNode(
    std::unique_ptr<Node> node,
    const Course& course,
    InsertResult& result) {

    if (!node) {
        result = InsertResult::Inserted;
        return std::make_unique<Node>(course);
    }

    if (course.courseNumber < node->course.courseNumber) {
        node->left = insertNode(std::move(node->left), course, result);
    } else if (course.courseNumber > node->course.courseNumber) {
        node->right = insertNode(std::move(node->right), course, result);
    } else {
        result = InsertResult::Duplicate;
        return node;
    }

    updateHeight(node.get());
    return rebalance(std::move(node));
}

std::unique_ptr<AVLTree::Node> AVLTree::rotateLeft(
    std::unique_ptr<Node> node) {

    std::unique_ptr<Node> newRoot = std::move(node->right);
    std::unique_ptr<Node> transferredSubtree = std::move(newRoot->left);

    newRoot->left = std::move(node);
    newRoot->left->right = std::move(transferredSubtree);

    updateHeight(newRoot->left.get());
    updateHeight(newRoot.get());
    return newRoot;
}

std::unique_ptr<AVLTree::Node> AVLTree::rotateRight(
    std::unique_ptr<Node> node) {

    std::unique_ptr<Node> newRoot = std::move(node->left);
    std::unique_ptr<Node> transferredSubtree = std::move(newRoot->right);

    newRoot->right = std::move(node);
    newRoot->right->left = std::move(transferredSubtree);

    updateHeight(newRoot->right.get());
    updateHeight(newRoot.get());
    return newRoot;
}

std::unique_ptr<AVLTree::Node> AVLTree::rebalance(
    std::unique_ptr<Node> node) {

    const int factor = balanceFactor(node.get());

    if (factor > 1) {
        if (balanceFactor(node->left.get()) < 0) {
            node->left = rotateLeft(std::move(node->left));
        }
        return rotateRight(std::move(node));
    }

    if (factor < -1) {
        if (balanceFactor(node->right.get()) > 0) {
            node->right = rotateRight(std::move(node->right));
        }
        return rotateLeft(std::move(node));
    }

    return node;
}

const Course* AVLTree::search(const std::string& courseNumber) const noexcept {
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

const Course* AVLTree::rootCourse() const noexcept {
    return root_ ? &root_->course : nullptr;
}

std::vector<Course> AVLTree::inOrderCourses() const {
    std::vector<Course> courses;
    courses.reserve(size_);
    collectInOrder(root_.get(), courses);
    return courses;
}

void AVLTree::collectInOrder(
    const Node* node,
    std::vector<Course>& courses) {

    if (node == nullptr) {
        return;
    }

    collectInOrder(node->left.get(), courses);
    courses.push_back(node->course);
    collectInOrder(node->right.get(), courses);
}

void AVLTree::clear() noexcept {
    root_.reset();
    size_ = 0;
}

bool AVLTree::empty() const noexcept {
    return size_ == 0;
}

std::size_t AVLTree::size() const noexcept {
    return size_;
}

int AVLTree::height() const noexcept {
    return nodeHeight(root_.get());
}

bool AVLTree::isBalanced() const noexcept {
    int computedHeight = 0;
    return validateBalance(root_.get(), computedHeight);
}

int AVLTree::nodeHeight(const Node* node) noexcept {
    return node == nullptr ? 0 : node->height;
}

int AVLTree::balanceFactor(const Node* node) noexcept {
    if (node == nullptr) {
        return 0;
    }

    return nodeHeight(node->left.get()) - nodeHeight(node->right.get());
}

void AVLTree::updateHeight(Node* node) noexcept {
    if (node == nullptr) {
        return;
    }

    node->height = 1 + std::max(
        nodeHeight(node->left.get()),
        nodeHeight(node->right.get()));
}

bool AVLTree::validateBalance(
    const Node* node,
    int& computedHeight) noexcept {

    if (node == nullptr) {
        computedHeight = 0;
        return true;
    }

    int leftHeight = 0;
    int rightHeight = 0;

    const bool leftBalanced = validateBalance(node->left.get(), leftHeight);
    const bool rightBalanced = validateBalance(node->right.get(), rightHeight);

    computedHeight = 1 + std::max(leftHeight, rightHeight);
    const int difference = leftHeight - rightHeight;
    const bool storedHeightIsCorrect = node->height == computedHeight;

    return leftBalanced && rightBalanced &&
           difference >= -1 && difference <= 1 &&
           storedHeightIsCorrect;
}
