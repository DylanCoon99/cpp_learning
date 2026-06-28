// Exercise 4: Task Queue System
//
// Task: Build a task management system using queue, stack, and priority_queue.
//
// Define:
//   enum class Priority { Low = 1, Medium = 2, High = 3, Critical = 4 };
//
//   struct Task {
//       int id;
//       std::string description;
//       Priority priority;
//       bool operator<(const Task& other) const {
//           return priority < other.priority;  // for priority_queue
//       }
//   };
//
// Part A — FIFO task queue:
//   Use std::queue<Task>
//   - Enqueue 5 tasks
//   - Process them in order (dequeue and print)
//   - Demonstrate FIFO: first in, first out
//
// Part B — Undo stack:
//   Use std::stack<std::string> to track completed task descriptions
//   - As each task is processed, push its description onto the undo stack
//   - Implement "undo" by popping from the stack
//   - Demonstrate: process 3 tasks, undo 1, process 2 more
//
// Part C — Priority task queue:
//   Use std::priority_queue<Task>
//   - Enqueue tasks with different priorities
//   - Process them — highest priority should come out first
//   - Demonstrate that Critical tasks are processed before Low tasks
//     regardless of insertion order
//
// Part D — Complete task system:
//   Combine all three:
//   - New tasks go into the priority queue
//   - When processed, they move to a "completed" stack (for undo)
//   - Maintain a std::map<int, Task> as a lookup by ID
//   - Menu:
//       1. Add task
//       2. Process next task (highest priority)
//       3. Undo last completed task (moves back to queue)
//       4. View pending tasks (priority order)
//       5. View completed tasks
//       6. Look up task by ID
//       7. Quit
//
// Compile: g++ -std=c++20 -Wall -Wextra -o ex04 ex04_task_queue.cpp

// YOUR CODE HERE
#include <string>
#include <queue>
#include <iostream>


enum class Priority { Low = 1, Medium = 2, High = 3, Critical = 4 };

struct Task {
	int id;
	std::string description;
	Priority priority;
	bool operator<(const Task& other) const {
		return priority < other.priority;  // for priority_queue
	}
};


std::string priority_to_string(const Priority &priority) {
	
	std::string priority_str;

	switch (priority) {
	case Priority::Low:
		priority_str = "Low"; break;
	case Priority::Medium:
		priority_str = "Medium"; break;
	case Priority::High:
		priority_str = "High"; break;
	case Priority::Critical:
		priority_str = "Critical"; break;
	}

	return priority_str;
}


void print_task(const Task& task) {
	

	std::cout << "Id: " << task.id << std::endl;
	std::cout << "Desc: " << task.description << std::endl;
	std::cout << "Priority: " << priority_to_string(task.priority) << std::endl;
	std::cout << std::endl;
}


Priority string_to_priority(const std::string& str) {

	if (str == "Low") {
		return Priority::Low;
	} else if (str == "Medium") {
		return Priority::Medium;
	} else if (str == "High") {
		return Priority::High;
	} else if (str == "Critical") {
		return Priority::Critical;
	}

	// default to low
	return Priority::Low;
}


int main() {

	{
		// Part A — FIFO task queue:
		std::queue<Task> tasks;
		tasks.push({1, "Fix login bug",       Priority::High});
		tasks.push({2, "Update README",       Priority::Low});
		tasks.push({3, "Deploy to staging",   Priority::Critical});
		tasks.push({4, "Review pull request", Priority::Medium});

		while (!tasks.empty()) {
			Task task = tasks.front();
			tasks.pop();
			print_task(task);
		}
	}

	// Part D — Complete Task System
	std::priority_queue<Task> tasks;
	std::stack<Task> stack;


	bool quit = false;
	int cmd;

	std::cout << R"(
	1. Add task
	2. Process next task (highest priority)
	3. Undo last completed task (moves back to queue)
	4. View pending tasks (priority order)
	5. View completed tasks
	6. Look up task by ID
	7. Quit)" << std::endl;

	while (!quit) {

		std::cout << "Enter a cmd: ";
		std::cin >> cmd;

		switch (cmd) {
		case 1:
			{
				int id;
				std::string desc;
				std::string priority;

				std::cout << "Enter an id: ";
				std::cin >> id;
				std::cout << "Enter a desc: ";
				std::cin >> desc;
				std::cout << "Enter a priority: ";
				std::cin >> priority;

				Task task = Task{id, desc, string_to_priority(priority)};
				tasks.push(task);
			}
			break;
		case 2:
			// 2. Process next task (highest priority)
			{
				Task task = tasks.top();
				tasks.pop();
				stack.push(task);
			}
			break;
		case 3:
			// 3. Undo last completed task (moves back to queue) 
			{
				Task task = stack.top();
				std::cout << "Adding task: " << task.description << " back to the queue." << std::endl;
				stack.pop();
				tasks.push(task);
			}
			break;
		case 4:
			// 4. View pending tasks (priority order)
			{
				auto copy = tasks;  // copy the whole queue
				while (!copy.empty()) {
					print_task(copy.top());
					copy.pop();
				}
			}
			break;
		case 5:
			// 5. View completed tasks
			{
				auto copy = stack;
				while (!copy.empty()) {
					print_task(copy.top());
					copy.pop();
				}
			}
			break;
		case 6:
			// 6. Look up task by ID
			{
				int id;
				std::cout << "Enter an id: ";
				std::cin >> id;
				bool found = false;

				// pop through the queue
				auto copy = tasks;  // copy the whole queue
				while (!copy.empty() && !found) {
					if (copy.top().id == id) {
						std::cout << "Found (Status: pending) " << std::endl;
						print_task(copy.top());
						found = true;
					} else {
						print_task(copy.top());
						copy.pop();
					}
				}

				// if not found -> pop through the stack
				if (!found) {
					auto copy_stack = stack;
					while (!copy_stack.empty()) {
						if (copy.top().id == id) {
							std::cout << "Found (Status: completed) " << std::endl;
							print_task(copy.top());
							found = true;
						} else {
							print_task(copy.top());
							copy.pop();
						}
					}
				}
			}
			break;
		case 7:
			// Quit
			quit = true;
		}

	}


}