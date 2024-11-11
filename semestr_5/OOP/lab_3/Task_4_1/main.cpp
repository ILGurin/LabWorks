#include <QCoreApplication>
#include <QStack>
#include <iostream>

using namespace std;

void printStack(QStack<int> stack) {
    while (!stack.isEmpty()) {
        cout << stack.pop() << " ";
    }
    cout << endl;
}

QStack<int> processStack(QStack<int> stack) {
    QVector<int> tempVector;
    QStack<int> temp;

    int stackSize = stack.size();
    for(int i = 0; i < stackSize; ++i) {
        int value = stack.pop();
        value = value % (i + 1);
        tempVector.push_back(value);
    }

    for (int i = tempVector.size() - 1; i >= 0; --i) {
        temp.push(tempVector[i]);
    }
    return temp;
}

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);
    srand(static_cast<unsigned int>(time(0)));
    QStack<int> stack;

    // Fill the stack with 10 random numbers from [-10, 80]
    for (int i = 0; i < 10; ++i) {
        int randomValue = rand() % 91 - 10;
        stack.push(randomValue);
    }

    cout << "Original stack: ";
    printStack(stack);
    stack = processStack(stack);
    cout << "Modified Stack Values: ";
    printStack(stack);

    return a.exec();
}
