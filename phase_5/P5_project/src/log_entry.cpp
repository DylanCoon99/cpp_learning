// Implement LogEntry::parse
//
// Format: "[2026-07-18 14:30:05] [ERROR] [db] Message text here"
//
// Parse by finding the brackets:
//   - timestamp: between first [ and ]
//   - level: between second [ and ]
//   - source: between third [ and ]
//   - message: everything after the third ]
//
// Return std::nullopt if the line doesn't match the expected format.

#include "log_entry.h"

// YOUR CODE HERE



std::optional<LogEntry> LogEntry::parse(const std::string& line) {

	// Format: "[2026-07-18 14:30:05] [ERROR] [db] Message text here"
	auto b1 = line.find('[');
	auto e1 = line.find(']', b1);
	auto b2 = line.find('[', e1);
	auto e2 = line.find(']', b2);
	auto b3 = line.find('[', e2);
	auto e3 = line.find(']', b3);
	

	if (b1 == std::string::npos || e1 == std::string::npos ||
		b2 == std::string::npos || e2 == std::string::npos ||
		b3 == std::string::npos || e3 == std::string::npos) {
		return std::nullopt;
	}



	std::string timestamp = line.substr(b1 + 1, e1 - b1 - 1);
	std::string level = line.substr(b2 + 1, e2 - b2 - 1);
	std::string source = line.substr(b3 + 1, e3 - b3 - 1);
	std::string message = line.substr(e3 + 2);


	LogEntry logEntry = {
		timestamp,
		level,
		source,
		message
	};


	return std::make_optional<LogEntry>(logEntry);
}