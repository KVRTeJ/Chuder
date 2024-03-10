#ifndef Binary_Tree_hpp
#define Binary_Tree_hpp

#include <iostream>
#include <vector>

class BinaryTree {
public:
    class Node;
public:
    BinaryTree(const int key = 0, const int count = 0) {
        for(int i = 0; i < key; ++i) {
            this->add(key);
        }
    }
    BinaryTree(const BinaryTree& other);//TODO: todo
    ~BinaryTree() = default;//TODO: todo
    
    int height() const;//TODO: todo
    int nodeCount() const;//TODO: todo
    int max() const;//TODO: todo
    int min() const;//TODO: todo
    int level(const int key) const;//TODO: todo
    Node* root() const {return m_root;}
    
    void clear();//TODO: todo
    void clearFrom(const Node*);//TODO: todo
    
    bool empty() const {return m_root == nullptr;}
    bool balance() const;//TODO: todo
    bool contains(const int key) const {return find(key) != nullptr;}
    
    void add(const int key);
    bool remove(const int key);//TODO: todo
    BinaryTree copy(const Node* other);//TODO: todo
    /// NLR - processing
    Node* find(Node* start, const int key) const;
    /// BFS - priccessing
    Node* find(const int key) const;
    
    /// BFS - proccessing
    std::vector<int> toVector() const;
    std::vector<int> toVectorNlr() const;
    
    void printLeafs(Node* root) const;
    void printHorizontal(Node *root, int marginLeft = 2, int levelSpacing = 4) const;
    
    BinaryTree& operator = (const BinaryTree& other);//TODO: todo
private:
    void toVectorNlr(Node* root, std::vector<int>& nums) const;
    
    Node* add(Node* root, const int value);
    
    Node* findParent(Node* root, Node* child);
    
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

#endif /* Binary_Tree_hpp */
