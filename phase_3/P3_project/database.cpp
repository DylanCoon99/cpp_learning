// Phase 3 Project: In-Memory Database
//
// Build a generic, query-able in-memory database engine.
// See README.md for full requirements.
//
// Compile: g++ -std=c++20 -Wall -Wextra -o db database.cpp

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <unordered_set>
#include <functional>
#include <algorithm>
#include <numeric>

// YOUR CODE HERE
struct Employee {
    std::string name;
    std::string department;
    double salary;
    int manager_id;  // ID of another Employee, or 0 if none

    friend std::ostream& operator<<(std::ostream& os, const Employee& e) {
    	os << e.name << " | " << e.department << " | $" << e.salary << " | mgr_id: " << e.manager_id;
    	return os;
    }
};

struct Project {
    std::string name;
    std::string status;  // "active", "completed", "on_hold"
    double budget;

    friend std::ostream& operator<<(std::ostream& os, const Project& p) {
    	os << p.name << " | " << p.status << " | $" << p.budget;
    	return os;
    }
};

struct Assignment {
    int employee_id;
    int project_id;
    std::string role;  // "lead", "developer", "tester"

    friend std::ostream& operator<<(std::ostream& os, const Assignment& a) {
    	os << "emp_id: " << a.employee_id << " | proj_id: " << a.project_id << " | " << a.role;
    	return os;
    }
};


template <typename T>
class Table {
public:
	// Insert a record, returns its ID
	int insert(T record) {
		int record_id = next_id_;
		records_[record_id] = record;
		++next_id_;
		return record_id;
	}

	// Remove by ID
	bool remove(int id) {
		records_.erase(id);
	}

	// Get by ID (returns nullptr if not found)
	T* get(int id) {
		if (records_.contains(id)) {
			return records_[id];
		}
		return nullptr;
	}

	const T* get(int id) const {
		if (records_.contains(id)) {
			return &records_.at(id);
		}
		return nullptr;
	}

	// Query — returns all records matching a predicate
	std::vector<const T*> where(std::function<bool(const T&)> predicate) const {
		// can't copy from a map iterator to a vector iterator
		// will have to iterate over map
		std::vector<const T*> result;

		for (auto &[_, record] : records_) {
			if (predicate(record)) {
				result.push_back(&record);
			}
		}

		return result;
	}

	// Get all records
	std::vector<const T*> all() const {
		std::vector<const T*> result;

		for (auto &[_, record] : records_) {
			result.push_back(&record);
		}

		return result;
	}

	// Aggregate operations
	int count() const {
		return records_.size();
	}

	int count_where(std::function<bool(const T&)> predicate) const {
		return std::count_if(records_.begin(), records_.end(), [predicate](const auto& pair) { 
			return predicate(pair.second);
		});
	}

	// Apply a function to all records matching a predicate
	void update_where(std::function<bool(const T&)> predicate, std::function<void(T&)> updater) {
		for (auto &[id, record] : records_) {
			if (predicate(record)) {
				updater(records_[id]);
			}
		}
		
	}

	// Sort records by a comparator, return sorted pointers
	std::vector<const T*> order_by(std::function<bool(const T&, const T&)> comparator) const {
		std::vector records = all();
		std::sort(records.begin(), records.end(), [comparator](const T* a, const T* b) {
			return comparator(*a, *b);
		});
		return records;
	}

	// Return the first N records by comparator
	std::vector<const T*> top_n(int n, std::function<bool(const T&, const T&)> comparator) const {

		std::vector records = all();
	
		std::sort(records.begin(), records.end(), [comparator](const T* a, const T* b) {
			return comparator(*a, *b);
		});

		std::vector<const T*> result(records.begin(), records.begin() + n);
		return result;

	}

	// Print all records (requires T to have operator<<)
	void print_all() const {
		for (auto &[_, record] : records_) {
			std::cout << record << std::endl;
		}
	}

private:
	std::map<int, T> records_;   // ID → record
	int next_id_ = 1;
};


class Database {
public:
    Table<Employee> employees;
    Table<Project> projects;
    Table<Assignment> assignments;

    // Cross-table queries:

    // Find all employees on a specific project
    std::vector<const Employee*> employees_on_project(int project_id) const {
    	// query the Assignment table to get vector of employees
    	std::vector<const Employee*> result;
    	
    	// get the assignments with this project id
    	std::vector<const Assignment*> assignments_with_project_id = assignments.where([project_id](const Assignment& a) {
    		if (a.project_id == project_id) {
    			return true;
    		}
    		return false;
    	});

    	for (auto &assignment : assignments_with_project_id) {
    		result.push_back(employees.get(assignment->employee_id));
    	}

    	return result;

    }

    // Find all projects for a specific employee
    std::vector<const Project*> projects_for_employee(int employee_id) const {
		std::vector<const Project*> result;
    	
    	// get the assignments with this project id
    	std::vector<const Assignment*> assignments_with_employee_id = assignments.where([employee_id](const Assignment& a) {
    		if (a.employee_id == employee_id) {
    			return true;
    		}
    		return false;
    	});

    	for (auto &assignment : assignments_with_employee_id) {
    		result.push_back(projects.get(assignment->project_id));
    	}

    	return result;
    }

    // Find the manager of an employee
    const Employee* manager_of(int employee_id) const {
    	return employees.get(employees.get(employee_id)->manager_id);
    }

    // Find all direct reports of a manager
    std::vector<const Employee*> direct_reports(int manager_id) const {
    	return employees.where([manager_id](const Employee& e) { return e.manager_id == manager_id; });
    }

    // Department summary: name, headcount, total salary, avg salary
    void department_summary() const {
    	// get all employees, collect unique department names, 
    	// then for each department call where and count_where 
    	// with a department-matching lambda.

    	std::unordered_set<std::string> departments;

    	for (auto &employee : employees.all()) {
    		departments.insert(employee->department);
    	}

    	for (const std::string& department : departments) {
    		int head_count = employees.count_where([department](const Employee& e) { return e.department == department; });
    		int total_salary = 0;
    		std::vector<const Employee*> department_employees = employees.where([department](const Employee& e) {
    			return e.department == department;
    		});
    		for (auto& employee : department_employees) {
    			total_salary += employee->salary;
    		} 

    		std::cout << "Department Name: " << department << std::endl;
    		std::cout << "Head Count: " << head_count << std::endl;
    		std::cout << "Total Salary: " << total_salary << std::endl;
    		std::cout << "Avg Salary: " << total_salary / head_count << std::endl;

    	}

    }
};




int main() {
    Database db;

    // Seed data
    int alice = db.employees.insert({"Alice",  "Engineering", 120000, 0});
    int bob   = db.employees.insert({"Bob",    "Engineering", 95000,  alice});
    int carol = db.employees.insert({"Carol",  "Marketing",   88000,  0});
    int dan   = db.employees.insert({"Dan",    "Engineering", 105000, alice});

    int p1 = db.projects.insert({"Project Alpha", "active",    500000});
    int p2 = db.projects.insert({"Project Beta",  "active",    300000});
    int p3 = db.projects.insert({"Project Gamma", "completed", 200000});

    db.assignments.insert({alice, p1, "lead"});
    db.assignments.insert({bob,   p1, "developer"});
    db.assignments.insert({bob,   p2, "developer"});
    db.assignments.insert({dan,   p1, "tester"});
    db.assignments.insert({carol, p2, "lead"});

    // Queries
    std::cout << "=== Engineers earning > 100k ===\n";
    auto high_earners = db.employees.where([](const Employee& e) {
        return e.department == "Engineering" && e.salary > 100000;
    });
    for (auto* e : high_earners) std::cout << *e << "\n";

    std::cout << "\n=== Employees on Project Alpha ===\n";
    for (auto* e : db.employees_on_project(p1)) std::cout << *e << "\n";

    std::cout << "\n=== Alice's direct reports ===\n";
    for (auto* e : db.direct_reports(alice)) std::cout << *e << "\n";

    std::cout << "\n=== Top 3 earners ===\n";
    auto top3 = db.employees.top_n(3, [](const Employee& a, const Employee& b) {
        return a.salary > b.salary;
    });
    for (auto* e : top3) std::cout << *e << "\n";

    std::cout << "\n=== Department Summary ===\n";
    db.department_summary();

    // Bulk update
    db.employees.update_where(
        [](const Employee& e) { return e.department == "Marketing"; },
        [](Employee& e) { e.salary *= 1.10; }
    );

    std::cout << "\n=== After Marketing raise ===\n";
    db.employees.print_all();
}