#include "HashTable.h"

int HashTable::add(Cell& pair) {
    const int expected = m_hashFunction->hash(m_data.size(), pair.key());

    if(m_data[expected].value() == "") {
        m_data[expected] = pair;
    } else {
        Cell* current = &m_data[expected];
        while(current->next()) {
            current = current->next();
        }

        bool hasFound = false;
        int i = 0;
        for(; i < m_data.size(); ++i) {
            if(m_data[i].value() == "") {
                m_data[i] = pair;
                hasFound = true;
                break;
            }
        }

        if(!hasFound) {
            return -1;
        }

        current->setNext(&m_data[i]);
        m_data[i].setPrev(current);
        return i;
    }

    return expected;
}

int HashTable::add(const int key, const std::string& value) {
    Cell pair(key, value, nullptr);
    return add(pair);
}

bool HashTable::remove(const Cell& pair) {
    const int index =  m_hashFunction->hash(m_data.size(), pair.key());

    if(m_data[index].value() == "") {
        return false;
    }

    if(!m_data[index].next()) {
        m_data.erase(m_data.begin() + index);
        return true;
    }

    Cell* last = &m_data[index];
    while(last->next()) {
        last = last->next();
    }

    Cell* target = &m_data[index];
    std::swap(*target, *last);


    return true;
}

bool HashTable::remove(const int key) {
    return remove(Cell(key));
}

bool HashTable::contains(const Cell& pair) const {
    int index = m_hashFunction->hash(m_data.size(), pair.key());

    for(const Cell* current = &m_data[index]; current->next(); current = current->next()) {
        if(current->value() == pair.value()) {
            return true;
        }
    }

    return false;
}

bool HashTable::contains(const int key, const std::string& value) const {
    return contains(Cell(key, value));
}

void HashTable::print() const {
    for(int i = 0; i < m_data.size(); ++i) {
        if(m_data[i].value() != "") {
            std::cout << '[' << i << ']';
            std::cout << ' ' << m_data[i].key();
            std::cout << " - " << m_data[i].value();
            std::cout << std::endl;
        }
    }
}

void HashTable::changeHashFunction(IHashFunction* hashFunction) {
    if(!hashFunction || m_hashFunction == hashFunction) {
        std::cout << "exit" << std::endl;
        return;
    }

    m_hashFunction = hashFunction;
    resize(m_data.size());
}

void HashTable::resize(const int size) {
    std::vector<Cell> oldData(size);
    std::swap(oldData, m_data);

    for(int i = 0; i < oldData.size(); ++i) {
        if(oldData[i].value() != "") {
            add(oldData[i].key(), oldData[i].value());
        }
    }
}


std::string& HashTable::operator [] (const int key) {
    int index = m_hashFunction->hash(m_data.size(), key);
    if(m_data[index].value() == "") {
        m_data[index] = Cell(key);
    }

    return m_data[index].m_value;
}
