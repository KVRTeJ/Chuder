#include "HashTable.h"

void HashTable::add(const Pair& pair) {
    m_data[m_hashFunction->hash] = pair;
}
