#include "HashTable.h"

bool HashTable::add(Pair& pair) {
    int expected = m_hashFunction->hash(m_data.size(), pair.key());

    std::cout << "expected - " << expected <<std::endl;
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
