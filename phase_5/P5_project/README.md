# Phase 5 Project: Concurrent Log Processor

A multi-threaded log file processor that reads, parses, filters, and aggregates log data using a thread pool. Demonstrates concurrency, file I/O, error handling, and proper project structure.

## Overview

Build a tool that processes large log files in parallel — splitting the work across multiple threads, aggregating results, and outputting reports. This is a realistic tool you'd use in production for analyzing server logs, application metrics, or event data.

## Architecture

```
┌──────────────┐    ┌──────────────┐    ┌──────────────┐
│  Log Reader  │───►│  Thread Pool │───►│  Aggregator  │
│  (file I/O)  │    │  (workers)   │    │  (results)   │
└──────────────┘    └──────────────┘    └──────────────┘
                           │
                    ┌──────┴──────┐
                    │  Parser +   │
                    │  Filter     │
                    └─────────────┘
```

## Components

### `LogEntry` — Parsed log line

```cpp
struct LogEntry {
    std::string timestamp;   // "2026-07-18 14:30:05"
    std::string level;       // "INFO", "WARN", "ERROR", "DEBUG"
    std::string source;      // "auth", "api", "db", "scheduler"
    std::string message;

    static std::optional<LogEntry> parse(const std::string& line);
};
```

Log format: `[2026-07-18 14:30:05] [ERROR] [db] Connection timeout`

### `LogFilter` — Configurable filter

```cpp
class LogFilter {
public:
    LogFilter& level(const std::string& lvl);       // filter by level
    LogFilter& source(const std::string& src);      // filter by source
    LogFilter& contains(const std::string& text);   // message contains text
    LogFilter& after(const std::string& timestamp); // after a time
    LogFilter& before(const std::string& timestamp);// before a time

    bool matches(const LogEntry& entry) const;

private:
    std::optional<std::string> level_;
    std::optional<std::string> source_;
    std::optional<std::string> contains_;
    std::optional<std::string> after_;
    std::optional<std::string> before_;
};
```

### `LogStats` — Aggregated statistics (thread-safe)

```cpp
class LogStats {
public:
    void record(const LogEntry& entry);  // thread-safe — uses mutex internally

    int total() const;
    int count_by_level(const std::string& level) const;
    int count_by_source(const std::string& source) const;
    std::string most_common_level() const;
    std::string most_common_source() const;
    std::vector<std::string> top_errors(int n) const;  // most frequent error messages

    void print_report() const;

private:
    mutable std::mutex mtx_;
    int total_ = 0;
    std::map<std::string, int> level_counts_;
    std::map<std::string, int> source_counts_;
    std::map<std::string, int> error_messages_;  // message → count
};
```

### `LogProcessor` — Orchestrates everything

```cpp
class LogProcessor {
public:
    explicit LogProcessor(int num_threads = 4);

    // Process a single file
    LogStats process_file(const fs::path& filepath, const LogFilter& filter);

    // Process multiple files in parallel
    LogStats process_files(const std::vector<fs::path>& files, const LogFilter& filter);

    // Process all .log files in a directory
    LogStats process_directory(const fs::path& dir, const LogFilter& filter);

private:
    ThreadPool pool_;

    // Process a chunk of lines — called by worker threads
    void process_chunk(const std::vector<std::string>& lines,
                       const LogFilter& filter,
                       LogStats& stats);
};
```

## Implementation Strategy

1. **Read**: Read all files, collect all lines into one vector
2. **Split**: Divide lines into chunks (e.g., 500 lines per chunk)
3. **Submit**: Each chunk is a task submitted to the thread pool
4. **Process**: Each worker parses lines, applies filter, records to shared LogStats
5. **Aggregate**: LogStats uses a mutex to safely merge results from all workers
6. **Report**: Print summary statistics

One level of parallelism — all lines from all files go into the same chunked work queue. The thread pool doesn't care which file a line came from.

## Features

- **Chunk-based parallelism** — all lines split into work units across the pool
- **Configurable filtering** — builder pattern for composable filters
- **Thread-safe aggregation** — mutex-protected statistics
- **Error tolerance** — malformed lines are skipped (logged to stderr), don't crash
- **Filesystem integration** — discover .log files in directories

## Sample Log File

Generate test data with varied entries. Create a `generate_logs.cpp` that writes sample log files, or hardcode test data in tests.

Format: `[YYYY-MM-DD HH:MM:SS] [LEVEL] [SOURCE] Message text here`

```
[2026-07-18 14:30:01] [INFO] [api] Request received: GET /users
[2026-07-18 14:30:01] [DEBUG] [db] Query: SELECT * FROM users
[2026-07-18 14:30:02] [INFO] [api] Response sent: 200 OK
[2026-07-18 14:30:05] [ERROR] [db] Connection timeout after 5000ms
[2026-07-18 14:30:05] [WARN] [api] Retrying request (attempt 2)
[2026-07-18 14:30:06] [INFO] [auth] Token refreshed for user_123
[2026-07-18 14:30:10] [ERROR] [scheduler] Job "cleanup" failed: disk full
[2026-07-18 14:30:11] [INFO] [api] Request received: POST /login
[2026-07-18 14:30:12] [WARN] [auth] Failed login attempt for user_456
[2026-07-18 14:30:15] [ERROR] [db] Connection timeout after 5000ms
```

## Build & Run

```bash
cmake -B build
cmake --build build

# Generate sample logs
./build/generate_logs

# Process logs
./build/log_processor logs/

# Run tests
cd build && ctest --output-on-failure
```

## What You Implement

- `LogEntry::parse()` — string parsing with error handling (std::optional for malformed lines)
- `LogFilter` — builder pattern, matching logic
- `LogStats` — thread-safe recording with mutex, aggregation queries
- `LogProcessor` — file reading, chunking, thread pool submission, directory iteration
- Tests for each component
