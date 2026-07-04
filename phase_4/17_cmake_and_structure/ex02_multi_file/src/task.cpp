// Exercise 2: Implement TaskList methods
//
// #include the header and implement each method declared in task.h.
// Remember: method definitions use ClassName::method_name syntax.
//
// Example:
//   int TaskList::add(const std::string& description) {
//       tasks_.push_back({next_id_, description, false});
//       return next_id_++;
//   }

// YOUR CODE HERE
#include "task.h"
#include <algorithm>


int TaskList::add(const std::string& description) {
	tasks_.push_back({next_id_, description, false});
	return next_id_++;
}


bool TaskList::complete(int id) {
	auto it = std::find_if(tasks_.begin(), tasks_.end(), [id](const Task& task) { return task.id == id; });
	if (it != tasks_.end()) {
		return (*it).done;
	}
	return false;
}

bool TaskList::remove(int id) {
	return std::erase_if(tasks_, [id](const Task& task) { return task.id == id;});
}

std::vector<Task> TaskList::pending() const {
	
	std::vector<Task> result;

	std::copy_if(tasks_.begin(), tasks_.end(), std::back_inserter(result), [](const Task& task) {
		return !task.done;
	});
	return result;
}


std::vector<Task> TaskList::completed() const {
	std::vector<Task> result;

	std::copy_if(tasks_.begin(), tasks_.end(), std::back_inserter(result), [](const Task& task) {
		return task.done;
	});
	return result;
}


void TaskList::print_all() const {
	for (const Task& task : tasks_) std::cout << task << std::endl;
}


int TaskList::count() const {
	return tasks_.size();
}