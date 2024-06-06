#include <QApplication>
#include <assert.h>

#include "MainWindow.h"

#include "HashTable.h"
#include "HashFunctionMultiplicationMethod.h"

int main() {
    HashFunctionQuadraticTest func;
    HashTable foo(10, &func);
    foo.add(20, "first");
    foo.add(10, "second");
    foo.add(8, "third");
    foo.add(4, "first1");
    foo.add(21, "first2");foo.add(30, "first3");foo.add(1, "first4");foo.add(34, "first5");foo.add(54, "first6");foo.add(1, "first7");foo.add(1, "first8");

    foo.print();

    std::cout << "resizing. . ." << std::endl;
    foo.resize(6);
    foo.print();

    std::cout << std::endl;

    HashFunctionMultiplicationMethod funcMult;
    foo.changeHashFunction(&funcMult);
    foo.print();

    return -1;
}
