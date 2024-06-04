#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <string>
#include <algorithm>
#include <math.h>

class IHashFunction {
public:
    virtual ~IHashFunction() = default;
    virtual int hash(const int size, const int key) = 0;
};

class HashFunctionQuadraticTest : public IHashFunction {
public:
    HashFunctionQuadraticTest() = default;
    ~HashFunctionQuadraticTest() override = default;

    int hash(const int size, const int key) override { //TODO: implement me
        return ((key % size) + 25 % 5 + 25 % 7) % size;
    }

    static HashFunctionQuadraticTest func();
};

class HashFunctionMultiplicationMethod : public IHashFunction {
public:
    HashFunctionMultiplicationMethod() = default;

    ~HashFunctionMultiplicationMethod() override = default;

    int hash(const int size, const int key) override { //TODO: implement me
        return (key * -(1 - static_cast<int>(sqrt(5))) * size) % size;
    }
};

class HashTable {
public:
    class Pair;
public:
    explicit HashTable(const int size, IHashFunction* hashFunction = nullptr)
        : m_data(std::vector<Pair>(size)) {
        if(hashFunction)
            m_hashFunction = hashFunction;
        else {
            HashFunctionQuadraticTest func;
            IHashFunction* temp = dynamic_cast<IHashFunction*>(&func);
            std::swap(temp, m_hashFunction);
        }
    }
    HashTable(const HashTable& other) = default;

    ~HashTable() = default;

    bool add(Pair& pair); //FIXME: collisions
    bool add(const int key, const std::string& value); //TODO: implement me
    bool remove(const Pair& pair); //TODO: implement me

    bool contains(const Pair& pair) const; //TODO: implement me

    void print() const; //TODO: implement me

    void changeHashFunction(IHashFunction* hashFunction); //TODO: make hash-functions

    void resize(const int size); //TODO: implement me

    HashTable& operator = (const HashTable& other) = default;
    std::string& operator [] (const int key); //TODO: implement me

//private:
    std::vector<Pair> m_data = {};
    IHashFunction* m_hashFunction = nullptr;
};

class HashTable::Pair {
public:
    Pair(const int key = {}, const std::string& value = {}, Pair* next = nullptr)
        : m_key(key), m_value(value), m_next(next)
    {}

    ~Pair() = default;

    int key() const {return m_key;}
    std::string value() const {return m_value;}

    void setKey(const int key) {m_key = key;}
    void setValue(const std::string& value) {m_value = value;}

    Pair* next() {return m_next;}
    void setNext(Pair* next) {m_next = next;}

private:
    int m_key = {};
    std::string m_value = {};

    Pair* m_next = nullptr;
};

#endif // HASHTABLE_H
