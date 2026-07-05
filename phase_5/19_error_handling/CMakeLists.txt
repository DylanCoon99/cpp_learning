cmake_minimum_required(VERSION 3.20)
project(config_parser LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Library
add_library(configlib
    src/config.cpp
)
target_include_directories(configlib PUBLIC include)
target_compile_options(configlib PRIVATE -Wall -Wextra)

# Application
add_executable(config_app app/main.cpp)
target_link_libraries(config_app PRIVATE configlib)

# Tests
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.tar.gz
)
FetchContent_MakeAvailable(googletest)

add_executable(tests tests/test_config.cpp)
target_link_libraries(tests PRIVATE GTest::gtest_main configlib)

include(GoogleTest)
gtest_discover_tests(tests)
