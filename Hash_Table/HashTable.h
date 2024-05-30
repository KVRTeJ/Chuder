#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <string>

struct Pair {
    int key = {};
    std::string value = {};
    Pair* next = nullptr;
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
