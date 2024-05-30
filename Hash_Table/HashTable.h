#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <string>

class Pair {
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

class HashTable {
public:
    HashTable() {
        std::cout << "HashTable is here!" << std::endl;
    }
    HashTable(const HashTable& other) = default;

    ~HashTable() {
        std::cout << "HashTable was here!" << std::endl;
    }

private:
    std::vector<Pair> m_data = {};
};

#endif // HASHTABLE_H
