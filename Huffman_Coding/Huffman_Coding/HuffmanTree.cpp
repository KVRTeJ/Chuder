#include <list>
#include <assert.h>
#include <algorithm>

#include "HuffmanTree.hpp"

namespace {
    void pushBack(std::list<HuffmanTree::Node*>& nodes, const char value) {
        if(!nodes.empty()) {
            for(auto it = nodes.begin(); it != nodes.end(); ++it) {
                if((*it)->contains(value)) {
                    (*it)->incrementFrequency();
                    return;
                }
            }
        }
        
        nodes.push_back(new HuffmanTree::Node(std::string(1, value)));
        return;
    }
    
    auto min(const std::list<HuffmanTree::Node*>::iterator& start, const std::list<HuffmanTree::Node*>::iterator& stop) {
        auto min = start;
        for(auto it = start; it != stop; ++it) {
            if((*it)->frequency() < (*min)->frequency()) {
                min = it;
            }
        }
        
        return min;
    }
    void sort(std::list<HuffmanTree::Node*>& nodes) { //TODO: ITS BETTER THAT BUBBLE SORT
        for(auto it = nodes.begin(); it != nodes.end(); ++it) {
            std::swap(*it, *min(it, nodes.end()));
        }
    }
    
    void add(std::list<HuffmanTree::Node*>& nodes, HuffmanTree::Node* node) {
        auto it = nodes.begin(), jt = ++nodes.begin();
        for(; jt != nodes.end(); it = jt, ++jt) {
            if((*it)->frequency() <= node->frequency() && node->frequency() < (*jt)->frequency()) {
                break;
            }
        }
        
        nodes.insert(jt, node);
    }
    
    void print(const std::list<HuffmanTree::Node*>& nodes) {
        std::cout << '[';
        for(auto it = nodes.begin(); it != nodes.end();) {
            std::cout << (*it)->data() << (++it == nodes.end()
                                           ? ""
                                           : ", ");
        }
        std::cout << ']' << std::endl;
    }
};

void HuffmanTree::clear(Node* current) {
    if(!current) {
        return;
    }
    
    clear(current->left());
    clear(current->right());
    delete current;
}

void HuffmanTree::build(const std::string& inputFileName) {
    std::list<Node*> nodes;
    
    
    std::ifstream input(inputFileName, std::ios_base::binary);
    if(!input.is_open()) {
        std::cerr << "HuffmanTree::build(const std::string& inputFileName):error opening file. . ." << std::endl;
        return;
    }
    
    char buffer = {};
    while(input >> std::noskipws >> buffer) {
        std::cout << "current - " << buffer << std::endl;
        pushBack(nodes, buffer);
    }
    
    print(nodes);
    sort(nodes);
    print(nodes);
    int currentSize = static_cast<int>(nodes.size());
    auto first = *(nodes.begin());
    auto second = *(++nodes.begin());
    Node* parent = nullptr;
    while(currentSize > 1) {
        nodes.pop_front();
        nodes.pop_front();
        
        parent = new Node(first->data() + second->data(), first->frequency() + second->frequency());
        parent->setLeft(first);
        parent->setRight(second);
        add(nodes, parent);
        
        
        first = *(nodes.begin());
        --currentSize;
        if(currentSize < 1) {
            break;
        }
        second = *(++nodes.begin());
    }
    m_root = first;
}

int HuffmanTree::encode(const std::string& inputFileName, std::string& outputFileName) {
    if(!m_root) {
        build(inputFileName);
    }
    
    //TODO: create the type point to file and to arguments in methdot
    int compressionRatio = -1; //TODO: IMPLEMENT ME
    doCoding(m_root, outputFileName);
    
    return compressionRatio;
}

bool HuffmanTree::decode(const std::string& inputFileName, std::string& outpuFileName) {
    if(inputFileName.empty()) {
        return false;
    }
    
    //TODO: also as in encode
    int pos = 0;
    doDeCoding(m_root, inputFileName, pos, outpuFileName);
    
    return false;
}

void HuffmanTree::printHorizontal(Node *root, int marginLeft, int levelSpacing) const {
    
    if (root == nullptr) {
        return;
    }
    
    printHorizontal(root->right(), marginLeft + levelSpacing, levelSpacing);
    std::cout << std::string(marginLeft, ' ') << root->data() << std::endl;
    printHorizontal(root->left(), marginLeft + levelSpacing, levelSpacing);
}

void HuffmanTree::printHorizontalUnicode(Node* root, const std::string& prefix, bool isLeft) const {
    if(!root) {
        return;
    }
    
    std::cout << prefix;
    
    std::cout << (isLeft ? "├──" : "└──" );
    
    std::cout << root->data() << std::endl;
    
    printHorizontalUnicode(root->left(), prefix + (isLeft ? "│   " : "    "), true);
    printHorizontalUnicode(root->right(), prefix + (isLeft ? "│   " : "    "), false);
}

void HuffmanTree::doCoding(Node* current, std::string& encoded) const {
    if(!current) {
        return;
    }
    
    if(current->left()) {
        encoded += '0';
        doCoding(current->left(), encoded);
    }
    if(current->right()) {
        encoded += '1';
        doCoding(current->right(), encoded += '1');
    }
    //result += ' ';
}

void HuffmanTree::doDeCoding(Node* current, const std::string& encoded, int& pos, std::string& decoded) const {
    if(!current) {
        return;
    }
    
    if(encoded[pos] == '0' && current->left()) {
        doDeCoding(current->left(), encoded, ++pos, decoded);
    }
    if(encoded[pos] == '1' && current->right()) {
        doDeCoding(current->right(), encoded, ++pos, decoded);
    }
    decoded = current->data();
}

bool HuffmanTree::Node::contains(const char symbol) const {
    for(int i = 0; i != m_data.size(); ++i) {
        if(symbol == m_data[i]) {
            return true;
        }
    }
    
    return false;
}
