// Implement LogStats methods.
//
// record(): MUST be thread-safe (lock the mutex)
//   - Increment total_
//   - Increment level_counts_[entry.level]
//   - Increment source_counts_[entry.source]
//   - If level is "ERROR", increment error_messages_[entry.message]
//
// Getters: lock the mutex, read the data, return.
//
// most_common_level/source: find the key with the highest count in the map.
//
// top_errors(n): sort error_messages_ by count descending, return first n messages.
//
// print_report(): print a formatted summary.

#include "log_stats.h"
#include <algorithm>

// YOUR CODE HERE
