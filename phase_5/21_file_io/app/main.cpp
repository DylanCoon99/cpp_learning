#include "kvstore.h"
#include <iostream>

int main() {
    fs::path store_path = "store.dat";
    fs::path binary_path = "store.bin";
    fs::path csv_path = "store.csv";

    // Clean up from previous runs
    if (fs::exists(store_path)) fs::remove(store_path);
    if (fs::exists(binary_path)) fs::remove(binary_path);
    if (fs::exists(csv_path)) fs::remove(csv_path);

    // === Create and populate ===
    std::cout << "=== Create Store ===\n";
    KVStore store(store_path);

    store.set("name", "Dylan");
    store.set("language", "C++");
    store.set("editor", "Xcode");
    store.set("os", "macOS");
    store.set("phase", "5");

    std::cout << "Size: " << store.size() << "\n";
    std::cout << "name: " << store.get("name").value_or("(not set)") << "\n";
    std::cout << "has 'editor': " << (store.has("editor") ? "yes" : "no") << "\n";
    std::cout << "has 'missing': " << (store.has("missing") ? "yes" : "no") << "\n";

    // === Save and reload (text) ===
    std::cout << "\n=== Save & Reload (text) ===\n";
    store.save();
    std::cout << "File exists: " << (store.file_exists() ? "yes" : "no") << "\n";
    std::cout << "File size: " << store.file_size() << " bytes\n";

    KVStore store2(store_path);  // loads from file in constructor
    std::cout << "Reloaded size: " << store2.size() << "\n";
    std::cout << "Reloaded name: " << store2.get("name").value_or("(not set)") << "\n";

    // === Binary save/load ===
    std::cout << "\n=== Binary Format ===\n";
    store.save_binary(binary_path);
    std::cout << "Binary file size: " << fs::file_size(binary_path) << " bytes\n";

    KVStore store3("store3.dat");
    store3.load_binary(binary_path);
    std::cout << "Loaded from binary, size: " << store3.size() << "\n";
    std::cout << "language: " << store3.get("language").value_or("(not set)") << "\n";

    // === CSV export/import ===
    std::cout << "\n=== CSV ===\n";
    store.export_csv(csv_path);
    std::cout << "CSV exported to " << csv_path << "\n";

    KVStore store4 = KVStore::from_csv(csv_path, "store4.dat");
    std::cout << "Imported from CSV, size: " << store4.size() << "\n";

    // === Keys listing ===
    std::cout << "\n=== All Keys ===\n";
    for (const auto& key : store.keys()) {
        std::cout << "  " << key << " = " << store.get(key).value_or("") << "\n";
    }

    // === Remove and clear ===
    std::cout << "\n=== Remove & Clear ===\n";
    store.remove("editor");
    std::cout << "After removing 'editor', size: " << store.size() << "\n";

    store.clear();
    std::cout << "After clear, size: " << store.size() << "\n";

    // Cleanup temp files
    for (auto& p : {"store.dat", "store.bin", "store.csv", "store3.dat", "store4.dat"}) {
        if (fs::exists(p)) fs::remove(p);
    }

    std::cout << "\nDone!\n";
}
