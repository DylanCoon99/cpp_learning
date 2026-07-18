// Implement LogFilter methods.
//
// Builder methods (level, source, contains, after, before):
//   Set the corresponding optional, return *this for chaining.
//
// matches():
//   Check each optional that has a value. ALL set conditions must match.
//   - level_: entry.level == *level_
//   - source_: entry.source == *source_
//   - contains_: entry.message.find(*contains_) != npos
//   - after_: entry.timestamp >= *after_ (string comparison works for ISO timestamps)
//   - before_: entry.timestamp <= *before_

#include "log_filter.h"

// YOUR CODE HERE
