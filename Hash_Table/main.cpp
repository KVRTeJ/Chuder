#include <QApplication>

#include "MainWindow.h"

#include "HashTable.h"

int main() {
    HashTable foo(10);
    std::cout << foo.m_hashFunction->hash(static_cast<int>(' '), 2) << std::endl;
    foo.add(1, "first");
    //foo.add(2, "second");
    //foo.add(3, "third");

    foo.print();
    return -1;
}
