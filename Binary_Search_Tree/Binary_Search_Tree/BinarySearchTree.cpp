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

