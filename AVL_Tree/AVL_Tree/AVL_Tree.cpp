#include "AVL_Tree.hpp"

AvlTree AvlTree::copy(Node* tree) {
    BinaryTree parent;
    parent = parent.copy(tree);
    AvlTree newTree = {};
    
    newTree.setRoot(parent.root());
    parent.setRoot(nullptr);
    
    return newTree;
}

BinaryTree::Node* AvlTree::turnRight(Node* middle, Node* top) {
    if(!middle || !middle->left()) {
        return {};
    }
    
    Node* bottom = middle->left();
    
    if(!top) {
        setRoot(bottom);
    } else {
        (top->left() == middle
         ? top->setLeft(bottom)
         : top->setRight(bottom));
    }
    
    middle->setLeft(bottom->right());
    bottom->setRight(middle);
    
    return bottom;
}

BinaryTree::Node* AvlTree::turnLeft(Node* middle, Node* top) {
    if(!middle || !middle->right()) {
        return {};
    }
    
    Node* bottom = middle->right();
    
    if(!top) {
        setRoot(bottom);
    } else {
        (top->left() == middle
         ? top->setLeft(bottom)
         : top->setRight(bottom));
    }
    
    middle->setRight(bottom->left());
    bottom->setLeft(middle);
    
    return bottom;
}

BinaryTree::Node* AvlTree::doubleTurnRightLeft(Node* middle, Node* top) {
    if(!middle || !middle->right() || !middle->right()->left()) {
        return {};
    }
    
    Node* bottom = middle->right();
    Node* extra = bottom->left();
    
    middle->setRight(extra);
    bottom->setLeft(extra->right());
    extra->setRight(bottom);
    
    if(!top) {
        setRoot(extra);
    } else {
        (top->left() == middle
         ? top->setLeft(extra)
         : top->setRight(extra));
    }
    middle->setRight(extra->left());
    extra->setLeft(middle);
    
    return extra;
}

BinaryTree::Node* AvlTree::doubleTurnLeftRight(Node* middle, Node* top) {
    if(!middle || !middle->left() || !middle->left()->right()) {
        return {};
    }
    
    Node* bottom = middle->left();
    Node* extra = bottom->right();
    
    middle->setLeft(extra);
    bottom->setRight(extra->left());
    extra->setLeft(bottom);
    
    if(!top) {
        setRoot(extra);
    } else {
        (top->left() == middle
         ? top->setLeft(extra)
         : top->setRight(extra));
    }
    
    middle->setLeft(extra->right());
    extra->setRight(middle);
    
    return extra;
}

void AvlTree::doBalance(Node*& root, Node* nodeSide, bool& isFixed, int& currentBalance) {
    if(nodeSide == root) {
        return;
    }
    
    currentBalance = balance(root);
    switch(currentBalance) {
        case 0:
            isFixed = true;
            break;
            
        case -2:
            if(balance(nodeSide) == 1) {
                root = doubleTurnLeftRight(root, (findParent(this->root(), root) == root
                                           ? nullptr
                                           : findParent(this->root(), root)) );
            } else {
                root = turnRight(root, (findParent(this->root(), root) == root
                                 ? nullptr
                                 : findParent(this->root(), root)) );
            }
            isFixed = true;
            break;
            
        case 2:
            if(balance(nodeSide) == -1) {
                root = doubleTurnRightLeft(root, (findParent(this->root(), root) == root
                                           ? nullptr
                                           : findParent(this->root(), root)) );
            } else {
                root = turnLeft(root, (findParent(this->root(), root) == root
                                ? nullptr
                                : findParent(this->root(), root)) );
            }
            isFixed = true;
            break;
    }
}

void AvlTree::doBalanceRemove(Node*& root, Node* nodeSide, bool& isFixed, int& currentBalance) {
    if(nodeSide == root) {
        return;
    }
    
    currentBalance = balance(root);
    switch(currentBalance) {
        case 1:
            isFixed = true;
            break;
            
        case -1:
            isFixed = true;
            break;
            
        case -2:
            if(balance(root->left()) < 1) {
                root = turnRight(root, (findParent(this->root(), root) == root
                                 ? nullptr
                                 : findParent(this->root(), root)) );
            } else {
                root = doubleTurnLeftRight(root, (findParent(this->root(), root) == root
                                           ? nullptr
                                           : findParent(this->root(), root)) );
            }
            isFixed = true;
            break;

        case 2:
            if(balance(root->right()) > -1) {
                root = turnLeft(root, (findParent(this->root(), root) == root
                                ? nullptr
                                : findParent(this->root(), root)) );
            } else {
                root = doubleTurnRightLeft(root, (findParent(this->root(), root) == root
                                           ? nullptr
                                           : findParent(this->root(), root)) );
            }
            isFixed = true;
            break;
    }
}


BinaryTree::Node* AvlTree::m_add(Node* root, const int value) {
    static bool isFixed = true;
    static int currentBalance = INT_MIN;
    
    if(!root) {
        root = new Node(value);
        isFixed = false;
    } else if(value < root->key()) {
        root->setLeft(m_add(root->left(), value));
        if(!isFixed) {
            doBalance(root, root->left(), isFixed, currentBalance);
        }
    } else if(value > root->key()){
        root->setRight(m_add(root->right(), value));
        if(!isFixed) {
            doBalance(root, root->right(), isFixed, currentBalance);
        }
    }
    
    return root;
}

SearchTree::m_removeData* AvlTree::allocateRemoveData() { return new m_removeDataAvl;}

void AvlTree::m_finishRemove(m_removeData* data) {
    if(!data->nodeParent) {
        return;
    }
    
    if(data->nodeParent == data->target) {
        setRoot(data->replacementNode);
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
    
    if(data->way().empty()) {
        data->way() = way(data->nodeParent);
    } else {
        data->way() = way(*--data->way().end());
    }
    
    int currentBalance;
    bool isFixed = false;
    auto itChild = data->way().end();
    auto itCurrent = itChild;
    Node* current = nullptr;
    Node* child = nullptr;
    while(itCurrent != data->way().begin()) {
        --itCurrent;
        current = *itCurrent;
        doBalanceRemove(current, child, isFixed, currentBalance);
        child = current;
    }
    
}

bool AvlTree::m_removeTrivialCase(m_removeData* data) {
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

void AvlTree::m_removeIfBothChildren(m_removeData* data) {
    int buffer = data->target->key();
    m_min(data->target->right(), buffer);
    
    data->replacementNode = find(buffer);
    Node* replacementNodeParent = findParent(data->target, data->replacementNode);
    
    if(replacementNodeParent != data->target) {
        data->way().push_back(replacementNodeParent);//TODO: перегрузить в нахождении ^
    } else {
        data->way().push_back(data->replacementNode);
    }
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
