#include "AVL_Tree.hpp"

int main() {
    avlTree boo;
    
    boo.add(10);
    boo.add(9);
    boo.add(11);
    boo.add(11);
    boo.add(12);
    boo.add(115);
    boo.add(114);
    
    boo.printHorizontal(boo.root());
    
    return 0;
}
