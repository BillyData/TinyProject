#include "Matrix.h"
#include <iostream>
using namespace std;

#include <cassert>

Matrix::Matrix(int numRows, int numCols) {
    this->mNumRows = numRows;
    this->mNumCols = numCols;
    this->mData = new double*[numRows];
    // cout << "still good" << numRows << " " << numCols << "\n"; 
    for (int i = 0; i < numRows; i++) {
        this->mData[i] = new double[numCols];
    }
}

int Matrix::getRows() const { return this->mNumRows; }

int Matrix::getCols() const { return this->mNumCols; }

double** Matrix::getData() const { return this->mData; }

Matrix::Matrix(const Matrix& other) {
    this->mNumRows = other.getRows();
    this->mNumCols = other.getCols();
    // cout << "very good\n";
    // Allocate new memory
    this->mData = new double*[mNumRows];
    for (int i = 0; i < mNumRows; ++i) {
        this->mData[i] = new double[mNumCols];
        for (int j = 0; j < mNumCols; ++j) {
            this->mData[i][j] = other.getData()[i][j];
        }
    }
}

double& Matrix::operator()(int i, int j) {
    assert(i >= 1 && i <= mNumRows);
    assert(j >= 1 && j <= mNumCols);
    return this->mData[i - 1][j - 1];
}

Vector Matrix::operator*(Vector& a) const {
    assert(this->mNumCols == a.getSize());

    Vector result(this->mNumRows);

    for (int i = 0; i < this->mNumRows; i++) {
        double temp = 0;
        for (int j = 0; j < this->mNumCols; j++) {
            temp += (this->mData[i][j] * a.getData()[j]);
        }
        result(i + 1) = temp;
    }
    return result;
};

Matrix Matrix::operator+(Vector& a) const {
    assert(this->mNumCols == a.getSize());
    Matrix result(this->mNumRows, this->mNumCols);
    for (int i = 0; i < this->mNumRows; i++) {
        for (int j = 0; j < this->mNumCols; j++) {
            result.getData()[i][j] = (this->getData()[i][j] + a.getData()[j]);
        }
    }
    return result;
}

Matrix Matrix::operator-(Vector& a) const {
    assert(this->mNumCols == a.getSize());
    Matrix result(this->mNumRows, this->mNumCols);
    for (int i = 0; i < this->mNumRows; i++) {
        for (int j = 0; j < this->mNumCols; j++) {
            result.getData()[i][j] = (this->getData()[i][j] - a.getData()[j]);
        }
    }
    return result;
}

Matrix& Matrix::operator=(const Matrix& a) {
    // Free old memory
    for (int i = 0; i < mNumRows; ++i) {
        delete[] mData[i];
    }
    delete[] mData;

    // Allocate new memory
    mNumRows = a.getRows();
    mNumCols = a.getCols();

    mData = new double*[mNumRows];
    for (int i = 0; i < mNumRows; ++i) {
        mData[i] = new double[mNumCols];
        for (int j = 0; j < mNumCols; ++j) {
            mData[i][j] = a.getData()[i][j];
        }
    }

    return *this;
}

Matrix Matrix::operator*(double a) const {
    Matrix result(this->mNumRows, this->mNumCols);
    for (int i = 0; i < this->mNumRows; i++) {
        for (int j = 0; j < this->mNumCols; j++) {
            result.mData[i][j] = (this->mData[i][j] * a);
        }
    }
    return result;
}

Matrix Matrix::operator+(double a) const {
    Matrix result(this->mNumRows, this->mNumCols);
    for (int i = 0; i < this->mNumRows; i++) {
        for (int j = 0; j < this->mNumCols; j++) {
            result.mData[i][j] = (this->mData[i][j] + a);
        }
    }
    return result;
}

Matrix Matrix::operator-(double a) const {
    Matrix result(this->mNumRows, this->mNumCols);
    for (int i = 0; i < this->mNumRows; i++) {
        for (int j = 0; j < this->mNumCols; j++) {
            result.mData[i][j] = (this->mData[i][j] - a);
        }
    }
    return result;
}

Matrix Matrix::operator*(const Matrix& a) const {
    assert(this->getCols() == a.getRows());
    Matrix result(this->mNumRows, a.getCols());

    for (int i = 0; i < this->mNumRows; i++) {
        Vector a1(this->mNumCols);
        // Fill a1 with the i-th row of this matrix
        for (int k = 0; k < this->mNumCols; k++) {
            a1(k + 1) = this->mData[i][k];  // 1-based indexing in Vector
        }

        for (int j = 0; j < a.getCols(); j++) {
            Vector a2(a.getRows());
            for (int k = 0; k < a.getRows(); k++) {
                a2(k + 1) = a.getData()[k][j];  // get column j of matrix a
            }
            double a3 = a1 * a2;
            result.getData()[i][j] = a3;
        }
    }

    return result;
}


Matrix Matrix::operator-(const Matrix& a) const {
    assert((this->mNumCols == a.getCols()) && (this->mNumRows == a.getRows()));
    Matrix result(this->mNumRows, a.getCols());
    for (int i = 0; i < this->mNumRows; i++) {
        for (int j = 0; j < this->mNumCols; j++) {
            result.getData()[i][j] = this->mData[i][j] - a.getData()[i][j];
        }
    }
    return result;
}

Matrix Matrix::operator+(const Matrix& a) const {
    assert((this->mNumCols == a.getCols()) && (this->mNumRows == a.getRows()));
    Matrix result(this->mNumRows, a.getCols());
    for (int i = 0; i < this->mNumRows; i++) {
        for (int j = 0; j < this->mNumCols; j++) {
            result.getData()[i][j] = this->mData[i][j] + a.getData()[i][j];
        }
    }
    return result;
}

double Matrix::determinant() const {
    int n = this->mNumRows;
    assert(n == this->mNumCols);  // must be square

    // Base case: 1x1 matrix
    if (n == 1) {
        return this->mData[0][0];
    }

    if (n == 2) {
        return this->mData[0][0] * this->mData[1][1] -
               this->mData[0][1] * this->mData[1][0];
    }

    double det = 0.0;

    // Recursive Case
    for (int col = 0; col < n; col++) {
        Matrix minor(n - 1, n - 1);
        for (int i = 1; i < n; i++) {
            int minorCol = 0;
            for (int j = 0; j < n; j++) {
                if (j == col) continue;
                minor.getData()[i - 1][minorCol] = this->mData[i][j];
                minorCol++;
            }
        }
        double sign = (col % 2 == 0) ? 1 : -1;
        det += sign * this->mData[0][col] * minor.determinant();
    }

    return det;
}

Matrix Matrix::inverse() const {
    int n = this->getRows();
    assert(n == this->getCols());  // must be square

    double det = this->determinant();  // assume you have Matrix::determinant()
    assert(det != 0);                  // matrix must be invertible

    Matrix cofactorMat(n, n);

    // Step 1: Compute cofactor matrix
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            // Create minor matrix
            Matrix minor(n - 1, n - 1);
            for (int r = 0, mi = 0; r < n; ++r) {
                if (r == i) continue;
                for (int c = 0, mj = 0; c < n; ++c) {
                    if (c == j) continue;
                    minor.getData()[mi][mj] = this->getData()[r][c];
                    ++mj;
                }
                ++mi;
            }

            double sign = ((i + j) % 2 == 0) ? 1 : -1;
            cofactorMat.getData()[i][j] = sign * minor.determinant();
        }
    }

    // Step 2: Transpose cofactor matrix → adjugate
    Matrix adjugate(n, n);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            adjugate.getData()[i][j] = cofactorMat.getData()[j][i];

    // Step 3: Divide each element by determinant
    Matrix inverseMat(n, n);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            inverseMat.getData()[i][j] = adjugate.getData()[i][j] / det;

    return inverseMat;
}

Matrix Matrix::transpose() const {
    int rows = this->getRows();
    int cols = this->getCols();

    Matrix result(cols, rows);  // Transposed dimensions

    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j)
            result.getData()[j][i] = this->getData()[i][j];

    return result;
}

Matrix Matrix::identity(int size) const {
    Matrix I(size, size);
    for (int i = 0; i < size; ++i)
        I(i + 1, i + 1) = 1.0;
    return I;
}


Matrix Matrix::pseudoInverse() const {
    const double lambda = 1e-8;
    int m = this->getRows();
    int n = this->getCols();
    Matrix A_T = this->transpose();

    std::cout << "\npseudoInverse() called, size: " << m << "x" << n << "\n";

    if (m >= n) {
        Matrix ATA = A_T * (*this);
        Matrix I = this->identity(n);
        Matrix regularized = ATA + (I * lambda);
        std::cout << "Determinant of regularized ATA: " << regularized.determinant() << "\n";

        Matrix regularized_inv = regularized.inverse();
        return regularized_inv * A_T;
    } else {
        Matrix AAT = (*this) * A_T;
        Matrix I = identity(m);
        Matrix regularized = AAT + (I * lambda);
        std::cout << "Determinant of regularized AAT: " << regularized.determinant() << "\n";

        Matrix regularized_inv = regularized.inverse();
        return A_T * regularized_inv;
    }
}


Matrix::~Matrix() {
    // Free allocated memory if Matrix owns it
        for (int i = 0; i < this->mNumRows; ++i) {
            delete[] this->mData[i];
        }
        delete[] this->mData;
        this->mData = nullptr;
}
