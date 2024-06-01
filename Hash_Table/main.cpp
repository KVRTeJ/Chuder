#include <QApplication>

#include "MainWindow.h"

#include "HashTable.h"

int main() {
    HashFunctionMultiplicationMethod hashFoo(10);

    HashTable foo(10, &hashFoo);
    foo.add(HashTable::Pair(1, "first"));
    foo.add(HashTable::Pair(2, "second"));
    foo.add(HashTable::Pair(3, "third"));

    foo.print();
    return -1;
}
