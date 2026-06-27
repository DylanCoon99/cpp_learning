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
