#ifndef BinarySearchTree_hpp
#define BinarySearchTree_hpp

#include "Binary_Tree.hpp"

class SearchTree : public BinaryTree {
public:
    template <typename NodeType, typename TreeType>
    class lnrTemplateIterator; //TODO: implement me
    using lnrConstIterator = lnrTemplateIterator<const Node, const SearchTree>;
    
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
    
    void removeIfBothChildren(removeData& data) override;
    
private:
    Node* add(Node* root, const int value) override;
    
};

template <typename NodeType, typename TreeType>
class SearchTree::lnrTemplateIterator : public IIterator<NodeType, TreeType> {
public:
    lnrTemplateIterator(TreeType* tree, NodeType* node)
    : m_tree(tree), m_currentNode(node) {
        updatePrevNode();
        updateNextNode();
    }
    
    ~lnrTemplateIterator() override = default;
    
    bool isValid() const override {return m_currentNode != nullptr;}//TODO: check prevNode nextNode
    
    NodeType* operator * () {return m_currentNode;}
    
    lnrTemplateIterator& operator ++ () {
        if(!m_nextNode)
            return *this;
        
        std::swap(m_currentNode, m_prevNode);
        m_currentNode = m_nextNode;
        updateNextNode();
        if(m_currentNode->key() > m_nextNode->key())
            m_nextNode = nullptr;
        return *this;
    }
    lnrTemplateIterator operator ++ (int) const;
    
    lnrTemplateIterator& operator -- () {
        
    }
    lnrTemplateIterator operator -- (int) const {
        
    }
    
    bool operator == (const lnrTemplateIterator& other) const {return m_currentNode == other.m_currentNode;}
    bool operator != (const lnrTemplateIterator& other) const {return !(this->operator==(other));}
    
private:
    void updatePrevNode() {
        m_prevNode = (m_currentNode->left()
                      ? m_tree->find(m_tree->BinaryTree::max(m_currentNode->left()))
                      : nullptr);
    }
    
    void updateNextNode() {
        if(m_currentNode->right()) {
            m_nextNode = m_tree->find(m_tree->BinaryTree::min(m_currentNode->right()));
            return;
        }
        m_nextNode = m_tree->findParent(m_tree->root(), m_currentNode);
        
        if(m_nextNode == m_tree->root()) {
            m_nextNode = m_tree->find(m_tree->BinaryTree::min(m_currentNode->right()));
            //return;
        }
        
        
        else if(m_nextNode == m_prevNode) {
            m_nextNode = m_tree->findParent(m_tree->root(), m_nextNode);
        }
         
    }
private:
    TreeType* m_tree = nullptr;
    
    NodeType* m_prevNode = nullptr;
    NodeType* m_currentNode = nullptr;
    NodeType* m_nextNode = nullptr;
    
};

#endif /* BinarySearchTree_hpp */
