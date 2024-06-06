#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <string>

#include "IHashFunction.h"
#include "HashFunctionQuadraticTest.h"

class HashTable {
public:
    class Pair;
public:
    explicit HashTable(const int size, IHashFunction* hashFunction = nullptr)
        : m_data(std::vector<Pair>(size)) {
        if(hashFunction)
            m_hashFunction = hashFunction;
        else {
            m_hashFunction = &HashFunctionQuadraticTest::function;
        }
    }
    HashTable(const HashTable& other) = default;

    ~HashTable() = default;

    bool add(Pair& pair);
    bool add(const int key, const std::string& value);
    bool remove(const Pair& pair);
    bool remove(const int key); //TODO: implement ^

    bool contains(const Pair& pair) const;
    bool contains(const int key, const std::string& value) const;

    void print() const;

    void changeHashFunction(IHashFunction* hashFunction);

    void resize(const int size);

    HashTable& operator = (const HashTable& other) = default;
    std::string& operator [] (const int key);

private:
    std::vector<Pair> m_data = {};
    IHashFunction* m_hashFunction = nullptr;
};

class HashTable::Pair {
    friend class HashTable;
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
    const Pair* next() const {return m_next;}
    void setNext(Pair* next) {m_next = next;}

private:
    int m_key = {};
    std::string m_value = {};

    Pair* m_next = nullptr;
};

#endif // HASHTABLE_H
