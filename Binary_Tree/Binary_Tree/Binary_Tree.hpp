#ifndef Binary_Tree_hpp
#define Binary_Tree_hpp

#include <iostream>
#include <vector>

class BinaryTree {
public:
    class Node;
public:
    BinaryTree();//TODO: todo
    BinaryTree(const BinaryTree& other);//TODO: todo
    ~BinaryTree();//TODO: todo
    
    int height() const;//TODO: todo
    int nodeCount() const;//TODO: todo
    int max() const;//TODO: todo
    int min() const;//TODO: todo
    int level(const int key) const;//TODO: todo
    Node* root() const {return m_root;};
    
    void clear();//TODO: todo
    void clearFrom(const Node*);//TODO: todo
    
    bool isEmpty() const {return m_root == nullptr;};//TODO: todo
    bool isBalance() const;//TODO: todo
    
    void add(const int value);//TODO: todo
    void remove(const int value);//TODO: todo
    BinaryTree copy(const Node* other);//TODO: todo
    Node* find(const int key) const;//TODO: todo
    
    std::vector<int> toVector() const;//TODO: todo
    
    void printSheets() const;//TODO: todo
    
    BinaryTree& operator = (const BinaryTree& other);//TODO: todo
private:
    void add(Node* root, const int value);//TODO: todo
    
private:
    Node* m_root = nullptr;
    
};

class BinaryTree::Node {
    friend BinaryTree;
public:
    Node(const int key = 0, Node* left = nullptr, Node* right = nullptr);//TODO: todo
    int getKey() const {return m_key;}
    void setKey(const int key) {m_key = key;};
    Node* left() const {return m_left;};
    Node* right() const {return m_right;};
    
private:
    void setLeft(Node* other) {m_left = other;}
    void setRight(Node* other) {m_right = other;}
    
private:
    int m_key = 0;
    Node* m_left = nullptr;
    Node* m_right = nullptr;
};

#endif /* Binary_Tree_hpp */
