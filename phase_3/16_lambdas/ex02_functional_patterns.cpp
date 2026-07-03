// Exercise 2: Functional Patterns — Callbacks and Event System
//
// Task: Build a simple event system using lambdas and std::function.
//       This is a practical use case you'd see in GUI frameworks, game
//       engines, and async systems.
//
// Build this event system:
//
//   class EventEmitter {
//   public:
//       // Register a callback for a named event
//       void on(const std::string& event, std::function<void()> callback);
//
//       // Register a callback that receives a string argument
//       void on(const std::string& event, std::function<void(const std::string&)> callback);
//
//       // Trigger all callbacks for an event
//       void emit(const std::string& event);
//       void emit(const std::string& event, const std::string& data);
//
//       // Remove all callbacks for an event
//       void off(const std::string& event);
//
//       // Register a callback that fires only once, then auto-removes
//       void once(const std::string& event, std::function<void()> callback);
//
//   private:
//       std::map<std::string, std::vector<std::function<void()>>> handlers_;
//       std::map<std::string, std::vector<std::function<void(const std::string&)>>> data_handlers_;
//   };
//
// Test scenario:
//
//   EventEmitter emitter;
//
//   // Register handlers
//   emitter.on("login", []() { std::cout << "User logged in\n"; });
//
//   int login_count = 0;
//   emitter.on("login", [&login_count]() {
//       ++login_count;
//       std::cout << "Login count: " << login_count << "\n";
//   });
//
//   emitter.on("message", [](const std::string& msg) {
//       std::cout << "Received: " << msg << "\n";
//   });
//
//   emitter.once("startup", []() { std::cout << "Starting up...\n"; });
//
//   // Trigger events
//   emitter.emit("login");          // both login handlers fire
//   emitter.emit("login");          // both fire again
//   emitter.emit("message", "hello world");
//   emitter.emit("startup");        // fires
//   emitter.emit("startup");        // does NOT fire (once)
//
//   emitter.off("login");
//   emitter.emit("login");          // nothing fires
//
// Compile: g++ -std=c++20 -Wall -Wextra -o ex02 ex02_functional_patterns.cpp

#include <iostream>
#include <functional>
#include <vector>
#include <string>
#include <map>

// YOUR CODE HERE

int main() {

    // YOUR CODE HERE

}
