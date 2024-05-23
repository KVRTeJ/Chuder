#include <iostream>
#include <assert.h>

#include "HuffmanTree.hpp"

namespace {
    void generateTestFile(const std::string& fileName, int range) {
        std::ofstream file(fileName);
        
        for(int i = 0; i < range; ++i) {
            file << static_cast<char>(rand() % 127); //127 - LIMIT OF SET
        }
        
        file.close();
    }
    
}

int main(int argc, const char * argv[]) {
    std::string exampleFileName = "example.txt";
    //generateTestFile(exampleFileName, 10000);
    
    HuffmanTree foo;
    foo.build(exampleFileName);
    auto temppp = foo.getLeafs(foo.root());
    
    foo.printHorizontalUnicode(foo.root());
    
    //std::cout << "original - " << foo.root()->data() << std::endl;
    
    std::string encodeFileName = "example_encode.txt";
    std::cout << "coef - " << foo.encode(exampleFileName, encodeFileName) << std::endl;
    
    
    std::ifstream encodeResult(encodeFileName);
    BoolVector bv(0, 0);
    int unsignif = 0;
    encodeResult >> unsignif;
    char temp;
    while(encodeResult >> std::noskipws >> temp) {
        bv.add(temp);
    }
    bv.print();
    
    std::string decodeFileName = "example_decoded.txt";
    foo.decode(encodeFileName, decodeFileName);
    
    return 0;
}
