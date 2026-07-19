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
//   - Submit each file as a task
//   - Each task calls process_file internally
//   - Merge results (or use a shared LogStats)
//
// process_directory():
//   - Use fs::directory_iterator to find .log files
//   - Collect paths, call process_files

#include "log_processor.h"
#include <fstream>

// YOUR CODE HERE

explicit LogProcessor::LogProcessor(int num_threads = 4) {
	// instantiate a thread pool
	pool_ = ThreadPool(num_threads);
}



LogStats LogProcessor::process_file(const fs::path& filepath, const LogFilter& filter) {

	// process_file():
	//   - Open file, read all lines into a vector
	//   - Split into chunks (e.g., 500 lines per chunk)
	//   - Submit each chunk as a task to pool_
	//   - Wait for all futures
	//   - Return the stats


}


LogStats LogProcessor::process_files(const std::vector<fs::path>& files, const LogFilter& filter) {

	// process_files():
	//   - Submit each file as a task
	//   - Each task calls process_file internally
	//   - Merge results (or use a shared LogStats)



}


LogStats LogProcessor::process_directory(const fs::path& dir, const LogFilter& filter) {

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
