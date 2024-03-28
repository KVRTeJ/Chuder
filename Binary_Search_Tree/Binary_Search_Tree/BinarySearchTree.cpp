#include "BinarySearchTree.hpp"

int SearchTree::max() const {
    const Node* result = root();
    
    for(;result->right() != nullptr; result = result->right());
    
    return result->key();
}

int SearchTree::min() const {
    const Node* result = root();
    
    for(;result->left() != nullptr; result = result->left());
    
    return result->key();
}

void SearchTree::add(const int key) {
    
    if(!root()) {
        setRoot(new Node(key));
    } else {
        add(root(), key);
    }
}

BinaryTree::Node* SearchTree::find(const int key) const {
    Node* current = const_cast<Node*>(root());
    
    while(current && (current->key() != key)) {
        if(current->key() > key) {
            current = current->left();
        } else {
            current = current->right();
        }
    }
    
    return current;
}

/* private */

BinaryTree::Node* SearchTree::add(Node* root, const int value) {
    
    if(!root) {
        root = new Node(value);
    } else if(value < root->key()) {
        root->setLeft(add(root->left(), value));
    } else {
        root->setRight(add(root->right(), value));
    }
    
    return root;
}