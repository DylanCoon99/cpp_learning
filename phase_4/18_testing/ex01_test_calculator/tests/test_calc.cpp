// Test the Calculator (RPN stack calculator)
//
// Write tests covering:
//
// Basic operations:
//   - push/pop/peek work correctly
//   - add, subtract, multiply, divide produce correct results
//   - Operations consume the top two values and push the result
//
// Edge cases:
//   - Pop from empty stack throws std::underflow_error
//   - Peek on empty stack throws std::underflow_error
//   - Divide by zero throws std::invalid_argument
//   - Operations with insufficient values throw
//
// Complex expressions:
//   - (3 + 4) * 2 = 14
//   - 10 / (5 - 3) = 5
//   - Chain of operations
//
// Custom apply:
//   - apply with a custom lambda (e.g., power)
//
// Use a test fixture (CalculatorTest) with a Calculator member.
// Use EXPECT_EQ for integers, EXPECT_DOUBLE_EQ for doubles,
// EXPECT_THROW for exceptions.

#include <gtest/gtest.h>
#include "calc.h"

// YOUR TESTS HERE
