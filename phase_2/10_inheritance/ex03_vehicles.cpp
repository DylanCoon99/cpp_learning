// Exercise 3: Vehicle Hierarchy with dynamic_cast
//
// Task: Build a vehicle hierarchy and use dynamic_cast to handle
//       type-specific behavior.
//
// Define:
//
//   class Vehicle (abstract base):
//       Vehicle(const std::string& make, const std::string& model, int year);
//       virtual std::string type() const = 0;
//       virtual double fuel_efficiency() const = 0;  // miles per gallon (or equivalent)
//       virtual void print() const;
//       virtual ~Vehicle() = default;
//   protected:
//       std::string make_, model_;
//       int year_;
//
//   class Car : public Vehicle
//       Additional: int num_doors_
//       fuel_efficiency() returns some value based on made-up data
//
//   class Truck : public Vehicle
//       Additional: double payload_capacity_ (tons)
//       double towing_capacity() const;
//       fuel_efficiency() returns a lower value (trucks are less efficient)
//
//   class ElectricCar : public Car
//       Additional: double battery_kwh_, double range_miles_
//       fuel_efficiency() override — return range_miles_ / (battery_kwh_ / 33.7)
//         (33.7 kWh ≈ 1 gallon of gas, for MPGe calculation)
//       double range() const;
//
//   class Motorcycle : public Vehicle
//       Additional: bool has_sidecar_
//       fuel_efficiency() returns a high value
//
// In main():
//   - Create a vector<Vehicle*> with several vehicles
//   - Loop and print all
//   - Use dynamic_cast to find all Trucks and print their towing capacity
//   - Use dynamic_cast to find all ElectricCars and print their range
//   - Find the most fuel-efficient vehicle
//   - Count vehicles by type using dynamic_cast
//   - Clean up
//
// This exercise demonstrates when dynamic_cast is useful: handling
// type-specific features that don't belong in the base interface.
//
// Compile: g++ -std=c++20 -Wall -Wextra -o ex03 ex03_vehicles.cpp

// YOUR CODE HERE
