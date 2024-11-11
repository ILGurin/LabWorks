#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->Process, SIGNAL(clicked(bool)), this, SLOT(on_processButton_clicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_processButton_clicked(){
    int numberOne, numberTwo, numberThree;
    numberOne = ui->lineEdit->text().toInt();
    numberTwo = ui->lineEdit_2->text().toInt();
    numberThree = ui->lineEdit_3->text().toInt();

    if(numberOne >= numberTwo) {
        if(numberTwo >= numberThree) {
            ui->lineEdit->setText(QString::number(numberOne * 2));
            ui->lineEdit_2->setText(QString::number(numberTwo * 2));
            ui->lineEdit_3->setText(QString::number(numberThree * 2));
        } else {
            ui->lineEdit->setText(QString::number(-numberOne));
            ui->lineEdit_2->setText(QString::number(-numberTwo));
            ui->lineEdit_3->setText(QString::number(-numberThree));
        }
    } else {
        ui->lineEdit->setText(QString::number(-numberOne));
        ui->lineEdit_2->setText(QString::number(-numberTwo));
        ui->lineEdit_3->setText(QString::number(-numberThree));
    }
}
