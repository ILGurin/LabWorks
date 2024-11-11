#include <QCoreApplication>
#include <QQueue>
#include <iostream>

using namespace std;

void printQueue(QQueue<int>& queue) {
    for (int i = 0; i < queue.size(); ++i) {
        cout << queue.at(i) << " ";
    }
    cout << endl;
}

void processQueue(QQueue<int> & queue) {
    for (int i = 0; i < queue.size() / 2; ++i) {
        int firstValue = queue.at(i);
        int lastValue = queue.at(queue.size() - 1 - i);
        queue[i] = firstValue + lastValue;
        //queue[queue.size() - 1 - i] = firstValue + lastValue;
    }
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    srand(static_cast<unsigned int>(time(0)));

    QQueue<int> queue;
    for (int i = 0; i < 8; ++i) {
        int randomValue = rand() % 101;
        queue.enqueue(randomValue);
    }
    cout << "Original queue: ";
    printQueue(queue);
    processQueue(queue);
    cout << "Result queue: ";
    printQueue(queue);

    return a.exec();
}
