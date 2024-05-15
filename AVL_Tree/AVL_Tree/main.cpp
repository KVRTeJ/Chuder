#include "AVL_Tree.hpp"

#include <thread>
#include <chrono>

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
    
    int size = -1;
    std::cout << "tree size: ";
    std::cin >> size;
    
    std::vector<int> nums(size);
    
    std::cout << '{';
    int num = INT_MIN;
    for(auto it = nums.begin(); it != nums.end();) {
        num = rand() % (size * 2);
        while(std::find(nums.begin(), nums.end(), num) != nums.end()){
            num = rand() % (size * 2);
        }
        *it = num;
        std::cout << *it << (++it == nums.end()
                             ? ""
                             : ", ");
    }
    std::cout << '}' << std::endl;
    
    int sleepTime = 0;
    std::cout << "sleep time(seconds): ";
    std::cin >> sleepTime;
    sleepTime *= 1000;
    
    char printAnswer = 'n';
    std::cout << "wanna print tree? y/n: ";
    std::cin >> printAnswer;
    
    std::cout << std::endl;
    
    int currentSize = -1;
    auto beginAdd = std::chrono::steady_clock::now();
    for(auto it = nums.begin(); it != nums.end(); ++it) {
        boo.add(*it);
        currentSize = boo.nodeCount(boo.root());
        
    
        std::this_thread::sleep_for(std::chrono::milliseconds(sleepTime));
        if(printAnswer == 'y') {
            std::cout << "added - " << *it << "\t current size - " << currentSize << std::endl;
            std::cout << "printing tree. . ." << std::endl;
            boo.print();
            std::cout << std::endl;
            std::cout << std::endl;
            std::cout << std::endl;
        }
        
        assert(boo.find(*it));
        assert(boo.find(*it)->key() == *it);
        assert(boo.balanced());
        
    }
    auto endAdd = std::chrono::steady_clock::now();
    
    auto elapsedMsAdd = std::chrono::duration_cast<std::chrono::milliseconds>(endAdd - beginAdd);
    std::cout << "The time of addition: " << (elapsedMsAdd / 1000.0).count() << " s\n";
    
    if(printAnswer != 'y') {
        std::cout << std::endl;
        std::cout << std::endl;
        std::cout << std::endl;
    }
    
    std::cout << "\t\t\tREMOVE TIME!" << std::endl;
    
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    
    currentSize = -1;
    int current = INT_MIN;
    int iterCount = 0;
    auto it = nums.begin();
    auto beginRemove = std::chrono::steady_clock::now();
    while(!nums.empty()) {
        
        if(*it == 10) {
            
        }
        ++iterCount;
        current = *it;
        boo.remove(*it);
        nums.erase(it);
        
        
        std::this_thread::sleep_for(std::chrono::milliseconds(sleepTime));
        if(printAnswer == 'y') {
            std::cout << "step - " << iterCount;
            std::cout << "\t removed - " << current << "\t current size - " << boo.nodeCount(boo.root()) <<  std::endl;
            std::cout << "printing tree. . ." << std::endl;
            boo.print();
            std::cout << std::endl;
            std::cout << std::endl;
            std::cout << std::endl;
        }
        
        currentSize = boo.nodeCount(boo.root());
        assert(currentSize == nums.size());
        assert(!boo.find(current));
        assert(boo.balanced());
        
        it = nums.begin();
    }
    auto endRemove = std::chrono::steady_clock::now();
    
    
    auto elapsedMsRemove = std::chrono::duration_cast<std::chrono::milliseconds>(endRemove - beginRemove);
    std::cout << "The time of deletion: " << (elapsedMsRemove / 1000.0).count() << " s\n";
    
    return 0;
}
