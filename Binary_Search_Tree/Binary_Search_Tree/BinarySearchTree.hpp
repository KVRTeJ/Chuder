#ifndef BinarySearchTree_hpp
#define BinarySearchTree_hpp

#include "Binary_Tree.hpp"

class SearchTree : public BinaryTree {
public:
    SearchTree() = default;
    ~SearchTree() = default;
    
    int max() const override;
    int min() const override;
    
    int level(const int key) const override;
    
    void add(const int key) override;
    bool remove(const int key) override {return false;} //TODO: implement me
    bool remove(Node* target) override {return false;}; //TODO: implement me
    
    Node* find(const int key) const override;
    
    std::vector<int> toVector() const override {return {};} //TODO: implement me
    
    SearchTree& operator = (const SearchTree& other) = default; //TODO: implement me
    
private:
    Node* add(Node* root, const int value) override;
    
};

#endif /* BinarySearchTree_hpp */
