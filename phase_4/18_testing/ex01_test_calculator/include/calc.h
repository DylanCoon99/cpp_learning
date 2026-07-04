#pragma once

#include <vector>
#include <functional>
#include <stdexcept>

class Calculator {
public:
    void push(double value);
    double pop();
    double peek() const;
    int size() const;
    bool empty() const;
    void clear();

    // Operations — operate on top two values, push result
    void add();
    void subtract();
    void multiply();
    void divide();

    // Apply arbitrary operation to top two values
    void apply(std::function<double(double, double)> op);

    // Print stack contents
    void print_stack() const;

private:
    std::vector<double> stack_;
};
