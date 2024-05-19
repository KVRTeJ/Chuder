#include <list>
#include <assert.h>

#include "HuffmanTree.hpp"

namespace {
    void addToList(std::list<HuffmanTree::Node*>& nodes, const char value) {
        if(!nodes.empty()) {
            for(auto it = nodes.begin(); it != nodes.end(); ++it) {
                if((*it)->contains(value)) {
                    (*it)++;
                    return;
                }
            }
        }
        
        nodes.push_back(new HuffmanTree::Node(std::string(1, value)));
        return;
    }
};

void HuffmanTree::build(const std::string& text) {
    std::list<Node*> nodes;
    for(int i = 0; i != text.size(); ++i) {
        addToList(nodes, text[i]);
    }
    assert(false);
}

bool HuffmanTree::Node::contains(const char symbol) const {
    for(int i = 0; i != m_data.size(); ++i) {
        if(symbol == m_data[i]) {
            return true;
        }
    }
    
    return false;
}
