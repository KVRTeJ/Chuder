#ifndef HASHFUNCTIONQUADRATICTEST_H
#define HASHFUNCTIONQUADRATICTEST_H

#include "IHashFunction.h"

class HashFunctionQuadraticTest : public IHashFunction {
public:
    HashFunctionQuadraticTest() = default;
    ~HashFunctionQuadraticTest() override = default;

    int hash(const int size, const int key) const override {
        return ((key % size) + 25 % 5 + 25 % 7) % size;
    }

    static HashFunctionQuadraticTest function;
};

inline HashFunctionQuadraticTest HashFunctionQuadraticTest::function;

#endif // HASHFUNCTIONQUADRATICTEST_H
