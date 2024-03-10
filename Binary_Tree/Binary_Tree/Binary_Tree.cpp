#include <list>
#include <stack>
#include <random>

#include "Binary_Tree.hpp"

namespace {

struct Data {
    BinaryTree::Node* target = nullptr;
    BinaryTree::Node* nodeParent = nullptr;
    BinaryTree::Node* replacementNode = nullptr;
};

}

BinaryTree::BinaryTree(const BinaryTree& other) {
    m_root = copy(other.m_root).m_root;
}

void BinaryTree::clear() {
    clearFrom(m_root);
    
    delete m_root;
    m_root = nullptr;
}

void BinaryTree::clearFrom(Node* root) {
    if(!root) {
        return;
    }
    
    std::vector<Node* > leafs = getLeafs(root);
    while(leafs[0] != root) {
        for(auto it = leafs.begin(); it != leafs.end(); ++it) {
            remove(*it);
        }
        leafs = getLeafs(root);
    }
}


void BinaryTree::add(const int key) {
    
    if(m_root) {
        add(m_root, key);
    } else {
        m_root = new Node(key);
    }
    
}

bool BinaryTree::remove(Node* node) {
    Data data = {};
    
    data.target = node;
    if(!data.target) {
        return false;
    }
    
    data.nodeParent = findParent(m_root, data.target);
    
    auto deleteChild {
        [this](Data& data) {
            if(data.nodeParent->left() == data.target) {
                data.nodeParent->setLeft(nullptr);
                delete data.target;
                if(data.replacementNode)
                    data.nodeParent->setLeft(data.replacementNode);
            } else {
                data.nodeParent->setRight(nullptr);
                delete data.target;
                if(data.replacementNode)
                    data.nodeParent->setRight(data.replacementNode);
            }
        }
    };
    
    if(data.nodeParent == data.target) {
        clear();
    } else {
        if(data.target->left() == nullptr && data.target->right() == nullptr) {
            deleteChild(data);
            
        } else if(!data.target->left()) {
            data.replacementNode = data.target->right();
            deleteChild(data);
        } else if(!data.target->right()) {
            data.replacementNode = data.target->left();
            deleteChild(data);
            
        } else {
            data.replacementNode = findParent(data.target, nullptr);
            Node* leafParent = findParent(data.target, data.replacementNode);
            if(leafParent->left() == data.replacementNode) {
                leafParent->setLeft(nullptr);
            } else {
                leafParent->setRight(nullptr);
            }
            data.replacementNode->setLeft(data.target->left());
            data.replacementNode->setRight(data.target->right());
            deleteChild(data);
        }
    }
    
    return true;
}

BinaryTree BinaryTree::copy(Node* other) const {
    if(!other) {
        return {};
    }
        
    BinaryTree newTree;
    newTree.m_root = new Node(other->key());
    
    std::list<Node*> unprocessedNodes;
    std::list<Node*> unprocessedNodesThis;
    unprocessedNodes.push_back(other);
    unprocessedNodesThis.push_back(newTree.m_root);
    Node* current = nullptr;
    Node* currentThis = nullptr;
    while(!unprocessedNodes.empty()) {
        current = unprocessedNodes.front();
        unprocessedNodes.pop_front();
        
        currentThis = unprocessedNodesThis.front();
        unprocessedNodesThis.pop_front();

        if(current->left()) {
            currentThis->setLeft(new Node(current->left()->key()));
            unprocessedNodes.push_back(current->left());
            unprocessedNodesThis.push_back(currentThis->left());
        }
        if(current->right()) {
            currentThis->setRight(new Node(current->right()->key()));
            unprocessedNodes.push_back(current->right());
            unprocessedNodesThis.push_back(currentThis->right());
        }
    }
    
    return newTree;
}

BinaryTree::Node* BinaryTree::find(Node* root, const int key) const {
    if(!root || root->key() == key) {
        return root;
    }
    
    Node* subTreeFindResult = find(root->left(), key);
    if(!subTreeFindResult) {
        subTreeFindResult = find(root->right(), key);
    }
    
    return subTreeFindResult;
}

BinaryTree::Node* BinaryTree::find(const int key) const {
    if(!m_root) {
        return m_root;
    }
    
    std::stack<Node*> unprocessedNodes;
    unprocessedNodes.push(m_root);
    
    Node* result = nullptr;
    while(!unprocessedNodes.empty()) {
        result = unprocessedNodes.top();
        unprocessedNodes.pop();
        
        if(result->key() == key) {
            return result;
        }
        
        if(result->left()) {
            unprocessedNodes.push(result->left());
        }
        if(result->right()) {
            unprocessedNodes.push(result->right());
        }
    }
    
    return nullptr;
}

std::vector<int> BinaryTree::toVector() const {
    if(!m_root) {
        return {};
    }
    
    std::vector<int> result;
    
    std::list<Node*> unprocessedNodes(1, m_root);
    Node* current = nullptr;
    while(!unprocessedNodes.empty()) {
        current = unprocessedNodes.front();
        unprocessedNodes.pop_front();
        result.push_back(current->key());
        if(current->left()) {
            unprocessedNodes.push_back(current->left());
        }
        if(current->right()) {
            unprocessedNodes.push_back(current->right());
        }
    }
    
    return result;
}

std::vector<int> BinaryTree::toVectorNlr() const {
    std::vector<int> result;
    
    toVectorNlr(m_root, result);
    
    return result;
}

std::vector<BinaryTree::Node* > BinaryTree::getLeafs(Node* root) const {
    if(!root) {
        return {};
    }
    
    std::vector<Node* > leafs;
    
    getLeafs(root, leafs);
    
    return leafs;
}

void BinaryTree::printLeafs(Node* root) const {
    std::vector<Node* > leafs = getLeafs(root);
    
    std::cout << '{';
    for(auto it = leafs.begin(); it != leafs.end(); ++it) {
        std::cout << (*it)->key() << ((it + 1) == leafs.end() ? "":", ");
    }
    std::cout << '}' << std::endl;
}

void BinaryTree::printHorizontal(Node *root, int marginLeft, int levelSpacing) const {
    
    if (root == nullptr) {
        return;
    }
    
    printHorizontal(root->right(), marginLeft + levelSpacing, levelSpacing);
    std::cout << std::string(marginLeft, ' ') << root->key() << std::endl;
    printHorizontal(root->left(), marginLeft + levelSpacing, levelSpacing);
}


BinaryTree& BinaryTree::operator = (const BinaryTree& other) {
    
    if(m_root != other.m_root) {
        clear();
        
        m_root = copy(other.m_root).m_root;
    }
    
        return *this;
}


/* private */

void BinaryTree::toVectorNlr(Node* root, std::vector<int>& nums) const {
    
    if(!root) {
        return;
    }
    
    nums.push_back(root->key());
    toVectorNlr(root->left(), nums);
    toVectorNlr(root->right(), nums);
}

void BinaryTree::getLeafs(Node* root, std::vector<Node* >& leafs) const {
    if(!root) {
        return;
    } else if(!root->left() && !root->right()) {
        leafs.push_back(root);
    } else {
        getLeafs(root->left(), leafs);
        getLeafs(root->right(), leafs);
    }
}

BinaryTree::Node* BinaryTree::add(Node* root, const int value) {

    if(!root) {
        root = new Node(value);
    } else if(rand() % 2) {
        root->setLeft(add(root->left(), value));
    } else {
        root->setRight(add(root->right(), value));
    }

    return root;
}

BinaryTree::Node* BinaryTree::findParent(Node* root, Node* child) {
    if(!root) {
        return nullptr;
    }
    
    std::stack<BinaryTree::Node*> unprocessedNodes;
    unprocessedNodes.push(root);
    Node* parent = nullptr;
    while(!unprocessedNodes.empty()) {
        parent = unprocessedNodes.top();
        unprocessedNodes.pop();
        
        if(parent == child) {
            return parent;
        }
        
        if(parent->left() == child) {
            if(child)
                return parent;
        } else if (parent->left()) {
            unprocessedNodes.push(parent->left());
        }
        
        if(parent->right() == child) {
            return parent;
        } else if(parent->right()) {
            unprocessedNodes.push(parent->right());
        }
    }
    
    return nullptr;
}

