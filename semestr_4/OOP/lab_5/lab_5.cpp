#include <iostream>
#include <deque>
#include <algorithm>
#include <vector>
#include <stack>
#include "Money.hpp"
#include "Task1.hpp"
#include "Task2.hpp"
#include "Task3.hpp"
#include "Task4.hpp"
#include "Task5.hpp"
#include "Windows.h"

template <class T>
void printDeque(std::deque<T> deque);


int main(){

    /*=============== Задача 1 ===============*/
    std::cout << "=============== Task 1 ===============" << std::endl;
    std::deque<int> deque = {3, 7, 2, 9, 5};
    std::cout << "Original deque: ";
    printDeque(deque);

    addMaxElement(deque);
    deleteByKey(deque, 7);
    addAverage(deque);

    std::cout << "Final deque: ";
    printDeque(deque);
    std::cout << std::endl;

    /*=============== Задача 2 ===============*/
    std::cout << "=============== Task 2 ===============" << std::endl;
    std::deque<Money> dequeMoney = { Money(20, 20), Money(), Money(40, 40), Money(245) };
    std::cout << "Original deque: " << std::endl;
    printDeque(dequeMoney);

    addMaxElementMoney(dequeMoney);
    deleteByKeyMoney(dequeMoney, Money(40, 40));
    addAverageMoney(dequeMoney);

    std::cout << "Final deque: " << std::endl;
    printDeque(dequeMoney);

    /*=============== Задача 3 ===============*/
    std::cout << "=============== Task 3 ===============" << std::endl;
    Container<int> container;
    container.addElement(4);
    container.addElement(5);
    container.addElement(1);
    std::cout << "Original container: ";
    container.printElements();

    container.addMaxElement();
    container.deleteByKey(4);
    container.addAverage();

    std::cout << "Final container: ";
    container.printElements();
    cout << endl;

    /*=============== Задача 4 ===============*/
    std::cout << "=============== Task 4 ===============" << std::endl;
    std::stack<Money> stack;
    stack.push(Money(20, 20));
    stack.push(Money());
    stack.push(Money(40, 40));
    stack.push(Money(245));
    std::cout << "Original stack: " << std::endl;
    printStack(stack);

    addMaxElement(stack);
    deleteByKey(stack, Money());
    addAverage(stack);
    std::cout << "Final stack: " << std::endl;
    printStack(stack);
    
    /*=============== Задача 5 ===============*/
    std::cout << "=============== Task 5 ===============" << std::endl;

    Vector<Money> vector = Vector<Money>();
    vector.addElement(Money());
    vector.addElement(Money(20, 20));
    vector.addElement(Money(245));
    std::cout << "Original: " << std::endl;
    vector.Print();

    vector.addMaxElement();
    vector.deleteByKey(Money());
    vector.addAverage();

    std::cout << "Final: " << std::endl;
    vector.Print();

    std::cout << "======================================" << std::endl;
}

template <class T>
void printDeque(std::deque<T> deque) {
    for (auto it = deque.begin(); it != deque.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}