#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSet>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->fillNamesButton, SIGNAL(clicked(bool)), this, SLOT(onFillNamesButton()));
    connect(ui->getResultButton, SIGNAL(clicked(bool)), this, SLOT(onGetResultButton()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onFillNamesButton() {
    ui->textEditNames->clear();
    names.clear();
    const int numberOfInnerLists = 3;
    const int namesPerInnerList = 3;

    for (int i = 0; i < numberOfInnerLists; ++i) {
        QList<QString> innerList;
        for (int j = 0; j < namesPerInnerList; ++j) {
            int randomIndex = rand() % availableNames.size();
            innerList.append(availableNames[randomIndex]);
        }
        names.append(innerList);
    }

    for (int i = 0; i < numberOfInnerLists; ++i) {
        for (int j = 0; j < namesPerInnerList; ++j) {
            ui->textEditNames->insertPlainText(names[i][j] + " ");
        }
        ui->textEditNames->insertPlainText("\n");
    }
}

void MainWindow::onGetResultButton() {
    ui->textEditInAll->clear();
    ui->textEditInSome->clear();
    ui->textEditNotInAny->clear();

    QSet<QString> allNames;

    for (const auto& name : availableNames) {
        allNames.insert(name);
    }

    // Имена, встречающиеся во всех классах
    QSet<QString> commonNames = QSet<QString>(names[0].begin(), names[0].end());
    for (const auto& classNames : names) {
        commonNames.intersect(QSet<QString>(classNames.begin(), classNames.end()));
    }

    // Имена, встречающиеся только в некоторых классах
    QSet<QString> someClassesNames;
    for (const auto& classNames : names) {
        someClassesNames.unite(QSet<QString>(classNames.begin(), classNames.end()));
    }

    QSet<QString> onlySomeClassesNames = someClassesNames - commonNames;

    // Имена, которые не встречаются ни в одном классе
    QSet<QString> notInAnyClass = allNames - someClassesNames;

    // Вывод результатов
    for (const auto& name : commonNames) {
        ui->textEditInAll->insertPlainText(name + " ");
    }

    for (const auto& name : onlySomeClassesNames) {
        ui->textEditInSome->insertPlainText(name + " ");
    }

    for (const auto& name : notInAnyClass) {
        ui->textEditNotInAny->insertPlainText(name + " ");
    }
}
