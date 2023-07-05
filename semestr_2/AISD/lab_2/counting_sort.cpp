#include <iostream>

using namespace std;

void CoutingSort(int* arr, int size, int max) {
    int* counters = new int[max] {0};
    for (int i = 0; i < size; i++) {
        counters[(arr[i])] += 1;
    }
    int k = 0;
    for (int i = 0; i < size; i++) {
        while (counters[i] != 0) {
            arr[k] = i;
            k++;
            counters[i]--;
        }
    }
}

int main(){
    int arr[10] = {1, 0, 2, 1, 0, 3, 2, 1, 1, 3};
    CoutingSort(arr, 10, 3);
    return 0;
}