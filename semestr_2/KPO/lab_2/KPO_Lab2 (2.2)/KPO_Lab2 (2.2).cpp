#include <iostream>
#include <ctime>

using namespace std;

long int Fib(long int n) {
    if (n == 1) {
        return 0;
    }
    else if (n == 2) {
        return 1;
    }
    else {
        return Fib(n - 1) + Fib(n - 2);
    }
}

int main()
{
    srand(time(NULL));
    long int n;
    cin >> n;
    long int fib;
    double time = 0.0;
    clock_t begin = clock();
    fib = Fib(n);
    clock_t end = clock();
    time += (double)(end - begin) / CLOCKS_PER_SEC*1000;
    cout << fib << endl;
    cout << time << " ms";
}
