cmake_minimum_required(VERSION 3.20)
project(log_processor LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Library
add_library(loglib
    src/thread_pool.cpp
    src/log_entry.cpp
    src/log_filter.cpp
    src/log_stats.cpp
    src/log_processor.cpp
)
target_include_directories(loglib PUBLIC include)
target_compile_options(loglib PRIVATE -Wall -Wextra)

# Application
add_executable(log_processor_app app/main.cpp)
target_link_libraries(log_processor_app PRIVATE loglib)

# Tests
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.tar.gz
)
FetchContent_MakeAvailable(googletest)

add_executable(tests tests/test_log.cpp)
target_link_libraries(tests PRIVATE GTest::gtest_main loglib)

include(GoogleTest)
gtest_discover_tests(tests)
