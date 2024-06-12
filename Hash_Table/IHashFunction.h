#ifndef IHASHFUNCTION_H
#define IHASHFUNCTION_H

#include <iostream>

class IHashFunction {
public:
    virtual ~IHashFunction() = default;
    virtual int hash(const int size, const int key) const = 0;
};

#endif // IHASHFUNCTION_H
