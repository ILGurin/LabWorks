#pragma once

#ifndef HEADER_H
#define HEADER_H

class SHAPES {
public:
    virtual double area() = 0;
    virtual double perimeter() = 0;
};

class RHOMBUS : public SHAPES {
private:
    double side;
    double diagonal_1;
    double diagonal_2;
public:
    RHOMBUS(double side, double diagonal_1, double diagonal_2) : side(side), diagonal_1(diagonal_1), diagonal_2(diagonal_2) {}
    double area();
    double perimeter();
    bool operator == (const RHOMBUS& other) { return other.side == side && other.diagonal_1 == diagonal_1 && other.diagonal_2 == diagonal_2; }
    bool operator != (const RHOMBUS& other) { return !(*this == other); }
    RHOMBUS& operator = (const RHOMBUS& other) {
        side = other.side;
        diagonal_1 = other.diagonal_1;
        diagonal_2 = other.diagonal_2;
        return *this;
    }
};

class PARALLELEPIPED : public SHAPES {
private:
    double length;
    double height;
    double width;
public:
    PARALLELEPIPED(double length, double height, double width) : length(length), height(height), width(width) {}
    double area();
    double perimeter();
    bool operator == (const PARALLELEPIPED& other) { return other.length == length && other.height == height && other.width == width; }
    bool operator != (const PARALLELEPIPED& other) { return !(*this == other); }
    PARALLELEPIPED& operator = (const PARALLELEPIPED& other) {
        length = other.length;
        height = other.height;
        width = other.width;
        return *this;
    }
};

class ELLIPSE : public SHAPES {
private:
    double halfAxle1;
    double halfAxle2;
public:
    ELLIPSE(double halfAxle1, double halfAxle2) : halfAxle1(halfAxle1), halfAxle2(halfAxle1) {}
    double area();
    double perimeter();
    bool operator == (const ELLIPSE& other) { return other.halfAxle1 == halfAxle1 && other.halfAxle2 == halfAxle2; }
    bool operator != (const ELLIPSE& other) { return !(*this == other); }
    ELLIPSE& operator = (const ELLIPSE& other) {
        halfAxle1 = other.halfAxle1;
        halfAxle2 = other.halfAxle2;
        return *this;
    }
};

typedef SHAPES* pSHAPE;
class COLLECTION {
    pSHAPE* shapes;
    int count;
public:
    COLLECTION(int shapesCount);
    ~COLLECTION();
    void add(SHAPES* obj);
    double totalArea();
    double totalPerimeter();

    SHAPES* operator[] (int n) const {
        if (n < 0 || n >= count) {
            return nullptr;
        }
        return shapes[n];
    }
};

#endif