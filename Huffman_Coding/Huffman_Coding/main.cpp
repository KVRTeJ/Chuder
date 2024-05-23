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

int main(int argc, const char * argv[]) {
    std::string exampleFileName = "example.txt";
    std::string example = "ehal greka cerez reky";
    
    
    HuffmanTree foo;
    foo.build(exampleFileName);
    
    foo.printHorizontalUnicode(foo.root());
    
    std::cout << "original - " << foo.root()->data() << std::endl;
    
    std::string encodeFile = "example_encode.txt";
    foo.encode(exampleFileName, encodeFile);
    
    
    std::ifstream encodeResult(encodeFile);
    BoolVector bv(0, 0);
    int unsignif = 0;
    encodeResult >> unsignif;
    char temp;
    while(encodeResult >> std::noskipws >> temp) {
        bv.add(temp);
    }
    bv.print();
    return -1;
    std::string decodeStr;
    //foo.decode(encodeStr, decodeStr);
    std::cout << "decoded  - " << decodeStr << std::endl;
    assert(foo.root()->data() == decodeStr);
    return 0;
}
