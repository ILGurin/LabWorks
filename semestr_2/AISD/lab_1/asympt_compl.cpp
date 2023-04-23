#include <iostream>
#include <ctime>

using namespace std;

int GetRandomNumber() {
    int a;
    a = rand() % 100;
    return a;
}

int main()
{
    srand(time(NULL));
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    int n;
    cout << "Введите размер матрицы: ";
    cin >> n;
    double time = 0.0;
    unsigned long long sum = 0;
    int** arr = new int*[n];
    for (int i = 0; i < n; i++) {
        arr[i] = new int[n];
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            arr[i][j] = GetRandomNumber();
        }
    }

    clock_t begin = clock();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            sum += arr[i][j];
        }
    }
    clock_t end = clock();

    for (int i = 0; i < n; i++) {
        delete[] arr[i];
    }
    delete[] arr;
    time += (double)(end - begin) / CLOCKS_PER_SEC;
    cout << "Матрица размером " << n << " на " << n << endl;
    cout << "Сумма: " << sum << endl;
    cout << "Время выполнения: " << time << endl;
}