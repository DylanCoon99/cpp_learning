#pragma once

#include <string>
#include <optional>
#include "log_entry.h"

class LogFilter {
public:
    LogFilter& level(const std::string& lvl);
    LogFilter& source(const std::string& src);
    LogFilter& contains(const std::string& text);
    LogFilter& after(const std::string& timestamp);
    LogFilter& before(const std::string& timestamp);

    bool matches(const LogEntry& entry) const;

private:
    std::optional<std::string> level_;
    std::optional<std::string> source_;
    std::optional<std::string> contains_;
    std::optional<std::string> after_;
    std::optional<std::string> before_;
};
