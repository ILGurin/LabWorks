#include <iostream>
#include <cstring>
#include "Header.h"

using namespace std;

int main(){
    setlocale(LC_ALL, "ru");
    RECEIPT receipt_1 = RECEIPT();
    RECEIPT receipt_2 = RECEIPT(10, 20, 30.3, "hello");
    RECEIPT receipt_3 = receipt_2;
    cout << endl;

    RECEIPT receipts[3];
    print_receipt(receipts[0]);
    print_receipt(receipts[1]);
    print_receipt(receipts[2]);

    cout << endl;

    RECEIPT* p;
    p = new RECEIPT[3];
    print_receipt(p[0]);
    print_receipt(p[1]);
    print_receipt(p[2]);
    delete[] p;

    RECEIPT* thisPtr = receipt_1.thisPtr;
    RECEIPT* thisPtr_1 = &receipt_2;
    RECEIPT* thisPtr_2 = receipt_3.thisPtr;

    int (RECEIPT::*getNumberPtr)() = &RECEIPT::getNumber;
    void (RECEIPT::*setNumberPtr)(int) = &RECEIPT::setNumber;
    int (RECEIPT::*getDatePtr)() = &RECEIPT::getDate;
    void (RECEIPT::*setDatePtr)(int) = &RECEIPT::setDate;
    float (RECEIPT::*getSumPtr)() = &RECEIPT::getSum;
    void (RECEIPT::*setSumPtr)(float) = &RECEIPT::setSum;

    cout << endl;
    cout << "Указатель на экземпляр класса: " << thisPtr << endl;
    cout << "Указатель на экземпляр класса: " << &thisPtr_1 << endl;
    cout << "Указатель на экземпляр класса: " << thisPtr_2 << endl;
    cout << endl;
    cout << "Объект receipt_1:" << endl;
    //cout << "Number: " << receipt_1.getNumber() << "   Date: " << receipt_1.getDate() << "   Sum: " << receipt_1.getSum() << "   Text: " << receipt_1.getText() << endl;
    print_receipt(receipt_1);
    cout << "Объект receipt_2:" << endl;
    cout << "Number: " << (receipt_2.*getNumberPtr)() << "   Date: " << (receipt_2.*getDatePtr)() << "   Sum: " << (receipt_2.*getSumPtr)() << "   Text: " << receipt_2.getText() << endl;
    cout << "Объект receipt_3:" << endl;
    cout << "Number: " << receipt_3.getNumber() << "   Date: " << receipt_3.getDate() << "   Sum: " << receipt_3.getSum() <<  "   Text: " << receipt_3.getText() << endl;

    (receipt_1.*setNumberPtr)(42);
    std::cout << "Number: " << (receipt_1.*getNumberPtr)() << std::endl;
    cout << endl;

    test_functiton(receipt_2);
    return 0;
}