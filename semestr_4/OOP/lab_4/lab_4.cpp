#include <iostream>
#include "Set.h"
#include "Money.h"
#include <list>

using namespace std;

template <template <typename> class Container, typename T>
class Wrapper {
    Container<T> data;
};

template <typename T>
class MyContainer {
public:
    T value;
};

int main(){
    Wrapper<MyContainer, int> wrapper;


    /*   Тестирование класса Money   */
    Money a = Money(50, 50);
    Money b = a;
    Money c;
    cin >> c;
    Money d = b + c;
    cout << a;
    cout << b;
    cout << c;
    cout << d;

    /*   Тестирование класса Set   */
    Set<Money> set(a);
    Set<Money> newSet = set;
    set.add(b); //Не добавится, т к элемент уже существует
    set.add(c);
    set.add(d);
    set.add(Money(30, 23));

    set != newSet ? cout << "set != newSet" << endl : cout << "set == newSet" << endl;
    newSet < a ? cout << "money in set" << endl : cout << "money not in set" << endl;

    cout << set;
    cout << set[2];
}