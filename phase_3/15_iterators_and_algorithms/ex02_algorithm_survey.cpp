// Exercise 2: STL Algorithm Survey
//
// Task: Apply at least 15 different STL algorithms to practice the
//       breadth of <algorithm> and <numeric>.
//
// Start with this data:
//   std::vector<int> data = {7, 2, 9, 4, 1, 8, 3, 6, 5, 2, 8, 1, 7, 3};
//
// Apply each algorithm, print the result, and add a brief comment:
//
//   1.  std::sort           — sort ascending
//   2.  std::reverse        — reverse the sorted vector
//   3.  std::find           — find value 8
//   4.  std::find_if        — find first value > 6
//   5.  std::count          — count how many 2s
//   6.  std::count_if       — count even numbers
//   7.  std::min_element    — find minimum
//   8.  std::max_element    — find maximum
//   9.  std::accumulate     — sum all elements (from <numeric>)
//   10. std::transform      — create a new vector with each element squared
//   11. std::replace        — replace all 1s with 100
//   12. std::remove + erase — remove all 3s (erase-remove idiom)
//   13. std::unique + erase — remove consecutive duplicates (sort first)
//   14. std::copy_if        — copy only odd numbers to a new vector
//   15. std::all_of         — check if all elements are positive
//   16. std::any_of         — check if any element is > 50
//   17. std::none_of        — check if no element is negative
//   18. std::fill           — fill a vector of size 5 with 42
//   19. std::iota           — fill with 1, 2, 3, 4, 5 (from <numeric>)
//   20. std::partial_sum    — running sum (from <numeric>)
//
// For each, print what the algorithm did and the resulting data.
//
// Reset data back to the original between operations if needed
// (or just use fresh copies).
//
// Compile: g++ -std=c++20 -Wall -Wextra -o ex02 ex02_algorithm_survey.cpp

// YOUR CODE HERE
#include <numeric>
#include <random>
#include <vector>
#include <algorithm>
#include <iostream>
#include <sys/types.h>


int main() {

	std::mt19937 gen(42);  // fixed seed for reproducibility
	std::uniform_int_distribution<int> dist(1, 1000000);

	std::vector<uint> v;

	for (int i = 0; i < 25; ++i) {
		v.push_back(dist(gen));
	}

	//   1.  std::sort           — sort ascending
	std::sort(v.begin(), v.end());
	std::cout << "Sorted: ";
	for (auto &e : v) {
		std::cout << e << std::endl;
	}
	std::cout << std::endl;
	//   2.  std::reverse        — reverse the sorted vector
	std::reverse(v.begin(), v.end());
	std::cout << "Reversed: ";
	for (auto &e : v) {
		std::cout << e << std::endl;
	}
	std::cout << std::endl;
	//   3.  std::find           — find value 8
	auto it = std::find(v.begin(), v.end(), 5);
	if (it != v.end()) {
		std::cout << "found at index " << (it - v.begin()) << std::endl;;
	} else {
		std::cout << "didn't find the value" << std::endl;;
	}
	//   4.  std::find_if        — find first value > 6
	auto it2 = std::find_if(v.begin(), v.end(), [](uint x) { return x > 100; });
	std::cout << "found first value > 100 " << *it2 << std::endl;;
	//   5.  std::count          — count how many 2s
	std::cout << "There are " << std::count(v.begin(), v.end(), 100) << " 100s in v" << std::endl;
	//   6.  std::count_if       — count even numbers
	std::cout << "Count of even nums: " << std::count_if(v.begin(), v.end(), [](uint x) { return x % 2 == 0; }) << std::endl;
	//   7.  std::min_element    — find minimum
	std::cout << "Min: " << *std::min_element(v.begin(), v.end()) << std::endl;
	//   8.  std::max_element    — find maximum
	std::cout << "Max: " << *std::max_element(v.begin(), v.end()) << std::endl;
	//   9.  std::accumulate     — sum all elements (from <numeric>)
	std::cout << "Sum: " << std::accumulate(v.begin(), v.end(), 0) << std::endl;
	//   10. std::transform      — create a new vector with each element squared
	std::vector<uint> result(v.size());
	std::transform(v.begin(), v.end(), result.begin(), [](uint x) {return x * x;});
	std::cout << "Squared: ";
	for (auto &e : result) {
		std::cout << e << std::endl;
	}
	std::cout << std::endl;
	//   11. std::replace        — replace all 1s with 100
	std::vector<int> m = {1, 2, 1, 3, 4, 5, 1, 1, 5, 1};
	std::replace(m.begin(), m.end(), 1, 100);
	for (auto &e : m) {
		std::cout << e << std::endl;
	}
	std::cout << std::endl;
	//   12. std::remove + erase — remove all 3s (erase-remove idiom)
	std::vector<int> threes_vector = {1, 2, 3, 4, 5, 3, 2, 3, 5, 6};
	auto new_end = std::remove(threes_vector.begin(), threes_vector.end(), 3);
	threes_vector.erase(new_end, threes_vector.end());
	for (auto &e : threes_vector) {
		std::cout << e << std::endl;
	}
	//   13. std::unique + erase — remove consecutive duplicates (sort first)
	std::vector<int> u = {3, 1, 2, 3, 1, 2, 2};
	std::sort(u.begin(), u.end());
 	auto last = std::unique(u.begin(), u.end());
 	u.erase(last, u.end());
 	for (auto &e : u) {
		std::cout << e << std::endl;
	}
	//   14. std::copy_if        — copy only odd numbers to a new vector
	
	std::vector<int> copy_vector;
	std::copy_if(m.begin(), m.end(), std::back_inserter(copy_vector), [](int i ) {return i % 2 != 0;});
	for (auto &e : copy_vector) {
		std::cout << e << std::endl;
	}
	

	std::cout << std::endl;
	//   15. std::all_of         — check if all elements are positive
	std::vector<int> nums = {1, 2, 3, 51, 34};
	if (std::all_of(nums.begin(), nums.end(), [](int i){return i>0;})){
		std::cout << "All nums are positive." << std::endl;
	}
	//   16. std::any_of         — check if any element is > 50
	if (std::any_of(nums.begin(), nums.end(), [](int i){return i>50;})){
		std::cout << "There are nums greater than 50 in nums." << std::endl;
	}
	//   17. std::none_of        — check if no element is negative
	std::vector<int> pos_nums = {1, 2, 4, 5, 6};
	std::vector<int> neg_nums = {-1, -2, -4, -5, -6};
	if (std::none_of(pos_nums.begin(), pos_nums.end(), [](int i){return i<0;})){
		std::cout << "There are no negative nums in pos_nums" << std::endl;
	}
	if (!std::none_of(neg_nums.begin(), neg_nums.end(), [](int i){return i<0;})){
		std::cout << "There are negative nums in neg_nums" << std::endl;
	} 
	
	//   18. std::fill           — fill a vector of size 5 with 42
	std::vector<int> fill_vector = {0, 1, 2, 3, 4};
	std::fill(fill_vector.begin(), fill_vector.end(), 42);
	for (auto &e : fill_vector) {
		std::cout << e << std::endl;
	}
	std::cout << std::endl;
	//   19. std::iota           — fill with 1, 2, 3, 4, 5 (from <numeric>)
	std::vector<int> iota_result(5);
	std::iota(iota_result.begin(), iota_result.end(), 1);
	for (auto &e : iota_result) {
		std::cout << e << std::endl;
	}
	std::cout << std::endl;
	//   20. std::partial_sum    — running sum (from <numeric>)
	std::vector<int> running(m.size());
	std::partial_sum(m.begin(), m.end(), running.begin());
	for (auto &e : running) {
		std::cout << e << std::endl;
	}
	std::cout << std::endl;
	

}