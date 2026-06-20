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
#include <iostream>
#include <vector>



class Employee {
public:
	Employee(const std::string& name, int id) : name_(name), id_(id) {}

	const std::string& name() const {
		return name_;
	}

	int id() {
		return id_;
	}

	// virtual methods with no default implementation
	virtual double pay() const = 0;
	virtual std::string role() const = 0;

	virtual void print() const {
		// default impl
		std::cout << "ID: " << id_ << std::endl;
		std::cout << "Name: " << name_ << std::endl;
	}
	
	// Destructor
	virtual ~Employee() = default;

protected:
	std::string name_;
	int id_;
};


class SalariedEmployee : public Employee {

public:
	SalariedEmployee(std::string name, int id, double salary) : Employee(name, id), salary_(salary) {} 

	double pay() const override {
		return salary_ / 52;
	}

	std::string role() const override {
		return "Salaried";
	}

protected:
	double salary_;

};


class HourlyEmployee : public Employee {

public:
	HourlyEmployee(std::string name, int id, double hourly_rate, int hours_worked) 
		: Employee(name, id), hourly_rate_(hourly_rate), hours_worked_(hours_worked) {} 

	double pay() const override {
		return (hours_worked_ < 40) ? (hours_worked_ * hourly_rate_) : (40 * hourly_rate_) + ((hours_worked_ - 40) * 1.5 * hourly_rate_);
	}

	std::string role() const override {
		return "Hourly";
	}

private:
	double hourly_rate_;
	int hours_worked_;

};



class CommissionEmployee : public SalariedEmployee {

public:
	CommissionEmployee(std::string name, int id, double base_salary, double sales, double commission_rate) 
		: SalariedEmployee(name, id, base_salary), sales_(sales), commission_rate_(commission_rate) {} 

	double pay() const override {
		return salary_/52 + sales_ * commission_rate_;
	}

	std::string role() const override {
		return "Commission";
	}

private:
	double sales_;
	double commission_rate_;

};



class Manager : public SalariedEmployee {

public:
	Manager(std::string name, int id, double salary, double bonus) 
		: SalariedEmployee(name, id, salary), bonus_(bonus) {}

	double pay() const override {
		return SalariedEmployee::pay() + bonus_;
	}

	std::string role() const override {
		return "Manager";
	}


private:
	double bonus_;
};




int main() {
	SalariedEmployee sal("Alice", 101, 80000);
	HourlyEmployee hr("Bob", 102, 25.0, 45);
	CommissionEmployee com("Carol", 103, 50000, 120000, 0.05);
	Manager mgr("Dan", 104, 120000, 500);

	std::vector<Employee*> employees = {&sal, &hr, &com, &mgr};

	// Print all employees
	for (auto* e : employees) {
		e->print();
		std::cout << "Role: " << e->role() << std::endl;
		std::cout << "Weekly Pay: $" << e->pay() << std::endl;
		std::cout << "---" << std::endl;
	}

	// Total payroll
	double total = 0;
	for (auto* e : employees) {
		total += e->pay();
	}
	std::cout << "Total weekly payroll: $" << total << std::endl;

	// Highest paid
	Employee* highest = employees[0];
	for (auto* e : employees) {
		if (e->pay() > highest->pay()) {
			highest = e;
		}
	}
	std::cout << "Highest paid: " << highest->name()
	          << " ($" << highest->pay() << "/week)" << std::endl;

}
