#include "BinarySearchTree.hpp"

int main() {
    
    SearchTree foo;
    
    int newValue = 0;
    for(int i = 0; i < 15; ++i) {
        newValue = rand() % 10;
        if(!foo.contains(newValue))
            foo.BinaryTree::add(newValue);
    }
    
    foo.printHorizontal(foo.root());
    
    std::cout << "max - " << foo.BinaryTree::max() << std::endl;
    std::cout << "min - " << foo.BinaryTree::min() << std::endl;
    const int targetKey = 9;
    std::cout << "target - " << (foo.find(targetKey) ? foo.find(targetKey)->key() : 0) << std::endl;
    std::cout << "level of target key - " << foo.level(targetKey) << std::endl;
    
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    
    auto nums = foo.toVectorAsc();
    for(auto it = nums.begin(); it != nums.end(); ++it) {
        std::cout << *it << ' ';
    }
    std::cout << std::endl;
    
    std::cout << std::endl;    std::cout << std::endl;    std::cout << std::endl;
    
    auto temp = foo.copy(foo.find(7));
    foo = temp;
    foo.printHorizontal(foo.root());
    return 0;
}
