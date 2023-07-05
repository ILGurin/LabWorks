#include <iostream>

using namespace std;

void BubleSort(int* arr, int size) {
    int tmp;
    bool is_sorted;
    while (true) {
        is_sorted = true;
        for (int i = 0; i < size - 1; i++) {
            if (arr[i] > arr[i + 1]) {
                tmp = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = tmp;
                is_sorted = false;
            }
        }
        if (is_sorted) {
            break;
        }
    }
}

int main(){
    int arr[10] = {1, 5, 2, 10, 4, 17, 23, 14, 2, 3};
    BubleSort(arr, 10);
    return 0;
}