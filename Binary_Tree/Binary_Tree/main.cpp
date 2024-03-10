#include <iostream>

#include "Binary_Tree.hpp"

int main() {
    BinaryTree foo;
    for(int i = 1; i < 10; ++i) {
        foo.add(i);
    }
    foo.printHorizontal(foo.root());
    //foo.printLeafs(foo.root());
    auto vFoo = foo.toVector();
    std::cout << '{';
    for(auto it = vFoo.begin(); it != vFoo.end(); ++it) {
        std::cout << *it << (it + 1 == vFoo.end() ? "":", ");
    }
    std::cout << '}' << std::endl;
    
    foo.remove(9);
    BinaryTree foo1 = foo;
    foo.printHorizontal(foo1.root());
    //foo.printLeafs(foo.root());
    auto vFoo1 = foo1.toVector();
    std::cout << '{';
    for(auto it = vFoo1.begin(); it != vFoo1.end(); ++it) {
        std::cout << *it << (it + 1 == vFoo1.end() ? "":", ");
    }
    std::cout << '}' << std::endl;
    
    return 0;
}
