#include <iostream>

using namespace std;

int partOfSortHoara(int*& arr, int left, int right) {
    int pivot = arr[(left + right) / 2];
    while (left <= right) {
        while (arr[left] < pivot) left++;
        while (arr[right] > pivot) right--;
        if (left <= right) {
            int temp = arr[left];
            arr[left] = arr[right];
            arr[right] = temp;
            left++;
            right--;
        }
    }
    return left;
}

void quickSortHoara(int*& arr, int start, int end) {
    if(start >= end){
        return;
    };
    int rightStart = partOfSortHoara(arr, start, end);
    quickSortHoara(arr, start, rightStart - 1);
    quickSortHoara(arr, rightStart, end);
}

void quickSortHoara(int*& arr, int size) {
    quickSortHoara(arr, 0, size - 1);
}

int main(){
    int arr[10] = {1, 5, 2, 10, 4, 17, 23, 14, 2, 3};
    quickSortHoara(arr, 10);
    return 0;
}