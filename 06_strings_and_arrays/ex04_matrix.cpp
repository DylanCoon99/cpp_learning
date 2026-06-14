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
#include <iostream>
#include <iomanip>
#include <string>


using Matrix = std::vector<std::vector<int>>;



void print_matrix(const Matrix& m) {

	std::cout << std::setw(4);
	for (int i = 0; i < static_cast<int>(m.size()); ++i) {
		for (int j = 0; j < static_cast<int>(m[0].size()); ++j) {
			std::cout << m[i][j] << std::setw(4);
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;

}



Matrix create_matrix(int rows, int cols, int fill = 0) {
	std::vector<std::vector<int>> matrix(rows, std::vector<int> (cols, fill));

	return matrix;
}



Matrix transpose(const Matrix& m) {


	Matrix r = create_matrix(m[0].size(), m.size());

	for (int i = 0; i < static_cast<int>(r.size()); ++i) {
		// the rows become columns
		for (int j = 0; j < static_cast<int>(r[0].size()); ++j) {
			r[i][j] = m[j][i];
		}
	}



	return r;
}



Matrix add(const Matrix& a, const Matrix& b) {

	// check the dimensions
	if (a.size() != b.size() || a[0].size() != b[0].size()) {
		return a;
	}

	// create an empty matrix
	Matrix m = create_matrix(a.size(), a[0].size());

	for (int i = 0; i < static_cast<int>(m.size()); ++i) {
		for (int j = 0; j < static_cast<int>(m[0].size()); ++j) {
			m[i][j] = a[i][j] + b[i][j];
		}
	}


	return m;
}



Matrix multiply(const Matrix& a, const Matrix& b) {
	
	/*

	must be 

		res = mxn * nxm

		res[i][j] = sum of a[i][k] * b[k][j] for all k


	*/

	if (a[0].size() != b.size()) {
		return a;
	}

	Matrix m = create_matrix(a.size(), b[0].size());

	for (int i = 0; i < static_cast<int>(a.size()); ++i){

		for (int j = 0; j < static_cast<int>(b[0].size()); ++j) {

			for (int k = 0; k < static_cast<int>(a[0].size()); ++k) {
				m[i][j] += (a[i][k] * b[k][j]);
			}
		}
	}


	return m;
}



int main() {


	//Matrix m = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};

	Matrix A = {{1, 2, 3}, {4, 5, 6}};
	Matrix B = {{7, 8}, {9, 10}, {11, 12}};
	print_matrix(A);
	print_matrix(transpose(A));
	print_matrix(multiply(A, B));




	// Test


}