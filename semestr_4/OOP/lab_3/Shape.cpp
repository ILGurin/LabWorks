#include "Header.h"

using namespace std;

double RHOMBUS::area() { return diagonal_1 * diagonal_2 / 2; }
double RHOMBUS::perimeter() { return side * 4; }

double PARALLELEPIPED::area() { return length * height * width; }
double PARALLELEPIPED::perimeter() { return 4 * (length + height + width); }

double ELLIPSE::area() { return 3.14 * halfAxle1 * halfAxle2; }
double ELLIPSE::perimeter() { return 4 * ((3.14 * halfAxle1 * halfAxle1 + (halfAxle1 - halfAxle2)) / (halfAxle1 + halfAxle1)); }

COLLECTION::COLLECTION(int shapesCount) {
    shapes = new pSHAPE[shapesCount];
    for (int i = 0; i < shapesCount; i++) {
        shapes[i] = nullptr;
    }
    count = shapesCount;
}
COLLECTION::~COLLECTION() {
    for (int i = 0; i < count; i++) {
        if (shapes != nullptr) {
            delete shapes[i];
        }
        delete[] shapes;
    }
}
void COLLECTION::add(SHAPES* obj) {
    int i = 0;

    while (shapes[i] != nullptr) {
        i++;
    }
    shapes[i] = obj;
}
double COLLECTION::totalArea() {
    double total = 0;
    for (int i = 0; i < count; i++) {
        if (shapes[i] != nullptr) {
            total += shapes[i]->area();
        }
    }
    return total;
}
double COLLECTION::totalPerimeter() {
    double total = 0;
    for (int i = 0; i < count; i++) {
        if (shapes[i] != nullptr) {
            total += shapes[i]->perimeter();
        }
    }
    return total;
}
void disposeShape(SHAPES** e) {
	if (*e != nullptr) {
		delete* e;
	}
	*e = nullptr;
}