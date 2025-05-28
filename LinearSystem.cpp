// LinearSystem.cpp
#include "LinearSystem.h"

#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>

#include "Matrix.h"
#include "Vector.h"

LinearSystem::LinearSystem(Matrix* A, Vector* b) {
    assert(A->getRows() == A->getCols());
    assert(A->getCols() == b->getSize());
    mSize = A->getCols();
    mpA = A;
    mpb = b;
}

Vector LinearSystem::Solve() {
    Matrix A = *mpA;
    Vector b = *mpb;
    int n = mSize;
    for (int i = 0; i < n; ++i) {
        int pivot = i;
        for (int j = i + 1; j < n; ++j) {
            if (std::fabs(A(j + 1, i + 1)) > std::fabs(A(pivot + 1, i + 1))) {
                pivot = j;
            }
        }
        if (pivot != i) {
            std::swap(b.getData()[i], b.getData()[pivot]);
            for (int k = 0; k < n; ++k) {
                std::swap(A(i + 1, k + 1), A(pivot + 1, k + 1));
            }
        }
        for (int j = i + 1; j < n; ++j) {
            double factor = A(j + 1, i + 1) / A(i + 1, i + 1);
            for (int k = i; k < n; ++k) {
                A(j + 1, k + 1) -= factor * A(i + 1, k + 1);
            }
            b.getData()[j] -= factor * b.getData()[i];
        }
    }

    Vector x(n);
    for (int i = n - 1; i >= 0; --i) {
        double sum = b.getData()[i];
        for (int j = i + 1; j < n; ++j) {
            sum -= A(i + 1, j + 1) * x.getData()[j];
        }
        x.getData()[i] = sum / A(i + 1, i + 1);
    }
    return x;
}

PosSymLinSystem::PosSymLinSystem(Matrix* A, Vector* b) : LinearSystem(A, b) {
    for (int i = 0; i < mSize; ++i) {
        for (int j = 0; j < mSize; ++j) {
            assert(std::fabs((*A)(i + 1, j + 1) - (*A)(j + 1, i + 1)) < 1e-10);
        }
    }
}

Vector PosSymLinSystem::Solve() {
    Vector x(mSize);
    Vector r = *mpb - (*mpA * x);
    Vector p = r;
    Vector Ap(mSize);
    double alpha, beta, r_old, r_new;
    r_old = r * r;

    for (int k = 0; k < mSize; ++k) {
        Ap = (*mpA) * p;
        alpha = r_old / (p * Ap);
        x = x + (p * alpha);
        r = r - (Ap * alpha);
        r_new = r * r;
        if (std::sqrt(r_new) < 1e-10) break;
        beta = r_new / r_old;
        p = r + (p * beta);
        r_old = r_new;
    }
    return x;
}

LeastSquaresSystem::LeastSquaresSystem(Matrix* A, Vector* b) {
    assert(A->getRows() == b->getSize());  // Ensure dimensions match
    mpA = A;
    mpb = b;
}

Vector LeastSquaresSystem::Solve() {
    Matrix A_pinv =
        mpA->pseudoInverse();  // Uses built-in regularized pseudo-inverse
    return A_pinv * (*mpb);    // x = A⁺ * b
}

