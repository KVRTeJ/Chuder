#include "AVL_Tree.hpp"

const int g_maxNum = 100;

int main() {
    
    auto printList = [](std::list<BinaryTree::Node*> list) {
        std::cout << '{';
        for(auto it = list.begin(); it != list.end();) {
            std::cout << (*it)->key() << (++it == list.end()
                                          ? "}\n"
                                          : ", ");
        }
    };
    
    AvlTree boo;
    
    int num = 0;
    std::vector<int> numbers(20);
    *numbers.begin() = 30;
    for(auto it = numbers.begin() + 1; it != numbers.end(); ++it) {
        *it = rand() % 60;
        boo.add(*it);
    }
    
    boo.print();
    std::cout << std::endl;
    
    boo.remove(2);
    boo.print();
    std::cout << std::endl;
    
    boo.remove(24);
    boo.print();
    std::cout << std::endl;
    
    auto list = boo.way(boo.find(2));
    printList(list);
    
    return -1;
    
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
