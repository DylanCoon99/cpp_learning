// Exercise 3: Matrix Class with Operators
//
// Task: Refactor your step 06 matrix code into a proper class with operators.
//
// Class definition:
//
//   class Matrix {
//   public:
//       Matrix(int rows, int cols, int fill = 0);
//       Matrix(std::initializer_list<std::initializer_list<int>> init);
//         // Allows: Matrix m = {{1,2},{3,4}};
//
//       // Dimensions
//       int rows() const;
//       int cols() const;
//
//       // Access — return a reference to the element
//       int& operator()(int row, int col);              // m(1,2) = 5
//       const int& operator()(int row, int col) const;  // int x = m(1,2)
//       // Note: we use () not [] because [] only takes one argument
//       // (C++23 adds multi-dimensional [], but () is the classic approach)
//
//       // Arithmetic
//       Matrix& operator+=(const Matrix& rhs);
//       Matrix& operator-=(const Matrix& rhs);
//       Matrix operator+(const Matrix& rhs) const;
//       Matrix operator-(const Matrix& rhs) const;
//       Matrix operator*(const Matrix& rhs) const;  // matrix multiplication
//       Matrix operator*(int scalar) const;          // scalar multiplication
//
//       // Comparison
//       bool operator==(const Matrix& rhs) const;
//       bool operator!=(const Matrix& rhs) const;
//
//       // Stream
//       friend std::ostream& operator<<(std::ostream& os, const Matrix& m);
//
//       // Utility
//       Matrix transpose() const;
//
//   private:
//       int rows_, cols_;
//       std::vector<std::vector<int>> data_;
//   };
//
// Requirements:
//   - operator() should throw std::out_of_range for invalid indices
//   - Arithmetic operators should throw std::invalid_argument for
//     incompatible dimensions
//   - The initializer_list constructor allows: Matrix m = {{1,2,3},{4,5,6}};
//     An initializer_list<initializer_list<int>> is a list of rows.
//     Loop over it to fill data_:
//       Matrix(std::initializer_list<std::initializer_list<int>> init) {
//           for (const auto& row : init) {
//               data_.push_back(std::vector<int>(row));
//           }
//           rows_ = data_.size();
//           cols_ = data_[0].size();
//       }
//   - Stream output should print a clean grid
//
// In main():
//   - Create matrices with both constructors
//   - Test element access with ()
//   - Test addition, subtraction, multiplication
//   - Test transpose
//   - Print with <<
//   - Test dimension mismatch error handling
//
// Compile: g++ -std=c++20 -Wall -Wextra -o ex03 ex03_matrix.cpp

// YOUR CODE HERE
#include <initializer_list>
#include <iostream>
#include <vector>
#include <iomanip>
#include <stdexcept>



class Matrix {
public:
		Matrix(int rows, int cols, int fill = 0) : rows_(rows), cols_(cols) {
			data_ = std::vector<std::vector<int>>(rows, std::vector<int>(cols, fill));
		}
		Matrix(std::initializer_list<std::initializer_list<int>> init) {
			// Allows: Matrix m = {{1,2},{3,4}};

			int rows = init.size();
			int cols = init.begin()[0].size();

			data_ = std::vector<std::vector<int>>(rows, std::vector<int>(cols));

			int i = 0;
			for (auto& v : init) {
				// for each list in the initializer list
				data_[i] = v;
				++i;
			}

			rows_ = rows;
			cols_ = cols;

		}
		

		// Dimensions
		int rows() const {
			return rows_;
		}

		int cols() const {
			return cols_;
		}

		// Access — return a reference to the element
		int& operator()(int row, int col) {
			// m(1,2) = 5
			if (row >= rows_ || col >= cols_) {
				throw std::runtime_error("Matrix dimensions don't match!");
			}
			return data_[row][col];
		}
		const int& operator()(int row, int col) const {
			// int x = m(1,2)
			if (row >= rows_ || col >= cols_) {
				throw std::runtime_error("Matrix dimensions don't match!");
			}
			return data_[row][col];
		}
		// Note: we use () not [] because [] only takes one argument
		// (C++23 adds multi-dimensional [], but () is the classic approach)

		// Arithmetic
		Matrix& operator+=(const Matrix& rhs) {
			if (!same_dimension(rhs)) {
				throw std::runtime_error("Matrix dimensions don't match!");
			}

			for (int i = 0; i < rows_; ++i) {
				for (int j = 0; j < cols_; ++j) {
					data_[i][j] += rhs(i, j);
				}
			}
			return *this;
		}

		Matrix& operator-=(const Matrix& rhs) {
			if (!same_dimension(rhs)) {
				throw std::runtime_error("Matrix dimensions don't match!");
			}

			for (int i = 0; i < rows_; ++i) {
				for (int j = 0; j < cols_; ++j) {
					data_[i][j] -= rhs(i, j);
				}
			}
			return *this;
		}

		Matrix operator+(const Matrix& rhs) const {
			if (!same_dimension(rhs)) {
				throw std::runtime_error("Matrix dimensions don't match!");
			}

			Matrix result = *this;
			result += rhs;
			return result;
		}

		Matrix operator-(const Matrix& rhs) const {
			if (!same_dimension(rhs)) {
				throw std::runtime_error("Matrix dimensions don't match!");
			}

			Matrix result = *this;
			result -= rhs;
			return result;
		}

		Matrix operator*(const Matrix& rhs) const {
			// matrix multiplication
			if (cols_ != rhs.rows_) {
				throw std::runtime_error("Matrices must take the form (m x n) * (n x p)!");
			}
			Matrix result = Matrix(rows_, rhs.cols_, 0);
			for (int i = 0; i < rows_; ++i) {
				for (int j = 0; j < rhs.cols_; ++j) {
					for (int k = 0; k < cols_; ++k) {
						result(i, j) = result(i, j) + (data_[i][k] * rhs(k, j));
					}
				}
			}
			return result;
		}

		Matrix operator*(int scalar) const {
			// scalar multiplication
			Matrix result = Matrix(rows_, cols_);

			for (int i = 0; i < rows_; ++i) {
				for (int j = 0; j < cols_; ++j) {
					result(i, j) = data_[i][j] * scalar;
				}
			}


			return result;
		}

		// Comparison
		bool operator==(const Matrix& rhs) const {

			if (!same_dimension(rhs)) {
				throw std::runtime_error("Matrix dimensions don't match!");
			}

			for (int i = 0; i < rows_; ++i) {
				for (int j = 0; j < cols_; ++j) {
					if (data_[i][j] != rhs(i, j)) {
						return false;
					}
				}
			}

			return true;

		}

		bool operator!=(const Matrix& rhs) const {
			return !(*this == rhs);
		}

		// Stream
		friend std::ostream& operator<<(std::ostream& os, const Matrix& m) {
			//os << "[";
			for (int i = 0; i < m.rows_; ++i) {
				for (int j = 0; j < m.cols_; ++j) {
					os << " " << m.data_[i][j] << " ";
				}
				os << std::endl;
			}
			//os << "]" << std::endl;
    		return os; 
		}

        // Utility
		Matrix transpose() const {

			Matrix result = Matrix(cols_, rows_);

			for (int i = 0; i < rows_; ++i) {
				for (int j = 0; j < cols_; ++j) {
					result(i, j) = data_[j][i];
				}
			}
			return result;
		}

		bool same_dimension(const Matrix& rhs) const {
			return (rows_ == rhs.rows_) && (cols_ == rhs.cols_);
		}

	private:
		int rows_, cols_;
		std::vector<std::vector<int>> data_;
};


int main() {
	// - Create matrices with both constructors
	Matrix m1 = Matrix(2, 2, 3);
	Matrix m2 = Matrix{{1,2},{3,4}};

	std::cout << m1 << std::endl;
	std::cout << m2 << std::endl;

	// - Test element access with ()
	std::cout << "m1(1, 1): " << m1(1, 1) << std::endl;
	std::cout << "m2(1, 1): " << m2(1, 1) << std::endl;
	// - Test addition, subtraction, multiplication
	Matrix m3 = m1 + m2;
	Matrix m4 = m1 - m2;
	Matrix m5 = m1 * m2;

	// results
	std::cout << "m1 + m2 = " << std::endl;
	std::cout << m3 << std::endl; 

	std::cout << "m1 - m2 = " << std::endl;
	std::cout << m4 << std::endl; 

	std::cout << "m1 * m2 = " << std::endl;
	std::cout << m5 << std::endl; 
	// - Test transpose
	std::cout << "m2^T: " << std::endl;
	std::cout << m2.transpose() << std::endl;
	// - Test dimension mismatch error handling
	//std::cout << "m1(4, 4): " << m1(4, 4) << std::endl;
	//Matrix m6 = Matrix(4, 6, 3);
	//std::cout << "m1 + m6: " << m1 + m6 << std::endl;
	//std::cout << "m1 * m6 " << m1 * m6 << std::endl;


}
