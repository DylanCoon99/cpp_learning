// Implement LogProcessor methods.
//
// Constructor: initialize pool_ with num_threads
//
// process_chunk():
//   For each line in the chunk:
//     - Parse it (LogEntry::parse) — skip if nullopt
//     - Check filter.matches() — skip if false
//     - Record in stats
//
// process_file():
//   - Open file, read all lines into a vector
//   - Split into chunks (e.g., 500 lines per chunk)
//   - Submit each chunk as a task to pool_
//   - Wait for all futures
//   - Return the stats
//
// process_files():
//   - Read all files, collect all lines into one vector
//   - Split into chunks, submit each chunk to the pool
//   - One level of parallelism — all lines go through the same chunk pipeline
//   - Use a shared LogStats (thread-safe via mutex)
//   - Wait for all futures, return stats
//
// process_directory():
//   - Use fs::directory_iterator to find .log files
//   - Collect paths, call process_files

#include "log_processor.h"
#include <fstream>

// YOUR CODE HERE



std::shared_ptr<LogStats> LogProcessor::process_file(const fs::path& filepath, const LogFilter& filter) {
	return process_files({filepath}, filter);
}


std::shared_ptr<LogStats> LogProcessor::process_files(const std::vector<fs::path>& files, const LogFilter& filter) {

	// 1. Read all lines from all files
	std::vector<std::string> all_lines;
	for (const auto& file : files) {
		std::ifstream in(file);
		if (!in) continue;
		std::string line;
		while (std::getline(in, line)) {
			all_lines.push_back(std::move(line));
		}
	}

	// 2. Split into chunks and submit to pool
	auto stats = std::make_shared<LogStats>();
	const int chunk_size = 500;
	std::vector<std::future<void>> futures;

	for (int i = 0; i < static_cast<int>(all_lines.size()); i += chunk_size) {
		int end = std::min(i + chunk_size, static_cast<int>(all_lines.size()));
		std::vector<std::string> chunk(all_lines.begin() + i, all_lines.begin() + end);

		futures.push_back(pool_.submit([this, chunk = std::move(chunk), &filter, stats]() {
			process_chunk(chunk, filter, *stats);
		}));
	}

	// 3. Wait for all tasks
	for (auto& f : futures) {
		f.get();
	}

	return stats;
}


std::shared_ptr<LogStats> LogProcessor::process_directory(const fs::path& dir, const LogFilter& filter) {

	// process_directory():
	//   - Use fs::directory_iterator to find .log files
	//   - Collect paths, call process_files

	std::vector<fs::path> files;


	if (fs::exists(dir) && fs::is_directory(dir)) {
		// iterate over the directory
		for (const auto& entry : fs::directory_iterator(dir)) {
			// entry.path()
			if (fs::is_regular_file(entry.path())) {
				if (entry.path().extension() == ".log") {
					files.push_back(entry.path());
				}
			}
		}
	}
	
	return process_files(files, filter);
}


void LogProcessor::process_chunk(const std::vector<std::string>& lines, const LogFilter& filter, LogStats& stats) {

	// process_chunk():
	//   For each line in the chunk:
	//     - Parse it (LogEntry::parse) — skip if nullopt
	//     - Check filter.matches() — skip if false
	//     - Record in stats

	for (auto& line : lines) {
		auto entry = LogEntry::parse(line);
		if (entry.has_value()) {
			if (filter.matches(*entry)) {
				stats.record(*entry);
			}
		}
	}


}
