// Tests for Config parser
//
// Write tests covering:
//
// Parsing:
//   - Valid key=value lines are parsed correctly
//   - Comments (#) are skipped
//   - Blank lines are skipped
//   - Whitespace around = is trimmed
//   - Line without = throws ParseError
//   - Empty key throws ParseError
//
// String access:
//   - get() returns correct value
//   - get() throws KeyNotFoundError for missing key
//   - get_or() returns value if exists, default if not
//   - get_optional() returns value or nullopt
//   - has() returns true/false
//
// Typed access:
//   - get_int() parses integers correctly
//   - get_int() throws TypeError for non-integer values
//   - get_double() parses doubles correctly
//   - get_bool() accepts true/false/yes/no/1/0
//   - get_bool() throws TypeError for invalid values
//   - Default versions never throw
//
// Keys:
//   - keys() returns all keys
//   - keys_with_prefix() filters correctly
//
// Use fixtures: create a Config loaded with test data in SetUp.

#include <gtest/gtest.h>
#include "config.h"

// YOUR TESTS HERE
