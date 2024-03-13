#ifndef Binary_Tree_hpp
#define Binary_Tree_hpp

#include <iostream>
#include <vector>
#include <list>
#include <assert.h>

class BinaryTree {
public:
    class Node;
    
    class TemplateIterator;
    
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
    ///returns std::list<Node*>
    std::list<Node*> levelNodes(const int level) const;
    int maxLevel() const;
    Node* root() const {return m_root;}
    
    //TemplateIterator begin() {return TemplateIterator(this, m_root);}
    //TemplateIterator end() {return TemplateIterator(this, nullptr);}
    
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
    
    void compareBinaryTreeGreater(Node* root, int& buffer) const;
    void compareBinaryTreeLess(Node* root, int& buffer) const;
    
private:
    Node* m_root = nullptr;
    
};

class BinaryTree::Node {
    friend class BinaryTree;
public:
    Node(const int key = 0, Node* left = nullptr, Node* right = nullptr)
    : m_key(key), m_left(left), m_right(right)
    {}
    
    int key() const {return (this ? m_key : 0);}
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

class BinaryTree::TemplateIterator {
    friend class BinaryTree;
public:
    TemplateIterator(BinaryTree* tree, Node* node) {
        assert(static_cast<bool>(tree));
        m_tree = tree;
        m_node = node;
        
        if(!node) {
            m_level = tree->maxLevel() + 1;
        } else {
            m_level = tree->level(tree->root(), m_node);
            update(m_level);
        }
    }
    
    ~TemplateIterator() = default;
    
    bool isValid() const {return m_node != nullptr;}
    
    Node* operator * () {return *m_iter;}
    
    TemplateIterator& operator ++ ();
    TemplateIterator operator ++ (int);//TODO: todo
    
    TemplateIterator& operator -- ();
    TemplateIterator operator -- (int);//TODO: todo
    
    auto operator <=> (const TemplateIterator other) {return m_node <=> other.m_node;}
    
private:
    void update(const int newLevel);
    
private:
    BinaryTree* m_tree = {};
    Node* m_node = nullptr;
    std::list<Node* > m_levelNodes = {};
    std::list<Node* >::iterator m_iter = {};
    int m_level = 0;
};

#endif /* Binary_Tree_hpp */
