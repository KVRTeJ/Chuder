#include <stdlib.h>

#include <QApplication>
#include <QDebug>

#include "MainWindow.h"

#include "HashTable.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MainWindow mw;
    mw.show();
    return app.exec();
}
