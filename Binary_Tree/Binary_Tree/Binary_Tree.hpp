#ifndef Binary_Tree_hpp
#define Binary_Tree_hpp

#include <iostream>
#include <vector>
#include <list>
#include <assert.h>

class BinaryTree {
public:
    class Node;
    
    template <typename NodeType, typename TreeType>
    class TemplateIterator;
    using Iterator = TemplateIterator<Node, BinaryTree>;
    using ConstIterator = TemplateIterator<const Node, const BinaryTree>;
    
public:
    BinaryTree() = default;
    BinaryTree(const BinaryTree& other);
    ~BinaryTree() {clear();}
    
    int height() const;
    int height(Node* root, int currentHeight = 0, int maxHeight = 0) const;
    int nodeCount(Node* root) const;
    int max() const;
    int min() const;
    ///returns -1 if not found
    int level(const int key) const;
    int level(Node* root, Node* target, int currentLevel = 0) const;
    int level(const Node* root, const Node* target, int currentLevel = 0) const;
    ///returns std::list<Node*>
    std::list<Node*> levelNodes(const int level) const;
    int maxLevel() const;
    Node* root() {return m_root;}
    const Node* root() const {return m_root;}
    
    Iterator begin();
    Iterator end();
    
    ConstIterator begin() const;
    ConstIterator end() const;

    void clear();
    void clearFrom(Node* root);
    
    bool empty() const {return m_root == nullptr;}
    bool balance() const;
    bool balance(Node* root) const;
    bool contains(const int key) const {return find(key) != nullptr;}
    
    void add(const int key);
    BinaryTree copy(Node* root) const;
    bool remove(const int key) {return remove(find(key));}
    bool remove(Node* target);
    /// BFS - proccessing
    Node* find(const int key) const;
    /// NLR - processing
    Node* find(Node* start, Node* target) const;
    ///if child == nullptr -> return leaf
    Node* findParent(Node* root, Node* child);
    
    /// BFS - proccessing
    std::vector<int> toVector() const;
    std::vector<int> toVectorNlr() const;
    std::vector<Node* > getLeafs(Node* root) const;
    
    void printLeafs(Node* root) const;
    void printHorizontal(Node *root, int marginLeft = 2, int levelSpacing = 4) const;
    
    BinaryTree& operator = (const BinaryTree& other);
    
private:
    void toVectorNlr(Node* root, std::vector<int>& nums) const;
    
    void getLeafs(Node* root, std::vector<Node* >& leafs) const;
    
    Node* add(Node* root, const int value);
    
    void max(Node* root, int& buffer) const;
    void min(Node* root, int& buffer) const;
    
private:
    Node* m_root = nullptr;
    
};

class BinaryTree::Node {
    friend class BinaryTree;
public:
    Node(const int key = 0, Node* left = nullptr, Node* right = nullptr)
    : m_key(key), m_left(left), m_right(right)
    {}
    
    int key() const {return m_key;}
    Node* left() const {return m_left;}
    Node* right() const {return m_right;}
    
    void setKey(const int key) {m_key = key;}
    
private:
    void setLeft(Node* other) {m_left = other;}
    void setRight(Node* other) {m_right = other;}
    
private:
    int m_key = 0;
    Node* m_left = nullptr;
    Node* m_right = nullptr;
};

template <typename NodeType, typename TreeType>
class BinaryTree::TemplateIterator {
    friend class BinaryTree;
public:
    TemplateIterator(TreeType* tree, NodeType* node) {
        assert(static_cast<bool>(tree));
        m_tree = tree;
        
        if(!node) {
            m_level = tree->maxLevel() + 1;
        } else {
            m_level = tree->level(tree->root(), node);
        }
        
        update(m_level, node);
    }
    
    ~TemplateIterator() = default;
    
    bool isValid() const {
        for(auto it = m_levelNodes.begin(); it != m_levelNodes.end(); ++it) {
            if(it == m_iter)
                return true;
        }
        
        return false;
    }
    
    NodeType* operator * () {
        if(!isValid() || m_iter == m_levelNodes.end())
            return {};
        
        return *m_iter;
    }
    
    TemplateIterator& operator ++ () {
        if(m_level > m_tree->maxLevel()) {
            return *this;
        }
        
        if(m_iter == --m_levelNodes.end()) {
            ++m_level;
            m_levelNodes = m_tree->levelNodes(m_level);
            if(!m_levelNodes.empty()) {
                m_iter = m_levelNodes.begin();
            } else {
                m_iter = m_levelNodes.end();
            }
        } else {
            ++m_iter;
        }
        
        return *this;
    }
    
    TemplateIterator operator ++ (int) {
        auto buffer = *this;
        
        this->operator++();
        
        return buffer;
    }
    
    TemplateIterator& operator -- () {
        if(m_level < 0) {
            return *this;
        }
        
        if(m_iter == m_levelNodes.begin()) {
            --m_level;
            m_levelNodes = m_tree->levelNodes(m_level);
            if(!m_levelNodes.empty()) {
                m_iter = --m_levelNodes.end();
            } else {
                m_iter = m_levelNodes.begin();
            }
        } else {
            --m_iter;
        }
        
        return *this;
    }
    
    TemplateIterator operator -- (int)  {
        auto buffer = *this;
        
        this->operator--();
        
        return buffer;
    }
    
    bool operator == (const TemplateIterator& other) const {return *m_iter == (*other.m_iter);}
    bool operator != (const TemplateIterator& other) const {return !(this->operator==(other));}
    
private:
    void update(const int newLevel, NodeType* node) {
        m_levelNodes = m_tree->levelNodes(m_level);
        m_iter = m_levelNodes.begin();
        
        for(; m_iter != m_levelNodes.end(); ++m_iter) {
            if(*m_iter == node) {
                break;
            }
        }
        
    }
    
private:
    TreeType* m_tree = {};
    std::list<NodeType* > m_levelNodes = {};
    std::list<NodeType* >::iterator m_iter = {};
    int m_level = 0;
};

#endif /* Binary_Tree_hpp */
