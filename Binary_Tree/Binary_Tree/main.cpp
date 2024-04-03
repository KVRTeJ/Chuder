#include <iostream>

#include "Binary_Tree.hpp"

int main() {
    BinaryTree foo;
    {
        int newNum = int();
        for(int i = 1; i < 10; ++i) {
            foo.add(i);
        }
    }
    foo.printHorizontal(foo.root());
    //foo.printLeafs(foo.root());
    auto nodes = foo.levelNodes(foo.root(), 5);
    std::cout << '{';
    for(auto it = nodes.begin(); it != nodes.end();) {
        std::cout << (*it)->key() << (++it == nodes.end() ? "" : ", ");
    }
    std::cout << '}' << std::endl;
    foo.printLeafs(foo.root());
    std::cout << "leaf - " << foo.findParent(foo.root(), nullptr)->key() << std::endl;
    std::cout << foo.level(foo.root(), foo.findParent(foo.root(), nullptr)) << std::endl;
    std::cout << foo.maxLevel() << std::endl;
    
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    
    foo.printLevels();
    
    std::cout << std::endl;std::cout << std::endl;std::cout << std::endl;
    
    auto vec = foo.toVector();
    for(auto it = vec.begin(); it != vec.end(); ++it) {
        std::cout << (*it) << ' ';
    }
    return 0;
}
