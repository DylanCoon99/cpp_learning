#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

int main() {
    std::vector<int> nums = {5, 3, 8, 1, 9, 2, 7};

    std::sort(nums.begin(), nums.end());

    std::cout << "Sorted: ";
    for (int n : nums) std::cout << n << " ";
    std::cout << "\n";

    int sum = std::accumulate(nums.begin(), nums.end(), 0);
    std::cout << "Sum: " << sum << "\n";
    std::cout << "CMake works!\n";
}
