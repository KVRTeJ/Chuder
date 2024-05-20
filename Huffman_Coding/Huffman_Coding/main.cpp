#include <iostream>
#include <assert.h>

#include "HuffmanTree.hpp"

int main(int argc, const char * argv[]) {
    HuffmanTree foo;
    std::string fooStr = "qwertyqwqqwee";
    std::string example = "ehal greka cerez reky";
    foo.build(example);
    
    foo.printHorizontalUnicode(foo.root());
    
    std::cout << "original - " << foo.root()->data() << std::endl;
    
    std::string encodeStr;
    foo.encode(example, encodeStr);
    std::cout << "encoded -  " << encodeStr << std::endl;
    
    std::string decodeStr;
    foo.decode(encodeStr, decodeStr);
    std::cout << "decoded -  " << decodeStr << std::endl;
    assert(foo.root()->data() == decodeStr);
    return 0;
}
