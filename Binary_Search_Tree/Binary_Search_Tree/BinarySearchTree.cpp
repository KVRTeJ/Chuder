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

int SearchTree::level(const int key) const {
    if(!root()) {
        return {};
    }
    
    int result = 1;
    for(const Node* n = root(); n && n->key() != key; ++result) {
        if(n->key() > key) {
            n = n->left();
        } else {
            n = n->right();
        }
    }
    
    return result;
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

std::vector<int> SearchTree::toVector() const {
    std::vector<int> result = toVectorLnr();;
    
    return result;
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
