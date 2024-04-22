#include "AVL_Tree.hpp"

int main() {
    AvlTree boo;
    
    boo.add(60);
    boo.add(50);
    boo.add(40);
    boo.add(41);
    boo.add(42);
    
    boo.printHorizontal(boo.root());
    assert(boo.doubleTurnLeftRight(boo.root()->left(), boo.root()));
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    boo.printHorizontal(boo.root());
    return 0;
}
