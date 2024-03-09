#include <iostream>

#include "Binary_Tree.hpp"

int main() {
    BinaryTree foo;
    for(int i = 1; i < 10; ++i) {
        foo.add(i);
    }
    foo.printHorizontal(foo.root());
    foo.printLeafs(foo.root());
    auto vFoo = foo.toVector();
    std::cout << '{';
    for(auto it = vFoo.begin(); it != vFoo.end(); ++it) {
        std::cout << *it << (it + 1 == vFoo.end() ? "":", ");
    }
    std::cout << '}';
    return 0;
}