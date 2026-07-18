// Implement the KVStore class.
//
// Methods to implement:
//
// Constructor: store the filepath, load from file if it exists
//
// set/get/remove/has/size/keys/clear: operate on the in-memory map (data_)
//   - These are straightforward map operations
//
// save: write data_ to filepath_ as text (key=value per line)
//   - Open with ofstream, iterate data_, write each pair
//   - Throw runtime_error if file can't be opened
//
// load: read filepath_ into data_ (clear existing data first)
//   - Open with ifstream, read line by line, split on '='
//   - Skip blank lines and lines starting with '#'
//   - Throw runtime_error if file can't be opened
//
// save_as: same as save but to a different path
//
// save_binary: write data as binary records
//   - For each entry, write: key_length (int), key (chars), value_length (int), value (chars)
//   - Use ofstream with ios::binary
//   - Use write() with reinterpret_cast
//
// load_binary: read binary format back
//   - Read key_length, then key, then value_length, then value
//   - Use ifstream with ios::binary
//   - Use read() with reinterpret_cast
//
// file_exists: return fs::exists(filepath_)
// file_size: return fs::file_size(filepath_) — throw if doesn't exist
// filepath: return filepath_
//
// export_csv: write as "key,value\n" (with header row "key,value")
// from_csv: static factory — read CSV into a new KVStore

#include "kvstore.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>

KVStore::KVStore(const fs::path& filepath) : filepath_(filepath) {
	if (file_exists()) {
		load();
	}

	std::map<std::string, std::string> data_;
}

void KVStore::set(const std::string& key, const std::string& value) {
	data_[key] = value;
}

std::optional<std::string> KVStore::get(const std::string& key) const {
	try {
		return std::make_optional<std::string>(data_.at(key));
	} catch (...) {
		return std::nullopt;
	}
}

bool KVStore::remove(const std::string& key) {
	if (data_.contains(key)) {
		data_.erase(key);
		return true;
	}
	return false;
}

bool KVStore::has(const std::string& key) const {
	return data_.contains(key);
}

int KVStore::size() const {
	return data_.size();
}

std::vector<std::string> KVStore::keys() const {
	std::vector<std::string> keys;
	for (auto& [key, _] : data_) {
		keys.push_back(key);
	}
	return keys;
}

void KVStore::clear() {
	data_.clear();
}

void KVStore::save() const {
	std::ofstream out(filepath_);
	if (!out) throw std::runtime_error("Can't open file");

	for (auto& [key, value] : data_) {
		out << key + "=" + value << std::endl;
	}
	// out should close automatically
}

void KVStore::load() {
	clear(); // clear existing data

	// load data from file to data_
	std::ifstream in(filepath_);
	if (!in) throw std::runtime_error("Can't open file");

	std::string line;
	while (std::getline(in, line)) {
		if (line.empty() || line[0] == '#') continue;
		if (line.find('=') == std::string::npos) continue;
		auto pos = line.find('=');
		std::string key = line.substr(0, pos);
		std::string value = line.substr(pos + 1);
		data_[key] = value;
	}
	// in should close automatically
}

void KVStore::save_as(const fs::path& filepath) const {
	std::ofstream out(filepath);
	if (!out) throw std::runtime_error("Can't open file");

	for (auto& [key, value] : data_) {
		out << key + "=" + value << std::endl;
	}
	// out should close automatically
}

void KVStore::save_binary(const fs::path& filepath) const {

	// for each entry, write: key_length (int), key (chars), value_length (int), value (chars)
	std::ofstream out(filepath, std::ios::binary);
	if (!out) throw std::runtime_error("Can't open file");

	for (auto& [key, value] : data_) {
		//out << key + "=" + value << std::endl;
		int key_length = key.length();                                                                                                                                                        
		int value_length = value.length(); 

		out.write(reinterpret_cast<const char*>(&key_length), sizeof(int)); // key length
		out.write(reinterpret_cast<const char*>(key.data()), key_length); // key
		out.write(reinterpret_cast<const char*>(&value_length), sizeof(int)); // value length
		out.write(reinterpret_cast<const char*>(value.data()), value_length); // value
	}
	// out should close automatically

}

void KVStore::load_binary(const fs::path& filepath) {
	clear(); // clear existing data

	// load data from file to data_
	std::ifstream in(filepath, std::ios::binary);
	if (!in) throw std::runtime_error("Can't open file");

	while (true) {
		int key_length;
		in.read(reinterpret_cast<char*>(&key_length), sizeof(int));
		if (!in) break;

		std::string key(key_length, '\0');
		in.read(key.data(), key_length);

		int value_length;
		in.read(reinterpret_cast<char*>(&value_length), sizeof(int));

		std::string value(value_length, '\0');
		in.read(value.data(), value_length);

		data_[key] = value;
	}

}

bool KVStore::file_exists() const {
	return fs::exists(filepath_);
}

std::uintmax_t KVStore::file_size() const {
	if (file_exists()) {
		return fs::file_size(filepath_);
	} else {
		throw std::runtime_error("File does not exist.");
	}
}

fs::path KVStore::filepath() const {
	return filepath_;
}

void KVStore::export_csv(const fs::path& filepath) const {
	std::cout << "key, value" << std::endl;
	std::ofstream out(filepath);
	if (!out) throw std::runtime_error("Can't open file");

	for (auto& [key, value] : data_) {
		out << key + "," + value << std::endl;
	}
	// out should close automatically
}

KVStore KVStore::from_csv(const fs::path& csv_path, const fs::path& store_path) {

	// load data from file to data_
	std::ifstream in(csv_path);
	if (!in) throw std::runtime_error("Can't open file");

	KVStore kvstore(store_path);


	std::string line;
	while (std::getline(in, line)) {
		if (!(line.find_first_not_of(' ') == std::string::npos || line.starts_with("#"))) {
			auto pos = line.find(',');
			std::string key = line.substr(0, pos);
			std::string value = line.substr(pos + 1);
			kvstore.set(key, value);
		}
	}

	return kvstore;
	
}
