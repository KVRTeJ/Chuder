#include "HashTable.h"

HashTable::Cell HashTable::getCell(const int index) const {
    return m_data[index];
}

int HashTable::add(Cell& pair) {
    if(contains(pair)) {
        return -1;
    }

    const int expected = m_hashFunction->hash(m_data.size(), pair.key());

    if(m_data[expected].key() == pair.key()) {
        return -1;
    } else if(m_data[expected].value() == "") {
        m_data[expected] = pair;
    } else {
        Cell* current = &m_data[expected];
        while(current->next()) {
            if(current->key() == pair.key()) {
                return -1;
            }
            current = current->next();
        }

        bool hasFound = false;
        int i = 0;
        for(; i < m_data.size(); ++i) {
            if(m_data[i].value() == "") {
                m_data[i] = pair;
                hasFound = true;
                break;
            } else if(m_data[i].key() == pair.key()) {
                return -1;
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

    if(m_data[index].value() == "" ) {
        return false;
    }

    Cell* current = &m_data[index];
    while(current) {
        if(current->key() == pair.key()) {
            break;
        }
        current = current->next();
    }

    if(!current) {
        return false;
    }

    if(!current->next()) {
        if(current->prev()) {
            current->prev()->setNext(nullptr);
        }
        *current = Cell();
        return true;
    }

    Cell* it = current->next();
    do {
        it->m_swap(current);
        current = current->next();
        it = current->next();
    } while(it);
    current->prev()->setNext(nullptr);
    *current = Cell();

    return true;
}

bool HashTable::remove(const int key) {
    return remove(Cell(key));
}

bool HashTable::contains(const Cell& pair) const {
    int index = m_hashFunction->hash(m_data.size(), pair.key());

    for(const Cell* current = &m_data[index]; current; current = current->next()) {
        if(current->operator == (pair)) {
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

bool HashTable::changeHashFunction(IHashFunction* hashFunction) {
    if(!hashFunction || m_hashFunction == hashFunction) {
        std::cout << "exit" << std::endl;
        return false;
    }

    m_hashFunction = hashFunction;
    resize(m_data.size());

    return true;
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

    if(m_data[index].key() != key) {
        for(Cell* it = &m_data[index]; it->next(); it = it->next()) {
            if(it->key() == key) {
                return it->m_value;
            }
        }
    }

    return m_data[index].m_value;
}

int HashTable::m_getIndex(const int key) const {
    int index = m_hashFunction->hash(m_data.size(), key);

    if(m_data[index].key() == key) {
        return index;
    } else {
        for(int i = 0; i < m_data.size(); ++i) {
            if(m_data[i].key() == key) {
                return i;
            }
        }
    }

    return -1;
}

void HashTable::Cell::m_swap(Cell* other) {
    std::swap(this->m_key, other->m_key);
    std::swap(this->m_value, other->m_value);
}
