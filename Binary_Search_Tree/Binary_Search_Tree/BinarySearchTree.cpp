#include "BinarySearchTree.hpp"

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

bool SearchTree::remove(const int key) {
    return false;
}

SearchTree SearchTree::copy(Node* tree) {
    BinaryTree parent = BinaryTree::copy(tree);
    SearchTree newTree = {};
    
    newTree.setRoot(parent.root());
    parent.setRoot(nullptr);
    
    return newTree;
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

std::vector<int> SearchTree::toVectorAsc() const {
    std::vector<int> result = toVectorLnr();;
    
    return result;
}

/* private */

BinaryTree::Node* SearchTree::add(Node* root, const int value) {
    
    if(!root) {
        root = new Node(value);
    } else if(value < root->key()) {
        root->setLeft(add(root->left(), value));
    } else if(value > root->key()){
        root->setRight(add(root->right(), value));
    }
    
    return root;
}

void SearchTree::max(Node* root, int& buffer) const {
    if(!root) {
        return;
    }
    
    buffer = root->key();
    max(root->right(), buffer);
}

void SearchTree::min(Node* root, int& buffer) const {
    if(!root) {
        return;
    }
    
    buffer = root->key();
    min(root->left(), buffer);
}
