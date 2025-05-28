#include "Vector.h"
#include <iostream>
#include <cassert>
using namespace std;

Vector::Vector(int Size) : mSize(Size) {
   this->mData = new double[Size]; 
}

int Vector::getSize() const { return this->mSize; }

Vector& Vector::operator=(const Vector& a) {
    this->mSize = a.getSize();
    this->mData = new double[this->mSize];

    for (int i = 0; i < mSize; i++) {
        this->mData[i] = a.getData()[i];
    }
    return *this;
}

double* Vector::getData() const { return this->mData; }

Vector::~Vector() { 
    // cout << "Destructor called\n";
    delete[] mData; 
}

Vector Vector::operator+(const Vector& a) const {
    assert(this->mSize == a.getSize());
    Vector result(this->mSize);
    for (int i = 0; i < mSize; i++) {
        result.mData[i] = this->mData[i] + a.mData[i];
    }
    return result;
}

Vector Vector::operator-(const Vector& a) const {
    assert(this->mSize == a.getSize());
    Vector result(this->mSize);
    for (int i = 0; i < this->mSize; i++) {
        result.mData[i] = this->mData[i] - a.mData[i];
    }
    return result;
}

double Vector::operator*(const Vector& a) const {
    assert(this->mSize == a.getSize());
    double result = 0;
    for (int i = 0; i < mSize; i++) {
        result += (this->mData[i] * a.mData[i]);
    }
    return result;
}

Vector Vector::operator+(double a) const {
    Vector result(this->mSize);
    for (int i = 0; i < this->mSize; i++) {
        result.mData[i] = (this->mData[i] + a);
    }
    return result;
}

Vector Vector::operator+(int a) const {
    Vector result(this->mSize);
    for (int i = 0; i < this->mSize; i++) {
        result.mData[i] = (this->mData[i] + a);
    }
    return result;
}

Vector Vector::operator-(double a) const {
    Vector result(this->mSize);
    for (int i = 0; i < this->mSize; i++) {
        result.mData[i] = (this->mData[i] - a);
    }
    return result;
}

Vector Vector::operator-(int a) const {
    Vector result(this->mSize);
    for (int i = 0; i < this->mSize; i++) {
        result.mData[i] = (this->mData[i] - a);
    }
    return result;
}

Vector Vector::operator*(double a) const {
    Vector result(this->mSize);
    for (int i = 0; i < this->mSize; i++) {
        result.mData[i] = (this->mData[i] * a);
    }
    return result;
}

Vector Vector::operator*(int a) const {
    Vector result(this->mSize);
    for (int i = 0; i < this->mSize; i++) {
        result.mData[i] = (this->mData[i] * a);
    }
    return result;
}

int Vector::operator[](int a) const {
    if (a >= 1 && a <= this->getSize()) {
        return 1;
    }
    return 0;
}

double& Vector::operator()(int a) {
    assert(a >= 1 && a <= this->getSize());
    return this->mData[a - 1];
}

