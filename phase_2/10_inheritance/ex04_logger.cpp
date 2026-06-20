// Exercise 4: Logger — Inheritance vs Composition
//
// Task: Build a logging system that demonstrates BOTH inheritance and
//       composition approaches, so you can see the trade-offs.
//
// Part A — Inheritance approach:
//
//   enum class LogLevel { Debug, Info, Warning, Error };
//
//   class Logger (abstract base):
//       void log(LogLevel level, const std::string& message);
//         — formats the message with timestamp and level, then calls write()
//       virtual ~Logger() = default;
//   protected:
//       virtual void write(const std::string& formatted_msg) = 0;
//   private:
//       std::string format(LogLevel level, const std::string& msg) const;
//         — returns something like "[INFO] 2026-06-19 14:30:00 | message"
//         — for timestamp, just use a counter or fixed string (real timestamps
//           require <chrono> which we haven't covered)
//
//   class ConsoleLogger : public Logger
//       write() prints to std::cout
//
//   class FileLogger : public Logger
//       Constructor takes filename, opens file (use std::ofstream)
//       write() writes to the file
//       Destructor closes the file
//
//   class NullLogger : public Logger
//       write() does nothing — useful for disabling logging
//
// Part B — Composition approach:
//
//   class LogSink (abstract base):
//       virtual void write(const std::string& msg) = 0;
//       virtual ~LogSink() = default;
//
//   class ConsoleSink : public LogSink { ... }
//   class FileSink : public LogSink { ... }
//
//   class ComposableLogger:
//       void add_sink(LogSink* sink);    // can log to MULTIPLE destinations
//       void log(LogLevel level, const std::string& message);
//         — formats, then calls write() on ALL sinks
//   private:
//       std::vector<LogSink*> sinks_;
//
// In main():
//   - Part A: Create a ConsoleLogger, log some messages at different levels
//   - Part A: Create a FileLogger, log some messages (verify file is created)
//   - Part B: Create a ComposableLogger with BOTH a ConsoleSink and FileSink
//     attached — one log() call writes to both destinations
//   - Compare: the composition approach is more flexible (multiple sinks,
//     add/remove at runtime). The inheritance approach is simpler for
//     single-destination logging.
//
// Compile: g++ -std=c++20 -Wall -Wextra -o ex04 ex04_logger.cpp

// YOUR CODE HERE
