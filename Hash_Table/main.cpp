#include <QApplication>

#include "MainWindow.h"

#include "HashTable.h"

int main() {
    HashFunctionQuadraticTest func;
    HashTable foo(10, &func);
    foo.add(1, "first");
    foo.add(1, "second");
    foo.add(8, "third");

    //foo.add(2, "second");
    //foo.add(3, "third");

    foo.print();
    return -1;
}
