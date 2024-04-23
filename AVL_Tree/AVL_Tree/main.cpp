#include "AVL_Tree.hpp"

int main() {
    AvlTree boo;
    std::vector<int> nums = {10, 20, 40, 35, 38, 36, 5};
    for(auto it = nums.begin(); it != nums.end(); ++it) {
        boo.add(*it);
        boo.print();
        std::cout << std::endl;
    }
    
    return 0;
}
