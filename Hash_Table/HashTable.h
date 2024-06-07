#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <string>

//#include "HashTableWidget.h"

#include "IHashFunction.h"
#include "HashFunctionQuadraticTest.h"

class HashTable {
    friend class HashTableWidget;
public:
    class Cell;
public:
    HashTable(const int size = 10, IHashFunction* hashFunction = nullptr)
        : m_data(std::vector<Cell>(size)) {
        if(hashFunction)
            m_hashFunction = hashFunction;
        else {
            m_hashFunction = &HashFunctionQuadraticTest::function;
        }
    }
    HashTable(const HashTable& other) = default;

    ~HashTable() = default;

    Cell getCell(const int index) const;

    int add(Cell& pair);
    int add(const int key, const std::string& value);
    bool remove(const Cell& pair);
    bool remove(const int key);

    bool contains(const Cell& pair) const;
    bool contains(const int key, const std::string& value) const;

    void print() const;

    void changeHashFunction(IHashFunction* hashFunction);

    void resize(const int size);

    HashTable& operator = (const HashTable& other) = default;
    std::string& operator [] (const int key);
private:
    int m_find(const int key) const;
private:
    std::vector<Cell> m_data = {};
    IHashFunction* m_hashFunction = nullptr;
};

class HashTable::Cell {
    friend class HashTable;
public:
    Cell(const int key = {}, const std::string& value = {}, Cell* prev = nullptr, Cell* next = nullptr)
        : m_key(key), m_value(value), m_prev(prev), m_next(next)
    {}

    ~Cell() = default;

    int key() const {return m_key;}
    std::string value() const {return m_value;}

    void setKey(const int key) {m_key = key;}
    void setValue(const std::string& value) {m_value = value;}

    Cell* next() {return m_next;}
    const Cell* next() const {return m_next;}
    Cell* prev() {return m_prev;}
    const Cell* prev() const {return m_prev;}
    void setPrev(Cell* prev) {m_prev = prev;}
    void setNext(Cell* next) {m_next = next;}
private:
    void m_swap(Cell* other);
private:
    int m_key = {};
    std::string m_value = {};

    Cell* m_prev = nullptr;
    Cell* m_next = nullptr;
};

#endif // HASHTABLE_H
