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


// Basic correctness
TEST(StatsTest, Sum) {
	EXPECT_EQ(stats::sum({1, 2, 3, 4, 5}), 15);
	EXPECT_THROW(stats::sum(std::vector<double>{}), std::invalid_argument);
}


TEST(StatsTest, Mean) {
	EXPECT_EQ(stats::mean({10, 20, 30}), 20);
	EXPECT_EQ(stats::mean({10}), 10);
	EXPECT_THROW(stats::mean(std::vector<double>{}), std::invalid_argument);
}


TEST(StatsTest, Median) {
	EXPECT_EQ(stats::median({1, 3, 5}), 3);
	EXPECT_EQ(stats::median({1, 2, 3, 4}), 2.5);
	EXPECT_EQ(stats::median({10}), 10);
	EXPECT_THROW(stats::median(std::vector<double>{}), std::invalid_argument);
}


TEST(StatsTest, MinMax) {
	EXPECT_EQ(stats::min({0, -4, -5, 4, 2, 7}), -5);
	EXPECT_EQ(stats::max({0, -4, -5, 4, 2, 7}), 7);
	EXPECT_THROW(stats::min(std::vector<double>{}), std::invalid_argument);
	EXPECT_THROW(stats::max(std::vector<double>{}), std::invalid_argument);
}


// Standard Deviation
TEST(MathTest, StandardDeviation) {
	EXPECT_EQ(stats::stddev({0, 0, 0, 0, 0, 0, 0}), 0);
	EXPECT_EQ(stats::stddev({2, 4, 4, 4, 5, 5, 7, 9}), 2.0);
	EXPECT_EQ(stats::stddev({10}), 0);
	EXPECT_THROW(stats::stddev(std::vector<double>{}), std::invalid_argument);	
}


