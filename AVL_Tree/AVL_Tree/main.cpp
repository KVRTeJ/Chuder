#include "AVL_Tree.hpp"

int main() {
    AvlTree boo;
    
    boo.add(6);
    boo.add(4);
    boo.add(8);
    boo.add(2);
    boo.add(3);
    boo.add(1);
    
    boo.printHorizontal(boo.root());
    
    boo.turnLeft(nullptr);
    return 0;
}
