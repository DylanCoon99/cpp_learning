#pragma once

#include <string>
#include <vector>
#include <iostream>

struct Task {
    int id;
    std::string description;
    bool done;

    friend std::ostream& operator<<(std::ostream& os, const Task& t) {
        os << "[" << (t.done ? "X" : " ") << "] #" << t.id << ": " << t.description;
        return os;
    }
};

class TaskList {
public:
    int add(const std::string& description);
    bool complete(int id);
    bool remove(int id);
    std::vector<Task> pending() const;
    std::vector<Task> completed() const;
    void print_all() const;
    int count() const;

private:
    std::vector<Task> tasks_;
    int next_id_ = 1;
};
