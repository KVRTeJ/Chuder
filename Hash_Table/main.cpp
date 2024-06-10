#include <stdlib.h>

#include <QApplication>
#include <QDebug>

#include "MainWindow.h"

#include "HashTable.h"

int main(int argc, char *argv[]) {
    /*
    HashTable foo(10);
    std::cout << foo.add(10, "10") << std::endl;
    std::cout << foo.add(10, "20") << std::endl;
    std::cout << foo.add(10, "30") << std::endl;

    foo.print();
    */
    QApplication app(argc, argv);
    MainWindow mw;
    mw.show();
    return app.exec();
}
