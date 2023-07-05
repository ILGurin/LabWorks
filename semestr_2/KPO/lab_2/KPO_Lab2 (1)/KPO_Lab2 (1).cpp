#include <iostream>
#include <string>

using namespace std;

void BubleSort(string* str) {
    string temp;
    for (int i = 0; i < 4; i++) {
        for (int i = 0; i < 4; i++) {
            if (str[i].size() > str[i + 1].size()) {
                temp = str[i];
                str[i] = str[i + 1];
                str[i + 1] = temp;
                continue;
            }
            if (str[i].size() == str[i + 1].size()) {
                for (int j = 0; j < str[i].size(); j++) {
                    if (str[i][j] > str[i + 1][j]) {
                        temp = str[i];
                        str[i] = str[i + 1];
                        str[i + 1] = temp;
                        break;
                    }
                }
            }
        }
    }
}

int main()
{
    string arr[5];
    cout << "Enter: \n";
    for (int i = 0; i < 5; i++) {
        cin >> arr[i];
    }

    BubleSort(arr);

    for (int i = 0; i < 5; i++) {
        cout << arr[i] << "\t";
    }





    /*int n;
    cin >> n;
    string b = " ";
    int tmp;
    while (n > 0) {
        tmp = n % 2;
        string s_tmp = to_string(tmp);
        b = s_tmp + b;
        n = n / 2;

    }
    cout << b;*/
}