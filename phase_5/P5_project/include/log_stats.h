#pragma once

#include <string>
#include <map>
#include <vector>
#include <mutex>
#include <iostream>
#include "log_entry.h"

class LogStats {
public:
    void record(const LogEntry& entry);

    int total() const;
    int count_by_level(const std::string& level) const;
    int count_by_source(const std::string& source) const;
    std::string most_common_level() const;
    std::string most_common_source() const;
    std::vector<std::string> top_errors(int n) const;

    void print_report() const;

private:
    mutable std::mutex mtx_;
    int total_ = 0;
    std::map<std::string, int> level_counts_;
    std::map<std::string, int> source_counts_;
    std::map<std::string, int> error_messages_;
};
