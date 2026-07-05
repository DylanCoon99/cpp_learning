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


// Setup using test fixtures
class CalculatorTest : public ::testing::Test {
protected:
	void SetUp() override {
		// push some initial values if you want, or leave empty
		calc.push(10);
		calc.push(20);
		calc.push(15);
		calc.push(25);
		calc.push(5);
	}

  Calculator calc;
};




// Use TEST_F instead of TEST — first arg is the fixture class name
TEST_F(CalculatorTest, TestPop) {
    EXPECT_DOUBLE_EQ(calc.pop(), 5);
}


TEST_F(CalculatorTest, TestPeek) {
    EXPECT_DOUBLE_EQ(calc.peek(), 5);
}


TEST_F(CalculatorTest, TestSize) {
    EXPECT_DOUBLE_EQ(calc.size(), 5);
}


TEST_F(CalculatorTest, TestEmpty) {
    EXPECT_FALSE(calc.empty());
}


TEST_F(CalculatorTest, TestAdd) {
    calc.add();
    EXPECT_DOUBLE_EQ(calc.peek(), 30);
}


TEST_F(CalculatorTest, TestSubtract) {
    calc.subtract();
    EXPECT_DOUBLE_EQ(calc.peek(), 20);
}


TEST_F(CalculatorTest, TestMultiply) {
    calc.multiply();
    EXPECT_DOUBLE_EQ(calc.peek(), 125);
}


TEST_F(CalculatorTest, TestDivide) {
    calc.divide();
    EXPECT_DOUBLE_EQ(calc.peek(), 5);
}


TEST_F(CalculatorTest, TestApply) {
    // a**2 + b**2
    calc.apply([](double a, double b) { return a * a + b * b; });                                                                                                                  
    EXPECT_DOUBLE_EQ(calc.peek(), 650);
}


TEST_F(CalculatorTest, TestComplex) {
	calc.add();      // 30 at top of stack
	calc.multiply(); // 450 on top of stack                         
	calc.subtract(); // -430 on top of stack
    EXPECT_DOUBLE_EQ(calc.peek(), -430);
}



// Edge Cases
TEST(CalculatorTestEdgeCases, PopFromEmptyStack) {
	Calculator calc;
	EXPECT_THROW(calc.pop(), std::underflow_error);
}


TEST(CalculatorTestEdgeCases, PeekFromEmptyStack) {
	Calculator calc;
	EXPECT_THROW(calc.peek(), std::underflow_error);
}


TEST(CalculatorTestEdgeCases, DivideByZero) {
	Calculator calc;
	calc.push(5);
	calc.push(0);
	EXPECT_THROW(calc.divide(), std::invalid_argument);
}


TEST(CalculatorTestEdgeCases, AddInsufficientValues) {
	Calculator calc;
	calc.push(5);
	EXPECT_THROW(calc.add(), std::underflow_error);
}



