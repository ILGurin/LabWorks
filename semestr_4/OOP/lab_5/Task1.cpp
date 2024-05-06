#include "Task1.hpp"

void deleteByKey(std::deque<int>& deque, int key) {
    for (auto it = deque.begin(); it != deque.end(); ++it) {
        if (*it == key) {
            deque.erase(it);
            break;
        }
    }
}

void addMaxElement(std::deque<int>& deque) {
    int maxElement = *max_element(deque.begin(), deque.end());
    deque.push_back(maxElement);
}

void addAverage(std::deque<int>& dec) {
    int sum = 0;
    for (int num : dec) {
        sum += num;
    }
    double average = static_cast<double>(sum) / dec.size();
    int averageInt = static_cast<int>(average);

    for (int& num : dec) {
        num += averageInt;
    }
}