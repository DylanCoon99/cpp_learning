#include "task.h"
#include <iostream>

int main() {
    TaskList tasks;

    int t1 = tasks.add("Set up CMake project");
    int t2 = tasks.add("Split into header and source");
    int t3 = tasks.add("Link library to executable");
    tasks.add("Run and verify");

    std::cout << "=== All Tasks ===\n";
    tasks.print_all();

    tasks.complete(t1);
    tasks.complete(t2);

    std::cout << "\n=== After completing first two ===\n";
    tasks.print_all();

    std::cout << "\nPending: " << tasks.pending().size() << "\n";
    std::cout << "Completed: " << tasks.completed().size() << "\n";

    tasks.remove(t3);
    std::cout << "\n=== After removing task #" << t3 << " ===\n";
    tasks.print_all();
}
