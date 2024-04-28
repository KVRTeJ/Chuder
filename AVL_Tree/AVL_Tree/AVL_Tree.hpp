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
    void doBalanceRemove(Node*& root, bool& isFixed, int& currentBalance);
    
    Node* m_add(Node* root, const int value) override;
    
    m_removeData* allocateRemoveData() override;
    
    class m_removeDataAvl;
    void m_finishRemove(m_removeData* data) override;
    Node* findReplasementNodeParent(m_removeData* data) override;
};

class AvlTree::m_removeDataAvl : public m_removeData {
public:
    m_removeDataAvl() = default;
    ~m_removeDataAvl() = default;
    
    std::list<BinaryTree::Node* >& way() override {return m_way;}
private:
    std::list<BinaryTree::Node* > m_way = {};
};

#endif /* AVL_Tree_hpp */
