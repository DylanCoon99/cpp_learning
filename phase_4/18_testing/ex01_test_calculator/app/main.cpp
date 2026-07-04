#include "calc.h"
#include "stats.h"
#include <iostream>
#include <vector>

int main() {
    // RPN Calculator demo
    std::cout << "=== RPN Calculator ===\n";
    Calculator calc;

    // Compute (3 + 4) * 2
    calc.push(3);
    calc.push(4);
    calc.add();
    calc.push(2);
    calc.multiply();
    std::cout << "(3 + 4) * 2 = " << calc.peek() << "\n";
    calc.clear();

    // Compute 10 / (5 - 3)
    calc.push(10);
    calc.push(5);
    calc.push(3);
    calc.subtract();
    calc.divide();
    std::cout << "10 / (5 - 3) = " << calc.peek() << "\n";
    calc.clear();

    // Custom operation: power
    calc.push(2);
    calc.push(10);
    calc.apply([](double base, double exp) {
        double result = 1;
        for (int i = 0; i < static_cast<int>(exp); ++i) result *= base;
        return result;
    });
    std::cout << "2 ^ 10 = " << calc.peek() << "\n";

    // Statistics demo
    std::cout << "\n=== Statistics ===\n";
    std::vector<double> data = {23, 45, 12, 67, 34, 89, 56, 78, 9, 41};

    std::cout << "Data: ";
    for (double d : data) std::cout << d << " ";
    std::cout << "\n";

    std::cout << "Sum:    " << stats::sum(data) << "\n";
    std::cout << "Mean:   " << stats::mean(data) << "\n";
    std::cout << "Median: " << stats::median(data) << "\n";
    std::cout << "Stddev: " << stats::stddev(data) << "\n";
    std::cout << "Min:    " << stats::min(data) << "\n";
    std::cout << "Max:    " << stats::max(data) << "\n";
}
