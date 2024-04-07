#ifndef BinarySearchTree_hpp
#define BinarySearchTree_hpp

#include "Binary_Tree.hpp"

class SearchTree : public BinaryTree {
public:
    SearchTree() = default;
    ~SearchTree() override = default;
    
    int level(const int key) const override;
    
    SearchTree copy(Node* tree);

    Node* find(const int key) const override;
    
    std::vector<int> toVectorAsc() const override;
    
    SearchTree& operator = (const SearchTree& other) = default;
    
protected:
    void max(Node* root, int& buffer) const override;
    void min(Node* root, int& buffer) const override;
    
    void removeIfBothChildren(removeData& data) override; //FIXME: fixme case replacedNodeParent == target
    
private:
    Node* add(Node* root, const int value) override;
    
};

#endif /* BinarySearchTree_hpp */
