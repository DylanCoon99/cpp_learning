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
