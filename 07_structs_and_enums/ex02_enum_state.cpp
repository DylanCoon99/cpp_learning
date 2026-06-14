// Exercise 2: State Machine with Scoped Enums
//
// Task: Model a traffic light as a state machine using enum class.
//
// Define:
//   enum class Light { Red, Yellow, Green };
//
// Write these functions:
//
//   std::string light_to_string(Light l)
//     — Return the name as a string ("Red", "Yellow", "Green")
//     — Use a switch statement
//
//   Light next_light(Light l)
//     — Return the next state: Red -> Green -> Yellow -> Red
//
//   int duration(Light l)
//     — Return how long each light lasts in seconds:
//       Red=30, Yellow=5, Green=25
//
// In main():
//   - Start at Red
//   - Simulate 5 full cycles, printing each state and its duration
//   - Track total elapsed time
//   - Print the total time at the end
//
// Bonus: Add a second enum:
//   enum class Mode : uint8_t { Normal, Flashing, Off };
//   Write a function that takes both a Light and a Mode and prints
//   the behavior (e.g., Flashing + Yellow = "caution")
//
// Compile: g++ -std=c++20 -Wall -Wextra -o ex02 ex02_enum_state.cpp

// YOUR CODE HERE
