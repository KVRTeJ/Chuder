#include <iostream>

#include "HuffmanTree.hpp"

int main(int argc, const char * argv[]) {
    HuffmanTree foo;
    std::string fooStr = "qwertyqwqqwee";
    std::string example = "ehal greka cerez reky";
    foo.build(example);
    return 0;
}
