#include "AVLTree.h"

#include <iomanip>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>

namespace {

class UnbalancedHeightProbe {
public:
    void insert(const std::string& key) {
        insertNode(root_, key);
    }

    int height() const noexcept {
        return nodeHeight(root_.get());
    }

private:
    struct Node {
        explicit Node(std::string value) : key(std::move(value)) {}
        std::string key;
        std::unique_ptr<Node> left;
        std::unique_ptr<Node> right;
    };

    static void insertNode(
        std::unique_ptr<Node>& node,
        const std::string& key) {

        if (!node) {
            node = std::make_unique<Node>(key);
            return;
        }

        if (key < node->key) {
            insertNode(node->left, key);
        } else if (key > node->key) {
            insertNode(node->right, key);
        }
    }

    static int nodeHeight(const Node* node) noexcept {
        if (node == nullptr) {
            return 0;
        }

        const int leftHeight = nodeHeight(node->left.get());
        const int rightHeight = nodeHeight(node->right.get());
        return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
    }

    std::unique_ptr<Node> root_;
};

std::string numberedCourse(int number) {
    std::ostringstream stream;
    stream << "CSCI" << std::setw(4) << std::setfill('0') << number;
    return stream.str();
}

}  // namespace

int main() {
    constexpr int courseCount = 1000;
    UnbalancedHeightProbe unbalancedTree;
    AVLTree avlTree;

    for (int number = 1; number <= courseCount; ++number) {
        const std::string key = numberedCourse(number);
        unbalancedTree.insert(key);
        avlTree.insert(Course{key, "Generated Course", {}});
    }

    std::cout << "Sorted insertion comparison (" << courseCount << " courses)\n"
              << "Unbalanced BST height: " << unbalancedTree.height() << '\n'
              << "AVL tree height: " << avlTree.height() << '\n'
              << "AVL balance check: "
              << (avlTree.isBalanced() ? "passed" : "failed") << '\n';

    return avlTree.isBalanced() ? 0 : 1;
}
