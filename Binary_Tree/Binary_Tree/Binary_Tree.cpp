#include <random>

#include "Binary_Tree.hpp"

BinaryTree::BinaryTree() {
    std::cout << "Hello! I'm Binary Tree!" << std::endl;
}

BinaryTree::~BinaryTree() {
    std::cout << "I was Binary Tree! Bye Bye" << std::endl;
}

void BinaryTree::add(const int value) {
    
    if(m_root) {
        add(m_root, value);
    } else {
        m_root = new Node(value);
    }
    
}

BinaryTree::Node* BinaryTree::add(Node* root, const int value) {

    if(!root) {
        root = new Node(value);
    } else if (rand() % 2) {
        root->setLeft(add(root->left(), value));
    } else {
        root->setRight(add(root->right(), value));
    }

    return root;
}
