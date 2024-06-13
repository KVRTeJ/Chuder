#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->hashTable->resize(ui->spinBox_tableSize->value());

    connect(ui->pushButton_add, &QPushButton::clicked, this, [this]() {
        ui->hashTable->addRow(ui->spinBox_key->value(), ui->lineEdit_value->text());
    });

    connect(ui->pushButton_remove, &QPushButton::clicked, this, [this]() {
        ui->hashTable->removeRow(ui->spinBox_key->value());
    });

    connect(ui->pushButton_find, &QPushButton::clicked, this, [this]() {
        ui->hashTable->findRow(ui->spinBox_key->value());
    });

    connect(ui->pushButton_setTableSize, &QPushButton::clicked, this, [this]() {
        ui->hashTable->resize(ui->spinBox_tableSize->value());
    });

    ui->hashTable->resize(99);
    for(int i = 0; i < 89; ++i) {
        ui->hashTable->addRow(rand() % 89 * 3, QString::number(i), false);
    }
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_comboBox_activated(int index) {
    if(index == 0) {
        ui->hashTable->changeHashFunction(0);
    } else if(index == 1) {
        ui->hashTable->changeHashFunction(1);
    }
}

