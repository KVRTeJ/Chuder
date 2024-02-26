#include <chrono>

#include "multiphase_sorting.hpp"

/*
 28 3 20 16 3 5 2 5 1 2
 20 15 27 13 25 12 1 15 23 2 24 6
 */

int main() {
    multiphaseSort("example.txt");
    return -2;
    std::string str("nums_10k_10.txt");
    
    auto begin = std::chrono::steady_clock::now();
    
    auto end = std::chrono::steady_clock::now();
    
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin)/1000;

    std::cout << "end\t time - " << elapsed_ms.count() << std::endl;

    assert(isFileContainsSortedArray("supported_file1.txt"));
    
    return -1;
}
