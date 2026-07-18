#pragma once

#include <string>
#include <optional>
#include <iostream>

struct LogEntry {
    std::string timestamp;
    std::string level;
    std::string source;
    std::string message;

    // Parse a log line: "[2026-07-18 14:30:05] [ERROR] [db] Message here"
    // Returns nullopt if the line is malformed
    static std::optional<LogEntry> parse(const std::string& line);

    friend std::ostream& operator<<(std::ostream& os, const LogEntry& e) {
        os << "[" << e.timestamp << "] [" << e.level << "] [" << e.source << "] " << e.message;
        return os;
    }
};
