#include <random>

#include "Binary_Tree.hpp"

void BinaryTree::add(const int value) {
    
    if(m_root) {
        add(m_root, value);
    } else {
        m_root = new Node(value);
    }
    
}

std::vector<int> BinaryTree::toVector() const {
    std::vector<int> result;
    
    toVector(m_root, result);
    
    return result;
}

void BinaryTree::printLeafs(Node* root) const {
    
    if(!root) {
        return;
    } else if(!root->left() && !root->right()) {
        std::cout << root->key() << std::endl;
    } else {
        printLeafs(root->left());
        printLeafs(root->right());
    }
    
}

void BinaryTree::printHorizontal(Node *root, int marginLeft, int levelSpacing) const {
    
    if (root == nullptr) {
        return;
    }
    
    printHorizontal(root->right(), marginLeft + levelSpacing, levelSpacing);
    std::cout << std::string(marginLeft, ' ') << root->key() << std::endl;
    printHorizontal(root->left(), marginLeft + levelSpacing, levelSpacing);
}

void BinaryTree::toVector(Node* root, std::vector<int>& nums) const {
    
    if(!root) {
        return;
    }
    
    //обход - RLR
    nums.push_back(root->key());
    toVector(root->left(), nums);
    toVector(root->right(), nums);
}

BinaryTree::Node* BinaryTree::add(Node* root, const int value) {

    if(!root) {
        root = new Node(value);
    } else if(rand() % 2) {
        root->setLeft(add(root->left(), value));
    } else {
        root->setRight(add(root->right(), value));
    }

    return root;
}

