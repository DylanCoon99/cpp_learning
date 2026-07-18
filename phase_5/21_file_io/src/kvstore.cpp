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
#include <stdexcept>

// YOUR CODE HERE
