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
    
    void sort(std::list<HuffmanTree::Node*>& nodes) {
        for(auto it = nodes.begin(); it != nodes.end(); it++) //TODO: PLEASE TAKE AWAY THIS SHAME
            for(auto jt = nodes.begin(); jt != nodes.end(); jt++)
                if((*it)->frequency() < (*jt)->frequency())
                    std::swap(*it, *jt);
    }
    
    void add(std::list<HuffmanTree::Node*>& nodes, HuffmanTree::Node* node) {
        auto it = nodes.begin(), jt = ++nodes.begin();
        for(; jt != nodes.end(); it = jt, ++jt) {
            std::cout << "node - " << node->frequency() << " it - " << (*it)->frequency() << " jt - " << (*jt)->frequency() << std::endl;
            if((*it)->frequency() <= node->frequency() && node->frequency() < (*jt)->frequency()) {
                break;
            }
        }
        
        nodes.insert(jt, node);
    }
};

void HuffmanTree::build(const std::string& text) {
    std::list<Node*> nodes;
    
    for(int i = 0; i != text.size(); ++i) {
        pushBack(nodes, text[i]);
    }
    sort(nodes);
    
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
        add(nodes, parent); //FIXME: fixmeeeee
        
        
        first = *(nodes.begin());
        --currentSize;
        if(currentSize < 1) {
            break;
        }
        second = *(++nodes.begin());
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
