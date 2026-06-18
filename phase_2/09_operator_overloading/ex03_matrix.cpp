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
