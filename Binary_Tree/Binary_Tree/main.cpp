#include <iostream>

#include "Binary_Tree.hpp"

int main() {
    BinaryTree foo;
    for(int i = 1; i < 10; ++i) {
        foo.add(i);
    }
    foo.printHorizontal(foo.root());
    //foo.printLeafs(foo.root());
    std::cout << foo.find(1)->key() << std::endl;
    auto vFoo = foo.toVector();
    std::cout << '{';
    for(auto it = vFoo.begin(); it != vFoo.end(); ++it) {
        std::cout << *it << (it + 1 == vFoo.end() ? "":", ");
    }
    std::cout << '}' << std::endl;
    BinaryTree::Node* temp = foo.find(3);
    foo.remove(4);
    foo.printHorizontal(foo.root());
    vFoo = foo.toVector();
    std::cout << '{';
    for(auto it = vFoo.begin(); it != vFoo.end(); ++it) {
        std::cout << *it << (it + 1 == vFoo.end() ? "":", ");
    }
    std::cout << '}' << std::endl;
    return 0;
}
