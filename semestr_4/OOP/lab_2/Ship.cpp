#include "Ship.h"
#include <iostream>
#include <string>

using namespace std;

ship::ship(){
	if (headShip == nullptr) {
		headShip = this;
	}
	next = nullptr;
	if (lastObject != nullptr) {

		lastObject->setNext(this);
	}
	lastObject = this;

	name = "name";
}

ship::ship(string name) {
	if (headShip == nullptr) {
		headShip = this;
	}
	next = nullptr;
	if (lastObject != nullptr) {
		lastObject->setNext(this);
	}
	lastObject = this;
	this->name = name;
}

void ship::printHead() {
	ship* ptr = headShip;
	while (ptr != NULL) {
		cout << ptr->getName() << endl;
		ptr = ptr->next;
	}
}

void ship::show() {
	ship* ptr = headShip;
	while (ptr != NULL) {
		cout << ptr->getName() << endl;
		ptr = ptr->next;
	}
}

void ship::printVirtual() {
	cout << "It's a ship (virtual function)" << endl;
}

void ship::print() {
	cout << "It's a ship" << endl;
}

ship* ship::getHead() {
	return headShip;
}
ship* ship::getNext() {
	return next;
}
void ship::setNext(ship* neext) {
	next = neext;
}
ship* ship::getThis() {
	return this;
}
string ship::getName() {
	return name;
}

ship* ship::headShip = nullptr;
ship* ship::lastObject = nullptr;

steamer::steamer() {
	ship();
	speed = 40;
}
steamer::steamer(string name, int speed) {
	this->name = name;
	this->speed = speed;
}
void steamer::printVirtual(){
	cout << "It's a steamer (virtual function)" << endl;
}
void steamer::show(){
	ship* ptr = headShip;
	while (ptr != NULL) {
		cout << ptr->getName() << endl;
		ptr = ptr->getNext();
		if (this->getNext() == ptr) {
			break;
		}
	}

}

sailboat::sailboat() {
	ship();
	speed = 20;
}
sailboat::sailboat(string name, int speed) {
	this->name = name;
	this->speed = speed;
}
void sailboat::printVirtual(){
	cout << "It's a sailboat (virtual function)" << endl;
}
void sailboat::show(){
	ship* ptr = headShip;
	while (ptr != NULL) {
		cout << ptr->getName() << endl;
		ptr = ptr->getNext();
		if (this->getNext() == ptr) {
			break;
		}
	}

}

corvette::corvette() {
	ship();
	speed = 20;
}
corvette::corvette(string name, int speed) {
	this->name = name;
	this->speed = speed;
}
void corvette::printVirtual(){
	cout << "This is a corvette (virtual function)" << endl;
}
void corvette::show(){
	ship* ptr = headShip;
	while (ptr != NULL) {
		cout << ptr->getName() << endl;
		ptr = ptr->getNext();
		if (this->getNext() == ptr) {
			break;
		}
	}

}