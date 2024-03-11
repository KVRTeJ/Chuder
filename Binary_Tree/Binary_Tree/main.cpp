#include <iostream>
#include <assert.h>

#include "Binary_Tree.hpp"

int main() {
    BinaryTree foo;
    {
        int newNum = int();
        for(int i = 1; i < 100; ++i) {
            newNum = rand() % 100;
            if(!foo.contains(newNum))
                foo.add(newNum);
        }
    }
    foo.printHorizontal(foo.root());
    //foo.printLeafs(foo.root());
    auto vFoo = foo.toVector();
    std::cout << '{';
    for(auto it = vFoo.begin(); it != vFoo.end(); ++it) {
        std::cout << *it << (it + 1 == vFoo.end() ? "":", ");
    }
    std::cout << '}' << std::endl;
    
    auto boo(foo);
    
    while(!foo.empty()) {
        std::cout << "max - " << foo.max() << std::endl;
        std::cout << "min - " << foo.min() << std::endl;
        std::cout << "height - " << foo.height() << std::endl;
        std::cout << "node count - " << foo.nodeCount(foo.root()) << std::endl;
        BinaryTree::Node* num = foo.find(1);
        std::cout << "level of " << num << " is - " << foo.level(foo.root(), num) << std::endl;
        std::cout << "removed - " << foo.find(foo.max())->key() << std::endl;
        std::cout << std::endl;
        
        auto max = foo.max();
        auto temp = foo.find(max);
        foo.remove(temp);
        assert(!foo.find(temp->key()));
    }
    
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    
    return 0;
}
