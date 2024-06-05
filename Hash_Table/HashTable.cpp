#include "HashTable.h"

bool HashTable::add(Pair& pair) {
    int expected = m_hashFunction->hash(m_data.size(), pair.key());

    if(m_data[expected].value() == "") {
        m_data[expected] = pair;
    } else {
        Pair* current = &m_data[expected];
        while(current->next()) {
            current = current->next();
        }
        current->setNext(&pair);

        bool hasFound = false;
        for(int i = 0; i < m_data.size(); ++i) {
            if(m_data[i].value() == "") {
                m_data[i] = pair;
                hasFound = true;
                break;
            }
        }

        if(!hasFound) {
            return false;
        }
    }

    return true;
}

bool HashTable::add(const int key, const std::string& value) {
    Pair pair(key, value, nullptr);
    return add(pair);
}

void HashTable::resize(const int size) {
    std::vector<Pair> oldData(size);
    std::swap(oldData, m_data);

    for(int i = 0; i < oldData.size(); ++i) {
        if(oldData[i].value() != "") {
            add(oldData[i].key(), oldData[i].value());
            std::cout << "added - " << oldData[i].key() << " - " << oldData[i].value() << std::endl;
        }
    }
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
