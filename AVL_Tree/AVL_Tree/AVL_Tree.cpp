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

void AvlTree::doBalance(Node*& root, Node* nodeSide) {
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

void AvlTree::doBalanceRemove(Node*& root) {
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
    if(!root) {
        root = new Node(value);
        isFixed = false;
    } else if(value < root->key()) {
        root->setLeft(m_add(root->left(), value));
        if(!isFixed) {
            doBalance(root, root->left());
        }
    } else if(value > root->key()){
        root->setRight(m_add(root->right(), value));
        if(!isFixed) {
            doBalance(root, root->right());
        }
    }
    
    return root;
}

SearchTree::RemoveData* AvlTree::allocateRemoveData() { return new RemoveDataAvl;}

void AvlTree::m_finishRemove(RemoveData* data) {
    
    BinaryTree::m_finishRemove(data);
    
    if(data->way().empty()) {
        data->way() = way(data->nodeParent);
    } else {
        data->way() = way(*--data->way().end());
    }
    
    auto itCurrent = data->way().end();
    while(itCurrent != data->way().begin()) {
        --itCurrent;
        doBalanceRemove(*itCurrent);
    }
    
}

BinaryTree::Node* AvlTree::findReplasementNodeParent(RemoveData* data) {
    Node* replacementNodeParent = findParent(data->target, data->replacementNode);
    
    if(replacementNodeParent != data->target) {
        data->way().push_back(replacementNodeParent);
    } else {
        data->way().push_back(data->replacementNode);
    }
    
    return replacementNodeParent;
}
