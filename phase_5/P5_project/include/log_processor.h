#pragma once

#include <string>
#include <vector>
#include <filesystem>
#include "log_stats.h"
#include "log_filter.h"
#include "thread_pool.h"

namespace fs = std::filesystem;

class LogProcessor {
public:
    explicit LogProcessor(int num_threads = 4);

    LogStats process_file(const fs::path& filepath, const LogFilter& filter);
    LogStats process_files(const std::vector<fs::path>& files, const LogFilter& filter);
    LogStats process_directory(const fs::path& dir, const LogFilter& filter);

private:
    ThreadPool pool_;

    void process_chunk(const std::vector<std::string>& lines,
                       const LogFilter& filter,
                       LogStats& stats);
};
