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
#include <queue>

// YOUR CODE HERE


void LogStats::record(const LogEntry& entry) {
	std::lock_guard<std::mutex> guard(mtx_);

	++total_;	
	std::string level = entry.level;
	++level_counts_[level];
	++source_counts_[entry.source];

	if (level == "ERROR") {
		++error_messages_[entry.message];
	}

}


int LogStats::total() const {
	return total_;
}


int LogStats::count_by_level(const std::string& level) const {
	return level_counts_.at(level);
}


int LogStats::count_by_source(const std::string& source) const {
	return source_counts_.at(source);
}


std::string LogStats::most_common_level() const {
	int highest_count = 0;
	std::string most_common_level;	

	for (auto& [level, count] : level_counts_) {
		if (count > highest_count) {
			highest_count = count;
			most_common_level = level;
		}
	}

	return most_common_level;
}


std::string LogStats::most_common_source() const {
	int highest_count = 0;
	std::string most_common_source;	

	for (auto& [source, count] : source_counts_) {
		if (count > highest_count) {
			highest_count = count;
			most_common_source = source;
		}
	}

	return most_common_source;

}


std::vector<std::string> LogStats::top_errors(int n) const {

	std::vector<std::string> result;

	std::priority_queue<
		std::pair<int, std::string>,
		std::vector<std::pair<int, std::string>>,
		std::greater<>
	> min_heap; 
	
	for (auto& [message, freq] : error_messages_) {
		min_heap.push({freq, message});
		if (static_cast<int>(min_heap.size()) > n) {
			min_heap.pop();
		}
	}

	while (!min_heap.empty()) {
		result.push_back(min_heap.top().second);
		min_heap.pop();
	}

	return result;
}


void LogStats::print_report() const {
	std::lock_guard<std::mutex> guard(mtx_);

	std::cout << "Total entries: " << total_ << "\n\n";

	std::cout << "By level:\n";
	for (const auto& [level, count] : level_counts_) {
		std::cout << "  " << level << ": " << count << "\n";
	}

	std::cout << "\nBy source:\n";
	for (const auto& [source, count] : source_counts_) {
		std::cout << "  " << source << ": " << count << "\n";
	}

	if (!error_messages_.empty()) {
		std::cout << "\nTop error messages:\n";
		for (const auto& [msg, count] : error_messages_) {
			std::cout << "  " << count << "x  " << msg << "\n";
		}
	}
}
