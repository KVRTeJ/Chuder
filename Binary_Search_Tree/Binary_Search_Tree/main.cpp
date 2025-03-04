#include "BinarySearchTree.hpp"

int main() {
    
    SearchTree tree;
    tree.add(5);
    for(int i = 0; i < 90; ++i) {
        tree.add(rand() % 20);
    }
    
    tree.add(1);
    tree.print(tree.root());

    
    auto nums = tree.toVectorAsc();
    int counter = 0;
    SearchTree::lnrIterator it = tree.begin();
    it--;
    while((*it)->key() != tree.max()) {
        assert(nums[counter] == (*it)->key());
        std::cout << (*it)->key() << ' ';
        ++it;
        ++counter;
    }
    it++;
    std::cout << std::endl;    std::cout << std::endl;    std::cout << std::endl;
    it--;
    while((*it)->key() != tree.min()) {
        assert(nums[counter] == (*it)->key());
        std::cout << (*it)->key() << ' ';
        --it;
        --counter;
    }
    
    srand(static_cast<unsigned>(time(0)));
    
    SearchTree foo;
    
    int newNum = 0;
    for(int i = 0; i < 150; ++i) {
        newNum = rand() % 100;
        foo.add(newNum);
    }
    bool wantPrint = false;
    char answer = {};
    std::cout << std::endl;
    std::cout << "Want to print tree? y/n: ";
    std::cin >> answer;
    if(answer == 'y')
        wantPrint = true;
    
    if(wantPrint)
        foo.printHorizontal(foo.root());
    
    int maxSize = foo.nodeCount(foo.root());
    std::vector<int> fooNums = foo.toVectorAsc();
    assert(maxSize == fooNums.size());
    
    std::cout << "size - " << maxSize << std::endl;
    
    std::cout << '{';
    for(auto it = fooNums.begin(); it != fooNums.end(); ++it) {
        std::cout << *it << (it + 1 == fooNums.end() ? "": ", ");
    }
    std::cout << '}' << std::endl;
    
    int currentSize = maxSize;
    int iterationsCount = 0;
    do {
        newNum = rand() % 100;
        std::cout << "deleted - " << newNum << (newNum / 10 ? " ": "  ");
        if(foo.remove(newNum)) {
            std::cout << "successfully";
            --currentSize;
            fooNums.erase(std::find(fooNums.begin(), fooNums.end(), newNum));
        } else {
            std::cout << "fail";
        }
        std::cout << std::endl;
        assert(!static_cast<bool>(foo.find(newNum)));
        assert(currentSize == foo.nodeCount(foo.root()));
        assert(currentSize == fooNums.size());
        ++iterationsCount;
    } while(!foo.empty());
    assert(currentSize == 0);
    float probability = (static_cast<float>(maxSize) / iterationsCount) * 100;
    std::cout << "Test is done!\nThe probability of a hit - " << probability << '%' << std::endl;
    return 0;
}
