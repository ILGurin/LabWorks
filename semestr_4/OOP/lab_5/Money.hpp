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
	Money(long cents) {
		this->ruble = cents / 100;
		this->cents = cents % 100;
	}
	Money(const Money& other);
	Money& operator=(const Money& other);
	Money operator+(Money k);
	bool operator== (Money m);

	long getRuble() {
		return this->ruble;
	}
	int getCents() {
		return this->cents;
	}

	friend ostream& operator<< (ostream& out, const Money&);
	friend istream& operator>> (istream& in, Money&);
};