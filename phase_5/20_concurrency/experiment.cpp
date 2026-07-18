// Step 20 experiment

#include <thread>
#include <iostream>
#include <mutex>
// g++ -std=c++20 -Wall -Wextra -o experiment experiment.cpp


std::atomic<int> counter{0};
//std::mutex mtx;

void increment() {
    for (int i = 0; i < 100000; ++i) {
    	//std::unique_lock<std::mutex> lock(mtx); // lock_guard mutex prevents deadlock when errors are thrown before unlock
        ++counter;
    }
}


int main() {

	std::thread t1(increment);
	std::thread t2(increment);
	t1.join(); t2.join();

	std::cout << "counter: " << counter << std::endl;

}