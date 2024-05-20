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

void HuffmanTree::build(const std::string& text) {
    std::list<Node*> nodes;
    
    for(int i = 0; i != text.size(); ++i) {
        pushBack(nodes, text[i]);
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

int HuffmanTree::encode(const std::string& text, std::string& encoded) {
    if(!m_root) {
        build(text);
    }
    
    int compressionRatio = -1; //TODO: IMPLEMENT ME
    doCoding(m_root, encoded);
    
    return compressionRatio;
}

bool HuffmanTree::decode(const std::string& encoded, std::string& decoded) {
    if(encoded.empty()) {
        return false;
    }
    
    int pos = 0;
    doDeCoding(m_root, encoded, pos, decoded);
    
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
