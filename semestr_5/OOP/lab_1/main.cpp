//Просмотрщик
#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QSpinBox>
#include <QSlider>
#include <QPlainTextEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>

void setColor(QPlainTextEdit* display, int red, int green, int blue)
{
    QString color = QString("#%1%2%3")
    .arg(red, 2, 16, QLatin1Char('0'))
        .arg(green, 2, 16, QLatin1Char('0'))
        .arg(blue, 2, 16, QLatin1Char('0'));
    display->setStyleSheet(QString("QPlainTextEdit { background-color: %1; }").arg(color));
}
void setRed(QSpinBox* redSpinBox, QSlider* redSlider, int value) {
    redSpinBox->setValue(value);
    redSlider->setValue(value);
}
void setGreen(QSpinBox* greenSpinBox, QSlider* greenSlider, int value) {
    greenSpinBox->setValue(value);
    greenSlider->setValue(value);
}
void setBlue(QSpinBox* blueSpinBox, QSlider* blueSlider, int value) {
    blueSpinBox->setValue(value);
    blueSlider->setValue(value);
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QWidget window;
    window.setWindowTitle("Цветовой подбор");
    window.resize(400, 400);
    QLabel redLabel("Красный:");
    QLabel greenLabel("Зеленый:");
    QLabel blueLabel("Синий:");


    QSpinBox redSpinBox, greenSpinBox, blueSpinBox;
    for (auto& spinBox : { &redSpinBox, &greenSpinBox, &blueSpinBox }) {
        spinBox->setRange(0, 255);
        spinBox->setStyleSheet("QSpinBox { width: 70px; }");
    }

    QSlider redSlider(Qt::Horizontal), greenSlider(Qt::Horizontal), blueSlider(Qt::Horizontal);
    redSlider.setRange(0, 255);
    greenSlider.setRange(0, 255);
    blueSlider.setRange(0, 255);

    QPlainTextEdit colorDisplay;
    colorDisplay.setFixedSize(120, 120);
    colorDisplay.setEnabled(false);


    QGridLayout layout;

    layout.addWidget(&redLabel, 0, 0);
    layout.addWidget(&redSpinBox, 0, 1);
    layout.addWidget(&redSlider, 0, 2);

    layout.addWidget(&greenLabel, 1, 0);
    layout.addWidget(&greenSpinBox, 1, 1);
    layout.addWidget(&greenSlider, 1, 2);

    layout.addWidget(&blueLabel, 2, 0);
    layout.addWidget(&blueSpinBox, 2, 1);
    layout.addWidget(&blueSlider, 2, 2);

    layout.addWidget(&colorDisplay, 0, 3, 3, 1);

    window.setLayout(&layout);



    QObject::connect(&redSpinBox, &QSpinBox::valueChanged,
                     [&](int value) {
                        setRed(&redSpinBox, &redSlider, value);
                        setColor(
                            &colorDisplay,
                            redSpinBox.value(),
                            greenSpinBox.value(),
                            blueSpinBox.value()
                        );
                    });

    QObject::connect(&greenSpinBox, &QSpinBox::valueChanged,
                     [&](int value) {
                        setGreen(&greenSpinBox, &greenSlider, value);
                        setColor(
                            &colorDisplay,
                            redSpinBox.value(),
                            greenSpinBox.value(),
                            blueSpinBox.value()
                        );
                    });

    QObject::connect(&blueSpinBox, &QSpinBox::valueChanged,
                     [&](int value) {
                        setBlue(&blueSpinBox, &blueSlider, value);
                        setColor(
                            &colorDisplay,
                            redSpinBox.value(),
                            greenSpinBox.value(),
                            blueSpinBox.value()
                        );
                    });

    QObject::connect(&redSlider, &QSlider::sliderMoved,
                     [&](int value) {
                        setRed(&redSpinBox, &redSlider, value);
                        setColor(
                            &colorDisplay,
                            redSpinBox.value(),
                            greenSpinBox.value(),
                            blueSpinBox.value()
                        );
                    });

    QObject::connect(&greenSlider, &QSlider::sliderMoved,
                     [&](int value) {
                        setGreen(&greenSpinBox, &greenSlider, value);
                        setColor(
                            &colorDisplay,
                            redSpinBox.value(),
                            greenSpinBox.value(),
                            blueSpinBox.value()
                        );
                    });

    QObject::connect(&blueSlider, &QSlider::sliderMoved,
                     [&](int value) {
                        setBlue(&blueSpinBox, &blueSlider, value);
                        setColor(
                            &colorDisplay,
                            redSpinBox.value(),
                            greenSpinBox.value(),
                            blueSpinBox.value()
                        );
                    });

    setColor(&colorDisplay, redSpinBox.value(), greenSpinBox.value(), blueSpinBox.value());

    window.show();
    return app.exec();
}
//Текстовый обозреватель
/*#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

void openFile(QTextEdit *textEdit)
{
    QString fileName = QFileDialog::getOpenFileName(nullptr, "Открыть .txt файл", "", "Text Files (*.txt);;All Files (*)");
    if (fileName.isEmpty())
        return;

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::warning(nullptr, "Ошибка", "Не удалось открыть файл");
        return;
    }

    QTextStream in(&file);
    QString fileContent = in.readAll();
    file.close();

    textEdit->setPlainText(fileContent);
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QWidget window;
    window.setWindowTitle("Обозреватель текста");
    window.resize(400, 300);
    QPalette palette = window.palette();
    palette.setColor(QPalette::Window, Qt::lightGray);
    window.setAutoFillBackground(true);
    window.setPalette(palette);

    QTextEdit *textEdit = new QTextEdit(&window);
    textEdit->setReadOnly(true);
    textEdit->setStyleSheet("font-family: Arial; font-size: 12px;");

    QPushButton *openButton = new QPushButton("Открыть .txt файл", &window);

    QVBoxLayout *layout = new QVBoxLayout(&window);
    layout->addWidget(textEdit);
    layout->addWidget(openButton);

    // Подключение сигнала нажатия кнопки к функции открытия файла
    QObject::connect(openButton, &QPushButton::clicked, [&]() {
        openFile(textEdit);
    });

    window.setLayout(layout);
    window.show();

    return app.exec();
}*/
