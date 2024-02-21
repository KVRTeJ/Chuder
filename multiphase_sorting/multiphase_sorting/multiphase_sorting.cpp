#include "multiphase_sorting.hpp"

namespace {

int fib(const int num) {
    if(num == 0)
        return 0;
    if(num == 1)
        return 1;
    return fib(num - 1) + fib(num - 2);
}

}

void outputFile(const std::string& fileName) {
    std::ifstream origin(fileName, std::ios_base::in);
    assert(origin.is_open());
    
    int current = 0;
    while(origin >> current) {
        std::cout << current << ' ';
    }
    
    origin.close();
    std::cout << std::endl;
}

bool isFileContainsSortedArray(const std::string &fileName) {
    std::ifstream origin(fileName, std::ios_base::in);
    int current = 0, next = 0;
    while(origin >> current) {
        origin >> next;
        std::cout << "cur - " << current << " next - " << next << std::endl;
        if(next > current)
            return false;
    }
    
    origin.close();
    return true;
}

bool merge(const std::string& boo, const std::string& foo, const std::string& merged) {
    std::ifstream f_boo(boo), f_foo(foo);
    std::ofstream f_merged(merged);
    
    if(!f_boo.is_open() || !f_foo.is_open() || !f_merged.is_open())
        return false;
    
    int currentFoo = 0, currentBoo = 0;
    f_boo >> currentBoo;
    f_foo >> currentFoo;
    
    while(f_boo && f_foo) {
        if(currentBoo > currentFoo) {
            f_merged << currentFoo << ' ';
            f_foo >> currentFoo;
        }
        else {
            f_merged << currentBoo << ' ';
            f_boo >> currentBoo;
        }
    }
    
    while(f_boo) {
        f_merged << currentBoo << ' ';
        f_boo >> currentBoo;
    }
    
    while(f_foo) {
        f_merged << currentFoo << ' ';
        f_foo >> currentFoo;
    }
    
    return true;
}
