#include "calc.h"
#include <iostream>
#include <stdexcept>

void Calculator::push(double value) {
    stack_.push_back(value);
}

double Calculator::pop() {
    if (stack_.empty()) throw std::underflow_error("Stack is empty");
    double val = stack_.back();
    stack_.pop_back();
    return val;
}

double Calculator::peek() const {
    if (stack_.empty()) throw std::underflow_error("Stack is empty");
    return stack_.back();
}

int Calculator::size() const {
    return stack_.size();
}

bool Calculator::empty() const {
    return stack_.empty();
}

void Calculator::clear() {
    stack_.clear();
}

void Calculator::add() {
    double b = pop(), a = pop();
    push(a + b);
}

void Calculator::subtract() {
    double b = pop(), a = pop();
    push(a - b);
}

void Calculator::multiply() {
    double b = pop(), a = pop();
    push(a * b);
}

void Calculator::divide() {
    double b = pop(), a = pop();
    if (b == 0) throw std::invalid_argument("Division by zero");
    push(a / b);
}

void Calculator::apply(std::function<double(double, double)> op) {
    double b = pop(), a = pop();
    push(op(a, b));
}

void Calculator::print_stack() const {
    for (double val : stack_) {
        std::cout << val << " ";
    }
    std::cout << "\n";
}
