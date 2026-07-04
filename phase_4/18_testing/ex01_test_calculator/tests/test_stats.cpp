// Test the stats functions
//
// Write tests covering:
//
// Basic correctness:
//   - sum of {1, 2, 3, 4, 5} = 15
//   - mean of {10, 20, 30} = 20
//   - median of odd-length vector: {1, 3, 5} = 3
//   - median of even-length vector: {1, 2, 3, 4} = 2.5
//   - min and max
//
// Standard deviation:
//   - stddev of identical values = 0
//   - stddev of known dataset (compute expected value by hand or use a reference)
//
// Edge cases:
//   - Single element: mean = that element, stddev = 0, median = that element
//   - Empty vector throws std::invalid_argument for all functions
//   - Negative numbers
//   - All same values
//
// Use EXPECT_DOUBLE_EQ for exact double comparison,
// EXPECT_NEAR for stddev (floating point tolerance),
// EXPECT_THROW for empty input.

#include <gtest/gtest.h>
#include "stats.h"

// YOUR TESTS HERE
