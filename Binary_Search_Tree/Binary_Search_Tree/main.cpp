#include "BinarySearchTree.hpp"

int main() {
    
    SearchTree foo;
    
    int newValue = 0;
    for(int i = 0; i < 15; ++i) {
        newValue = rand() % 10;
        if(!foo.contains(newValue))
            foo.add(newValue);
    }
    
    foo.printHorizontal(foo.root());
    
    std::cout << "max - " << foo.max() << std::endl;
    std::cout << "min - " << foo.min() << std::endl;
    const int targetKey = 9;
    std::cout << "target - " << (foo.find(targetKey) ? foo.find(targetKey)->key() : 0) << std::endl;
    std::cout << "level of target key - " << foo.level(targetKey) << std::endl;
    
    return 0;
}
