# Step 21: File I/O

## Concepts

You've used `std::ifstream` briefly in the config parser. This step covers the full I/O picture: text files, binary files, and the C++17 filesystem library.

### 1. Text File I/O

**Writing:**
```cpp
#include <fstream>

std::ofstream out("output.txt");
if (!out) throw std::runtime_error("Can't open file");

out << "Hello, file!\n";
out << "Value: " << 42 << "\n";
out.close();  // optional — closes automatically when out goes out of scope (RAII)
```

**Reading:**
```cpp
std::ifstream in("output.txt");
if (!in) throw std::runtime_error("Can't open file");

// Read line by line
std::string line;
while (std::getline(in, line)) {
    std::cout << line << "\n";
}

// Or read word by word
std::string word;
while (in >> word) {
    std::cout << word << "\n";
}
```

**Append mode:**
```cpp
std::ofstream out("log.txt", std::ios::app);  // append, don't overwrite
out << "New log entry\n";
```

### 2. File Open Modes

```cpp
std::ios::in       // read (default for ifstream)
std::ios::out      // write (default for ofstream)
std::ios::app      // append to end
std::ios::trunc    // truncate file (default with out)
std::ios::binary   // binary mode (no text translation)
std::ios::ate      // seek to end after opening

// Combine with |
std::fstream f("data.txt", std::ios::in | std::ios::out);  // read and write
```

### 3. `std::fstream` — Read and Write

```cpp
std::fstream file("data.txt", std::ios::in | std::ios::out);
// Can both read from and write to the same file
// Use seekg (get position) and seekp (put position) to navigate
```

### 4. Stream State

```cpp
std::ifstream in("file.txt");

in.good();   // no errors
in.eof();    // reached end of file
in.fail();   // last operation failed (format error or eof)
in.bad();    // unrecoverable error (disk failure, etc.)

// Check with bool conversion
if (in) { /* stream is good */ }
if (!in) { /* stream has an error */ }

// Clear error state
in.clear();

// Check after reading
int x;
if (in >> x) {
    // read succeeded
} else {
    // read failed (not an int, eof, etc.)
}
```

### 5. Binary File I/O

Text mode interprets data as characters. Binary mode reads/writes raw bytes — no text translation, no formatting.

**Writing binary:**
```cpp
std::ofstream out("data.bin", std::ios::binary);

int x = 42;
double pi = 3.14159;

// write raw bytes
out.write(reinterpret_cast<const char*>(&x), sizeof(x));
out.write(reinterpret_cast<const char*>(&pi), sizeof(pi));

// write a struct
struct Record { int id; double value; char name[32]; };
Record r = {1, 99.5, "test"};
out.write(reinterpret_cast<const char*>(&r), sizeof(r));
```

**Reading binary:**
```cpp
std::ifstream in("data.bin", std::ios::binary);

int x;
double pi;
in.read(reinterpret_cast<char*>(&x), sizeof(x));
in.read(reinterpret_cast<char*>(&pi), sizeof(pi));

Record r;
in.read(reinterpret_cast<char*>(&r), sizeof(r));
```

**`reinterpret_cast<const char*>(&x)`** — treats the memory of `x` as raw bytes. This is the low-level C++ way to serialize data. It's not portable across architectures (endianness, padding) but it's fast and simple.

### 6. Seeking

```cpp
std::fstream file("data.bin", std::ios::in | std::ios::out | std::ios::binary);

// Get current position
auto pos = file.tellg();   // get (read) position
auto pos2 = file.tellp();  // put (write) position

// Seek to position
file.seekg(0);                      // beginning of file
file.seekg(0, std::ios::end);       // end of file
file.seekg(-10, std::ios::cur);     // 10 bytes back from current
file.seekg(100, std::ios::beg);     // 100 bytes from beginning

// Get file size
file.seekg(0, std::ios::end);
auto size = file.tellg();
file.seekg(0, std::ios::beg);  // reset to beginning
```

### 7. `std::stringstream` — In-Memory Streams

Streams that read/write to strings instead of files. Useful for formatting and parsing:

```cpp
#include <sstream>

// Build a string with stream formatting
std::ostringstream oss;
oss << "Name: " << name << ", Age: " << age << ", Score: " << std::fixed << std::setprecision(1) << score;
std::string result = oss.str();

// Parse a string
std::istringstream iss("42 3.14 hello");
int i;
double d;
std::string s;
iss >> i >> d >> s;  // i=42, d=3.14, s="hello"
```

### 8. C++17 `<filesystem>`

A modern API for working with files and directories. Like Python's `os.path` and `pathlib`:

```cpp
#include <filesystem>
namespace fs = std::filesystem;

// Paths
fs::path p = "/Users/Dylan/Documents/file.txt";
p.filename();       // "file.txt"
p.extension();      // ".txt"
p.stem();           // "file"
p.parent_path();    // "/Users/Dylan/Documents"
p / "subdir";       // path concatenation with /

// Existence and type
fs::exists(p);              // true/false
fs::is_regular_file(p);     // true if it's a file
fs::is_directory(p);        // true if it's a directory
fs::file_size(p);           // size in bytes

// Create/remove
fs::create_directory("new_dir");
fs::create_directories("a/b/c");   // mkdir -p
fs::remove("file.txt");            // delete file
fs::remove_all("dir");             // rm -rf

// Copy/rename
fs::copy("src.txt", "dst.txt");
fs::rename("old.txt", "new.txt");

// Iterate directory
for (const auto& entry : fs::directory_iterator("some_dir")) {
    std::cout << entry.path() << "\n";
    if (entry.is_regular_file()) {
        std::cout << "  size: " << entry.file_size() << "\n";
    }
}

// Recursive iteration
for (const auto& entry : fs::recursive_directory_iterator("some_dir")) {
    std::cout << entry.path() << "\n";
}

// Temp directory
auto tmp = fs::temp_directory_path();
```

### 9. Error Handling with Filesystem

```cpp
// Option 1: exceptions (default)
try {
    fs::copy("nonexistent.txt", "dest.txt");
} catch (const fs::filesystem_error& e) {
    std::cerr << e.what() << "\n";
    std::cerr << "path1: " << e.path1() << "\n";
}

// Option 2: error codes (no exceptions)
std::error_code ec;
fs::copy("nonexistent.txt", "dest.txt", ec);
if (ec) {
    std::cerr << "Error: " << ec.message() << "\n";
}
```

---

## Exercise

One exercise: build a file-based key-value store that uses text and binary I/O with filesystem operations.
