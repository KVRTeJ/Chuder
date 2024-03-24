#ifndef BinarySearchTree_hpp
#define BinarySearchTree_hpp

#include "Binary_Tree.hpp"

class SearchTree : public BinaryTree {
public:
    SearchTree() = default;
    ~SearchTree() = default;
    
    SearchTree& operator = (const SearchTree& other) = default;
private:
};

#endif /* BinarySearchTree_hpp */
