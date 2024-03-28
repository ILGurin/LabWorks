#pragma once

#include <string>
#include <iostream>

using namespace std;
#ifndef SHIP_H
#define SHIP_H

class ship {
protected:
	string name;
	ship* next;
	static ship* headShip;
	static ship* lastObject;
public:
	ship();
	ship(string name);

	static void printHead();

	virtual void show();
	virtual void printVirtual();
	void print();

	ship* getHead();
	ship* getNext();
	void setNext(ship* neext);
	ship* getThis();
	string getName();
};

class steamer : public ship {
private:
	int speed;

public:
	steamer();
	steamer(string name, int speed);
	void printVirtual() override;
	void show() override;
};

class sailboat : public ship {
private:
	int speed;

public:
	sailboat();
	sailboat(string name, int speed);
	void printVirtual() override;
	void show() override;
};

class corvette : public ship {
private:
	int speed;

public:
	corvette();
	corvette(string name, int speed);
	void printVirtual() override;
	void show() override;
};

#endif