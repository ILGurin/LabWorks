#include <iostream>

using namespace std;

int Sum50() {
    int number;
    number = 50;
    int sum = 0;
    while (number <= 70) {
        for (int i = 1; i < 70; i++) {
            if (number % i == 0) {
                sum += i;
            }
        }
        number++;
    }
    return sum;
}

int main()
{
    int sum = 0;
    sum = Sum50();
    cout << sum;
}
