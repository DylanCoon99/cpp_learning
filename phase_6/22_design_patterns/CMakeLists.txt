cmake_minimum_required(VERSION 3.20)
project(design_patterns LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Library
add_library(pipelinelib
    src/pipeline.cpp
    src/stages.cpp
)
target_include_directories(pipelinelib PUBLIC include)
target_compile_options(pipelinelib PRIVATE -Wall -Wextra)

# Application
add_executable(pipeline_app app/main.cpp)
target_link_libraries(pipeline_app PRIVATE pipelinelib)

# Tests
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.tar.gz
)
FetchContent_MakeAvailable(googletest)

add_executable(tests tests/test_pipeline.cpp)
target_link_libraries(tests PRIVATE GTest::gtest_main pipelinelib)

include(GoogleTest)
gtest_discover_tests(tests)
