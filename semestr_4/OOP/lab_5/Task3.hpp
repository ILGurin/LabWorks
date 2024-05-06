#pragma once
#include <iostream>
#include <algorithm>
#include <numeric>
#include <vector>

template <typename T>
class Container {
private:
	std::vector<T> data;
public:
	void addElement(const T element);
	void deleteBackElement();
	void addMaxElement();
	void deleteByKey(T key);
	void addAverage();
	void printElements();
};

template <class T>
void Container<T>::addElement(const T element) {
	data.push_back(element);
}

template <class T>
void Container<T>::deleteBackElement() {
	data.pop_back();
}

template <class T>
void Container<T>::addMaxElement() {
	auto maxIt = std::max_element(data.begin(), data.end());
	T value = *maxIt;
	data.push_back(value);
}

template <class T>
void Container<T>::deleteByKey(T key) {
	auto it = std::find(data.begin(), data.end(), key);

	if (it != data.end()) {
		data.erase(it);
	}
}

template <class T>
void Container<T>::addAverage() {
	T average = std::accumulate(data.begin(), data.end(), 0) / data.size();
	for (T& num : data) {
		num += average;
	}
}

template <class T>
void Container<T>::printElements() {
	for (const T& element : data) {
		std::cout << element << " ";
	}
	std::cout << std::endl;
}