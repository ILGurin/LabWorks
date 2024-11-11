#include <QCoreApplication>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    int arraySize;
    cout << "Enter array size: ";
    cin >> arraySize;;

    cout << "Enter array:" << endl;
    int *arr = new int[arraySize];
    for(int i = 0; i < arraySize; i++) {
        cin >> arr[i];
    }

    bool ok = false;
    for(int i = 0; i < arraySize; i++) {
        if(arr[1] < arr[i] && arr[i] < arr[10]) {
            cout << i;
            ok = true;
            break;
        }
    }

    if(!ok) {
        cout << 0 << endl;
    }

    return a.exec();
}
