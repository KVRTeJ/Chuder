#ifndef AVL_Tree_hpp
#define AVL_Tree_hpp

#include "BinarySearchTree.hpp"

class AvlTree : public SearchTree {
public:
    AvlTree() = default;
    ~AvlTree() = default;
    
    static AvlTree copy(Node* tree);
    
    AvlTree& operator = (const AvlTree& other) = default;
    
private:
    ///returns middle->left()
    Node* turnRight(Node* middle, Node* top = nullptr);
    ///returns middle->right()
    Node* turnLeft(Node* middle, Node* top = nullptr);
    ///returns middle->right()->left()
    Node* doubleTurnRightLeft(Node* middle, Node* top = nullptr);
    ///returns middle->left()->right()
    Node* doubleTurnLeftRight(Node* middle, Node* top = nullptr);
    
    void doBalance(Node*& root, Node* nodeSide, bool& isFixed, int& currentBalance);
    
    Node* m_add(Node* root, const int value) override;
};

#endif /* AVL_Tree_hpp */
