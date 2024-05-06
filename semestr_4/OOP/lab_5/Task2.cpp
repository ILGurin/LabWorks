#include "Task2.hpp"

void addMaxElementMoney(deque<Money>& dequeMoney) {
    Money maxMoney = Money(0, 0);
    for (Money money : dequeMoney) {
        if (money.getRuble() >= maxMoney.getRuble()) {
            if (money.getCents() >= maxMoney.getCents()) {
                maxMoney = money;
            }
        }
    }

    dequeMoney.push_back(maxMoney);
}

void deleteByKeyMoney(deque<Money>& dequeMoney, Money money) {
    auto it = find(dequeMoney.begin(), dequeMoney.end(), money);
    if (it != dequeMoney.end()) {
        dequeMoney.erase(it);
    }
}

void addAverageMoney(deque<Money>& dequeMoney) {
    long sum = 0;
    for (Money money : dequeMoney) {
        sum += money.getRuble() * 100 + money.getCents();
    }
    long average = sum / dequeMoney.size();

    Money averageMoney = Money(average);
    for (Money& money : dequeMoney) {
        money = money + averageMoney;
    }
}