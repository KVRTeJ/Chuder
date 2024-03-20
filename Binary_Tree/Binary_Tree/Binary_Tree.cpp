#include <stack>
#include <random>
#include <algorithm>

#include "Binary_Tree.hpp"

namespace {
    
    struct Data {
        BinaryTree::Node* target = nullptr;
        BinaryTree::Node* nodeParent = nullptr;
        BinaryTree::Node* replacementNode = nullptr;
    };
    
}

BinaryTree::BinaryTree(const BinaryTree& other) {
    auto temp = copy(other.m_root);
    std::swap(m_root, temp.m_root);
}

void BinaryTree::clear() {
    clearFromInclusiveRoot(m_root);
}

int BinaryTree::nodeCount(Node* root) const {
    if(!root) {
        return {};
    }
    
    int result = 0;
    
    std::stack<Node* > unprocessedNodes;
    unprocessedNodes.push(root);
    
    Node* current = nullptr;
    while(!unprocessedNodes.empty()) {
        current = unprocessedNodes.top();
        unprocessedNodes.pop();
        
        result++;
        
        if(current->left()) {
            unprocessedNodes.push(current->left());
        }
        if(current->right()) {
            unprocessedNodes.push(current->right());
        }
        
    }
    
    return result;
}

int BinaryTree::max() const {
    if(!m_root) {
        return {};
    }
    
    int buffer = m_root->key();
    max(m_root, buffer);
    
    return buffer;
}

int BinaryTree::min() const {
    if(!m_root) {
        return {};
    }
    
    int buffer = m_root->key();
    min(m_root, buffer);
    
    return buffer;
}

int BinaryTree::height() const {
    return height(m_root);
}

int BinaryTree::height(Node* root, int currentHeight, int maxHeight) const {
    if(!root) {
        return maxHeight;
    }
    
    ++currentHeight;
    
    if(currentHeight > maxHeight) {
        maxHeight = currentHeight;
    }
    
    int leftSubTree = height(root->left(), currentHeight, maxHeight);
    int rightSubTree = height(root->right(), currentHeight, maxHeight);
    
    return std::max(leftSubTree, rightSubTree);
};

int BinaryTree::level(const int key) const {
    
    Node* target = find(key);
    if(!target) {
        return -1;
    }
    
    return level(m_root, target);
    
}

int BinaryTree::level(Node* root, Node* target, int currentLevel) const {
    if(!root) {
        return -1;
    }
    
    ++currentLevel;
    
    if(root == target) {
        return currentLevel;
    }
    
    int leftSubTree = level(root->left(), target, currentLevel);
    if(leftSubTree == -1) {
        int rightSubTree = level(root->right(), target, currentLevel);
        return rightSubTree;
    }
    
    return leftSubTree;
}

int BinaryTree::level(const Node* root, const Node* target, int currentLevel) const {
    return level(const_cast<Node* >(root), const_cast<Node* >(target), currentLevel);
}

int BinaryTree::maxLevel() const {
    if(!m_root) {
        return 0;
    }
    
    int result = 1;
    
    for(auto l = levelNodes(m_root, result); !l.empty(); ++result, l = levelNodes(m_root, result));
    
    return result - 1;
}

BinaryTree::Iterator BinaryTree::begin() {return Iterator(this, m_root);}
BinaryTree::Iterator BinaryTree::end() {return Iterator(this, nullptr);}

BinaryTree::ConstIterator BinaryTree::begin() const {return ConstIterator(this, m_root);}
BinaryTree::ConstIterator BinaryTree::end() const {return ConstIterator(this, nullptr);}

void BinaryTree::clearFrom(Node* root) {
    if(!root) {
        return;
    }
    
    clearFromInclusiveRoot(root->left());
    clearFromInclusiveRoot(root->right());
}

void BinaryTree::clearFromInclusiveRoot(Node* root) {
    if(!root) {
        return;
    }
    
    clearFrom(root->left());
    clearFrom(root->right());
    delete root;
}

bool BinaryTree::balanced() const {
    return balanced(m_root);
}

bool BinaryTree::balanced(Node* root) const {
    if(!root) {
        return true;
    }
    
    int leftSubTreeHeight = height(root->left());
    int rightSubTreeHeight = height(root->right());
    
    int heightDifference = leftSubTreeHeight - rightSubTreeHeight;
    bool isBalance = !heightDifference || heightDifference == 1 || heightDifference == -1;
    
    return isBalance && balanced(root->left()) && balanced(root->right());
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
    
    auto finishRemove {
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
            finishRemove(data);
            
        } else if(!data.target->left()) {
            data.replacementNode = data.target->right();
            finishRemove(data);
        } else if(!data.target->right()) {
            data.replacementNode = data.target->left();
            finishRemove(data);
            
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
            finishRemove(data);
        }
    }
    
    return true;
}

BinaryTree BinaryTree::copy(Node* root) const {
    if(!root) {
        return {};
    }
        
    BinaryTree newTree;
    newTree.m_root = new Node(root->key());
    
    std::list<Node*> unprocessedNodes;
    std::list<Node*> unprocessedNodesThis;
    unprocessedNodes.push_back(root);
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


BinaryTree::Node* BinaryTree::find(Node* root, Node* target) const {
    if(!root || root == target) {
        return root;
    }
    
    Node* subTreeFindResult = find(root->left(), target);
    if(!subTreeFindResult) {
        subTreeFindResult = find(root->right(), target);
    }
    
    return subTreeFindResult;
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

std::vector<int> BinaryTree::toVector() const {
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

void BinaryTree::printLevels() const {
    
    int current = {};
    for(auto it = begin(); it != end();) {
        if(current != it.getLevel()) {
            std::cout << '\n';
            current = it.getLevel();
            std::cout << "Level " << current << '|' << ' ';
        }
        std::cout << (*it)->key() << (++it == end() ? "" : ", ");
    }
    
    std::cout << std::endl;
}

BinaryTree& BinaryTree::operator = (const BinaryTree& other) {
    
    if(m_root != other.m_root) {
        clear();
        
        auto temp = copy(other.m_root);
        std::swap(m_root, temp.m_root);
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

void BinaryTree::max(Node* root, int& buffer) const {
    if(!root) {
        return;
    }
    
    if(root->key() > buffer) {
        buffer = root->key();
    }
    
    max(root->left(), buffer);
    max(root->right(), buffer);
}

void BinaryTree::min(Node* root, int& buffer) const {
    if(!root) {
        return;
    }
    
    if(root->key() < buffer) {
        buffer = root->key();
    }
    
    min(root->left(), buffer);
    min(root->right(), buffer);
}
