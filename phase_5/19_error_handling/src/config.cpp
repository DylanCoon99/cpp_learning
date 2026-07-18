// Implement the error-handling methods. The boilerplate methods are done for you.
//
// YOU implement these (they involve throwing/catching exceptions or using std::optional):
//   - load_file      — throw ConfigError if file can't be opened
//   - get            — throw KeyNotFoundError if key is missing
//   - get_optional   — return std::optional (nullopt if missing)
//   - get_int        — catch stoi failure, throw TypeError
//   - get_double     — catch stod failure, throw TypeError
//   - get_bool       — validate input, throw TypeError for invalid values
//   - get_int_or     — return default on any failure (never throw)
//   - get_double_or  — return default on any failure (never throw)
//   - get_bool_or    — return default on any failure (never throw)
//   - parse_line     — throw ParseError for malformed lines

#include "config.h"
#include <sstream>
#include <fstream>
#include <algorithm>

// === PROVIDED — no error handling needed ===

std::string Config::trim(const std::string& s) {
    auto start = s.find_first_not_of(" \t\r\n");
    if (start == std::string::npos) return "";
    auto end = s.find_last_not_of(" \t\r\n");
    return s.substr(start, end - start + 1);
}

void Config::load_string(const std::string& content) {
    std::istringstream stream(content);
    std::string line;
    int line_number = 0;
    while (std::getline(stream, line)) {
        ++line_number;
        auto result = parse_line(line, line_number);
        if (result) {
            data_[result->first] = result->second;
        }
    }
}

std::string Config::get_or(const std::string& key, const std::string& default_value) const {
    auto it = data_.find(key);
    if (it != data_.end()) return it->second;
    return default_value;
}

bool Config::has(const std::string& key) const {
    return data_.contains(key);
}

std::vector<std::string> Config::keys() const {
    std::vector<std::string> result;
    for (const auto& [key, _] : data_) {
        result.push_back(key);
    }
    return result;
}

std::vector<std::string> Config::keys_with_prefix(const std::string& prefix) const {
    std::vector<std::string> result;
    for (const auto& [key, _] : data_) {
        if (key.substr(0, prefix.size()) == prefix) {
            result.push_back(key);
        }
    }
    return result;
}

int Config::size() const {
    return data_.size();
}

void Config::set(const std::string& key, const std::string& value) {
    data_[key] = value;
}

// === YOUR CODE — implement these ===

void Config::load_file(const std::string& filename) {
    // Open with std::ifstream. If it fails, throw ConfigError.
    // Otherwise read line by line, same pattern as load_string.
}

std::string Config::get(const std::string& key) const {
    // Return value if found. Throw KeyNotFoundError if not.
}

std::optional<std::string> Config::get_optional(const std::string& key) const {
    // Return the value wrapped in optional, or std::nullopt if missing.
}

int Config::get_int(const std::string& key) const {
    // Get the string value (this may throw KeyNotFoundError — let it).
    // Convert with std::stoi. If conversion fails, throw TypeError.
}

double Config::get_double(const std::string& key) const {
    // Same pattern as get_int but with std::stod.
}

bool Config::get_bool(const std::string& key) const {
    // Get the string value, lowercase it.
    // Accept: "true", "yes", "1" → return true
    //         "false", "no", "0" → return false
    // Anything else → throw TypeError
}

int Config::get_int_or(const std::string& key, int default_value) const {
    // Try get_int. If ANY exception is thrown, return default_value.
}

double Config::get_double_or(const std::string& key, double default_value) const {
    // Try get_double. If ANY exception is thrown, return default_value.
}

bool Config::get_bool_or(const std::string& key, bool default_value) const {
    // Try get_bool. If ANY exception is thrown, return default_value.
}

std::optional<std::pair<std::string, std::string>> Config::parse_line(const std::string& line, int line_number) {
    // Trim the line.
    // If empty or starts with '#', return std::nullopt.
    // Find '='. If not found, throw ParseError with line_number.
    // Split into key and value at '=', trim both.
    // If key is empty, throw ParseError.
    // Return {key, value}.
}
