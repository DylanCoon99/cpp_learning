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
#include <string>
#include <iostream>


enum class Light { Red, Yellow, Green };
enum class Mode : uint8_t { Normal, Flashing, Off };






std::string light_to_string(Light l) {
	switch (l) {
	case Light::Red:
		return "Red";
	case Light::Yellow:
		return "Yellow";
	case Light::Green:
		return "Green";
	}
}

std::string mode_to_string(Mode l) {
	switch (l) {
	case Mode::Normal:
		return "Normal";
	case Mode::Flashing:
		return "Flashing";
	case Mode::Off:
		return "Off";
	}
}


Light next_light(Light l) {

	switch (l) {
	case Light::Red:
		return Light::Green;
	case Light::Yellow:
		return Light::Red;
	case Light::Green:
		return Light::Yellow;
	}
}


int duration(Light l) {
	switch (l) {
	case Light::Red:
		return 30;
	case Light::Yellow:
		return 5;
	case Light::Green:
		return 25;
	}
}


void behavior(Light l, Mode m) {
	std::string light = light_to_string(l);
	std::string mode = mode_to_string(m);

	std::cout << mode << " + " << light << std::endl;

}



int main() {


	Light l = Light::Red;
	int time = 0;

	for (int i = 0; i < 5; ++i) {
		std::cout << light_to_string(l) << std::endl;
		time += duration(l);
		l = next_light(l);
	}

	std::cout << "Total Elapsed Time: " << time << std::endl;



}