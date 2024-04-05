#ifndef BinarySearchTree_hpp
#define BinarySearchTree_hpp

#include "Binary_Tree.hpp"

class SearchTree : public BinaryTree {
public:
    SearchTree() = default;
    ~SearchTree() override = default;
    
    int level(const int key) const override;
    
    bool remove(const int key) override {return false;} //TODO: implement me
    
    SearchTree copy(Node* tree);

    Node* find(const int key) const override;
    
    std::vector<int> toVectorAsc() const override;
    
    SearchTree& operator = (const SearchTree& other) = default;
    
protected:
    void max(Node* root, int& buffer) const override;
    void min(Node* root, int& buffer) const override;
    
private:
    Node* add(Node* root, const int value) override;
    
    
    
};

#endif /* BinarySearchTree_hpp */
