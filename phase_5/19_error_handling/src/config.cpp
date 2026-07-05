// Implement the Config class methods declared in config.h.
//
// Key things to practice:
//
// parse_line:
//   - Skip empty lines and lines starting with '#' (return std::nullopt)
//   - Find '=' to split key and value
//   - If no '=' found, throw ParseError with line number
//   - Trim whitespace from key and value
//   - If key is empty after trimming, throw ParseError
//
// load_string:
//   - Use std::istringstream to read line by line
//   - Track line numbers for error reporting
//   - Call parse_line for each line
//
// load_file:
//   - Open file with std::ifstream
//   - If file can't be opened, throw ConfigError
//   - Read line by line, call parse_line
//
// Typed getters:
//   - get_int: use std::stoi, catch std::invalid_argument/std::out_of_range → throw TypeError
//   - get_double: use std::stod, same pattern
//   - get_bool: accept "true"/"false"/"1"/"0"/"yes"/"no" (case-insensitive)
//     throw TypeError for anything else

#include "config.h"
#include <sstream>
#include <fstream>
#include <algorithm>

// YOUR CODE HERE
