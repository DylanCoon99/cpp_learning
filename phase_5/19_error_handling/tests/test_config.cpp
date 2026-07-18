#include <gtest/gtest.h>
#include "config.h"

class ConfigTest : public ::testing::Test {
protected:
    void SetUp() override {
        config.load_string(R"(
# App settings
app.name = MyApp
app.version = 2.1

# Database
database.host = localhost
database.port = 5432

# Features
debug = true
verbose = false
max_retries = 3
timeout = 30.5
enabled = yes
disabled = no
flag_on = 1
flag_off = 0
)");
    }

    Config config;
};

// === Parsing ===

TEST(ConfigParsing, ValidKeyValueParsed) {
    Config c;
    c.load_string("key = value");
    EXPECT_EQ(c.get("key"), "value");
}

TEST(ConfigParsing, CommentsSkipped) {
    Config c;
    c.load_string("# this is a comment\nkey = value");
    EXPECT_EQ(c.size(), 1);
}

TEST(ConfigParsing, BlankLinesSkipped) {
    Config c;
    c.load_string("\n\n\nkey = value\n\n");
    EXPECT_EQ(c.size(), 1);
}

TEST(ConfigParsing, WhitespaceTrimmed) {
    Config c;
    c.load_string("  key  =  value  ");
    EXPECT_EQ(c.get("key"), "value");
}

TEST(ConfigParsing, NoEqualsThrowsParseError) {
    Config c;
    EXPECT_THROW(c.load_string("bad line without equals"), ParseError);
}

TEST(ConfigParsing, EmptyKeyThrowsParseError) {
    Config c;
    EXPECT_THROW(c.load_string(" = value"), ParseError);
}

TEST(ConfigParsing, FileNotFoundThrows) {
    Config c;
    EXPECT_THROW(c.load_file("nonexistent_file.conf"), ConfigError);
}

// === String Access ===

TEST_F(ConfigTest, GetReturnsValue) {
    EXPECT_EQ(config.get("app.name"), "MyApp");
    EXPECT_EQ(config.get("database.host"), "localhost");
}

TEST_F(ConfigTest, GetThrowsOnMissingKey) {
    EXPECT_THROW(config.get("nonexistent"), KeyNotFoundError);
}

TEST_F(ConfigTest, GetOrReturnsValueIfExists) {
    EXPECT_EQ(config.get_or("app.name", "default"), "MyApp");
}

TEST_F(ConfigTest, GetOrReturnsDefaultIfMissing) {
    EXPECT_EQ(config.get_or("missing", "fallback"), "fallback");
}

TEST_F(ConfigTest, GetOptionalReturnsValueIfExists) {
    auto result = config.get_optional("app.name");
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(*result, "MyApp");
}

TEST_F(ConfigTest, GetOptionalReturnsNulloptIfMissing) {
    auto result = config.get_optional("missing");
    EXPECT_FALSE(result.has_value());
}

TEST_F(ConfigTest, HasReturnsTrueForExistingKey) {
    EXPECT_TRUE(config.has("app.name"));
}

TEST_F(ConfigTest, HasReturnsFalseForMissingKey) {
    EXPECT_FALSE(config.has("missing"));
}

// === Typed Access — int ===

TEST_F(ConfigTest, GetIntParsesCorrectly) {
    EXPECT_EQ(config.get_int("database.port"), 5432);
    EXPECT_EQ(config.get_int("max_retries"), 3);
}

TEST_F(ConfigTest, GetIntThrowsTypeErrorOnNonInt) {
    EXPECT_THROW(config.get_int("app.name"), TypeError);
}

TEST_F(ConfigTest, GetIntOrReturnsValueIfValid) {
    EXPECT_EQ(config.get_int_or("database.port", 9999), 5432);
}

TEST_F(ConfigTest, GetIntOrReturnsDefaultIfMissing) {
    EXPECT_EQ(config.get_int_or("missing", 42), 42);
}

TEST_F(ConfigTest, GetIntOrReturnsDefaultIfInvalid) {
    EXPECT_EQ(config.get_int_or("app.name", 42), 42);
}

// === Typed Access — double ===

TEST_F(ConfigTest, GetDoubleParsesCorrectly) {
    EXPECT_DOUBLE_EQ(config.get_double("timeout"), 30.5);
}

TEST_F(ConfigTest, GetDoubleThrowsTypeErrorOnNonDouble) {
    EXPECT_THROW(config.get_double("app.name"), TypeError);
}

TEST_F(ConfigTest, GetDoubleOrReturnsDefault) {
    EXPECT_DOUBLE_EQ(config.get_double_or("missing", 1.5), 1.5);
}

// === Typed Access — bool ===

TEST_F(ConfigTest, GetBoolParsesTrue) {
    EXPECT_TRUE(config.get_bool("debug"));
    EXPECT_TRUE(config.get_bool("enabled"));
    EXPECT_TRUE(config.get_bool("flag_on"));
}

TEST_F(ConfigTest, GetBoolParsesFalse) {
    EXPECT_FALSE(config.get_bool("verbose"));
    EXPECT_FALSE(config.get_bool("disabled"));
    EXPECT_FALSE(config.get_bool("flag_off"));
}

TEST_F(ConfigTest, GetBoolThrowsTypeErrorOnInvalid) {
    EXPECT_THROW(config.get_bool("app.name"), TypeError);
}

TEST_F(ConfigTest, GetBoolOrReturnsDefault) {
    EXPECT_TRUE(config.get_bool_or("missing", true));
    EXPECT_FALSE(config.get_bool_or("missing", false));
}

// === Keys ===

TEST_F(ConfigTest, KeysReturnsAllKeys) {
    auto k = config.keys();
    EXPECT_GT(k.size(), 0);
}

TEST_F(ConfigTest, KeysWithPrefixFilters) {
    auto db_keys = config.keys_with_prefix("database.");
    EXPECT_EQ(db_keys.size(), 2);
}

TEST_F(ConfigTest, KeysWithPrefixNoMatch) {
    auto k = config.keys_with_prefix("nonexistent.");
    EXPECT_EQ(k.size(), 0);
}

// === Set ===

TEST_F(ConfigTest, SetAddsNewKey) {
    config.set("new_key", "new_value");
    EXPECT_EQ(config.get("new_key"), "new_value");
}

TEST_F(ConfigTest, SetOverwritesExistingKey) {
    config.set("app.name", "NewApp");
    EXPECT_EQ(config.get("app.name"), "NewApp");
}

// === Size ===

TEST_F(ConfigTest, SizeReturnsCorrectCount) {
    EXPECT_EQ(config.size(), 11);
}
