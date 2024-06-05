#include <QApplication>

#include "MainWindow.h"

#include "HashTable.h"

int main() {
    HashFunctionQuadraticTest func;
    HashTable foo(10, &func);
    foo.add(1, "first");
    foo.add(1, "second");
    foo.add(8, "third");
    foo.add(1, "first1");
    foo.add(1, "first2");foo.add(1, "first3");foo.add(1, "first4");foo.add(1, "first5");foo.add(1, "first6");foo.add(1, "first7");foo.add(1, "first8");

    foo.print();

    std::cout << "resizing. . ." << std::endl;
    foo.resize(6);
    foo.print();
    std::cout << std::endl;std::cout << std::endl;std::cout << std::endl;

    std::cout << "hash - " << foo.m_hashFunction->hash(foo.m_data.size(), 8) << std::endl;
    foo[8] = "fixed";
    foo.print();
    return -1;
}
