# Step 18: Testing with Google Test

## Concepts

### 1. Why Test?

You've been testing by running programs and eyeballing output. Automated tests:
- Catch regressions when you change code
- Document expected behavior
- Let you refactor with confidence
- Run in CI pipelines

### 2. Google Test (gtest)

The most popular C++ testing framework. It provides:
- Test macros (`TEST`, `TEST_F`)
- Assertion macros (`EXPECT_EQ`, `ASSERT_TRUE`, etc.)
- Test fixtures for shared setup/teardown
- Test discovery and filtering

### 3. Installing gtest with CMake

The modern way is `FetchContent` — CMake downloads and builds gtest automatically:

```cmake
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.tar.gz
)
FetchContent_MakeAvailable(googletest)
```

Then link your test executable against it:
```cmake
add_executable(tests
    tests/test_main.cpp
    tests/test_calculator.cpp
)
target_link_libraries(tests PRIVATE GTest::gtest_main mylib)

# Enable CTest integration
include(GoogleTest)
gtest_discover_tests(tests)
```

`GTest::gtest_main` provides the `main()` function for you — no need to write one in your test files.

### 4. Writing Tests

```cpp
#include <gtest/gtest.h>

// Basic test
TEST(MathTest, Addition) {
    EXPECT_EQ(2 + 2, 4);
    EXPECT_EQ(-1 + 1, 0);
}

TEST(MathTest, Division) {
    EXPECT_DOUBLE_EQ(10.0 / 3.0, 3.3333333333333335);
    EXPECT_NEAR(10.0 / 3.0, 3.333, 0.001);  // within tolerance
}
```

`TEST(TestSuiteName, TestName)` — each test has a suite name and a test name. Suite groups related tests.

### 5. Assertion Macros

**EXPECT vs ASSERT:**
- `EXPECT_*` — if it fails, the test continues (reports all failures)
- `ASSERT_*` — if it fails, the test stops immediately

Use `EXPECT_*` by default. Use `ASSERT_*` when continuing makes no sense (e.g., a pointer is null — no point testing its contents).

**Common assertions:**

```cpp
// Equality
EXPECT_EQ(a, b);       // a == b
EXPECT_NE(a, b);       // a != b

// Comparison
EXPECT_LT(a, b);       // a < b
EXPECT_LE(a, b);       // a <= b
EXPECT_GT(a, b);       // a > b
EXPECT_GE(a, b);       // a >= b

// Boolean
EXPECT_TRUE(condition);
EXPECT_FALSE(condition);

// String
EXPECT_STREQ(s1, s2);      // C-string equality
EXPECT_STRNE(s1, s2);

// Floating point (handles rounding)
EXPECT_FLOAT_EQ(a, b);     // float comparison
EXPECT_DOUBLE_EQ(a, b);    // double comparison
EXPECT_NEAR(a, b, tol);    // within tolerance

// Exceptions
EXPECT_THROW(statement, exception_type);   // must throw this type
EXPECT_NO_THROW(statement);                // must not throw
EXPECT_ANY_THROW(statement);               // must throw something
```

### 6. Test Fixtures

When multiple tests need the same setup, use a fixture:

```cpp
class StackTest : public ::testing::Test {
protected:
    // Runs before EACH test
    void SetUp() override {
        stack.push(10);
        stack.push(20);
        stack.push(30);
    }

    // Runs after EACH test (optional)
    void TearDown() override {
        // cleanup if needed
    }

    Stack<int> stack;  // shared across tests in this fixture
};

// Use TEST_F instead of TEST — first arg is the fixture class name
TEST_F(StackTest, PopReturnsTop) {
    EXPECT_EQ(stack.pop(), 30);
}

TEST_F(StackTest, SizeIsCorrect) {
    EXPECT_EQ(stack.size(), 3);
}

TEST_F(StackTest, PopReducesSize) {
    stack.pop();
    EXPECT_EQ(stack.size(), 2);
}
```

Each `TEST_F` gets a fresh instance — `SetUp` runs before each test, so modifications in one test don't affect another.

### 7. Testing Exceptions

```cpp
TEST(CalculatorTest, DivideByZeroThrows) {
    Calculator calc;
    calc.push(10);
    calc.push(0);
    EXPECT_THROW(calc.divide(), std::invalid_argument);
}

TEST(CalculatorTest, PopEmptyThrows) {
    Calculator calc;
    EXPECT_THROW(calc.pop(), std::underflow_error);
}
```

### 8. Test Organization

```
project/
├── CMakeLists.txt
├── include/
│   └── calc.h
├── src/
│   └── calc.cpp
└── tests/
    ├── test_calc.cpp        ← unit tests for Calculator
    └── test_stats.cpp       ← unit tests for stats functions
```

Convention: one test file per source file. Name them `test_<module>.cpp`.

### 9. Running Tests

```bash
# Build
cmake -B build
cmake --build build

# Run all tests
cd build && ctest

# Or run the test binary directly (more verbose output)
./build/tests

# Run specific tests by filter
./build/tests --gtest_filter="StackTest.*"         # all StackTest tests
./build/tests --gtest_filter="*PopReturnsTop"      # specific test
./build/tests --gtest_filter="-SlowTest.*"         # exclude tests

# Verbose output
./build/tests --gtest_print_time=0
```

### 10. What Makes a Good Unit Test

- **Test one thing** — each test checks one behavior
- **Descriptive names** — `TEST(Calculator, DivideByZeroThrowsInvalidArgument)` not `TEST(Calc, Test1)`
- **Arrange-Act-Assert** pattern:
  ```cpp
  TEST(StatsTest, MeanOfThreeValues) {
      // Arrange
      std::vector<double> data = {10, 20, 30};

      // Act
      double result = stats::mean(data);

      // Assert
      EXPECT_DOUBLE_EQ(result, 20.0);
  }
  ```
- **Test edge cases** — empty input, single element, negative values, overflow
- **Test error cases** — invalid input should throw/fail gracefully
- **Independent** — tests should not depend on each other or on execution order

---

## Exercise

This step has one exercise: add a full test suite to the calculator library from step 17 ex03.

**ex01_test_calculator/** — Add gtest to the calculator project and write comprehensive tests.
