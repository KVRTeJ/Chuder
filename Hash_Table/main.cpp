#include <stdlib.h>

#include <QApplication>
#include <QDebug>

#include "MainWindow.h"

#include "HashTable.h"

int main(int argc, char *argv[])
{

    HashTable tabl(8);
    tabl.add(1, "1");
    tabl.add(2, "2");
    tabl.add(33, "3");
    tabl.add(10, "4");
    tabl.add(5, "5");
    tabl.add(3, "6");
    tabl.add(7, "7");
    tabl.add(20, "8");

    tabl.print();

    std::cout << std::endl;

    tabl.remove(5);
    tabl.print();
    /*
    QApplication app(argc, argv);
    MainWindow mw;
    mw.show();
    return app.exec();
*/
}
