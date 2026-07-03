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
