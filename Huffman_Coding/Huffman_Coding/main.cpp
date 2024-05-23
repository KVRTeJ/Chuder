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
 
 [{e}, {h}, {a}, {l}, {/SPACE}, {g}, {r}, {k}, {c}, {z}, {y}]
 [{h}, {l}, {g}, {c}, {z}, {y}, {k}, {a}, {/SPACE}, {r}, {e}]
 first - {h} second - {l} parent - {h, l}
 first - {g} second - {c} parent - {c, g}
 first - {z} second - {y} parent - {y, z}
 first - {k} second - {a} parent - {a, k}
 first - {h, l} second - {c, g} parent - {c, g, h, l}
 first - {y, z} second - {/SPACE} parent - {/SPACE, y, z}
 first - {r} second - {a, k} parent - {a, k, r}
 first - {c, g, h, l} second - {e} parent - {c, e, g, h, l}
 first - {/SPACE, y, z} second - {a, k, r} parent - {/SPACE, a, k, r, y, z}
 first - {c, e, g, h, l} second - {/SPACE, a, k, r, y, z} parent - {/SPACE, a, c, e, g, h, k, l, r, y, z}
 └──{/SPACE, a, c, e, g, h, k, l, r, y, z}
     ├──{c, e, g, h, l}
     │   ├──{c, g, h, l}
     │   │   ├──{h, l}
     │   │   │   ├──{h}
     │   │   │   └──{l}
     │   │   └──{c, g}
     │   │       ├──{g}
     │   │       └──{c}
     │   └──{e}
     └──{/SPACE, a, k, r, y, z}
         ├──{/SPACE, y, z}
         │   ├──{y, z}
         │   │   ├──{z}
         │   │   └──{y}
         │   └──{/SPACE}
         └──{a, k, r}
             ├──{r}
             └──{a, k}
                 ├──{k}
                 └──{a}
 original - {/SPACE, a, c, e, g, h, k, l, r, y, z}
 encoded  - 000011110111111000111111011011
 */

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
    std::string exampleFileName = "example1.txt"; //TODO: FIX EXAMPLE 1111111111111111
    //generateTestFile(exampleFileName, 10000);
    
    HuffmanTree foo;
    foo.build(exampleFileName);
    
    foo.printHorizontalUnicode(foo.root());
    
    std::cout << "original - " << foo.root()->data() << std::endl;
    
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
