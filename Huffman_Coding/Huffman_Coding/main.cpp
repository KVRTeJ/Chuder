#include <iostream>

#include "HuffmanTree.hpp"

int main(int argc, const char * argv[]) {
    HuffmanTree foo;
    std::string fooStr = "qwertyq";
    foo.build(fooStr);
    return 0;
}
