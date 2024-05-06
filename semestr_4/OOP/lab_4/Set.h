#pragma once
#include <iostream>
using namespace std;

template <class T>
class Set {
    int size;
    T* data;
public:
    Set(T object);
    Set(const Set<T>& other);
    ~Set();
    Set& operator = (const Set<T>& other);
    T& operator [] (int index);
    bool operator != (const Set& other);
    bool operator < (T other);

    void add(T other);

    friend ostream& operator<< <>(ostream& out, const Set<T>& a);
    friend istream& operator>> <>(istream& in, Set<T>& a);
};


template <class T>
Set<T>::Set(T object) {
    size = 1;
    data = new T[size];
    for (int i = 0; i < size; i++) {
        data[i] = object;
    }
}

template <class T>
Set<T>::Set(const Set<T>& other) {
    size = other.size;
    data = new T[size];
    for (int i = 0; i < size; i++) {
        data[i] = other.data[i];
    }
}

template <class T>
Set<T>::~Set() {
    delete[] data;
    data = 0;
}

template <class T>
void Set<T>::add(T other) {
    //if element in set -> return
    for (int i = 0; i < size; i++) {
        if (data[i] == other) {
            return;
        }
    }

    T* tmp = new T[size + 1];
    for (int i = 0; i < size; i++) {
        tmp[i] = data[i];
    }
    tmp[size] = other;
    delete[] data;
    data = tmp;
    size++;
}

template <class T>
Set<T>& Set<T>::operator= (const Set<T>& other) {
    if (this == &other) {
        return *this;
    }
    size = other.size;
    if (data != 0) {
        delete[] data;
    }
    data = new T[size];
    for (int i = 0; i < size; i++) {
        data[i] = other.data[i];
    }
    return *this;
}

template <class T>
T& Set<T>::operator[](int index) {
    if (index < size) {
        return data[index];
    }
    else {
        std::cout << "Error! index < size" << std::endl;
    }
}

template <class T>
bool Set<T>::operator != (const Set& other) {
    return size != other.size || data != other.data;
}

template <class T>
bool Set<T>::operator< (T other) {
    for (int i = 0; i < size; i++) {
        if (data[i] == other) {
            return true;
        }
    }
    return false;
}

template <class T>
ostream& operator<< (ostream& out, const Set<T>& a) {
    cout << endl;
    cout << "Values: " << endl;
    for (int i = 0; i < a.size; i++) {
        out << a.data[i];
    }
    cout << endl;
    return out;
}

template <class T>
istream& operator>> (istream& in, Set<T>& a) {
    for (int i = 0; i < a.size; ++i) {
        in >> a.data[i];
    }
    return in;
}