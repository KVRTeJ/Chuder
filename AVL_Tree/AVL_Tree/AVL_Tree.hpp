#ifndef AVL_Tree_hpp
#define AVL_Tree_hpp

#include "BinarySearchTree.hpp"

class AvlTree : public SearchTree {
    using BinaryTree::findParent;
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
    
    void doBalance(Node*& root, Node* nodeSide);
    bool doBalanceRemove(Node*& root);
    
    Node* m_add(Node* root, const int value) override;
    
    RemoveData* allocateRemoveData() override;
    
    class RemoveDataAvl;
    void m_finishRemove(RemoveData* data) override;
    Node* findReplaсementNodeParent(RemoveData* data) override;
    
private:
    bool isFixed = false;
};

class AvlTree::RemoveDataAvl : public RemoveData {
public:
    RemoveDataAvl() = default;
    ~RemoveDataAvl() = default;
    
    std::list<BinaryTree::Node* >& way() override {return m_way;}
    bool& wasLeft() override {return m_wasLeft;}
    
private:
    std::list<BinaryTree::Node* > m_way = {};
    bool m_wasLeft = false;
};

#endif /* AVL_Tree_hpp */
