#include <iostream>
#include <ctime>
using namespace std;

long long int Fib(long long n) {
    long long int tmp = 0;
    long long int last = 0;
    long long int fib = 1;
    for (int i = 2; i < n; i++) {
        tmp = fib;
        fib = fib + last;
        last = tmp;
    }
    return fib;
}
int main()
{
    srand(time(NULL));
    long long int n;
    cout << "Enter: ";
    cin >> n;
    double time = 0.0;
    long long int fib = 0;

    clock_t begin = clock();
    fib = Fib(n);
    clock_t end = clock();

    time += (double)(end - begin)/ CLOCKS_PER_SEC *1000;
    cout << "Number: " << fib << endl;
    cout << "Time: " << time << " ms" << endl;
}
