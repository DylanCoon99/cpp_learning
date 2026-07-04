#include "stats.h"
#include <algorithm>
#include <numeric>
#include <cmath>
#include <stdexcept>

namespace stats {

double sum(const std::vector<double>& data) {
    if (data.empty()) throw std::invalid_argument("Empty data");
    return std::accumulate(data.begin(), data.end(), 0.0);
}

double mean(const std::vector<double>& data) {
    return sum(data) / data.size();
}

double median(std::vector<double> data) {
    if (data.empty()) throw std::invalid_argument("Empty data");
    std::sort(data.begin(), data.end());
    int n = data.size();
    if (n % 2 == 0) return (data[n / 2 - 1] + data[n / 2]) / 2.0;
    return data[n / 2];
}

double stddev(const std::vector<double>& data) {
    if (data.empty()) throw std::invalid_argument("Empty data");
    double m = mean(data);
    double sq_sum = std::accumulate(data.begin(), data.end(), 0.0,
        [m](double acc, double val) { return acc + (val - m) * (val - m); });
    return std::sqrt(sq_sum / data.size());
}

double min(const std::vector<double>& data) {
    if (data.empty()) throw std::invalid_argument("Empty data");
    return *std::min_element(data.begin(), data.end());
}

double max(const std::vector<double>& data) {
    if (data.empty()) throw std::invalid_argument("Empty data");
    return *std::max_element(data.begin(), data.end());
}

}
