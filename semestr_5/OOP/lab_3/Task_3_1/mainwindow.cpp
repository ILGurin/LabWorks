#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QList>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->createListsButton, SIGNAL(clicked(bool)), this, SLOT(onCreateListsButton()));
    connect(ui->addButton, SIGNAL(clicked(bool)), this, SLOT(onAddButton()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

QString QListToString(const QList<int>& list) {
    QString result;
    for (int number : list) {
        result += QString::number(number) + " "; // Append each number followed by a space
    }
    return result.trimmed(); // Remove trailing space
}

void MainWindow::onCreateListsButton() {
    ui->list1->clear();
    ui->list2->clear();
    list1.clear();
    list2.clear();

    int size = 10;
    for(int i = 0; i < size; i++) {
        list1.push_back(rand() % 9 + 1);
        list2.push_back(rand() % 9 + 1);
    }

    ui->list1->setText(QListToString(list1));
    ui->list2->setText(QListToString(list2));
}

void MainWindow::onAddButton(){
    if(ui->checkBoxToFirst->isChecked()) {
        list1.push_back(rand() % 9 + 1);
        ui->list1->clear();
        ui->list1->setText(QListToString(list1));
    }
    if(ui->checkBoxToSecond->isChecked()) {
        list2.push_back(rand() % 9 + 1);
        ui->list2->clear();
        ui->list2->setText(QListToString(list2));
    }
}







