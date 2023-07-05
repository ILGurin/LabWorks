#include <iostream>
#include <vector>
#include <Windows.h>
#include <random>

int GetRandomNumber(){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 100);
    int pivotIndex = dis(gen);
    return pivotIndex;
}

void BubleSort(std::vector<int> &arr, int size){
    int tmp;
    bool is_sorted;
    while(true){
        is_sorted = true;
        for (int i = 0; i < size-1; i++){
            if(arr[i] > arr[i+1]){
                tmp = arr[i];
                arr[i] = arr[i+1];
                arr[i+1] = tmp;
                is_sorted = false;
            }
        }
        if(is_sorted){
            break;
        }
    }
}
int interpolationSearch(std::vector<int> arr, int low, int high, int x)
{
    int pos;
    if (low <= high && x >= arr[low] && x <= arr[high]) {
        pos = low + (((double)(high - low) / (arr[high] - arr[low])) * (x - arr[low]));
        if (arr[pos] == x)
            return pos;
        if (arr[pos] < x)
            return interpolationSearch(arr, pos + 1, high, x);
        if (arr[pos] > x)
            return interpolationSearch(arr, low, pos - 1, x);
    }
    return -1;
}

int main(){
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    
    std::vector<int> arr = {2, 3, 4, 6, 8, 9, 11, 13, 14, 17, 20, 21, 25};
    std::vector<int> arrr(20);
    for (int i = 0; i < arrr.size(); i++){
        arrr[i] = GetRandomNumber();
    }
    BubleSort(arrr, arrr.size());
    for (int i = 0; i < arrr.size(); i++){
        std::cout << arrr[i] << "   ";
    }
    
    int desired_number;
    std::cout << "Какое число нужно найти?: ";
    std::cin >> desired_number;
    int index = interpolationSearch(arrr, 0, arrr.size() - 1, desired_number);
    if (index != -1)
        std::cout << "Элемент найден по индексу " << index;
    else
        std::cout << "Элемент не найден";
    return 0;
}