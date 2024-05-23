#ifndef HuffmanTree_hpp
#define HuffmanTree_hpp

#include <fstream>

#include "BoolVector.hpp"

class HuffmanTree {
public:
    class Node;
public:
    HuffmanTree() = default;
    ~HuffmanTree() {clear(m_root);}
    
    void clear(Node* current);
    
    Node* root() const {return m_root;}
    
    void build(const std::string& inputFileName);
    ///returns compression ratio in percent
    int encode(const std::string& inputFileName, std::string& outputFileName); //TODO: to filename
    bool decode(const std::string& encodedFileName, std::string& decodedFileName); //TODO: to filename
    
    void printHorizontal(Node *root, int marginLeft = 3, int levelSpacing = 5) const;
    void printHorizontalUnicode(Node* root, const std::string& prefix = "", bool isLeft = false) const;
    
private:
    void doCoding(Node* current, std::string& encoded) const;
    void doDeCoding(Node* current, const std::string& encoded, int& pos, std::string& decoded) const;
    
private:
    Node* m_root = nullptr;
};

class HuffmanTree::Node {
public:
    explicit Node(std::string symbols = "", int frequency = 1)
    : m_data(symbols), m_frequency(frequency)
    {}
    ~Node() = default;
    
    bool contains(const char symbol) const;
    void add(const std::string& data) {m_data += data;}
    
    std::string data() const {return m_data;}
    int frequency() const {return m_frequency;}
    Node* left() const {return m_left;}
    Node* right() const {return m_right;}
    
    void setData(const std::string& data) {m_data = data;}
    void setFrequency(const int value) {m_frequency = value;}
    void setLeft(Node* node) {m_left = node;}
    void setRight(Node* node) {m_right = node;}
    
    void incrementFrequency() {++m_frequency;}
    
private:
    std::string m_data = {};//TODO: to BoolVector
    int m_frequency = 1;
    Node* m_left = nullptr;
    Node* m_right = nullptr;
};

#endif /* HuffmanTree_hpp */
