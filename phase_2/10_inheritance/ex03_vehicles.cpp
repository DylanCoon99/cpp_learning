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
#include <iostream>
#include <string>



class Vehicle {

public:
	Vehicle(const std::string& make, const std::string& model, int year) : make_(make), model_(model), year_(year) { }
	
	// virtual methods with no default
	virtual std::string type() const = 0;
	virtual double fuel_efficiency() const = 0;  // miles per gallon (or equivalent)

	virtual void print() const {
		std::cout << "Make: " << make_ << std::endl;
		std::cout << "Model: " << model_ << std::endl;
		std::cout << "Year: " << year_ << std::endl;
	}

	// Destructor
	virtual ~Vehicle() = default;

protected:
	std::string make_, model_;
	int year_;
};


class Car : public Vehicle {

public:
	Car(const std::string& make, const std::string& model, int year, int num_doors) 
		: Vehicle(make, model, year), num_doors_(num_doors) {}

	virtual std::string type() const override {
		return "Car";
	}

	virtual double fuel_efficiency() const override {
		// miles per gallon (or equivalent)
		return 40.0;
	}

protected:
	int num_doors_;

};


class Truck : public Vehicle {
public:
	Truck(const std::string& make, const std::string& model, int year, double payload_capacity) 
		: Vehicle(make, model, year), payload_capacity_(payload_capacity) {}

	virtual std::string type() const override {
		return "Truck";
	}

	double towing_capacity() {
		return payload_capacity_;
	}

	double fuel_efficiency() const override {
		return 20;
	}

protected:
	double payload_capacity_;
};



class ElectricCar : public Car {
public:
	ElectricCar(const std::string& make, const std::string& model, int year, int num_doors, double battery_kwh, double range_miles) 
		: Car(make, model, year, num_doors), battery_kwh_(battery_kwh), range_miles_(range_miles) {}

	virtual std::string type() const override {
		return "Electric Car";
	}

	double fuel_efficiency() const override {
		return range_miles_ / (battery_kwh_ / 33.7);
	}

	double range() const {
		return range_miles_;
	}

protected:
	double battery_kwh_;
	double range_miles_;
};



class Motorcycle : public Vehicle {

public:
	Motorcycle(const std::string& make, const std::string& model, int year, bool has_sidecar) 
		: Vehicle(make, model, year), has_sidecar_(has_sidecar) {}

	virtual std::string type() const override {
		return "Motorcycle";
	}

	double fuel_efficiency() const override{
		return 60;
	}

protected:
	bool has_sidecar_;

};




int main() {

	//   - Create a vector<Vehicle*> with several vehicles
	std::vector<Vehicle*> vehicles;
	vehicles.push_back(new Car("toyota", "corolla", 2020, 2));
	vehicles.push_back(new Truck("ford", "f150", 2020, 1));
	vehicles.push_back(new ElectricCar("tesla", "model s", 2020, 2, 100, 300));
	vehicles.push_back(new Motorcycle("Harley-Davidson", "fat boy", 2020, false));
	//   - Loop and print all
	for (auto& vehicle : vehicles) {
		vehicle->print();
	}
	//   - Use dynamic_cast to find all Trucks and print their towing capacity
	std::cout << "Looking for trucks" << std::endl;
	for (Vehicle* vehicle : vehicles) {
		if (Truck* t = dynamic_cast<Truck*>(vehicle)) {
			std::cout << "towing capacity: " << t->towing_capacity() << std::endl;
		}
	}

	//   - Use dynamic_cast to find all ElectricCars and print their range
	std::cout << "Looking for electric cars" << std::endl;
	for (Vehicle* vehicle : vehicles) {
		if (ElectricCar* e = dynamic_cast<ElectricCar*>(vehicle)) {
			std::cout << "range: " << e->range() << std::endl;
		}
	}
	//   - Find the most fuel-efficient vehicle
	double highest_efficiency = 0.0;
	Vehicle* best_vehicle;
	for (Vehicle* v : vehicles) {
		if (v->fuel_efficiency() > highest_efficiency) {
			highest_efficiency = v->fuel_efficiency();
			best_vehicle = v;
		}
	}

	std::cout << "Best Efficiency Vehicle: ";
	best_vehicle->print();
	//   - Count vehicles by type using dynamic_cast
	int num_cars = 0;
	int num_trucks = 0;
	int num_e_cars = 0;
	int num_motorcycles = 0;

	for (Vehicle* vehicle : vehicles) {
		if (dynamic_cast<ElectricCar*>(vehicle)) {
			++num_e_cars;
		} else if (dynamic_cast<Car*>(vehicle)) {
			++num_cars;
		} else if (dynamic_cast<Truck*>(vehicle)) {
			++num_trucks;
		} else {
			++num_motorcycles;
		}
	}

	std::cout << "Num cars: " << num_cars << std::endl;
	std::cout << "Num trucks: " << num_trucks << std::endl;
	std::cout << "Num electric cars: " << num_e_cars << std::endl;
	std::cout << "Num motorcycle: " << num_motorcycles << std::endl;

	//   - Clean up

	std::cout << "Cleaning up..." << std::endl;
	for (Vehicle* v : vehicles) {
		delete v;
	}
}