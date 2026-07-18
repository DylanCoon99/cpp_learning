#pragma once

#include <string>
#include <map>
#include <optional>
#include <vector>
#include <filesystem>

namespace fs = std::filesystem;

// A persistent key-value store backed by files.
//
// Text mode: stores data as "key=value\n" in a plain text file
// Binary mode: stores data as fixed-size binary records
//
// This exercises:
//   - Text file reading/writing (ifstream, ofstream)
//   - Binary file reading/writing (read/write with reinterpret_cast)
//   - std::filesystem for file operations
//   - Error handling for I/O failures

class KVStore {
public:
    explicit KVStore(const fs::path& filepath);

    // Basic operations
    void set(const std::string& key, const std::string& value);
    std::optional<std::string> get(const std::string& key) const;
    bool remove(const std::string& key);
    bool has(const std::string& key) const;
    int size() const;
    std::vector<std::string> keys() const;
    void clear();

    // Persistence — text format (key=value per line)
    void save() const;            // write in-memory data to file
    void load();                  // read file into memory
    void save_as(const fs::path& filepath) const;  // save to a different file

    // Persistence — binary format
    void save_binary(const fs::path& filepath) const;
    void load_binary(const fs::path& filepath);

    // File info (using std::filesystem)
    bool file_exists() const;
    std::uintmax_t file_size() const;   // size of the backing file in bytes
    fs::path filepath() const;

    // Import/Export
    void export_csv(const fs::path& filepath) const;  // key,value per line
    static KVStore from_csv(const fs::path& csv_path, const fs::path& store_path);

private:
    fs::path filepath_;
    std::map<std::string, std::string> data_;
};
