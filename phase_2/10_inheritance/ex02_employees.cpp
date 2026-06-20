// Exercise 2: Employee Hierarchy
//
// Task: Model different types of employees with virtual pay calculation.
//
// Define:
//
//   class Employee (abstract base):
//       Employee(const std::string& name, int id);
//       const std::string& name() const;
//       int id() const;
//       virtual double pay() const = 0;         // weekly pay
//       virtual std::string role() const = 0;
//       virtual void print() const;             // default impl
//       virtual ~Employee() = default;
//   protected:
//       std::string name_;
//       int id_;
//
//   class SalariedEmployee : public Employee
//       Constructor: takes name, id, annual_salary
//       pay() returns annual_salary / 52
//       role() returns "Salaried"
//
//   class HourlyEmployee : public Employee
//       Constructor: takes name, id, hourly_rate, hours_worked
//       pay() returns hourly_rate * hours_worked
//         (overtime: hours > 40 are paid at 1.5x)
//       role() returns "Hourly"
//
//   class CommissionEmployee : public Employee
//       Constructor: takes name, id, base_salary, sales, commission_rate
//       pay() returns base_salary/52 + sales * commission_rate
//       role() returns "Commission"
//
//   class Manager : public SalariedEmployee
//       Constructor: takes name, id, annual_salary, bonus
//       pay() returns SalariedEmployee::pay() + bonus
//         (calls the parent's pay() and adds to it)
//       role() returns "Manager"
//
// In main():
//   - Create a vector<Employee*> with one of each type
//   - Print all employees
//   - Calculate total payroll (sum of all pay())
//   - Find highest paid employee
//   - Clean up memory
//
// Compile: g++ -std=c++20 -Wall -Wextra -o ex02 ex02_employees.cpp

// YOUR CODE HERE
