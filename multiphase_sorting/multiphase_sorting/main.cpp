#include "multiphase_sorting.hpp"

int main() {
    std::string str("hello.txt");
    
    naturalMergeSort3Files(str);
    
    std::cout << "merged" << std::endl;

    assert(isFileContainsSortedArray("supported_file1.txt"));
    
    return -1;
}
