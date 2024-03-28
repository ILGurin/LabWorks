#pragma once
#ifndef MYCLASS_H
#define MYCLASS_H

class RECEIPT {
private:
    int number;
    int date;
    float sum;
    char* text;

public:
    RECEIPT();
    RECEIPT(int number, int date, float sum, const char* textt);
    RECEIPT(const RECEIPT& p);
    ~RECEIPT();

    int getNumber();
    void setNumber(int number);
    int getDate();
    void setDate(int date);
    float getSum();
    void setSum(float sum);
    const char* getText() const;
    void setMyString(const char* str);

    RECEIPT* thisPtr = this;
};
void print_receipt(RECEIPT p);
RECEIPT test_functiton(RECEIPT p);

#endif