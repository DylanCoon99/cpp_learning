#pragma once

#include <string>
#include <map>
#include <optional>
#include <stdexcept>
#include <vector>

// Custom exception hierarchy for config parsing errors
class ConfigError : public std::runtime_error {
public:
    ConfigError(const std::string& msg, int line = 0)
        : std::runtime_error(msg), line_(line) {}
    int line() const { return line_; }
private:
    int line_;
};

class ParseError : public ConfigError {
public:
    ParseError(const std::string& msg, int line)
        : ConfigError("Parse error (line " + std::to_string(line) + "): " + msg, line) {}
};

class KeyNotFoundError : public ConfigError {
public:
    KeyNotFoundError(const std::string& key)
        : ConfigError("Key not found: " + key) {}
};

class TypeError : public ConfigError {
public:
    TypeError(const std::string& key, const std::string& expected_type)
        : ConfigError("Cannot convert '" + key + "' to " + expected_type) {}
};


// Config file parser
// Parses files in the format:
//   # comment
//   key = value
//   database.host = localhost
//   database.port = 5432
//   debug = true
//   max_connections = 100
//
class Config {
public:
    // Parse from file — throws ParseError on malformed lines
    void load_file(const std::string& filename);

    // Parse from string (for testing without files)
    void load_string(const std::string& content);

    // Get raw string value — throws KeyNotFoundError if missing
    std::string get(const std::string& key) const;

    // Get with default — never throws
    std::string get_or(const std::string& key, const std::string& default_value) const;

    // Get as optional — returns nullopt if missing
    std::optional<std::string> get_optional(const std::string& key) const;

    // Typed getters — throw TypeError if conversion fails
    int get_int(const std::string& key) const;
    double get_double(const std::string& key) const;
    bool get_bool(const std::string& key) const;

    // Typed getters with defaults — never throw
    int get_int_or(const std::string& key, int default_value) const;
    double get_double_or(const std::string& key, double default_value) const;
    bool get_bool_or(const std::string& key, bool default_value) const;

    // Check existence
    bool has(const std::string& key) const;

    // Get all keys
    std::vector<std::string> keys() const;

    // Get all keys with a prefix (e.g., "database." returns database.host, database.port)
    std::vector<std::string> keys_with_prefix(const std::string& prefix) const;

    // Number of entries
    int size() const;

    // Set a value
    void set(const std::string& key, const std::string& value);

private:
    std::map<std::string, std::string> data_;

    // Parse a single line — returns {key, value} or throws ParseError
    // Skips comments (#) and blank lines
    std::optional<std::pair<std::string, std::string>> parse_line(const std::string& line, int line_number);

    // Trim whitespace from both ends of a string
    static std::string trim(const std::string& s);
};
