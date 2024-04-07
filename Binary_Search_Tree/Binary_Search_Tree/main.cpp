#include "BinarySearchTree.hpp"

int main() {
    
    SearchTree foo;
    std::vector<int> nums = {50, 20, 70, 10, 30, 60, 90, 5, 15, 25, 40, 35, 45};
    for(auto it = nums.begin(); it != nums.end(); ++it) {
        foo.BinaryTree::add(*it);
    }
    
    foo.BinaryTree::add(27);
    foo.printHorizontal(foo.root());
    
    foo.remove(20);
    std::cout << std::endl; std::cout << "-=-=-=-=-=-" << std::endl; std::cout << std::endl;
    foo.printHorizontal(foo.root());
    
    foo.remove(25);
    std::cout << std::endl; std::cout << "-=-=-=-=-=-" << std::endl; std::cout << std::endl;
    foo.printHorizontal(foo.root());
    
    foo.remove(27);
    std::cout << std::endl; std::cout << "-=-=-=-=-=-" << std::endl; std::cout << std::endl;
    foo.printHorizontal(foo.root());
    
    return 0;
}
