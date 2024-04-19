#ifndef BinarySearchTree_hpp
#define BinarySearchTree_hpp

#include "Binary_Tree.hpp"

class SearchTree : public BinaryTree {
public:
    template <typename NodeType, typename TreeType>
    class lnrTemplateIterator;
    using lnrConstIterator = lnrTemplateIterator<const Node, const SearchTree>;
    using lnrIterator = lnrTemplateIterator<Node, SearchTree>;
    
public:
    SearchTree() = default;
    ~SearchTree() override = default;
    
    lnrIterator begin();
    lnrIterator end();
    
    lnrConstIterator begin() const;
    lnrConstIterator end() const;
    
    int level(const int key) const override;
    
    SearchTree copy(Node* tree);

    Node* find(const int key) const override;
    
    std::vector<int> toVectorAsc() const override;
    
    SearchTree& operator = (const SearchTree& other) = default;
    
protected:
    void m_max(Node* root, int& buffer) const override;
    void m_min(Node* root, int& buffer) const override;
    
    void m_removeIfBothChildren(m_removeData& data) override;
    
private:
    Node* m_add(Node* root, const int value) override;
    
};

template <typename NodeType, typename TreeType>
class SearchTree::lnrTemplateIterator : public IIterator<NodeType, TreeType> {
public:
    lnrTemplateIterator(TreeType* tree, NodeType* node)
    : m_tree(tree), m_currentNode(node) {
        m_updatePrevNode();
        m_updateNextNode();
    }
    
    ~lnrTemplateIterator() override = default;
    
    bool isValid() const override {
        bool isProspective = m_prevNode && m_nextNode;
        return isProspective || m_currentNode;
    }
    
    NodeType* operator * () {
        if(!m_currentNode) {
            Node empty = Node();
            Node* result = &empty;
            return result;
        }
        
        return m_currentNode;
    }
    
    lnrTemplateIterator& operator ++ () {
        if(!m_currentNode) {
            return *this;
        }
        if(!m_nextNode) {
            std::swap(m_currentNode, m_prevNode);
            m_currentNode = nullptr;
            return *this;
        }
            
        std::swap(m_currentNode, m_prevNode);
        m_currentNode = m_nextNode;
        m_updateNextNode();
        return *this;
    }
    
    lnrTemplateIterator operator ++ (int) {
        auto old = *this;
        this->operator++();
        return old;
    }
    
    lnrTemplateIterator& operator -- () {
        if(!m_prevNode)
            return *this;
        
        if(!m_currentNode) {
            m_currentNode = m_prevNode;
            m_updatePrevNode();
            return *this;
        }
        std::swap(m_currentNode, m_nextNode);
        std::swap(m_currentNode, m_prevNode);
        m_updatePrevNode();
        return *this;
    }
    
    lnrTemplateIterator operator -- (int) {
        auto old = *this;
        this->operator--();
        return old;
    }
    
    bool operator == (const lnrTemplateIterator& other) const {return m_currentNode == other.m_currentNode;}
    bool operator != (const lnrTemplateIterator& other) const {return !(this->operator==(other));}
    
private:
    void m_updatePrevNode() {
        if(!m_currentNode)
            return;
        
        if(m_currentNode->left()) {
            m_prevNode = m_tree->find(m_tree->max(m_currentNode->left()));
            return;
        }
        m_prevNode = m_tree->findParent(m_tree->root(), m_currentNode);
        
        if(m_prevNode == m_tree->root() && m_currentNode == m_tree->root()) {
            m_prevNode = m_tree->find(m_tree->max(m_currentNode->left()));
            return;
        }
        
        while(m_currentNode->key() < m_prevNode->key()) {
            m_prevNode = m_tree->findParent(m_tree->root(), m_prevNode);
            if(m_prevNode == m_tree->root()) {
                if(m_prevNode->key() > m_currentNode->key())
                    m_prevNode = nullptr;
                break;
            }
        }
        
    }
    
    void m_updateNextNode() {
        if(!m_currentNode)
            return;
        
        if(m_currentNode->right()) {
            m_nextNode = m_tree->find(m_tree->min(m_currentNode->right()));
            return;
        }
        m_nextNode = m_tree->findParent(m_tree->root(), m_currentNode);
        
        if(m_nextNode == m_tree->root() && m_currentNode == m_tree->root()) {
            m_nextNode = m_tree->find(m_tree->min(m_currentNode->right()));
            return;
        }
        
        while(m_currentNode->key() > m_nextNode->key()) {
            m_nextNode = m_tree->findParent(m_tree->root(), m_nextNode);
            if(m_nextNode == m_tree->root()) {
                if(m_nextNode->key() < m_currentNode->key())
                    m_nextNode = nullptr;
                break;
            }
        }
         
    }
private:
    TreeType* m_tree = nullptr;
    
    NodeType* m_prevNode = nullptr;
    NodeType* m_currentNode = nullptr;
    NodeType* m_nextNode = nullptr;
    
};

#endif /* BinarySearchTree_hpp */
