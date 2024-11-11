#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->swapFilesButton, SIGNAL(clicked(bool)), this, SLOT(onSwapFilesButtonPressed()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onSwapFilesButtonPressed() {
    QString f1 = "C:\\Users\\ASUS\\Documents\\GitHub\\LabWorks\\semestr_5\\OOP\\lab_3\\Task_6\\file1.txt";
    QString f2 = "C:\\Users\\ASUS\\Documents\\GitHub\\LabWorks\\semestr_5\\OOP\\lab_3\\Task_6\\file2.txt";
    QString h = "C:\\Users\\ASUS\\Documents\\GitHub\\LabWorks\\semestr_5\\OOP\\lab_3\\Task_6\\helperFile.txt";

    QFile file1(f1);
    if (!file1.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return;
    }

    QFile file2(f2);
    if (!file2.open(QIODevice::ReadOnly | QIODevice::Text)) {
        file1.close();
        return;
    }

    QFile helperFile(h);
    if (!helperFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        file1.close();
        file2.close();
        return;
    }

    QTextStream in1(&file1);
    QTextStream outHelper(&helperFile);

    while (!in1.atEnd()) {
        QString line = in1.readLine();
        outHelper << line << "\n";
    }

    file1.close();

    QFile outputFile1(f1);
    if (!outputFile1.open(QIODevice::WriteOnly | QIODevice::Text)) {
        file2.close();
        helperFile.close();
        return;
    }

    QTextStream in2(&file2);
    QTextStream outFile1(&outputFile1);

    while (!in2.atEnd()) {
        QString line = in2.readLine();
        outFile1 << line << "\n";
    }

    file2.close();
    outputFile1.close();

    file1.close();
    helperFile.close();

    QFile helperInput(h);
    if (!helperInput.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return;
    }

    QFile outputFile2(f2);
    if (!outputFile2.open(QIODevice::WriteOnly | QIODevice::Text)) {
        helperInput.close();
        return;
    }

    QTextStream outFile2(&outputFile2);

    while (!helperInput.atEnd()) {
        QString line = helperInput.readLine();
        outFile2 << line << "\n"; // Write back to f2
    }

    helperInput.close();
    outputFile2.close();

    QFile::remove(h);

}
