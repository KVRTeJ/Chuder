#include "HashTable.h"

bool HashTable::add(Pair& pair) {
    const int expected = m_hashFunction->hash(m_data.size(), pair.key());

    if(m_data[expected].value() == "") {
        m_data[expected] = pair;
    } else {
        Pair* current = &m_data[expected];
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
            return false;
        }

        current->setNext(&m_data[i]);
    }

    return true;
}

bool HashTable::add(const int key, const std::string& value) {
    Pair pair(key, value, nullptr);
    return add(pair);
}

bool HashTable::remove(const Pair& pair) {
    const int index =  m_hashFunction->hash(m_data.size(), pair.key());

    if(m_data[index].value() == "") {
        return false;
    }

    auto replacement = m_data[index].next();
    m_data.erase(m_data.begin() + index);
    if(replacement) {
        m_data[index] = *replacement;
    }

    return true;
}

bool HashTable::remove(const int key) {
    return remove(Pair(key));
}

bool HashTable::contains(const Pair& pair) const {
    int index = m_hashFunction->hash(m_data.size(), pair.key());

    for(const Pair* current = &m_data[index]; current->next(); current = current->next()) {
        if(current->value() == pair.value()) {
            return true;
        }
    }

    return false;
}

bool HashTable::contains(const int key, const std::string& value) const {
    return contains(Pair(key, value));
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
    std::vector<Pair> oldData(size);
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
        m_data[index] = Pair(key);
    }

    return m_data[index].m_value;
}
