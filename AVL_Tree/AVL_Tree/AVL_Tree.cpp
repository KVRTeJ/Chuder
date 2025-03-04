#include "AVL_Tree.hpp"

#include <algorithm>

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
    
    middle->setBalance(middle->balance() + 1 + std::max(0, -bottom->balance()));
    bottom->setBalance(bottom->balance() + 1 + std::max(0, static_cast<int>(middle->balance())));
    
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
    
    middle->setBalance(middle->balance() - 1 - std::max(0, static_cast<int>(bottom->balance())));
    bottom->setBalance(bottom->balance() - 1 - std::max(0, -middle->balance()));
    
    return bottom;
}

BinaryTree::Node* AvlTree::doubleTurnRightLeft(Node* middle, Node* top) {
    if(!middle || !middle->right() || !middle->right()->left()) {
        return {};
    }
    
    Node* bottom = middle->right();
    turnRight(bottom, middle);
    return turnLeft(middle, top);

}

BinaryTree::Node* AvlTree::doubleTurnLeftRight(Node* middle, Node* top) {
    if(!middle || !middle->left() || !middle->left()->right()) {
        return {};
    }
    
    Node* bottom = middle->left();
    turnLeft(bottom, middle);
    return turnRight(middle, top);
}

void AvlTree::doBalance(Node*& root, Node* nodeSide) {
    if(nodeSide == root) {
        return;
    }
    
    auto rootParent = findParent(this->root(), root);
    switch(root->balance()) {
        case 0:
            isFixed = true;
            break;
            
        case -2:
            if(nodeSide->balance() == 1) {
                root = doubleTurnLeftRight(root, (rootParent == root
                                           ? nullptr
                                           : rootParent) );
            } else {
                root = turnRight(root, (rootParent == root
                                 ? nullptr
                                 : rootParent) );
            }
            isFixed = true;
            break;
            
        case 2:
            if(nodeSide->balance() == -1) {
                root = doubleTurnRightLeft(root, (rootParent == root
                                           ? nullptr
                                           : rootParent) );
            } else {
                root = turnLeft(root, (rootParent == root
                                ? nullptr
                                : rootParent) );
            }
            isFixed = true;
            break;
            
        default:
            break;
    }
}

bool AvlTree::doBalanceRemove(Node*& root) {
    auto rootParent = findParent(this->root(), root);
    
    switch(root->balance()) {
        case 1:
            isFixed = true;
            return true;
            break;
            
        case -1:
            isFixed = true;
            return true;
            break;
            
        case -2:
            if(root->left()->balance() < 1) {
                root = turnRight(root, (rootParent == root
                                 ? nullptr
                                 : rootParent) );
            } else {
                root = doubleTurnLeftRight(root, (rootParent == root
                                           ? nullptr
                                           : rootParent) );
            }
            break;

        case 2:
            if(root->right()->balance() > -1) {
                root = turnLeft(root, (rootParent == root
                                ? nullptr
                                : rootParent) );
            } else {
                root = doubleTurnRightLeft(root, (rootParent == root
                                           ? nullptr
                                           : rootParent) );
            }
            break;
            
        default:
            return true;
            break;
    }
    
    return false;
}


BinaryTree::Node* AvlTree::m_add(Node* root, const int value) {
    if(!root) {
        root = new Node(value);
        isFixed = false;
    } else if(value < root->key()) {
        root->setLeft(m_add(root->left(), value));
        if(!isFixed) {
            root->setBalance(root->balance() - 1);
            doBalance(root, root->left());
        }
    } else if(value > root->key()){
        root->setRight(m_add(root->right(), value));
        if(!isFixed) {
            root->setBalance(root->balance() + 1);
            doBalance(root, root->right());
        }
    }
    
    return root;
}

SearchTree::RemoveData* AvlTree::allocateRemoveData() { return new RemoveDataAvl;}

void AvlTree::m_finishRemove(RemoveData* data) {
    BinaryTree::m_finishRemove(data);
    isFixed = false;
    
    if(data->way().empty()) {
        data->way() = way(data->nodeParent);
    } else {
        data->way() = way(*data->way().rbegin());
    }
    
    
    bool canNext = false;
    for(auto it = data->way().rbegin(), itBefore = it; it != data->way().rend(); canNext = false, itBefore = it, ++it) {
        
        if(itBefore != it) {
            (*it)->setBalance((*it)->balance() + ((*it)->left() == *itBefore
                                                  ? 1
                                                  : -1));
        } else {
            (*it)->setBalance((*it)->balance() + (data->wasLeft()
                                                  ? 1
                                                  : -1));
        }
        
        while(!canNext) {
            canNext = doBalanceRemove(*it);
        }
        if(isFixed) break;
    }
}

BinaryTree::Node* AvlTree::findReplaсementNodeParent(RemoveData* data) {
    Node* replacementNodeParent = findParent(data->target, data->replacementNode);
    
    if(replacementNodeParent != data->target) {
        data->way().push_back(replacementNodeParent);
    } else {
        data->way().push_back(data->replacementNode);
    }
    
    return replacementNodeParent;
}
