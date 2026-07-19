#include "log_processor.h"
#include <iostream>
#include <fstream>

// Generate sample log files for testing
void generate_sample_logs(const fs::path& dir) {
    fs::create_directories(dir);

    std::vector<std::string> levels = {"INFO", "WARN", "ERROR", "DEBUG"};
    std::vector<std::string> sources = {"api", "db", "auth", "scheduler"};
    std::vector<std::string> messages = {
        "Request received: GET /users",
        "Query executed successfully",
        "Connection timeout after 5000ms",
        "Token refreshed for user_123",
        "Job completed in 230ms",
        "Failed login attempt for user_456",
        "Disk usage at 85%",
        "Cache miss for key: session_789",
        "Response sent: 200 OK",
        "Retry attempt 2 of 3",
    };

    // Generate 3 log files with ~1000 lines each
    for (int file_num = 0; file_num < 3; ++file_num) {
        std::ofstream out(dir / ("server_" + std::to_string(file_num) + ".log"));
        for (int i = 0; i < 1000; ++i) {
            int hour = 10 + (i / 200);
            int min = (i / 4) % 60;
            int sec = (i * 7) % 60;
            out << "[2026-07-18 " << (hour < 10 ? "0" : "") << hour << ":"
                << (min < 10 ? "0" : "") << min << ":"
                << (sec < 10 ? "0" : "") << sec << "] "
                << "[" << levels[i % levels.size()] << "] "
                << "[" << sources[i % sources.size()] << "] "
                << messages[i % messages.size()] << "\n";
        }
    }
    std::cout << "Generated 3 log files in " << dir << "\n";
}

int main() {
    fs::path log_dir = "sample_logs";

    // Generate test data
    generate_sample_logs(log_dir);

    // Process all logs in directory
    std::cout << "\n=== Processing All Logs ===\n";
    LogProcessor processor(4);
    LogFilter no_filter;
    auto stats = processor.process_directory(log_dir, no_filter);
    stats->print_report();

    // Process with filter: only errors
    std::cout << "\n=== Errors Only ===\n";
    LogFilter error_filter;
    error_filter.level("ERROR");
    auto error_stats = processor.process_directory(log_dir, error_filter);
    error_stats->print_report();

    // Process with filter: db source, after a certain time
    std::cout << "\n=== DB logs after 12:00 ===\n";
    LogFilter db_filter;
    db_filter.source("db").after("2026-07-18 12:00:00");
    auto db_stats = processor.process_directory(log_dir, db_filter);
    db_stats->print_report();

    // Process with filter: messages containing "timeout"
    std::cout << "\n=== Timeout messages ===\n";
    LogFilter timeout_filter;
    timeout_filter.contains("timeout");
    auto timeout_stats = processor.process_directory(log_dir, timeout_filter);
    timeout_stats->print_report();

    // Cleanup
    fs::remove_all(log_dir);
    std::cout << "\nCleaned up sample logs.\n";
}
