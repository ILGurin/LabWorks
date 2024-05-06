#include "Money.hpp"


Money::Money() {
	ruble = 10;
	cents = 0;
}

Money::Money(long ruble, int cents) {
	this->ruble = ruble;
	this->cents = cents;
}

Money::Money(const Money& other) {
	this->ruble = other.ruble;
	this->cents = other.cents;
}

Money& Money::operator= (const Money& other) {
	ruble = other.ruble;
	cents = other.cents;
	return *this;
}

ostream& operator<< (ostream& out, const Money& m) {
	out << m.ruble << "," << m.cents << endl;
	return out;
}

istream& operator>> (istream& in, Money& m) {
	cout << "Enter the rubles: ";
	in >> m.ruble;
	cout << "Enter the cents: ";
	in >> m.cents;
	return in;
}

Money Money::operator+(Money m) {
	long myMoneyCents = (long)cents + ruble * 100;
	long mMoneyCents = (long)m.cents + m.ruble * 100;
	long commonMoneyCents = myMoneyCents + mMoneyCents;
	return Money(commonMoneyCents / 100, commonMoneyCents % 100);
}

bool Money::operator==(Money m) {
	return ruble == m.ruble && cents == m.cents;
}