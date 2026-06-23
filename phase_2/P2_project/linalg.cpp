// Phase 2 Project: Linear Algebra Library
//
// Build a matrix/vector math library with full operator support,
// inheritance, and Rule of Five resource management.
// See README.md for full requirements.
//
// Compile: g++ -std=c++20 -Wall -Wextra -o linalg linalg.cpp

// YOUR CODE HERE
#include <algorithm>
#include <iostream>
#include <stdexcept>

class Matrix {
public:
    // Constructors
    Matrix() : data_(new double[0]), rows_(0), cols_(0) { } // default: 0x0

    Matrix(int rows, int cols, double fill = 0) : data_(new double[cols * rows]), rows_(rows), cols_(cols) {
    	for (int i = 0; i < rows_ * cols_; ++i) {
    		data_[i] = fill;
    	}
    } // sized with fill value

    Matrix(std::initializer_list<std::initializer_list<double>> init) {
		rows_ = init.size();
		cols_ = init.begin()->size();
		data_ = new double[rows_ * cols_];

		int i = 0;
		for (const auto& row : init) {
			for (double val : row) {
				data_[i] = val;
				++i;
			}
		}
    }

    // Rule of Five
    ~Matrix() {
    	delete[] data_;
    }

    Matrix(const Matrix& other) 
    	: data_(new double[other.rows_ * other.cols_]), rows_(other.rows_), cols_(other.cols_) {
    	// copy constructor
    	std::copy(other.data_, other.data_ + (rows_ * cols_), data_);
    }

    Matrix& operator=(const Matrix& other) {
    	// copy assignment
    	// free up old resource
    	delete[] data_;

    	data_ = new double[other.rows_ * other.cols_];
    	rows_ = other.rows_;
    	cols_ = other.cols_;

		std::copy(other.data_, other.data_ + (rows_ * cols_), data_);    
		return *this;	
    }

	Matrix(Matrix&& other) noexcept                                                                                                                                                    
		: data_(other.data_), rows_(other.rows_), cols_(other.cols_) {                                                                                                                 
		other.data_ = nullptr;                                                                                                                                                         
		other.rows_ = 0;                                                                                                                                                               
		other.cols_ = 0;                                                                                                                                                             
	} 

    Matrix& operator=(Matrix&& other) noexcept {
    	// move assignment
    	// free up old resource
    	data_ = other.data_;
    	rows_ = other.rows_;
    	cols_ = other.cols_;

    	// other should be valid but empty
    	other.rows_ = 0;
    	other.cols_ = 0;
    	other.data_ = nullptr;
    	return *this;
    }

    // Element access
    double& operator()(int row, int col) {
    	return data_[index(row, col)];
    }

    const double& operator()(int row, int col) const {
    	return data_[index(row, col)];
    }

    // Dimensions
    int rows() const { return rows_; }
    int cols() const { return cols_; }

    // Arithmetic operators
    Matrix operator*(const Matrix& rhs) const {
    	// matrix multiply
    	if (cols_ != rhs.rows_) {
			throw std::runtime_error("Matrices must take the form (m x n) * (n x p)!");
		}
		Matrix result = Matrix(rows_, rhs.cols_, 0);
		for (int i = 0; i < rows_; ++i) {
			for (int j = 0; j < rhs.cols_; ++j) {
				for (int k = 0; k < cols_; ++k) {
					result(i, j) = result(i, j) + (data_[index(i, k)] * rhs(k, j));
				}
			}
		}
		return result;
    }

    Matrix& operator*=(double scalar) {

    	for (int i = 0; i < rows_; ++i) {
    		for (int j = 0; j < cols_; ++j) {
    			data_[index(i, j)] *= scalar;
    		}
    	}
    	return *this;
    }

    Matrix operator*(double scalar) const {
    	// scalar multiply
    	Matrix result = *this;
    	result *= scalar;
    	return result;
    }

    Matrix& operator+=(const Matrix& rhs) {

    	for (int i = 0; i < rows_; ++i) {
    		for (int j = 0; j < cols_; ++j) {
    			data_[index(i, j)] += rhs.data_[index(i, j)];
    		}
    	}
 		return *this;
    }

    Matrix& operator-=(const Matrix& rhs) {

		for (int i = 0; i < rows_; ++i) {
    		for (int j = 0; j < cols_; ++j) {
    			data_[index(i, j)] -= rhs.data_[index(i, j)];
    		}
    	}
 		return *this;
    }

    Matrix operator+(const Matrix& rhs) const {
    	Matrix result = *this;
    	result += rhs;
    	return result;
    }
    
    Matrix operator-(const Matrix& rhs) const {
    	Matrix result = *this;
    	result -= rhs;
    	return result;
    }
    
    // Comparison
    bool operator==(const Matrix& rhs) const {
    	if (!same_dimension(rhs)) {
    		return false;
    	}
    	for (int i = 0; i < rows_ * cols_; ++i) {
    		if (data_[i] != rhs.data_[i]) {
    			return false;
    		}
    	}
    	return true;
    }

    bool operator!=(const Matrix& rhs) const {
    	return !(*this == rhs);
    }

    // Stream I/O
    friend std::ostream& operator<<(std::ostream& os, const Matrix& m) {
    	for (int i = 0; i < m.rows_; ++i) {
			for (int j = 0; j < m.cols_; ++j) {
				os << m(i, j) << " ";
			}
			os << std::endl;
		}
		return os;
    }

    // Operations
    Matrix transpose() const {
    	Matrix result = Matrix(cols_, rows_);

		for (int i = 0; i < rows_; ++i) {
			for (int j = 0; j < cols_; ++j) {
				result(i, j) = data_[index(j, i)];
			}
		}
		return result;
    }

    double determinant() const {
    	// only for square matrices
    	if (rows_ != cols_) {
    		throw std::runtime_error("Can only compute determinant for square matrices.");
    	}
    	// compute the determinant

    	// I am not computing the determinant. This is out of scope of what I want to learn.
    	return 0.0;
    }


    Matrix submatrix(int exclude_row, int exclude_col) const {
    	Matrix result(rows_ - 1, cols_ - 1, 0);
    	for (int i = 0; i < rows_; ++i) {
			for (int j = 0; j < cols_; ++j) {
				if (i != exclude_row && j != exclude_col) {
					int row_i = (i > exclude_row) ? (i - 1) : i;
					int col_j = (j > exclude_col) ? (j - 1) : j;
					result(row_i, col_j) = data_[index(i, j)];
				}
			}
		}
		return result;
    }

    // Utility
    void swap(Matrix& other) noexcept {
    	std::swap(other.data_, data_);
    	std::swap(other.rows_, rows_);
    	std::swap(other.cols_, cols_);
    }

    static Matrix identity(int size) {
    	// returns size x size identity matrix

    	Matrix result = Matrix(size, size, 0);

		for (int i = 0; i < size; ++i) {
			for (int j = 0; j < size; ++j) {
				if (i == j) {
					result(i, j) = 1;
				}
			}
		}

		return result;
    }
    static Matrix zeros(int rows, int cols) {
    	return Matrix(rows, cols, 0);
    }
    static Matrix ones(int rows, int cols) {
    	return Matrix(rows, cols, 1);
    }

    bool same_dimension(const Matrix& rhs) const {
		return (rows_ == rhs.rows_) && (cols_ == rhs.cols_);
	}

protected:
    double* data_;     // flat 1D array storing row-major data
    int rows_;
    int cols_;

    int index(int row, int col) const { return row * cols_ + col; }
};

// Free function: scalar * matrix (scalar on left side)
Matrix operator*(double scalar, const Matrix& m) {
	Matrix result = m;
	result *= scalar;
	return result;
}



class Vector : public Matrix {
public:
	explicit Vector(int size, double fill = 0) : Matrix(size, 1, fill) { } // column vector (size x 1)

	Vector(std::initializer_list<double> init) {
		rows_ = init.size();
		cols_ = 1;

		data_ = new double[rows_];

		int i = 0;
		for (const double& val : init) {
			data_[i] = val;
			++i;
		}
	}

	// Element access (single index)
	double& operator[](int index) {
		return data_[index];
	}
	const double& operator[](int index) const {
		return data_[index];
	}

	// Vector-specific operations
	double dot(const Vector& other) const {
		int result = 0;

		for (int i = 0; i < rows_; ++i) {
			result += (data_[i] * other.data_[i]);
		}

		return result;
	}
	double magnitude() const {
		double result = 0.0;
		
		for (int i = 0; i < rows_; ++i) {
			result += (data_[i] * data_[i]);
		}

		return std::sqrt(result);
	}

	Vector normalized() const {
		Vector result = *this;
		for (int i = 0; i < rows_; ++i) {
			result[i] /= magnitude();
		}
		return result;
	}

	static Vector cross(const Vector& a, const Vector& b) {
		// 3D only
		return Vector{a[1] * b[2] - a[2] * b[1], a[2] * b[0] - a[0] * b[2], a[0] * b[1] - a[1] * b[0]};
	}

	// Stream
	friend std::ostream& operator<<(std::ostream& os, const Vector& v) {
		for (int i = 0; i < v.rows_; ++i) {
			os << v[i] << std::endl;
		}
		return os;
	}
};


class SquareMatrix : public Matrix {
public:
	explicit SquareMatrix(int size, double fill = 0) : Matrix(size, size, fill) {};
	SquareMatrix(std::initializer_list<std::initializer_list<double>> init) : Matrix(init) {};

	// Square-specific
	double trace() const {
		// sum of diagonal elements
		double result = 0.0;

		for (int i = 0; i < rows_; ++i)  {
			for (int j = 0; j < cols_; ++j) {
				if (i == j) {
					result += data_[index(i, j)];
				}
			}
		}

		return result;
	}
	bool is_symmetric() const {
		return *this == transpose();
	}
	bool is_diagonal() const {

		for (int i = 0; i < rows_; ++i)  {
			for (int j = 0; j < cols_; ++j) {
				if (i != j) {
					if (data_[index(i, j)] != 0) {
						return false;
					}
				}
			}
		}
		
		return true;
	}

	static SquareMatrix identity(int size) {
		SquareMatrix result = SquareMatrix(size, 0);

		for (int i = 0; i < size; ++i) {
			for (int j = 0; j < size; ++j) {
				if (i == j) {
					result(i, j) = 1;
				}
			}
		}

		return result;
	}
};



int main() {
	/*
	// === Construction ===
	Matrix a(2, 3, 5.0);
	std::cout << "a (2x3 filled with 5):\n" << a << std::endl;

	Matrix b(2, 3, 2.0);
	std::cout << "b (2x3 filled with 2):\n" << b << std::endl;

	// === Element access ===
	a(0, 0) = 1.0;
	a(0, 1) = 2.0;
	a(0, 2) = 3.0;
	a(1, 0) = 4.0;
	a(1, 1) = 5.0;
	a(1, 2) = 6.0;
	std::cout << "a after setting elements:\n" << a << std::endl;

	// === Arithmetic ===
	std::cout << "a + b:\n" << a + b << std::endl;
	std::cout << "a - b:\n" << a - b << std::endl;
	std::cout << "a * 3.0:\n" << a * 3.0 << std::endl;
	std::cout << "2.0 * a:\n" << 2.0 * a << std::endl;

	// === Matrix multiplication ===
	Matrix c(3, 2, 1.0);
	c(0, 0) = 7; c(0, 1) = 8;
	c(1, 0) = 9; c(1, 1) = 10;
	c(2, 0) = 11; c(2, 1) = 12;
	std::cout << "c (3x2):\n" << c << std::endl;
	std::cout << "a * c (2x3 * 3x2 = 2x2):\n" << a * c << std::endl;
	
	// === Compound assignment ===
	Matrix d = a;
	d += b;
	std::cout << "d = a; d += b:\n" << d << std::endl;
	d -= b;
	std::cout << "d -= b (should equal a):\n" << d << std::endl;
	d *= 10.0;
	std::cout << "d *= 10:\n" << d << std::endl;

	

	// === Transpose ===
	std::cout << "a^T:\n" << a.transpose() << std::endl;

	// === Submatrix ===
	Matrix sq(3, 3, 0);
	sq(0,0)=1; sq(0,1)=2; sq(0,2)=3;
	sq(1,0)=4; sq(1,1)=5; sq(1,2)=6;
	sq(2,0)=7; sq(2,1)=8; sq(2,2)=9;
	std::cout << "sq:\n" << sq << std::endl;
	std::cout << "submatrix(0,0):\n" << sq.submatrix(0, 0) << std::endl;
	std::cout << "submatrix(1,1):\n" << sq.submatrix(1, 1) << std::endl;

	// === Static factories ===
	std::cout << "identity(3):\n" << Matrix::identity(3) << std::endl;
	std::cout << "zeros(2,4):\n" << Matrix::zeros(2, 4) << std::endl;
	std::cout << "ones(3,3):\n" << Matrix::ones(3, 3) << std::endl;

	// === Comparison ===
	Matrix e = a;
	std::cout << "a == e: " << (a == e ? "true" : "false") << std::endl;
	std::cout << "a != b: " << (a != b ? "true" : "false") << std::endl;

	// === Copy semantics ===
	Matrix f = a;
	f(0, 0) = 999.0;
	std::cout << "f(0,0) = 999, a(0,0) = " << a(0, 0) << " (should be 1)\n" << std::endl;

	// === Move semantics ===
	Matrix g = std::move(f);
	std::cout << "g (moved from f):\n" << g << std::endl;
	std::cout << "f rows after move: " << f.rows() << std::endl;

	// === Move assignment ===
	Matrix h(1, 1, 0);
	h = std::move(g);
	std::cout << "h (move assigned from g):\n" << h << std::endl;
	std::cout << "g rows after move: " << g.rows() << std::endl;
	

	// === Vector tests ===
	std::cout << "\n=== Vector Tests ===\n" << std::endl;

	// Construction
	Vector v1 = {1.0, 2.0, 3.0};
	Vector v2 = {4.0, 5.0, 6.0};
	std::cout << "v1:\n" << v1 << std::endl;
	std::cout << "v2:\n" << v2 << std::endl;

	// Size constructor
	Vector v3(4, 7.0);
	std::cout << "v3 (size 4, fill 7):\n" << v3 << std::endl;
	
	// Element access with []
	std::cout << "v1[0]: " << v1[0] << std::endl;
	std::cout << "v1[1]: " << v1[1] << std::endl;
	std::cout << "v1[2]: " << v1[2] << std::endl;
	v1[0] = 10.0;
	std::cout << "v1[0] after setting to 10: " << v1[0] << std::endl;
	v1[0] = 1.0;

	// Dot product
	std::cout << "v1 dot v2: " << v1.dot(v2) << " (expected 32)" << std::endl;

	// Magnitude
	Vector v4 = {3.0, 4.0};
	std::cout << "magnitude of (3,4): " << v4.magnitude() << " (expected 5)" << std::endl;
	
	// Normalized
	Vector v4_norm = v4.normalized();
	std::cout << "normalized (3,4):\n" << v4_norm << std::endl;
	std::cout << "magnitude of normalized: " << v4_norm.magnitude() << " (expected 1)" << std::endl;

	// Cross product
	Vector i_hat = {1.0, 0.0, 0.0};
	Vector j_hat = {0.0, 1.0, 0.0};
	Vector k = Vector::cross(i_hat, j_hat);
	std::cout << "i x j:\n" << k << " (expected 0, 0, 1)" << std::endl;
	*/

	// === SquareMatrix tests ===
	std::cout << "\n=== SquareMatrix Tests ===\n" << std::endl;

	// Construction
	SquareMatrix s1(3, 0.0);
	s1(0,0)=1; s1(0,1)=2; s1(0,2)=3;
	s1(1,0)=2; s1(1,1)=5; s1(1,2)=6;
	s1(2,0)=3; s1(2,1)=6; s1(2,2)=9;
	std::cout << "s1:\n" << s1 << std::endl;

	// Initializer list construction
	SquareMatrix s2 = {{1, 0, 0}, {0, 2, 0}, {0, 0, 3}};
	std::cout << "s2 (diagonal):\n" << s2 << std::endl;

	// Trace
	std::cout << "trace(s1): " << s1.trace() << " (expected 15)" << std::endl;
	std::cout << "trace(s2): " << s2.trace() << " (expected 6)" << std::endl;

	// Is symmetric
	std::cout << "s1 is_symmetric: " << (s1.is_symmetric() ? "true" : "false") << " (expected true)" << std::endl;
	SquareMatrix s3 = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
	std::cout << "s3 is_symmetric: " << (s3.is_symmetric() ? "true" : "false") << " (expected false)" << std::endl;

	// Is diagonal
	std::cout << "s2 is_diagonal: " << (s2.is_diagonal() ? "true" : "false") << " (expected true)" << std::endl;
	std::cout << "s1 is_diagonal: " << (s1.is_diagonal() ? "true" : "false") << " (expected false)" << std::endl;

	// Identity
	SquareMatrix id = SquareMatrix::identity(4);
	std::cout << "identity(4):\n" << id << std::endl;
	std::cout << "identity trace: " << id.trace() << " (expected 4)" << std::endl;
	std::cout << "identity is_diagonal: " << (id.is_diagonal() ? "true" : "false") << " (expected true)" << std::endl;
	std::cout << "identity is_symmetric: " << (id.is_symmetric() ? "true" : "false") << " (expected true)" << std::endl;

}