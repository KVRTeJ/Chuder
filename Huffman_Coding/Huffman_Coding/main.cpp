#include <iostream>

#include "HuffmanTree.hpp"

int main(int argc, const char * argv[]) {
    HuffmanTree foo;
    std::string fooStr = "qwertyqwqqwee";
    foo.build(fooStr);
    return 0;
}
