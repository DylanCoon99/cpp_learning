// Exercise 1: unique_ptr Fundamentals
//
// Task: Practice creating, using, transferring, and observing unique_ptr.
//
// Part A — Basic usage:
//   - Create a unique_ptr<int> using make_unique, set its value, print it
//   - Create a unique_ptr<std::string>, call string methods through ->
//   - Let both go out of scope in a block {} and verify cleanup
//     (add a wrapper class with a destructor that prints to prove it)
//
// Part B — Ownership transfer:
//   Define a class:
//     class Sensor {
//     public:
//         Sensor(std::string name) : name_(name) {
//             std::cout << "Sensor " << name_ << " created\n";
//         }
//         ~Sensor() { std::cout << "Sensor " << name_ << " destroyed\n"; }
//         void read() const { std::cout << name_ << ": " << rand() % 100 << "\n"; }
//         const std::string& name() const { return name_; }
//     private:
//         std::string name_;
//     };
//
//   Write these functions:
//     std::unique_ptr<Sensor> create_sensor(const std::string& name)
//       — creates and returns a unique_ptr (demonstrates return-by-move)
//
//     void install_sensor(std::unique_ptr<Sensor> sensor)
//       — takes ownership, uses the sensor, sensor is destroyed at end
//
//     void inspect_sensor(const Sensor& sensor)
//       — borrows the sensor (no ownership change), calls read()
//
//   In main():
//     - Create a sensor with create_sensor
//     - Borrow it with inspect_sensor(*sensor)
//     - Transfer it with install_sensor(std::move(sensor))
//     - Verify sensor is nullptr after the move
//
// Part C — unique_ptr with arrays:
//   - Create a unique_ptr<int[]> of size 10 using make_unique<int[]>(10)
//   - Fill it with squares: arr[i] = (i+1)*(i+1)
//   - Print all elements
//   - No delete needed — it's automatic
//
// Compile: g++ -std=c++20 -Wall -Wextra -o ex01 ex01_unique_basics.cpp

// YOUR CODE HERE
