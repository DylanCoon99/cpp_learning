// Exercise 1: Lambda Fundamentals
//
// Task: Explore captures, mutable, closures, and std::function.
//
// Part A — Capture modes:
//   - Create variables: int x = 10, y = 20, z = 30
//   - Write a lambda that captures x by value and y by reference
//   - Call it, modify y outside, call again — observe the difference
//   - Write a lambda with [=] that uses all three
//   - Write a lambda with [&] that modifies all three
//
// Part B — mutable and closures:
//   Write a function that returns a counter lambda:
//     std::function<int()> make_counter(int start = 0);
//   Each call to the returned lambda returns the next number:
//     auto c = make_counter(10);
//     c(); // 10
//     c(); // 11
//     c(); // 12
//
//   Write a function that returns an accumulator:
//     std::function<int(int)> make_accumulator();
//   Each call adds to a running total:
//     auto acc = make_accumulator();
//     acc(5);  // 5
//     acc(3);  // 8
//     acc(10); // 18
//
// Part C — std::function storage:
//   Create a std::vector<std::function<int(int)>> of transformations:
//     - double the value
//     - square the value
//     - add 10
//     - negate
//   Apply each transformation to the number 5 and print results.
//   Then chain them: apply all transformations in sequence to a starting value.
//
// Part D — Generic lambdas:
//   Write a generic lambda:
//     auto print_twice = [](const auto& x) { ... };
//   That prints any value twice on one line separated by a space.
//   Test with int, double, string, vector (you'll need to handle vector
//   specially — or just let it fail and observe the error).
//
// Compile: g++ -std=c++20 -Wall -Wextra -o ex01 ex01_lambda_fundamentals.cpp

#include <iostream>
#include <functional>
#include <vector>
#include <string>
#include <functional>


std::function<int()> make_counter(int start) {                                                                                                                                     
    return [start]() mutable { return start++; };                                                                                                                                  
}   


std::function<int(int)> make_accumulator() {
    int start = 0;
    return [start](int a) mutable { 
        return start += a;
    }; 
}

int main() {
    // YOUR CODE HERE

    // Part A — Capture modes:
    int x = 10, y = 20, z = 30;

    //   - Write a lambda that captures x by value and y by reference
    auto lambda1 = [x, &y](int a) { 
        // return x * a + y
        return x * a + y; 
    };
    //   - Call it, modify y outside, call again — observe the difference
    std::cout << "lambda1(1): " << lambda1(2) << std::endl;
    y = 15;
    std::cout << "lambda1(1): " << lambda1(2) << std::endl;
    x = 15;  // modifying x outside the lambda should have no effect because x was captured by value
    std::cout << "lambda1(1): " << lambda1(2) << std::endl;    
    //   - Write a lambda with [=] that uses all three
    x = 10, y = 20, z = 30;
    auto lambda2 = [=](int a) { 
        // return x * a + y
        return x * a + y; 
    };
    std::cout << "lambda2(1): " << lambda2(2) << std::endl;    
    //   - Write a lambda with [&] that modifies all three
    auto lambda3 = [&](int a) { 
        // return x * a + y
        return x * a + y; 
    };
    std::cout << "lambda3(1): " << lambda3(2) << std::endl;    


    // Part B — mutable and closures:
    //   Write a function that returns a counter lambda:
    //     std::function<int()> make_counter(int start = 0);
    //   Each call to the returned lambda returns the next number:
    //     auto c = make_counter(10);
    //     c(); // 10
    //     c(); // 11
    //     c(); // 12

    
    std::function<int(int, int)> op;

    op = [](int a, int b) { return a + b; };

    auto c = make_counter(10);

    std::cout << "c(): " << c() << std::endl;
    std::cout << "c(): " << c() << std::endl;
    std::cout << "c(): " << c() << std::endl;

    //   Write a function that returns an accumulator:
    //     std::function<int(int)> make_accumulator();
    //   Each call adds to a running total:
    //     auto acc = make_accumulator();
    //     acc(5);  // 5
    //     acc(3);  // 8
    //     acc(10); // 18
    auto a = make_accumulator();
    std::cout << "a(): " << a(5) << std::endl;
    std::cout << "a(): " << a(3) << std::endl;
    std::cout << "a(): " << a(10) << std::endl;


    // Part C — std::function storage:
    //   Create a std::vector<std::function<int(int)>> of transformations:
    //     - double the value
    //     - square the value
    //     - add 10
    //     - negate
    //   Apply each transformation to the number 5 and print results.
    //   Then chain them: apply all transformations in sequence to a starting value.
    std::vector<std::function<int(int)>> transformations;

    auto times_two = [](int a) { return 2 * a;};
    auto square = [](int a) { return a * a;};
    auto add_ten = [](int a) { return a + 10;};
    auto negate = [](int a) { return a * -1; };

    transformations.push_back(times_two);
    transformations.push_back(square);
    transformations.push_back(add_ten);
    transformations.push_back(negate);

    // times_two
    std::cout << times_two(5) << std::endl;
    // square
    std::cout << square(5) << std::endl;
    // add_ten
    std::cout << add_ten(5) << std::endl;
    // negate
    std::cout << negate(5) << std::endl;

    // chain them together
    std::cout << negate(add_ten(square(times_two(5)))) << std::endl;

    // Part D — Generic lambdas:
    //   Write a generic lambda:
    //     auto print_twice = [](const auto& x) { ... };
    //   That prints any value twice on one line separated by a space.
    //   Test with int, double, string, vector (you'll need to handle vector
    //   specially — or just let it fail and observe the error).

    auto print_twice = [](const auto& x) {
        std::cout << x << std::endl;
        std::cout << x << std::endl;
        std::cout << std::endl;
    };

    print_twice(5);
    print_twice(6.9);
    print_twice("this is my string");




}
