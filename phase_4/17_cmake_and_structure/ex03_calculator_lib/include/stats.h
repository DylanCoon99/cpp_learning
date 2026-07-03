#pragma once

#include <vector>

namespace stats {
    double mean(const std::vector<double>& data);
    double median(std::vector<double> data);  // takes by value (needs to sort)
    double stddev(const std::vector<double>& data);
    double min(const std::vector<double>& data);
    double max(const std::vector<double>& data);
    double sum(const std::vector<double>& data);
}
