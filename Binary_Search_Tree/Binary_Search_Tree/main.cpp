#include "BinarySearchTree.hpp"

int main() {
    
    SearchTree foo;
    for(int i = 0; i < 10; ++i) {
        foo.add(rand() % 10);
    }
    
    foo.printHorizontal(foo.root());
    
    std::cout << "max - " << foo.max() << std::endl;
    std::cout << "min - " << foo.min() << std::endl;
    const int targetKey = 11;
    std::cout << "target - " << (foo.find(targetKey) ? foo.find(targetKey)->key() : 0) << std::endl;
    return 0;
}
