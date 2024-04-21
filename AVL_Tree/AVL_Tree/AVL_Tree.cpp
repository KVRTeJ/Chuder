#include "AVL_Tree.hpp"

AvlTree AvlTree::copy(Node* tree) const {
    BinaryTree parent = BinaryTree::copy(tree);
    AvlTree newTree = {};
    
    newTree.setRoot(parent.root());
    parent.setRoot(nullptr);
    
    return newTree;
}

bool AvlTree::turnRight(Node* middle, Node* top) {
    if(!middle || !middle->left()) {
        return false;
    }
    
    Node* bottom = middle->left();
    
    if(top) {
        top->setLeft(bottom);
    } else {
        setRoot(bottom);
    }
    
    if(middle->left()) {
        middle->setLeft(bottom->right());
    }
    bottom->setRight(middle);
    
    return true;
}

bool AvlTree::turnLeft(Node* middle, Node* top) {
    if(!middle || !middle->right()) {
        return false;
    }
    
    Node* bottom = middle->right();
    
    if(top) {
        top->setRight(bottom);
    } else {
        setRoot(bottom);
    }
    
    middle->setRight(bottom->left());
    bottom->setLeft(middle);
    
    return true;
}

BinaryTree::Node* AvlTree::m_add(Node* root, const int value) {
    
    if(!root) {
        root = new Node(value);
    } else if(value < root->key()) {
        root->setLeft(m_add(root->left(), value));
        
    } else if(value > root->key()){
        root->setRight(m_add(root->right(), value));
        
    }
    
    return root;
}

