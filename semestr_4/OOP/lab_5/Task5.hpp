#pragma once
#include <iostream>
#include <vector>
#include <stack>

template <class T>
class Vector {
private:
	stack<T> stack;
	int size;
public:
	Vector();
	void Print();
	void addElement(T element);
	void addMaxElement();
	void deleteByKey(T key);
	void addAverage();
};

template <class T>
std::vector<T> copyStackToVector(std::stack<T> stack) {
	std::vector<T> vector;
	while (!stack.empty()) {
		vector.push_back(stack.top());
		stack.pop();
	}
	return vector;
}

template <class T>
std::stack<T> copyVectorToStack(std::vector<T> vector) {
	std::stack<T> stack;
	for (int i = vector.size() - 1; i >= 0; i--) {
		stack.push(vector[i]);
	}
	return stack;
}

template <class T>
Vector<T>::Vector() {
	size = 0;
}

template <class T>
void Vector<T>::Print(){
	std::vector<T> v = copyStackToVector(stack);
	while (!stack.empty()){
		std::cout << stack.top();
		stack.pop();
	}
	std::cout << std::endl;
	stack = copyVectorToStack(v);
}

template <class T>
void Vector<T>::addMaxElement() {
	vector<T> vector = copyStackToVector(stack);

	T maxObject = T(0, 0);
	for (T object : vector) {
		if (object.getRuble() > maxObject.getRuble()) {
			maxObject = object;
		}
		else if (object.getRuble() > maxObject.getRuble() && object.getCents() > maxObject.getCents()) {
			maxObject = object;
		}
	}
	vector.insert(vector.begin(), maxObject);

	stack = copyVectorToStack(vector);
}

template <class T>
void Vector<T>::deleteByKey(T key) {
	std::vector<T> vector = copyStackToVector(stack);

	auto it = std::find(vector.begin(), vector.end(), key);
	if (it != vector.end()) {
		vector.erase(it);
	}

	stack = copyVectorToStack(vector);
}

template <class T>
void Vector<T>::addAverage() {
	std::vector<T> vector = copyStackToVector(stack);

	long sum = 0;
	for (T money : vector) {
		sum += money.getRuble() * 100 + money.getCents();
	}

	long average = sum / vector.size();

	T averageMoney = T(average);
	for (T& money : vector) {
		money = money + averageMoney;
	}

	stack = copyVectorToStack(vector);
}

template <class T>
void Vector<T>::addElement(T element) {
	stack.push(element);
}