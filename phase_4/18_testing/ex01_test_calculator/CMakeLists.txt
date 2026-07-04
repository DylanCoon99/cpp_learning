# Exercise 1: Add Google Test to the Calculator Project
#
# Task: Set up gtest and write comprehensive tests for the calculator
#       library (calc and stats modules).
#
# Your CMakeLists.txt should:
#   1. Set up the project (cmake_minimum_required, project, C++20)
#   2. Create the mathlib library from src/calc.cpp and src/stats.cpp
#   3. Set include directories on mathlib (PUBLIC)
#   4. Create the calculator executable from app/main.cpp, linked to mathlib
#   5. Fetch Google Test using FetchContent
#   6. Create a test executable from tests/test_calc.cpp and tests/test_stats.cpp
#   7. Link the test executable against GTest::gtest_main and mathlib
#   8. Enable CTest with gtest_discover_tests
#
# Build and run:
#   cmake -B build
#   cmake --build build
#   cd build && ctest --output-on-failure
#   # or: ./build/tests

# YOUR CMAKE HERE
