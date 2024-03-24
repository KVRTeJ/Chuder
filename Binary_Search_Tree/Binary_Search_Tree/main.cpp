#include "BinarySearchTree.hpp"

int main() {
    
    SearchTree foo;
    for(int i = 0; i < 10; ++i) {
        foo.add(i);
    }
    
    foo.printHorizontal(foo.root());
    
    std::cout << "max - " << foo.max() << std::endl;
    std::cout << "min - " << foo.min() << std::endl;
    
    return 0;
}
