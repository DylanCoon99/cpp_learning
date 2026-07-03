# Exercise 3: Reusable Calculator Library
#
# Task: Build a math library that's separate from the application.
#       This models real-world project structure: library + app that uses it.
#
# Structure:
#   include/calc.h        — Calculator class declaration
#   include/stats.h       — Statistics functions declaration
#   src/calc.cpp          — Calculator implementation
#   src/stats.cpp         — Statistics implementation
#   app/main.cpp          — Application that uses both
#
# Your CMakeLists.txt should:
#   - Create a library "mathlib" from src/calc.cpp and src/stats.cpp
#   - Set include directories PUBLIC (so the app inherits them)
#   - Create an executable "calculator" from app/main.cpp
#   - Link calculator against mathlib
#   - Add compile options: -Wall -Wextra
#
# Build and run:
#   cmake -B build
#   cmake --build build
#   ./build/calculator

# YOUR CMAKE HERE
