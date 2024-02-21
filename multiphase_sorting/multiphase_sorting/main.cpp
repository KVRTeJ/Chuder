#include "multiphase_sorting.hpp"

int main() {
    
    std::string boo("boo.txt"), foo("foo.txt"), merged("merged.txt");
    
    std::ofstream write(boo);
    std::ifstream read(foo);
    int current = 0;
    
    while(read) {
        read >> current;
        if(!(current % 2))
            write << current << ' ';
    }
    
    write.close();
    read.close();
    
    outputFile(boo);
    
    return -1;
}
