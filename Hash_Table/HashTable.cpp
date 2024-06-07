#include "HashTable.h"

int HashTable::add(Cell& pair) {
    const int expected = m_hashFunction->hash(m_data.size(), pair.key());
    std::cout << "key - " << pair.key() << " hash - " << expected << std::endl;
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

    std::cout << "processing current" << std::endl;

    Cell* current = &m_data[index];
    while(current) {
        if(current->key() == pair.key()) {
            std::cout << "break\n";
            break;
        }
        std::cout << "keys - " << current->key() << " = " << pair.key() << std::endl;
        current = current->next();
    }

    std::cout << "current processed" << std::endl;

    if(!current) {
        std::cout << "!current - > false\n";
        return false;
    }

    std::cout << "current1" << std::endl;

    if(!current->next()) {
        if(current->prev()) {
            current->setPrev(nullptr);
        }
        *current = Cell();
        std::cout << "removed - > true \n";
        return true;
    }

    Cell* it = current->next();
    do {
        it->m_swap(current);
        current = current->next();
        it = current->next();
    } while(it);
    if(current->prev()) {
        current->setPrev(nullptr);
    }
    *current = Cell();

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

void HashTable::Cell::m_swap(Cell* other) {
    std::swap(this->m_key, other->m_key);
    std::swap(this->m_value, other->m_value);
}
