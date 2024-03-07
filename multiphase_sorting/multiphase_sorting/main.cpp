#include <assert.h>

#include "multiphase_sorting.hpp"

int main() {
    
    MultiphaseSort temp;
    temp.setFileCount((rand() % 22) + 3);
    temp.setFileName("nums_1kk_100000.txt");
    temp.sort();
    assert(temp.isFileContainsSortedArray("result.txt"));
    
    return 0;
}
