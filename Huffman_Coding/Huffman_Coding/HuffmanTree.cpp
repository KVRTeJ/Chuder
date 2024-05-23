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
    
    void addToFile(std::ofstream* file, const Set& set) {
        //std::ofstream file(fileName, std::ios_base::app);
        for(int i = 0; i < Set::MAX_CARDINALIS; ++i) {
            if(set.contains(i)) {
                (*file) << static_cast<char>(i);
            }
        }
        
        //file.close();
    }
    
    int bytes(const std::string& fileName) {
        std::ifstream file(fileName);
        int result = 0;
        
        while(!file.eof()) {
            file.get();
            ++result;
        }
        --result;
        
        file.close();
        return result;
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
        
        parent = new Node(first->data() | second->data(), first->frequency() + second->frequency());
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
    
    input.close();
}

int HuffmanTree::encode(const std::string& inputFileName, std::string& outputFileName) {
    if(!m_root) {
        build(inputFileName);
    }
    
    std::ofstream output(outputFileName);
    
    BoolVector encoded(0, 0);
    
    std::ifstream input(inputFileName);
    
    char current = {};
    while(input >> std::noskipws >> current) {
        doCoding(m_root, BoolVector(0,0), encoded, current);
    }
    if(encoded.lenth() == 0) {
        for(int i = 0; i < m_root->frequency(); ++i) {
        encoded += true;
            
    }
    std::cout << "encoded - ";
    encoded.print();
    uint8_t* coded = encoded.cells();
    output << encoded.unsignificantRankCount();
    for(int i = 0; i < encoded.cellCount(); ++i) {
        output << coded[i];
    }
    
    output.close();
    //TODO: считать когда записываются биты, а исходник сложить все повторения у списка
    //TODO: optimize me vvvvvv
    return static_cast<float>(bytes(outputFileName) - 1 - ((1 - encoded.unsignificantRankCount()) / 8)) / static_cast<float>(bytes(inputFileName)) * 100;;
}

bool HuffmanTree::decode(const std::string& inputFileName, std::string& outpuFileName) {
    if(inputFileName.empty()) {
        return false;
    }
    
    std::ifstream input(inputFileName);
    
    BoolVector code(0, 0);
    int unsignificantRankCount = 0;
    input >> unsignificantRankCount;
    
    {
        char current;
        while(input >> std::noskipws >> current) {
            code.add(current);
        }
    }
    code.setUnsignificantRankCount(unsignificantRankCount);
    
    std::ofstream* output = new std::ofstream(outpuFileName);
    int pos = 0;
    Node* current = m_root;
    while(pos <= code.lenth()) {
        if(!current->left() && !current->right()) {
            addToFile(output, current->data());
            current = m_root;
        }
        
        if(pos == code.lenth()) 
            break;
        if(code[pos] == false)
            current = current->left();
        else
            current = current->right();
        ++pos;
    }
    
    output->close();
    delete output;
    input.close();
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

void HuffmanTree::doCoding(Node* current, BoolVector currentCode, BoolVector& encoded, char symbol) const {
    if(!current) {
        return;
    }
    
    if(!current->left() && !current->right()) {
        encoded += currentCode;
    }
    if(current->left() && current->left()->contains(symbol)) {
        doCoding(current->left(), currentCode + false, encoded, symbol);
    }
    else if(current->right() && current->right()->contains(symbol)) {
        doCoding(current->right(), currentCode + true, encoded, symbol);
    }
}
