#include "config.h"
#include <iostream>

int main() {
    Config config;

    // Load from a string (simulating a config file)
    try {
        config.load_string(R"(
# Application settings
app.name = MyApp
app.version = 2.1

# Database
database.host = localhost
database.port = 5432
database.name = mydb

# Features
debug = true
max_connections = 100
timeout = 30.5
verbose = no
)");
    } catch (const ParseError& e) {
        std::cerr << "Failed to parse config: " << e.what() << "\n";
        return 1;
    }

    // Basic access
    std::cout << "=== Basic Access ===\n";
    std::cout << "app.name: " << config.get("app.name") << "\n";
    std::cout << "database.host: " << config.get("database.host") << "\n";

    // Typed access
    std::cout << "\n=== Typed Access ===\n";
    std::cout << "port: " << config.get_int("database.port") << "\n";
    std::cout << "debug: " << (config.get_bool("debug") ? "yes" : "no") << "\n";
    std::cout << "timeout: " << config.get_double("timeout") << "\n";
    std::cout << "verbose: " << (config.get_bool("verbose") ? "yes" : "no") << "\n";

    // Optional / default access
    std::cout << "\n=== Optional / Default ===\n";
    auto missing = config.get_optional("nonexistent");
    std::cout << "nonexistent: " << (missing ? *missing : "(not set)") << "\n";
    std::cout << "log_level (default): " << config.get_or("log_level", "INFO") << "\n";
    std::cout << "retries (default): " << config.get_int_or("retries", 3) << "\n";

    // Prefix query
    std::cout << "\n=== Database Keys ===\n";
    for (const auto& key : config.keys_with_prefix("database.")) {
        std::cout << key << " = " << config.get(key) << "\n";
    }

    // Error handling demos
    std::cout << "\n=== Error Handling ===\n";

    try {
        config.get("nonexistent_key");
    } catch (const KeyNotFoundError& e) {
        std::cout << "Caught: " << e.what() << "\n";
    }

    try {
        config.get_int("app.name");  // "MyApp" is not an int
    } catch (const TypeError& e) {
        std::cout << "Caught: " << e.what() << "\n";
    }

    try {
        config.load_string("bad line without equals sign");
    } catch (const ParseError& e) {
        std::cout << "Caught: " << e.what() << "\n";
    }

    std::cout << "\nTotal config entries: " << config.size() << "\n";
}
