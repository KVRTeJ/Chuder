#include <chrono>
#include <assert.h>

#include "multiphase_sorting.hpp"

/*
 28 3 20 16 3 5 2 5 1 2
 20 15 27 13 25 12 1 15 23 2 24 6
 */

int main() {
    MultiphaseSort temp;
    temp.setFileCount(4);
    temp.setFileName("example.txt");
    temp.sort();
    
    
    return 0;
}
