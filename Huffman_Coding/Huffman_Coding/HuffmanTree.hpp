#ifndef HuffmanTree_hpp
#define HuffmanTree_hpp

#include "BoolVector.hpp"

class HuffmanTree {
public:
    class Node;
public:
    HuffmanTree() = default;
    ~HuffmanTree() = default;
    
    void build(const std::string& text);
    ///returns compression ratio in percent
    int encode(const std::string& text, std::string& result) const; //TODO: to filename
    bool decode(const std::string& text, std::string& result) const; //TODO: to filename
    
private:
    Node* m_root = nullptr;
};

class HuffmanTree::Node {
public:
    explicit Node(std::string symbols)
    {
        add(symbols);
    }
    ~Node() = default;
    
    bool contains(const char symbol) const;
    void add(const std::string& data) {m_data += data;}
    
    int frequency() const {return m_frequency;}
    Node* left() const {return m_left;}
    Node* right() const {return m_right;}
    
    void setFrequency(const int value) {m_frequency = value;}
    void setLeft(Node* node) {m_left = node;}
    void setRight(Node* node) {m_right = node;}
    
    Node& operator++() {
        ++m_frequency; return *this;
    }
    Node operator++(int) {
        auto old = *this;
        ++m_frequency;
        return old;
    }
    
private:
    std::string m_data = {};//TODO: to BoolVector
    int m_frequency = 1;
    Node* m_left = nullptr;
    Node* m_right = nullptr;
};

#endif /* HuffmanTree_hpp */
