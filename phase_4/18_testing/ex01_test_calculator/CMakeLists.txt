cmake_minimum_required(VERSION 3.20)
project(calculator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Library
add_library(mathlib
    src/calc.cpp
    src/stats.cpp
)
target_include_directories(mathlib PUBLIC include)
target_compile_options(mathlib PRIVATE -Wall -Wextra)

# Application
add_executable(calculator app/main.cpp)
target_link_libraries(calculator PRIVATE mathlib)

# Fetch Google Test
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.tar.gz
)
FetchContent_MakeAvailable(googletest)

# Tests
add_executable(tests
    tests/test_calc.cpp
    tests/test_stats.cpp
)
target_link_libraries(tests PRIVATE GTest::gtest_main mathlib)

include(GoogleTest)
gtest_discover_tests(tests)
