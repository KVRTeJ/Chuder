#ifndef AVL_Tree_hpp
#define AVL_Tree_hpp

#include "BinarySearchTree.hpp"

class AvlTree : public SearchTree {
public:
    AvlTree() = default;
    ~AvlTree() = default;
    
    AvlTree copy(Node* tree) const;
    
    AvlTree& operator = (const AvlTree& other) = default;
    
//private:
    bool turnRight(Node* middle, Node* top = nullptr);
    bool turnLeft(Node* middle, Node* top = nullptr);
    bool doubleTurnRightLeft(Node* middle, Node* top = nullptr);
    bool doubleTurnLeftRight(Node* middle, Node* top = nullptr);
    void doBalance(Node* root, Node* nodeSide, bool& isFixed, int& currentBalance);
    
    Node* m_add(Node* root, const int value) override;
};

#endif /* AVL_Tree_hpp */
