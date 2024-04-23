#include "AVL_Tree.hpp"

const int g_maxNum = 200;

int main() {
    AvlTree boo;
    
    std::vector<int> nums(g_maxNum / 2);
    *nums.begin() = g_maxNum / 2;
    
    std::cout << '{';
    for(auto it = nums.begin() + 1; it != nums.end();) {
        *it = rand() % g_maxNum;
        std::cout << *it << (++it == nums.end()
                             ? ""
                             : ", ");
    }
    std::cout << '}' << std::endl;
    
    std::cout << std::endl;
    
    for(auto it = nums.begin(); it != nums.end(); ++it) {
        boo.add(*it);
        assert(boo.find(*it));
        assert(boo.find(*it)->key() == *it);
        assert(boo.balanced());
        boo.print();
        std::cout << std::endl;
        std::cout << std::endl;
        std::cout << std::endl;
    }
    
    auto foo = AvlTree::copy(boo.find(9));
    foo.print();
    assert(foo != boo);
    std::cout << std::endl;
    foo.printHorizontalUnicode(foo.root());
    return 0;
}
