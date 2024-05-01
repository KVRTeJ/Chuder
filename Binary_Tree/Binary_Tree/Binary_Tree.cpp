#include <stack>
#include <queue>
#include <random>
#include <algorithm>

#include "Binary_Tree.hpp"

BinaryTree::BinaryTree(const BinaryTree& other) {
    auto temp = copy(other.m_root);
    std::swap(m_root, temp.m_root);
}

void BinaryTree::clear() {
    clearFrom(m_root);
    delete m_root;
    m_root = nullptr;
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

int BinaryTree::max(Node* root) const {
    if(!root) {
        return {};
    }
    
    int buffer = root->key();
    m_max(root, buffer);
    
    return buffer;
}

int BinaryTree::min(Node* root) const {
    if(!root) {
        return {};
    }
    
    int buffer = root->key();
    m_min(root, buffer);
    
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

std::list<BinaryTree::Node* > BinaryTree::way(Node* target) const {
    if(!target) {
        return {};
    }
    
    std::list<Node* > result;
    m_way(m_root, target, result);
    return result;
}

BinaryTree::bfsIterator BinaryTree::begin() {return bfsIterator(this, m_root);}
BinaryTree::bfsIterator BinaryTree::end() {return bfsIterator(this, nullptr);}

BinaryTree::bfsConstIterator BinaryTree::begin() const {return bfsConstIterator(this, m_root);}
BinaryTree::bfsConstIterator BinaryTree::end() const {return bfsConstIterator(this, nullptr);}

void BinaryTree::clearFrom(Node* root) {
    if(!root) {
        return;
    }
    
    if(root->left()) {
        m_clearFromInclusiveRoot(root->left());
        root->setLeft(nullptr);
    }
    if(root->right()) {
        m_clearFromInclusiveRoot(root->right());
        root->setRight(nullptr);
    }
}

bool BinaryTree::m_way(Node* root, Node* target, std::list<Node* >& result) const {
    if(!root) {
        return false;
    }
    
    result.push_back(root);
    
    if(root == target) {
        return true;
    } else {
        bool isFindLeft = m_way(root->left(), target, result);
        bool isFindRight = m_way(root->right(), target, result);
        if(isFindLeft || isFindRight) {
            return true;
        } else {
            result.pop_back();
            return false;
        }
    }
}

void BinaryTree::m_clearFromInclusiveRoot(Node* root) {
    if(!root) {
        return;
    }
    
    if(root->left()) {
        m_clearFromInclusiveRoot(root->left());
        root->setLeft(nullptr);
    }
    if(root->right()) {
        m_clearFromInclusiveRoot(root->right());
        root->setRight(nullptr);
    }
    delete root;
    root = nullptr;
}

bool BinaryTree::balanced() const {
    return balanced(m_root);
}

bool BinaryTree::balanced(Node* root) const {
    if(!root)
        return true;
    
    int heightDifference = balance(root);
    bool isBalance = !heightDifference || heightDifference == 1 || heightDifference == -1;
    
    return isBalance && balanced(root->left()) && balanced(root->right());
}

int BinaryTree::balance(Node* root) const {
    if(!root) {
        return 0;
    }
    
    int leftSubTreeHeight = height(root->left());
    int rightSubTreeHeight = height(root->right());
    
    int heightDifference = rightSubTreeHeight - leftSubTreeHeight;
    
    return heightDifference;
}

void BinaryTree::add(const int key) {
    
    if(m_root) {
        m_add(m_root, key);
    } else {
        m_root = new Node(key);
    }
    
}

bool BinaryTree::remove(Node* node) {
    RemoveData* data = allocateRemoveData();
    
    data->target = node;
    if(!data->target) {
        return false;
    }
    
    data->nodeParent = findParent(m_root, data->target);
    if(m_removeTrivialCase(data));
    else {
        m_removeIfBothChildren(data);
    }
    
    delete data;
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

const BinaryTree::Node* BinaryTree::findParent(const Node* root, const Node* child) const {
    if(!root) {
        return nullptr;
    }
    
    std::stack<const Node*> unprocessedNodes;
    unprocessedNodes.push(root);
    const Node* parent = nullptr;
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

BinaryTree::Node* BinaryTree::findParent(Node* root, Node* child) {
    return const_cast<Node*>(findParent(const_cast<const Node*>(root), const_cast<const Node*>(child)));
}

std::vector<int> BinaryTree::toVectorAsc() const {
    std::vector<int> result = toVectorLnr();
    
    std::sort(result.begin(), result.end());
    
    return result;
}

std::vector<int> BinaryTree::toVectorLnr() const {
    std::vector<int> result;
    
    m_toVectorLnr(m_root, result);
    
    return result;
}

std::vector<BinaryTree::Node* > BinaryTree::getLeafs(Node* root) const {
    if(!root) {
        return {};
    }
    
    std::vector<Node* > leafs;
    
    m_getLeafs(root, leafs);
    
    return leafs;
}

void BinaryTree::print(Node* root) const {
    if(!root) {
        root = m_root;
        if(!root) {
            return;
        }
    }
    
    auto setIndentation = [](const int count, const char symbol = ' ') {
        for (int i = 0; i < count; ++i)
            std::cout << symbol;
    };
    
    int height = this->height(root);
    std::queue<Node*> unprocessedNodes;
    unprocessedNodes.push(root);
    
    int levelNodes = 1;
    int level = 0;
    int maxLevelWidth = pow(2, height) - 1;
    
    while(!unprocessedNodes.empty() && level <= height) {
        int width = maxLevelWidth / pow(2, level);
        int padding = width / 2;
        setIndentation(padding);
        
        for(int i = 0; i < levelNodes; ++i) {
            Node* current = unprocessedNodes.front();
            unprocessedNodes.pop();
            if(current) {
                std::cout << "┌";
                setIndentation(padding, '-');
                
                std::cout << current->key() << (current->key() < 10 ? '-' : '\0');
                
                setIndentation(padding, '-');
                std::cout << "┐";
                
                unprocessedNodes.push(current->left());
                unprocessedNodes.push(current->right());
            } else {
                if(level >= height) {
                    return;
                }
                
                std::cout << "┌";
                setIndentation(padding, '-');
                std::cout << "xx";
                setIndentation(padding, '-');
                std::cout << "┐";
    
                unprocessedNodes.push(nullptr);
                unprocessedNodes.push(nullptr);
            }
            setIndentation(width - 1);
            
        }
        std::cout << std::endl;
        
        levelNodes *= 2;
        ++level;
    }
    
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

void BinaryTree::printHorizontalUnicode(Node* root, const std::string& prefix, bool isLeft) const {
    if(!root) {
        return;
    }
    
    std::cout << prefix;
    
    std::cout << (isLeft ? "├──" : "└──" );
    
    std::cout << root->key() << std::endl;
    
    printHorizontalUnicode(root->left(), prefix + (isLeft ? "│   " : "    "), true);
    printHorizontalUnicode(root->right(), prefix + (isLeft ? "│   " : "    "), false);
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
        clearFrom(m_root);
        
        auto temp = copy(other.m_root);
        std::swap(m_root, temp.m_root);
    }
    
        return *this;
}

bool BinaryTree::operator == (const BinaryTree& other) const {
    if(m_root == other.m_root) {
        return true;
    }
    
    if(!m_root || !other.m_root) {
        return false;
    }
    
    auto it = begin();
    auto jt = other.begin();
    for(;it != end() && jt != other.end(); ++it, ++jt) {
        if((*it)->key() != (*jt)->key()) {
            return false;
        }
    }
    
    return true;
}

/* protected */

BinaryTree::RemoveData* BinaryTree::allocateRemoveData() {
    return new RemoveData;
}

void BinaryTree::m_finishRemove(RemoveData* data) {
    if(!data->nodeParent) {
        return;
    }
    
    if(data->nodeParent == data->target) {
        m_root = data->replacementNode;
        delete data->target;
        data->target = nullptr;
        data->nodeParent = nullptr;
    } else if(data->nodeParent->left() == data->target) {
        data->nodeParent->setLeft(nullptr);
        delete data->target;
        data->target = nullptr;
        if(data->replacementNode)
            data->nodeParent->setLeft(data->replacementNode);
    } else {
        data->nodeParent->setRight(nullptr);
        delete data->target;
        data->target = nullptr;
        if(data->replacementNode)
            data->nodeParent->setRight(data->replacementNode);
    }
    
}

bool BinaryTree::m_removeTrivialCase(RemoveData* data) {
    
    if(data->target->left() == nullptr && data->target->right() == nullptr) {
        m_finishRemove(data);
    } else if(!data->target->left()) {
        data->replacementNode = data->target->right();
        m_finishRemove(data);
    } else if(!data->target->right()) {
        data->replacementNode = data->target->left();
        m_finishRemove(data);
    } else {
        return false;
    }
    
    return true;
}

void BinaryTree::m_removeIfBothChildren(RemoveData* data) {
    data->replacementNode = findParent(data->target, nullptr);
    Node* leafParent = findParent(data->target, data->replacementNode);
    
    if(leafParent->left() == data->replacementNode) {
        leafParent->setLeft(nullptr);
    } else {
        leafParent->setRight(nullptr);
    }
    
    data->replacementNode->setLeft(data->target->left());
    data->replacementNode->setRight(data->target->right());
    m_finishRemove(data);
}

/* private */
void BinaryTree::m_toVectorLnr(Node* root, std::vector<int>& nums) const {
    
    if(!root) {
        return;
    }
    
    m_toVectorLnr(root->left(), nums);
    nums.push_back(root->key());
    m_toVectorLnr(root->right(), nums);
}

void BinaryTree::m_getLeafs(Node* root, std::vector<Node* >& leafs) const {
    if(!root) {
        return;
    } else if(!root->left() && !root->right()) {
        leafs.push_back(root);
    } else {
        m_getLeafs(root->left(), leafs);
        m_getLeafs(root->right(), leafs);
    }
}

BinaryTree::Node* BinaryTree::m_add(Node* root, const int value) {

    if(!root) {
        root = new Node(value);
    } else if(rand() % 2) {
        root->setLeft(m_add(root->left(), value));
    } else {
        root->setRight(m_add(root->right(), value));
    }

    return root;
}

void BinaryTree::m_max(Node* root, int& buffer) const {
    if(!root) {
        return;
    }
    
    if(root->key() > buffer) {
        buffer = root->key();
    }
    
    m_max(root->left(), buffer);
    m_max(root->right(), buffer);
}

void BinaryTree::m_min(Node* root, int& buffer) const {
    if(!root) {
        return;
    }
    
    if(root->key() < buffer) {
        buffer = root->key();
    }
    
    m_min(root->left(), buffer);
    m_min(root->right(), buffer);
}
