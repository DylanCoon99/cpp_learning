cmake_minimum_required(VERSION 3.20)
project(kvstore LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Library
add_library(kvlib
    src/kvstore.cpp
)
target_include_directories(kvlib PUBLIC include)
target_compile_options(kvlib PRIVATE -Wall -Wextra)

# Application
add_executable(kv_app app/main.cpp)
target_link_libraries(kv_app PRIVATE kvlib)

# Tests
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.tar.gz
)
FetchContent_MakeAvailable(googletest)

add_executable(tests tests/test_kvstore.cpp)
target_link_libraries(tests PRIVATE GTest::gtest_main kvlib)

include(GoogleTest)
gtest_discover_tests(tests)
