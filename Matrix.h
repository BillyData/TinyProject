#ifndef MATRIX_H
#define MATRIX_H
#include "Vector.h"

class Matrix {
   private:
    int mNumRows;
    int mNumCols;
    double** mData;
    Matrix();

   public:
    Matrix(int numRows, int numCols);
    Matrix(const Matrix& other);
    int getRows() const; 
    int getCols() const; 
    double** getData() const; 
    Matrix identity(int size) const;
    double& operator()(int i, int j);
    Vector operator*(Vector& a) const;
    Matrix operator+(Vector& a) const;
    Matrix operator-(Vector& a) const;
    Matrix& operator=(const Matrix& a);
    Matrix operator*(double a) const;
    Matrix operator+(double a) const;
    Matrix operator-(double a) const;
    Matrix operator*(const Matrix& a) const;
    Matrix operator-(const Matrix& a) const;
    Matrix operator+(const Matrix& a) const;
    double determinant() const;
    Matrix inverse() const;
    Matrix pseudoInverse() const;
    Matrix transpose() const;
    ~Matrix();
};

#endif
