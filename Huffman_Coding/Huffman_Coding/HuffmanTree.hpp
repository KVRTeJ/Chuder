#ifndef HuffmanTree_hpp
#define HuffmanTree_hpp

#include <iostream>

class HuffmanTree {
public:
    class Node;
public:
    HuffmanTree() = default;
    ~HuffmanTree() = default;
    
private:
    Node* m_root = nullptr;
};

class HuffmanTree::Node {
public:
    explicit Node(std::string symbols)
    {
        throw std::runtime_error("IMPLEMENT ME");
    }
    ~Node() = default;
    
private:
    std::string m_data = {};
    Node* m_left = nullptr;
    Node* m_right = nullptr;
};

#endif /* HuffmanTree_hpp */
