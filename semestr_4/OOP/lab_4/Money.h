#pragma once
#include <iostream>
using namespace std;

class Money {
private:
	long ruble;
	int cents;
public:
	Money();
	Money(long, int);
	Money(const Money&);
	Money& operator=(const Money&);
	Money operator+(Money k);
	bool operator== (Money m);

	friend ostream& operator<< (ostream& out, const Money&);
	friend istream& operator>> (istream& in, Money&);
};