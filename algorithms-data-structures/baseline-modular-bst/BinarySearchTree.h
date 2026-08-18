#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include "Course.h"

#include <cstddef>
#include <memory>
#include <string>
#include <vector>

class BinarySearchTree {
public:
    enum class InsertResult {
        Inserted,
        Duplicate
    };

    BinarySearchTree() = default;
    ~BinarySearchTree() = default;

    BinarySearchTree(const BinarySearchTree&) = delete;
    BinarySearchTree& operator=(const BinarySearchTree&) = delete;
    BinarySearchTree(BinarySearchTree&&) noexcept = default;
    BinarySearchTree& operator=(BinarySearchTree&&) noexcept = default;

    InsertResult insert(const Course& course);
    const Course* search(const std::string& courseNumber) const;
    std::vector<Course> inOrderCourses() const;

    void clear() noexcept;
    bool empty() const noexcept;
    std::size_t size() const noexcept;

private:
    struct Node {
        explicit Node(const Course& value) : course(value) {}

        Course course;
        std::unique_ptr<Node> left;
        std::unique_ptr<Node> right;
    };

    static InsertResult insertNode(std::unique_ptr<Node>& node, const Course& course);
    static void collectInOrder(const Node* node, std::vector<Course>& courses);

    std::unique_ptr<Node> root_;
    std::size_t size_ = 0;
};

#endif
