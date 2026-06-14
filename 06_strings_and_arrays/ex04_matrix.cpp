// Exercise 4: 2D Vector (Matrix) Operations
//
// Task: Implement basic matrix operations using vector<vector<int>>.
//
// Define a type alias at the top:
//   using Matrix = std::vector<std::vector<int>>;
//
// Implement these functions:
//
//   void print_matrix(const Matrix& m)
//     — Print the matrix in a grid format, with values right-aligned
//     — Hint: use std::setw() from <iomanip> for alignment
//
//   Matrix create_matrix(int rows, int cols, int fill = 0)
//     — Create and return a matrix of given size, filled with fill value
//
//   Matrix transpose(const Matrix& m)
//     — Return the transpose (rows become columns)
//     — If input is 2x3, output is 3x2
//
//   Matrix add(const Matrix& a, const Matrix& b)
//     — Element-wise addition (assume same dimensions)
//
//   Matrix multiply(const Matrix& a, const Matrix& b)
//     — Standard matrix multiplication
//     — a is (m x n), b is (n x p), result is (m x p)
//     — result[i][j] = sum of a[i][k] * b[k][j] for all k
//
// In main():
//   - Create a 2x3 matrix A: {{1, 2, 3}, {4, 5, 6}}
//   - Create a 3x2 matrix B: {{7, 8}, {9, 10}, {11, 12}}
//   - Print A
//   - Print transpose of A
//   - Print A * B (should be 2x2: {{58, 64}, {139, 154}})
//
// Compile: g++ -std=c++20 -Wall -Wextra -o ex04 ex04_matrix.cpp

// YOUR CODE HERE
