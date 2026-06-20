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
#include <iostream>
#include <string>
#include <fstream>
#include <stdexcept>
#include <vector>

// Part A

enum class LogLevel { Debug, Info, Warning, Error };


class Logger {

public:
	void log(LogLevel level, const std::string& message) {
		write(format(level, message));
	}
	// formats the message with timestamp and level, then calls write()
	virtual ~Logger() = default;

protected:
	virtual void write(const std::string& formatted_msg) = 0;

private:
	std::string format(LogLevel level, const std::string& msg) const {

		// "[INFO] 2026-06-19 14:30:00 | message"

		std::string level_str;

		switch (level) {
		case LogLevel::Debug:
			level_str = "[DEBUG]";break;
		case LogLevel::Info:
			level_str = "[INFO]";break; 
		case LogLevel::Warning:
			level_str = "[WARNING]";break; 
		case LogLevel::Error:
			level_str = "[ERROR]";break; 
		}

		return level_str + " <TIMESTAMP> | " + msg;
	}

};


class ConsoleLogger : public Logger {

public:

	void write(const std::string& formatted_msg) override {
		std::cout << formatted_msg << std::endl;
	}

};


class FileLogger : public Logger {

public:
	FileLogger(std::string filename) : file_(filename) {

		// 2. Check if the file opened successfully
		if (!file_) {
		    std::cerr << "Error opening file!" << std::endl;
			throw std::runtime_error("Failed to open file: " + filename);
		}
	}

	void write(const std::string& formatted_msg) override {
		file_ << formatted_msg;
		file_ << std::endl;
	}

	~FileLogger() {
		file_.close();
	}

protected:
	std::ofstream file_;

};


class NullLogger : public Logger {
public:

	void write(const std::string& formatted_msg) override {
		return;
	}

};



// Part B

class LogSink {
public:
	virtual void write(const std::string& msg) = 0;
	virtual ~LogSink() = default;

};


class ConsoleSink : public LogSink { 

public:
	void write(const std::string& msg) {
		std::cout << msg << std::endl;
	}


};



class FileSink : public LogSink {

public:

	FileSink(std::string filename) : file_(filename) {}

	void write(const std::string& msg) {
		file_ << msg;
		file_ << std::endl;
	}

private:
	std::ofstream file_;

};



class ComposableLogger {
public:
	void add_sink(LogSink* sink) {
		sinks_.push_back(sink);
	}

	void log(LogLevel level, const std::string& message) {
		for (auto& sink : sinks_) {
			sink->write(format(level, message));
		}
	}


private:
	std::vector<LogSink*> sinks_;
	std::string format(LogLevel level, const std::string& msg) const {

		// "[INFO] 2026-06-19 14:30:00 | message"

		std::string level_str;

		switch (level) {
		case LogLevel::Debug:
			level_str = "[DEBUG]";break;
		case LogLevel::Info:
			level_str = "[INFO]";break; 
		case LogLevel::Warning:
			level_str = "[WARNING]";break; 
		case LogLevel::Error:
			level_str = "[ERROR]";break; 
		}

		return level_str + " <TIMESTAMP> | " + msg;
	}

};



int main() {

	// Test Part A

	// ConsoleLogger
	ConsoleLogger console_logger{};
	console_logger.log(LogLevel::Debug, "Debugging in the console...");
	console_logger.log(LogLevel::Info, "Logging info in the console...");

	// FileLogger
	FileLogger file_logger("./file.log");
	file_logger.log(LogLevel::Debug, "Debugging in the console...");
	file_logger.log(LogLevel::Info, "Logging info in the console...");

	// NullLogger
	NullLogger null_logger{};


	// Test Part B

	ComposableLogger logger{};
	FileSink file_sink("file2.log");
	ConsoleSink console_sink{};
	logger.add_sink(&file_sink);
	logger.add_sink(&console_sink);

	logger.log(LogLevel::Info, "Testing the logger.");
	logger.log(LogLevel::Info, "Should see in the console and the file.");


}
