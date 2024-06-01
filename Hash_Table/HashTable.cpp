#include "HashTable.h"

void HashTable::add(const Pair& pair) {
    int expected = m_hashFunction->hash(pair.key());

    if(m_data[expected].value() == "") {
        m_data[expected] = pair;
    } else {
        m_data[expected].setNext(&pair);
        bool hasFound = false;
        for(int i = 0; i < m_data.size(); ++i) {
            if(m_data[i].value() == "") {
                m_data[i] = pair;
                hasFound = true;
                break;
            }
        }

        if(!hasFound) {
            int oldSize = m_data.size();
            resize(oldSize * 2);
            m_data[oldSize] = pair;
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
