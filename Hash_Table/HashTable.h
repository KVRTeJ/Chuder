#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <string>

class IHashFunction {
public:
    virtual int hash(const int key) = 0;
};

class HashFunction : public IHashFunction {
public:
    explicit HashFunction(const int size)
        : m_size((size >= 0
                  ? size
                      : 0 ))
    {}

    ~HashFunction() = default;

    int size() const {return m_size;}
    void setSize(const int size) {m_size = (size >= 0
                                            ? size
                                                : 0 );}

    int hash(const int key) override { //TODO: implement me
        return ((key % m_size) + 5 + 7) % m_size; // hi(K) = (hi-1(K) + c × i + d × i2) mod N
    }

private:
    int m_size = 0;
};

class HashTable {
public:
    class Pair;
public:
    HashTable(const int size, IHashFunction* hashFunction = &foo)
        : m_data(std::vector<Pair>(size)), m_hashFunction(hashFunction)
    {}
    HashTable(const HashTable& other) = default;

    ~HashTable() = default;

    void add(const Pair& pair); //TODO: implement me
    bool remove(const Pair& pair); //TODO: implement me

    bool contains(const Pair& pair) const; //TODO: implement me

    void print() const; //TODO: implement me

    void changeHashFunction(IHashFunction* hashFunction); //TODO: make hash-functions

    void resize(const int size); //TODO: implement me

    HashTable& operator = (const HashTable& other) = default;
    std::string& operator [] (const int key); //TODO: implement me

    static HashFunction foo;
private:
    std::vector<Pair> m_data = {};
    IHashFunction* m_hashFunction = &foo;
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
