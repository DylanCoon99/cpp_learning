// Exercise 4: Log File Analyzer
//
// Task: Analyze a simulated server log using STL algorithms.
//       Solve each query with STL algorithms, not manual loops.
//
// Compile: g++ -std=c++20 -Wall -Wextra -o ex04 ex04_data_pipeline.cpp

#include <pthread.h>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>
#include <iterator>

struct LogEntry {
    int timestamp;
    std::string level;     // "INFO", "WARN", "ERROR", "DEBUG"
    std::string service;   // "auth", "api", "db", "cache"
    int response_ms;
};


void print_entry(const LogEntry& entry) {
	std::cout << "timestamp: " << entry.timestamp << std::endl;
	std::cout << "level: " << entry.level << std::endl;
	std::cout << "service: " << entry.service << std::endl;
	std::cout << "response_ms: " << entry.response_ms << std::endl;

}


int main() {

    std::vector<LogEntry> logs = {
        {1000, "INFO",  "api",   45},
        {1001, "DEBUG", "auth",  12},
        {1002, "INFO",  "api",   78},
        {1003, "WARN",  "db",    230},
        {1004, "ERROR", "db",    1500},
        {1005, "INFO",  "cache", 5},
        {1006, "INFO",  "api",   92},
        {1007, "ERROR", "auth",  890},
        {1008, "DEBUG", "cache", 8},
        {1009, "WARN",  "api",   310},
        {1010, "INFO",  "db",    67},
        {1011, "ERROR", "db",    2100},
        {1012, "INFO",  "auth",  55},
        {1013, "INFO",  "api",   120},
        {1014, "WARN",  "cache", 340},
        {1015, "DEBUG", "api",   15},
        {1016, "ERROR", "api",   950},
        {1017, "INFO",  "db",    88},
        {1018, "INFO",  "auth",  42},
        {1019, "WARN",  "db",    450},
        {1020, "ERROR", "db",    1800},
        {1021, "INFO",  "cache", 3},
        {1022, "DEBUG", "auth",  10},
        {1023, "INFO",  "api",   65},
        {1024, "ERROR", "auth",  720},
        {1025, "WARN",  "api",   280},
        {1026, "INFO",  "db",    95},
        {1027, "INFO",  "cache", 7},
        {1028, "ERROR", "db",    1350},
        {1029, "DEBUG", "api",   18},
        {1030, "INFO",  "api",   110},
    };

    // YOUR CODE HERE

    // Queries — implement each using STL algorithms (avoid raw loops):
    // 1. Count entries by level (count_if for each level)
    std::vector<std::string> levels = {"INFO", "WARN", "ERROR", "DEBUG"};
    int count;
    for (const std::string &level : levels) {
    	count = std::count_if(logs.begin(), logs.end(), [level](LogEntry entry) { return entry.level == level; });
    	std::cout << level << ": " << count;
    	std::cout << std::endl;
    }
    // 2. Find the slowest request (max_element by response_ms)
    LogEntry slowest_req = *std::max_element(logs.begin(), logs.end(), [](const LogEntry& a, const LogEntry& b) {
    	return a.response_ms < b.response_ms;
    });
    std::cout << "Slowest request: ";
    print_entry(slowest_req);
    // 3. Find the average response time (accumulate + size)
    int average = std::accumulate(logs.begin(), logs.end(), 0, [](int acc, const LogEntry& entry) {
    	return acc + entry.response_ms;
    });
    std::cout << "Average response_ms: " << static_cast<double>(average) / logs.size() << "ms" << std::endl;
    // 4. Find all ERROR entries from the "db" service (copy_if)
    std::vector<LogEntry> error_db_entries;
	std::copy_if(logs.begin(), logs.end(), std::back_inserter(error_db_entries), [](LogEntry entry) {return entry.service == "db" && entry.level == "ERROR";});
    for (auto &entry : error_db_entries) {
		print_entry(entry);
	}
	std::cout << std::endl;
    // 5. Sort by response time, print the 5 slowest (partial_sort)
	std::partial_sort(logs.begin(), logs.begin() + 5, logs.end(), [](const LogEntry& a, const LogEntry& b) {
		return a.response_ms > b.response_ms;
	});
	for (auto &entry : logs) {
		print_entry(entry);
	}
	std::cout << std::endl;
    // 6. Are there any requests over 1000ms? (any_of)
	bool over_1000 = std::any_of(logs.begin(), logs.end(), [](const LogEntry& entry) {
		return entry.response_ms > 1000;
	});
	std::cout << "There are " << (over_1000 ? "" : "not ") << "response times over 1000ms" << std::endl;
    // 7. What percentage of requests are under 100ms?
    int count_under_100 = std::count_if(logs.begin(), logs.end(), [](LogEntry entry) { return entry.response_ms < 100; });
    std::cout << "There are " << count_under_100 << " requests under 100ms"<< std::endl;
    // 8. Group by service: for each service, compute average response time
   	std::vector<std::string> services = {"api", "auth", "db", "cache"};
    int average_per_service;
    for (const std::string& service : services) {
    	average_per_service = std::accumulate(logs.begin(), logs.end(), 0, [service](int acc, const LogEntry& entry) {
	    	if (entry.service == service) {
	    		return acc + entry.response_ms;
	    	}
	    	return acc;
	    });
	    std::cout << "Average for " << service << " is " << average_per_service << "ms" << std::endl; 
    }
    std::cout << std::endl;
    //    (sort by service, then walk through with adjacent iterators)
    std::sort(logs.begin(), logs.end(), [](const LogEntry& a, const LogEntry& b) {
    	return a.service < b.service;
    });
	for (auto &entry : logs) {
		print_entry(entry);
	}

    

}
