# Exercise 2: Multi-File Project
#
# Task: Set up CMake for a multi-file project with header/source separation.
#
# The code is a simple "task list" — split across:
#   include/task.h      — Task struct and TaskList class declaration
#   src/task.cpp        — TaskList method definitions
#   src/main.cpp        — main() that uses TaskList
#
# Your CMakeLists.txt should:
#   - Create a library called "tasklib" from src/task.cpp
#   - Set include directories so #include "task.h" works
#   - Create an executable called "taskapp" from src/main.cpp
#   - Link taskapp against tasklib
#
# Build and run:
#   cmake -B build
#   cmake --build build
#   ./build/taskapp

# YOUR CMAKE HERE

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

cmake_minimum_required(VERSION 3.20)
project(taskapp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Create an executable from source files
add_library(tasklib
    src/task.cpp
)

add_executable(taskapp
    src/main.cpp
)


target_link_libraries(taskapp PUBLIC tasklib)
target_include_directories(tasklib PUBLIC include)