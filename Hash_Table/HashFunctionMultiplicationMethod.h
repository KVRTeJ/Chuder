#ifndef HASHFUNCTIONMULTIPLICATIONMETHOD_H
#define HASHFUNCTIONMULTIPLICATIONMETHOD_H

#include <math.h>

#include "IHashFunction.h"

class HashFunctionMultiplicationMethod : public IHashFunction {
public:
    HashFunctionMultiplicationMethod() = default;

    ~HashFunctionMultiplicationMethod() override = default;

    int hash(const int size, const int key) const override {
        return static_cast<int>((key * - (1 - (sqrt(5)) * size))) % size;
    }

    static HashFunctionMultiplicationMethod function;
};

inline HashFunctionMultiplicationMethod HashFunctionMultiplicationMethod::function;

#endif // HASHFUNCTIONMULTIPLICATIONMETHOD_H
