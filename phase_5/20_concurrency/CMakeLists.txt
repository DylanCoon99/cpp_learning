cmake_minimum_required(VERSION 3.20)
project(thread_pool LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Library
add_library(poollib
    src/thread_pool.cpp
)
target_include_directories(poollib PUBLIC include)
target_compile_options(poollib PRIVATE -Wall -Wextra)

# Application
add_executable(pool_app app/main.cpp)
target_link_libraries(pool_app PRIVATE poollib)

# Tests
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.tar.gz
)
FetchContent_MakeAvailable(googletest)

add_executable(tests tests/test_thread_pool.cpp)
target_link_libraries(tests PRIVATE GTest::gtest_main poollib)

include(GoogleTest)
gtest_discover_tests(tests)
