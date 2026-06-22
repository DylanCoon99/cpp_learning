# Phase 2 Project: Linear Algebra Library

A matrix and vector math library that exercises classes, operator overloading, inheritance, and the Rule of Five.

## Overview

Build a small linear algebra library with a class hierarchy, full operator support, and proper resource management. This pulls together everything from Phase 2: classes, encapsulation, operator overloading, inheritance, polymorphism, and copy/move semantics.

## Class Hierarchy

### `Matrix` — The Core Class

A dynamically allocated 2D matrix of doubles.

```cpp
class Matrix {
public:
    // Constructors
    Matrix();                                    // default: 0x0
    Matrix(int rows, int cols, double fill = 0); // sized with fill value
    Matrix(std::initializer_list<std::initializer_list<double>> init);

    // Rule of Five
    ~Matrix();
    Matrix(const Matrix& other);
    Matrix& operator=(const Matrix& other);
    Matrix(Matrix&& other) noexcept;
    Matrix& operator=(Matrix&& other) noexcept;

    // Element access
    double& operator()(int row, int col);
    const double& operator()(int row, int col) const;

    // Dimensions
    int rows() const;
    int cols() const;

    // Arithmetic operators
    Matrix operator+(const Matrix& rhs) const;
    Matrix operator-(const Matrix& rhs) const;
    Matrix operator*(const Matrix& rhs) const;   // matrix multiply
    Matrix operator*(double scalar) const;        // scalar multiply
    Matrix& operator+=(const Matrix& rhs);
    Matrix& operator-=(const Matrix& rhs);
    Matrix& operator*=(double scalar);

    // Comparison
    bool operator==(const Matrix& rhs) const;
    bool operator!=(const Matrix& rhs) const;

    // Stream I/O
    friend std::ostream& operator<<(std::ostream& os, const Matrix& m);

    // Operations
    Matrix transpose() const;
    double determinant() const;     // only for square matrices
    Matrix inverse() const;         // only for square matrices (bonus)
    Matrix submatrix(int exclude_row, int exclude_col) const;

    // Utility
    void swap(Matrix& other) noexcept;
    static Matrix identity(int size);    // returns size x size identity matrix
    static Matrix zeros(int rows, int cols);
    static Matrix ones(int rows, int cols);

private:
    double* data_;     // flat 1D array storing row-major data
    int rows_;
    int cols_;

    int index(int row, int col) const { return row * cols_ + col; }
};

// Free function: scalar * matrix (scalar on left side)
Matrix operator*(double scalar, const Matrix& m);
```

**Storage:** Use a single flat `double*` array in row-major order, not `vector<vector<double>>`. Access element `(r, c)` as `data_[r * cols_ + c]`. This is more cache-friendly and exercises raw memory management.

### `Vector` — Inherits from Matrix

A mathematical vector (column vector) implemented as an Nx1 matrix.

```cpp
class Vector : public Matrix {
public:
    explicit Vector(int size, double fill = 0);  // column vector (size x 1)
    Vector(std::initializer_list<double> init);

    // Element access (single index)
    double& operator[](int index);
    const double& operator[](int index) const;

    // Vector-specific operations
    double dot(const Vector& other) const;
    double magnitude() const;
    Vector normalized() const;
    static Vector cross(const Vector& a, const Vector& b);  // 3D only

    // Stream
    friend std::ostream& operator<<(std::ostream& os, const Vector& v);
};
```

### `SquareMatrix` — Inherits from Matrix

A convenience class for square matrices with additional operations.

```cpp
class SquareMatrix : public Matrix {
public:
    explicit SquareMatrix(int size, double fill = 0);
    SquareMatrix(std::initializer_list<std::initializer_list<double>> init);

    // Square-specific
    double trace() const;                // sum of diagonal elements
    bool is_symmetric() const;
    bool is_diagonal() const;

    static SquareMatrix identity(int size);
};
```

## Required Features

### 1. Memory Management
- Store matrix data in a flat `double*` array (row-major order)
- Implement full Rule of Five
- Use copy-and-swap for copy assignment
- Move operations must be `noexcept`
- All operations must be leak-free

### 2. Operator Overloading
- `()` for element access (row, col)
- `+`, `-`, `*` for matrix arithmetic
- `*` for scalar multiplication (both sides)
- `+=`, `-=`, `*=` compound assignment
- `==`, `!=` comparison (use epsilon for floating point)
- `<<` for stream output

### 3. Determinant (Recursive)
For an NxN matrix, compute the determinant using cofactor expansion:
- Base case: 1x1 matrix → return the single element
- Base case: 2x2 matrix → `ad - bc`
- Recursive: expand along the first row
  ```
  det(A) = sum over j: (-1)^j * A(0,j) * det(submatrix(0, j))
  ```
  where `submatrix(i, j)` is the matrix with row i and column j removed.

### 4. Static Factory Methods
- `Matrix::identity(n)` — NxN identity matrix
- `Matrix::zeros(r, c)` — all zeros
- `Matrix::ones(r, c)` — all ones

### 5. Error Handling
- Throw `std::invalid_argument` for dimension mismatches in arithmetic
- Throw `std::out_of_range` for invalid indices
- Throw `std::invalid_argument` for determinant/inverse of non-square matrices

## Suggested File Structure

Keep it in one file for now (multi-file comes in Phase 4):

```
P2_project/
├── README.md
└── linalg.cpp
```

## Example Usage

```cpp
int main() {
    // Create matrices
    Matrix a = {{1, 2, 3},
                {4, 5, 6},
                {7, 8, 9}};

    Matrix b = {{9, 8, 7},
                {6, 5, 4},
                {3, 2, 1}};

    // Arithmetic
    std::cout << "A + B:\n" << a + b << "\n";
    std::cout << "A * B:\n" << a * b << "\n";
    std::cout << "A * 2:\n" << a * 2.0 << "\n";
    std::cout << "3 * A:\n" << 3.0 * a << "\n";

    // Transpose
    std::cout << "A^T:\n" << a.transpose() << "\n";

    // Determinant
    Matrix m = {{1, 2}, {3, 4}};
    std::cout << "det(m) = " << m.determinant() << "\n";  // -2

    // Identity
    std::cout << "I(3):\n" << Matrix::identity(3) << "\n";

    // Vector
    Vector v = {1, 2, 3};
    Vector w = {4, 5, 6};
    std::cout << "v dot w = " << v.dot(w) << "\n";        // 32
    std::cout << "||v|| = " << v.magnitude() << "\n";

    // Move semantics
    Matrix big(100, 100, 1.0);
    Matrix moved = std::move(big);  // fast — no allocation
    // big is now empty

    // Copy
    Matrix copy = moved;            // deep copy — independent
    copy(0, 0) = 999;
    // moved(0,0) is still 1.0
}
```

## Bonus Features (Optional)
- Matrix inverse using adjugate method: `A^-1 = adj(A) / det(A)`
- `Row` proxy class so `m[0][1]` syntax works (advanced)
- LU decomposition for more efficient determinant
- Matrix exponentiation: `m.pow(n)`
- Gaussian elimination to solve `Ax = b`

## Getting Started

```bash
g++ -std=c++20 -Wall -Wextra -o linalg linalg.cpp
./linalg
```
