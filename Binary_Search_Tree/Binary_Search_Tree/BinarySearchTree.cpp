#include "BinarySearchTree.hpp"

SearchTree::lnrIterator SearchTree::begin() {
    return lnrIterator(this, find(min()));
}

SearchTree::lnrIterator SearchTree::end() {
    return ++lnrIterator(this, find(max()));
}

SearchTree::lnrConstIterator SearchTree::begin() const {
    return lnrConstIterator(this, find(min()));
}

SearchTree::lnrConstIterator SearchTree::end() const {
    return ++lnrConstIterator(this, find(max()));
}

int SearchTree::level(const int key) const {
    if(!root()) {
        return {};
    }
    
    int result = 1;
    for(const Node* n = root(); n && n->key() != key; ++result) {
        if(n->key() > key) {
            n = n->left();
        } else {
            n = n->right();
        }
    }
    
    return result;
}

SearchTree SearchTree::copy(Node* tree) {
    BinaryTree parent;
    parent = parent.copy(tree);
    SearchTree newTree = {};
    
    newTree.setRoot(parent.root());
    parent.setRoot(nullptr);
    
    return newTree;
}

BinaryTree::Node* SearchTree::find(const int key) const {
    Node* current = const_cast<Node*>(root());
    
    while(current && (current->key() != key)) {
        if(current->key() > key) {
            current = current->left();
        } else {
            current = current->right();
        }
    }
    
    return current;
}

const BinaryTree::Node* SearchTree::findParent(const Node* root, const Node* child) const {
    if(!child || !root) {
        return BinaryTree::findParent(root, child);
    }
    
    if(root->key() == child->key()) {
        return root;
    }

    const Node* current = root;
    
    while(current->left() || current->right()) {
        
        if(current->left())
            if(current->left()->key() == child->key()) {
                return current;
            }
        if(current->right())
            if(current->right()->key() == child->key()) {
                return current;
            }
        
        current = (current->key() > child->key()
                   ? (current->left() ? current->left() : current)
                   : (current->right() ? current->right() : current));
        
    }
    
    return nullptr;
}

std::vector<int> SearchTree::toVectorAsc() const {
    std::vector<int> result = toVectorLnr();;
    
    return result;
}

/* private */

BinaryTree::Node* SearchTree::m_add(Node* root, const int value) {
    
    if(!root) {
        root = new Node(value);
    } else if(value < root->key()) {
        root->setLeft(m_add(root->left(), value));
    } else if(value > root->key()){
        root->setRight(m_add(root->right(), value));
    }
    
    return root;
}

void SearchTree::m_max(Node* root, int& buffer) const {
    if(!root) {
        return;
    }
    
    buffer = root->key();
    m_max(root->right(), buffer);
}

void SearchTree::m_min(Node* root, int& buffer) const {
    if(!root) {
        return;
    }
    
    buffer = root->key();
    m_min(root->left(), buffer);
}

void SearchTree::m_removeIfBothChildren(RemoveData* data) {
    int buffer = data->target->key();
    m_min(data->target->right(), buffer);
    
    data->replacementNode = find(buffer);
    Node* replacementNodeParent = findReplasementNodeParent(data);
    
    if(replacementNodeParent == data->target) {
        data->replacementNode->setLeft(data->target->left());
        m_finishRemove(data);
        return;
    }
    
    if(data->replacementNode->right()) {
        replacementNodeParent->setLeft(data->replacementNode->right());
    } else {
        if(replacementNodeParent->right() == data->replacementNode)
            replacementNodeParent->setRight(nullptr);
        else
            replacementNodeParent->setLeft(nullptr);
    }
    
    
    data->replacementNode->setLeft(data->target->left());
    data->replacementNode->setRight(data->target->right());
    m_finishRemove(data);
}

bool SearchTree::m_way(Node* root, Node* target, std::list<Node* >& result) const {
    if(!root) {
        return false;
    }
    
    result.push_back(root);
    
    if(root == target) {
        return true;
    } else {
        return m_way( (root->key() > target->key()
                     ? root->left()
                     : root->right()), target, result);
    }
}
