#include "AVL_Tree.hpp"

AvlTree AvlTree::copy(Node* tree) const {
    BinaryTree parent = BinaryTree::copy(tree);
    AvlTree newTree = {};
    
    newTree.setRoot(parent.root());
    parent.setRoot(nullptr);
    
    return newTree;
}

bool AvlTree::turnRight(Node* middle, Node* top) {
    if(!middle || !middle->left()) {
        return false;
    }
    
    Node* bottom = middle->left();
    
    if(!top || top == this->root()) {
        setRoot(bottom);
    } else {
        top->setLeft(bottom);
    }
    
    middle->setLeft(bottom->right());
    bottom->setRight(middle);
    
    return true;
}

bool AvlTree::turnLeft(Node* middle, Node* top) {
    if(!middle || !middle->right()) {
        return false;
    }
    
    Node* bottom = middle->right();
    
    if(!top || top == this->root()) {
        setRoot(bottom);
    } else {
        top->setRight(bottom);
    }
    
    middle->setRight(bottom->left());
    bottom->setLeft(middle);
    
    return true;
}

bool AvlTree::doubleTurnRightLeft(Node* middle, Node* top) {
    if(!middle || !middle->right() || !middle->right()->left()) {
        return false;
    }
    
    Node* bottom = middle->right();
    Node* extra = bottom->left();
    
    middle->setRight(extra);
    bottom->setLeft(extra->right());
    extra->setRight(bottom);
    
    if(!top || top == this->root()) {
        setRoot(extra);
    } else {
        top->setRight(extra);
    }
    middle->setRight(extra->left());
    extra->setLeft(middle);
    
    return true;
}

bool AvlTree::doubleTurnLeftRight(Node* middle, Node* top) {
    if(!middle || !middle->left() || !middle->left()->right()) {
        return false;
    }
    
    Node* bottom = middle->left();
    Node* extra = bottom->right();
    
    middle->setLeft(extra);
    bottom->setRight(extra->left());
    extra->setLeft(bottom);
    
    if(!top || top == this->root()) {
        setRoot(extra);
    } else {
        top->setLeft(extra);
    }
    
    middle->setLeft(extra->right());
    extra->setRight(middle);
    
    return true;
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
            
            currentBalance = balance(root);
            switch(currentBalance) {
                case 0:
                    isFixed = true;
                    break;
                    
                case -2:
                    if(balance(root->left()) == 1) {
                        doubleTurnLeftRight(root, findParent(this->root(), root));
                    } else {
                        turnRight(root, findParent(this->root(), root));
                    }
                    break;
                    
                case 2:
                    if(balance(root->left()) == -1) {
                        doubleTurnRightLeft(root, findParent(this->root(), root));
                    } else {
                        turnLeft(root, findParent(this->root(), root));
                    }
                    break;
            }
            
        }
    } else if(value > root->key()){
        root->setRight(m_add(root->right(), value));
        if(!isFixed) {
            
            currentBalance = balance(root);
            switch(currentBalance) {
                case 0:
                    isFixed = true;
                    break;
                    
                case -2:
                    if(balance(root->right()) == 1) {
                        doubleTurnLeftRight(root, findParent(this->root(), root));
                        turnRight(root, findParent(this->root(), root));
                    } else {
                        turnRight(root, findParent(this->root(), root));
                    }
                    break;
                    
                case 2:
                    if(balance(root->right()) == -1) {
                        doubleTurnRightLeft(root, findParent(this->root(), root));
                    } else {
                        turnLeft(root, findParent(this->root(), root));
                    }
                    break;
            }
            
        }
    }
    
    return root;
}

