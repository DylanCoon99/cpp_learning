# Exercise 1: Your First CMake Project
#
# Task: Get this project building with CMake.
#
# The source file (src/main.cpp) is already written.
# Fill in this CMakeLists.txt to build it.
#
# Requirements:
#   - Set minimum CMake version to 3.20
#   - Name the project "hello_cmake"
#   - Set C++20 standard
#   - Create an executable called "hello" from src/main.cpp
#
# Build and run:
#   cmake -B build
#   cmake --build build
#   ./build/hello

# YOUR CMAKE HERE

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

cmake_minimum_required(VERSION 3.20)
project(hello_cmake LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Create an executable from source files
add_executable(hello
    src/main.cpp
)

