#include <iostream>
#include <assert.h>

#include "HuffmanTree.hpp"

/*
 qwertyqwqqwee
 ehal greka cerez reky
 [e, h, a, l,  , g, r, k, c, z, y]
 [h, l, g, c, z, y, k, a,  , r, e]
 original - hlgcezy rka
 encoded  - 000011110111111000111111011011
 decoded  - hlgcezy rka
 */

int main(int argc, const char * argv[]) {
    std::string exampleFileName = "example.txt";
    std::string example = "ehal greka cerez reky";
    
    
    HuffmanTree foo;
    foo.build(exampleFileName);
    
    foo.printHorizontalUnicode(foo.root());
    
    std::cout << "original - " << foo.root()->data() << std::endl;
    
    std::string encodeStr;
    foo.encode(example, encodeStr);
    std::cout << "encoded  - " << encodeStr << std::endl;
    
    std::string decodeStr;
    foo.decode(encodeStr, decodeStr);
    std::cout << "decoded  - " << decodeStr << std::endl;
    assert(foo.root()->data() == decodeStr);
    return 0;
}
