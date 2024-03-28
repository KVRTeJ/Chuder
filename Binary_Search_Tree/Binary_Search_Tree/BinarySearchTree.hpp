#ifndef BinarySearchTree_hpp
#define BinarySearchTree_hpp

#include "Binary_Tree.hpp"

class SearchTree : public BinaryTree {
public:
    SearchTree() = default;
    ~SearchTree() = default;
    
    int max() const override;
    int min() const override;
    
    int level(const int key) const override {return -1;} //TODO: implement me
    int level(Node* root, Node* target, int currentLevel = 0) const override {return -1;} //TODO: implement me
    
    void add(const int key) override;
    bool remove(const int key) override {return false;} //TODO: implement me
    bool remove(Node* target) override {return false;}; //TODO: implement me
    
    Node* find(const int key) const override; //TODO: implement me
    
    std::vector<int> toVector() const override {return {};} //TODO: implement me
    
    SearchTree& operator = (const SearchTree& other) = default; //TODO: implement me
    
private:
    Node* add(Node* root, const int value) override;
    
};

#endif /* BinarySearchTree_hpp */
