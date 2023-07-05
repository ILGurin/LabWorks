#include <iostream>
#include <vector> 
using namespace std; 

int main()
{
    setlocale(LC_ALL, "rus");
    vector <int> a = { 5, 10, 25, 8, 7, 11, 15, 4, 3 };
    int max1 = 0, max2 = 0, max3 = 0, max4 = 0;

    for (int i = 0; i < a.size(); i++) {
        if (a[i] > max1) {
            max4 = max3;
            max3 = max2;
            max2 = max1;
            max1 = a[i];
        }
        else if (a[i] > max2) {
            max4 = max3;
            max3 = max2;
            max2 = a[i];
        }
        else if (a[i] > max3) {
            max4 = max3;
            max3 = a[i];
        }
        else if (a[i] > max4) {
            max4 = a[i];
        }
    }
    cout << "4 максимальных элемента в массиве: ";
    cout << max1 << " " << max2 << " " << max3 << " " << max4;

    return 0;
}