#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QList<QString> availableNames = {"Alice", "Melissa", "Mia", "Marnie", "Caroline"};
    QList<QList<QString>> names;

private slots:
    void onFillNamesButton();
    void onGetResultButton();
};
#endif // MAINWINDOW_H
