#ifndef AVL_TREE_H
#define AVL_TREE_H

#include "Course.h"

#include <cstddef>
#include <memory>
#include <string>
#include <vector>

class AVLTree {
public:
    enum class InsertResult {
        Inserted,
        Duplicate
    };

    AVLTree() = default;
    ~AVLTree() = default;

    AVLTree(const AVLTree&) = delete;
    AVLTree& operator=(const AVLTree&) = delete;
    AVLTree(AVLTree&&) noexcept = default;
    AVLTree& operator=(AVLTree&&) noexcept = default;

    InsertResult insert(const Course& course);
    const Course* search(const std::string& courseNumber) const noexcept;
    const Course* rootCourse() const noexcept;
    std::vector<Course> inOrderCourses() const;

    void clear() noexcept;
    bool empty() const noexcept;
    std::size_t size() const noexcept;
    int height() const noexcept;
    bool isBalanced() const noexcept;

private:
    struct Node {
        explicit Node(const Course& value) : course(value) {}

        Course course;
        int height = 1;
        std::unique_ptr<Node> left;
        std::unique_ptr<Node> right;
    };

    static std::unique_ptr<Node> insertNode(
        std::unique_ptr<Node> node,
        const Course& course,
        InsertResult& result);

    static std::unique_ptr<Node> rotateLeft(std::unique_ptr<Node> node);
    static std::unique_ptr<Node> rotateRight(std::unique_ptr<Node> node);
    static std::unique_ptr<Node> rebalance(std::unique_ptr<Node> node);

    static int nodeHeight(const Node* node) noexcept;
    static int balanceFactor(const Node* node) noexcept;
    static void updateHeight(Node* node) noexcept;
    static bool validateBalance(const Node* node, int& computedHeight) noexcept;
    static void collectInOrder(const Node* node, std::vector<Course>& courses);

    std::unique_ptr<Node> root_;
    std::size_t size_ = 0;
};

#endif
