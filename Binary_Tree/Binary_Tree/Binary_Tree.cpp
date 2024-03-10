#include <list>
#include <stack>
#include <random>

#include "Binary_Tree.hpp"

namespace {
struct Data {
    BinaryTree::Node* targetNode = nullptr;
    BinaryTree::Node* nodeParent = nullptr;
};

void findNodeAndParent(Data& data, const int key) {
    std::stack<BinaryTree::Node*> unprocessedNodes;
    unprocessedNodes.push(data.nodeParent);
    
    while(!unprocessedNodes.empty()) {
        data.nodeParent = unprocessedNodes.top();
        unprocessedNodes.pop();
        
        if(data.nodeParent->key() == key) {
            break;
        }
        
        if(data.nodeParent->left()) {
            if(data.nodeParent->left()->key() == key) {
                data.targetNode = data.nodeParent->left();
                break;
            }
            unprocessedNodes.push(data.nodeParent->left());
        }
        if(data.nodeParent->right()) {
            if(data.nodeParent->right()->key() == key) {
                data.targetNode = data.nodeParent->right();
                break;
            }
            unprocessedNodes.push(data.nodeParent->right());
        }
    }
    
}

}

void BinaryTree::add(const int key) {
    
    if(m_root) {
        add(m_root, key);
    } else {
        m_root = new Node(key);
    }
    
}

bool BinaryTree::remove(const int key) {
    Data data = {};
    data.nodeParent = m_root;
    
    findNodeAndParent(data, key);
    
    //Узла со значением key нет
    if(data.targetNode->key() != key) {
        return false;
    }
    
    //Первая итерация не дошла до конца, искомый узел - корень
    Node* replacementNode = nullptr;
    if(!data.targetNode) {
        //TODO: удаление корня
    } else {
        //Нет потомков - лист
        if(data.targetNode->left() == nullptr && data.targetNode->right() == nullptr) {
            if(data.nodeParent->left() == data.targetNode) {
                data.nodeParent->setLeft(nullptr);
                delete data.targetNode;
            } else {
                data.nodeParent->setRight(nullptr);
                delete data.targetNode;
            }
        } else if(!data.targetNode->left()) {
            replacementNode = data.targetNode->right();
            //TODO: убрать копипасту
            //////////////
            if(data.nodeParent->left() == data.targetNode) {
                data.nodeParent->setLeft(nullptr);
                delete data.targetNode;
                data.nodeParent->setLeft(replacementNode);
            } else {
                data.nodeParent->setRight(nullptr);
                delete data.targetNode;
                data.nodeParent->setRight(replacementNode);
            }
            //////////////

        } else if(!data.targetNode->right()) {
            replacementNode = data.targetNode->left();
            
            //////////////
            if(data.nodeParent->left() == data.targetNode) {
                data.nodeParent->setLeft(nullptr);
                delete data.targetNode;
                data.nodeParent->setLeft(replacementNode);
            } else {
                data.nodeParent->setRight(nullptr);
                delete data.targetNode;
                data.nodeParent->setRight(replacementNode);
            }
            //////////////
            
        } else {
            Data replacementNode = {};
            
        }
    }
    
    
    
    return false;
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

void BinaryTree::printLeafs(Node* root) const {
    
    if(!root) {
        return;
    } else if(!root->left() && !root->right()) {
        std::cout << root->key() << std::endl;
    } else {
        printLeafs(root->left());
        printLeafs(root->right());
    }
    
}

void BinaryTree::printHorizontal(Node *root, int marginLeft, int levelSpacing) const {
    
    if (root == nullptr) {
        return;
    }
    
    printHorizontal(root->right(), marginLeft + levelSpacing, levelSpacing);
    std::cout << std::string(marginLeft, ' ') << root->key() << std::endl;
    printHorizontal(root->left(), marginLeft + levelSpacing, levelSpacing);
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

