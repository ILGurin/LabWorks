#pragma once
#include <vector>
#include <stack>
#include "Money.hpp"

std::vector<Money> copyStackToVector(std::stack<Money> stack);
std::stack<Money> copyVectorToStack(std::vector<Money> vector);
void printStack(std::stack<Money> stack);
void addMaxElement(std::stack<Money>& stack);
void deleteByKey(std::stack<Money>& stack, Money money);
void addAverage(std::stack<Money>& stack);
