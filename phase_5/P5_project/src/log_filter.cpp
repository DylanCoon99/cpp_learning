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


LogFilter& LogFilter::level(const std::string& lvl) {

	level_ = std::make_optional<std::string>(lvl);

	return *this;
}

LogFilter& LogFilter::source(const std::string& src) {

	source_ = std::make_optional<std::string>(src);

	return *this;

}

LogFilter& LogFilter::contains(const std::string& text) {

	text_ = std::make_optional<std::string>(text);

	return *this;

}

LogFilter& LogFilter::after(const std::string& timestamp) {

	after_ = std::make_optional<std::string>(timestamp);

	return *this;

}

LogFilter& LogFilter::before(const std::string& timestamp) {

	before_ = std::make_optional<std::string>(timestamp);

	return *this;

}

bool matches(const LogEntry& entry) const {

	// if optional value is empty -> default that match to true
	bool level_match = (!level_.has_value()) ? true : ( (*level_ == entry.level) ? true : false);
	bool source_match = (!source_.has_value()) ? true : ( (*source_ == entry.source) ? true : false);
	bool contains_match = (!contains_.has_value()) ? true : ( (*contains_ == entry.contains) ? true : false);
	bool after_match = (!after_.has_value()) ? true : ( (*after_ == entry.after) ? true : false);
	bool before_match = (!before_.has_value()) ? true : ( (*before_ == entry.before) ? true : false);

	return level_match && source_match && contains_match && after_match && before_match;

}
