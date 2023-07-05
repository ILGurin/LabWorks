#include <iostream>

using namespace std;

bool Test(int *arr) {
    int size = 8;
    int result = 1;
    for (int i = 0; i < 8; i++) {
        result *= arr[i];
    }
    if (result < 10000) {
        return true;
    }
    else {
        return false;
    }
    cout << result;
}

int main()
{
    int arr[8];
    for (int i = 0; i < 8; i++) {
        cin >> arr[i];
    }
    bool test;
    test = Test(arr);
    test == true ? cout << "Yes, <10000" : cout << "No, >10000";
}