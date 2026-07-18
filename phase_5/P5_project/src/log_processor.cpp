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
