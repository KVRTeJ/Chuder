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
    
    middle->setLeft(bottom->right());
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

bool AvlTree::doubleTurnLRightLeft(Node* middle, Node* top) {
    if(!middle || !middle->right() || !middle->right()->left()) {
        return false;
    }
    
    Node* bottom = middle->right();
    Node* extra = bottom->left();
    
    middle->setRight(extra);
    bottom->setLeft(extra->right());
    extra->setRight(bottom);
    
    if(top) {
        top->setRight(extra);
    } else {
        setRoot(extra);
    }
    middle->setRight(extra->left());
    extra->setLeft(middle);
    
    return true;
}

bool AvlTree::doubleTurnLeftRight(Node* middle, Node* top) {
    if(!middle || !middle->left() || !middle->left()->right()) {
        return false;
    }
    
    Node* bottom = middle->left();
    Node* extra = bottom->right();
    
    middle->setLeft(extra);
    bottom->setRight(extra->left());
    extra->setLeft(bottom);
    
    if(top) {
        top->setLeft(extra);
    } else {
        setRoot(extra);
    }
    middle->setLeft(extra->right());
    extra->setRight(middle);
    
    return true;
}

BinaryTree::Node* AvlTree::m_add(Node* root, const int value) {
    static bool isFixed = true;
    
    if(!root) {
        root = new Node(value);
        isFixed = false;
    } else if(value < root->key()) {
        root->setLeft(m_add(root->left(), value));
        //TODO: balace
    } else if(value > root->key()){
        root->setRight(m_add(root->right(), value));
        //TODO: balance
    }
    
    return root;
}

