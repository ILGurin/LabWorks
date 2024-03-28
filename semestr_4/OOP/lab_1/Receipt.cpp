#include "Header.h"
#include <iostream>
#include <cstring>

using namespace std;

RECEIPT::RECEIPT(){
    this->number = 1;
    this->date = 1;
    this->sum = 1.0;
    const char* defaultStr = "Hello world";
    this->text = new char[strlen(defaultStr) + 1];
    strcpy_s(this->text, strlen(defaultStr) + 1, defaultStr);
}

RECEIPT::RECEIPT(int number, int date, float sum, const char* textt) {
    this->number = number;
    this->date = date;
    this->sum = sum;
    text = new char[strlen(textt) + 1];
    strcpy_s(text, strlen(textt) + 1, textt);
}

RECEIPT::RECEIPT(const RECEIPT& p) {
    number = p.number;
    date = p.date;
    sum = p.sum;
    text = new char[strlen(p.text) + 1];
    strcpy_s(text, strlen(p.text) + 1, p.text);
}

RECEIPT::~RECEIPT() {
    delete[] text;
}

int RECEIPT::getNumber() {
    return this->number;
}
void RECEIPT::setNumber(int number) {
    this->number = number;
}
int RECEIPT::getDate() {
    return this->date;
}
void RECEIPT::setDate(int date) {
    this->date = date;
}
float RECEIPT::getSum() {
    return this->sum;
}
void RECEIPT::setSum(float sum) {
    this->sum = sum;
}
const char* RECEIPT::getText() const {
    return text;
}
void RECEIPT::setMyString(const char* str) {
    delete[] text;
    text = new char[strlen(str) + 1];
    strcpy_s(text, strlen(str) + 1, str);
}

void print_receipt(RECEIPT p) {
    cout << "Number: " << p.getNumber() << "   Date: " << p.getDate() << "   Sum: " << p.getSum() << "   Text: " << p.getText() << endl;
}
RECEIPT test_functiton(RECEIPT p) {
    RECEIPT test(p);
    return test;
}