#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->comboBox->addItem("min", QVariant(1));
    ui->comboBox->addItem("max", QVariant(2));
    connect(ui->createMatrixButton, SIGNAL(clicked(bool)), this, SLOT(onCreateButtonClicked()));
    connect(ui->findButton, SIGNAL(clicked(bool)), this, SLOT(onFindButtonClicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onCreateButtonClicked() {
    ui->matrixTextEdit->clear();

    int rows = ui->rows->text().toInt();
    int cols = ui->cols->text().toInt();

    //Create array
    arr = new int*[rows];
    for(int i = 0; i < rows; i++) {
        arr[i] = new int [cols];
    }

    //Fill array
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            arr[i][j] = rand() % 9 + 1;
            ui->matrixTextEdit->insertPlainText(QString::number(arr[i][j]) + " ");
        }
        ui->matrixTextEdit->insertPlainText("\n");
    }
}

void MainWindow::onFindButtonClicked() {
    ui->resultTextEdit->clear();

    int rows = ui->rows->text().toInt();
    int cols = ui->cols->text().toInt();

    QString comboBoxText = ui->comboBox->currentText();

    if(comboBoxText == "min") {
        int min = 10;
        for(int i = 0; i < rows; i++) {
            for(int j = 0; j < cols; j++) {
                if(arr[i][j] < min) {
                    min = arr[i][j];
                }
            }
            ui->resultTextEdit->insertPlainText(QString::number(min) + " ");
            min = 10;
        }
    } else {
        int max = 0;
        for(int i = 0; i < rows; i++) {
            for(int j = 0; j < cols; j++) {
                if(arr[i][j] > max) {
                    max = arr[i][j];
                }
            }
            ui->resultTextEdit->insertPlainText(QString::number(max) + " ");
            max = 0;
        }
    }
}













