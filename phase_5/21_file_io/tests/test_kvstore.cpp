#include <gtest/gtest.h>
#include "kvstore.h"

class KVStoreTest : public ::testing::Test {
protected:
    fs::path test_path = "test_store.dat";
    fs::path bin_path = "test_store.bin";
    fs::path csv_path = "test_store.csv";

    void SetUp() override {
        // Clean up any leftover files
        for (auto& p : {test_path, bin_path, csv_path}) {
            if (fs::exists(p)) fs::remove(p);
        }
    }

    void TearDown() override {
        for (auto& p : {test_path, bin_path, csv_path}) {
            if (fs::exists(p)) fs::remove(p);
        }
    }
};

// === Basic operations ===

TEST_F(KVStoreTest, SetAndGet) {
    KVStore store(test_path);
    store.set("key", "value");
    auto result = store.get("key");
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(*result, "value");
}

TEST_F(KVStoreTest, GetMissingReturnsNullopt) {
    KVStore store(test_path);
    EXPECT_FALSE(store.get("nonexistent").has_value());
}

TEST_F(KVStoreTest, HasExistingKey) {
    KVStore store(test_path);
    store.set("key", "value");
    EXPECT_TRUE(store.has("key"));
    EXPECT_FALSE(store.has("missing"));
}

TEST_F(KVStoreTest, RemoveKey) {
    KVStore store(test_path);
    store.set("key", "value");
    EXPECT_TRUE(store.remove("key"));
    EXPECT_FALSE(store.has("key"));
}

TEST_F(KVStoreTest, RemoveMissingReturnsFalse) {
    KVStore store(test_path);
    EXPECT_FALSE(store.remove("nonexistent"));
}

TEST_F(KVStoreTest, SizeAndClear) {
    KVStore store(test_path);
    store.set("a", "1");
    store.set("b", "2");
    store.set("c", "3");
    EXPECT_EQ(store.size(), 3);

    store.clear();
    EXPECT_EQ(store.size(), 0);
}

TEST_F(KVStoreTest, OverwriteValue) {
    KVStore store(test_path);
    store.set("key", "old");
    store.set("key", "new");
    EXPECT_EQ(*store.get("key"), "new");
    EXPECT_EQ(store.size(), 1);
}

TEST_F(KVStoreTest, KeysReturnsAllKeys) {
    KVStore store(test_path);
    store.set("b", "2");
    store.set("a", "1");
    store.set("c", "3");
    auto k = store.keys();
    EXPECT_EQ(k.size(), 3);
}

// === Text persistence ===

TEST_F(KVStoreTest, SaveAndLoad) {
    {
        KVStore store(test_path);
        store.set("name", "Dylan");
        store.set("lang", "C++");
        store.save();
    }
    KVStore store2(test_path);
    EXPECT_EQ(store2.size(), 2);
    EXPECT_EQ(*store2.get("name"), "Dylan");
    EXPECT_EQ(*store2.get("lang"), "C++");
}

TEST_F(KVStoreTest, FileExistsAfterSave) {
    KVStore store(test_path);
    EXPECT_FALSE(store.file_exists());
    store.set("key", "value");
    store.save();
    EXPECT_TRUE(store.file_exists());
}

TEST_F(KVStoreTest, FileSizeIsPositiveAfterSave) {
    KVStore store(test_path);
    store.set("key", "value");
    store.save();
    EXPECT_GT(store.file_size(), 0);
}

// === Binary persistence ===

TEST_F(KVStoreTest, BinarySaveAndLoad) {
    KVStore store(test_path);
    store.set("x", "100");
    store.set("pi", "3.14159");
    store.save_binary(bin_path);

    KVStore store2("temp.dat");
    store2.load_binary(bin_path);
    EXPECT_EQ(store2.size(), 2);
    EXPECT_EQ(*store2.get("x"), "100");
    EXPECT_EQ(*store2.get("pi"), "3.14159");

    if (fs::exists("temp.dat")) fs::remove("temp.dat");
}

// === CSV ===

TEST_F(KVStoreTest, CsvExportAndImport) {
    KVStore store(test_path);
    store.set("a", "1");
    store.set("b", "2");
    store.export_csv(csv_path);

    KVStore store2 = KVStore::from_csv(csv_path, "csv_import.dat");
    EXPECT_EQ(store2.size(), 2);
    EXPECT_EQ(*store2.get("a"), "1");
    EXPECT_EQ(*store2.get("b"), "2");

    if (fs::exists("csv_import.dat")) fs::remove("csv_import.dat");
}
