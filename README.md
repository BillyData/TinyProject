# Project Report: Linear Algebra-Based Machine Learning in C++

## Team Member:
- Nguyen Vo Minh Khoi - 10423063
- Le Quang Minh Khoa - 10423057
- Nguyen Duc Khang - 10423054
- Tran Nguyen Khoa - 10423060
- Phan Thanh Hung - 10423051
- Duong Quy Trang - 10423110

## Overview
This project implements a lightweight machine learning model using custom-built linear algebra structures and solvers in C++. It focuses on reading a dataset, preprocessing it, training a regression model using least squares optimization, and evaluating its performance.

---

## 1. Code Components and Their Roles

### 1.1 `Vector` Class
- Implements a dynamic array for mathematical vectors.
- Supports arithmetic operations: addition, subtraction, scalar multiplication, and dot product.
- Operator overloading allows for intuitive usage, such as `v1 + v2` or `v1 * scalar`.
- Handles memory allocation and deallocation with proper constructors and a destructor.

### 1.2 `Matrix` Class
- Encapsulates a 2D matrix with dynamic memory handling.
- Provides essential matrix operations:
  - Addition, subtraction
  - Scalar and matrix multiplication
  - Transpose, identity generation
  - Determinant, inverse, pseudoinverse
- Operator overloading enables intuitive matrix arithmetic.
- Includes a regularized pseudoinverse method to improve numerical stability.

### 1.3 `LinearSystem` Classes
These classes solve equations of the form \(Ax = b\):
- **`LinearSystem`**: Solves square systems using Gaussian elimination with partial pivoting.
- **`PosSymLinSystem`**: Uses the Conjugate Gradient method for symmetric positive-definite matrices.
- **`LeastSquaresSystem`**: Solves overdetermined systems via the pseudoinverse, useful in regression.

---

## 2. Main Application (`main.cpp`)

### 2.1 Dataset Parsing
- Reads from `machine.data` containing CPU performance data.
- Extracts six numerical features and one target value (PRP).
- Skips non-numeric fields (vendor, model) and ERP.

### 2.2 Data Preprocessing
- Randomly shuffles data to eliminate order bias.
- Splits into 80% training and 20% testing sets.
- Converts data into `Matrix` and `Vector` structures.

### 2.3 Model Training
- Builds a `LeastSquaresSystem` using training data.
- Solves for the parameter vector $x$ using the pseudoinverse formula:

$$
x = (A^T A + \lambda I)^{-1} A^T b
$$

- The regularization term $\lambda = 1 \times 10^{-8}$ adds numerical stability.

### 2.4 Evaluation
- Predicts outputs on test data: $\hat{y} = A_{\text{test}} x$ 
- Computes Root Mean Squared Error (RMSE) for accuracy evaluation.

---

## 3. Notable Implementation Features

- **Memory Safety**: Custom destructors and deep copies for dynamic arrays.
- **Numerical Stability**: Regularized pseudoinverse prevents singularities.
- **Modularity**: Clear separation across vector, matrix, and solver classes.
- **Operator Overloading**: Simplifies mathematical operations.

---

## 4. Example Output
The program prints:
- Total number of samples parsed.
- Size of training and test sets.
- First row of training data (sanity check).
- Learned model coefficients.
- RMSE on the test data.

---

## 5. Recommendations for Improvement

- **Error Handling**: Add robust input validation and exception support.
- **Normalization**: Include data scaling for improved model performance.
- **Performance**: Consider optimized libraries like Eigen or Armadillo.
- **Evaluation**: Add more metrics (e.g., R², MAE).
- **User Feedback**: Provide clearer errors if `machine.data` is missing.

---

## Conclusion
This project showcases an educational and modular implementation of linear regression using C++. It emphasizes understanding numerical algorithms and object-oriented programming without relying on external libraries.

