#include "Task4.hpp"

std::vector<Money> copyStackToVector(std::stack<Money> stack) {
    vector<Money> vector;
    while (!stack.empty()) {
        vector.push_back(stack.top());
        stack.pop();
    }
    return vector;
}

std::stack<Money> copyVectorToStack(std::vector<Money> vector) {
    stack<Money> stack;
    for (int i = vector.size() - 1; i >= 0; i--) {
        stack.push(vector[i]);
    }
    return stack;
}

void printStack(stack<Money> stack) {
    vector<Money> vector = copyStackToVector(stack);

    for (Money num : vector) {
        cout << num;
    }
    cout << endl;
}

void addMaxElement(stack<Money>& stack) {
    vector<Money> vector = copyStackToVector(stack);

    Money maxMoney = Money(0, 0);
    for (Money money : vector) {
        if (money.getRuble() > maxMoney.getRuble()) {
            maxMoney = money;
        }
        else if (money.getRuble() > maxMoney.getRuble() && money.getCents() > maxMoney.getCents()) {
            maxMoney = money;
        }
    }
    vector.insert(vector.begin(), maxMoney);

    stack = copyVectorToStack(vector);
}

void deleteByKey(stack<Money>& stack, Money key) {
    vector<Money> vector = copyStackToVector(stack);

    auto it = find(vector.begin(), vector.end(), key);
    if (it != vector.end()) {
        vector.erase(it);
    }

    stack = copyVectorToStack(vector);
}

void addAverage(stack<Money>& stack) {
    vector<Money> vector = copyStackToVector(stack);

    long sum = 0;
    for (Money money : vector) {
        sum += money.getRuble() * 100 + money.getCents();
    }

    long average = sum / vector.size();

    Money averageMoney = Money(average);
    for (Money& money : vector) {
        money = money + averageMoney;
    }

    stack = copyVectorToStack(vector);
}