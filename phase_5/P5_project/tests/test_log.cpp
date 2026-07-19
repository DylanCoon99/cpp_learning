#include <gtest/gtest.h>
#include "log_entry.h"
#include "log_filter.h"
#include "log_stats.h"
#include "log_processor.h"
#include <fstream>

// === LogEntry::parse ===

TEST(LogEntryTest, ParseValidLine) {
    auto entry = LogEntry::parse("[2026-07-18 14:30:05] [ERROR] [db] Connection timeout");
    ASSERT_TRUE(entry.has_value());
    EXPECT_EQ(entry->timestamp, "2026-07-18 14:30:05");
    EXPECT_EQ(entry->level, "ERROR");
    EXPECT_EQ(entry->source, "db");
    EXPECT_EQ(entry->message, "Connection timeout");
}

TEST(LogEntryTest, ParseMalformedReturnsNullopt) {
    EXPECT_FALSE(LogEntry::parse("this is not a log line").has_value());
    EXPECT_FALSE(LogEntry::parse("").has_value());
    EXPECT_FALSE(LogEntry::parse("[incomplete").has_value());
}

// === LogFilter ===

TEST(LogFilterTest, EmptyFilterMatchesEverything) {
    LogFilter filter;
    LogEntry entry{"2026-07-18 14:30:05", "ERROR", "db", "timeout"};
    EXPECT_TRUE(filter.matches(entry));
}

TEST(LogFilterTest, LevelFilter) {
    LogFilter filter;
    filter.level("ERROR");
    LogEntry err{"2026-07-18 14:30:05", "ERROR", "db", "msg"};
    LogEntry info{"2026-07-18 14:30:05", "INFO", "db", "msg"};
    EXPECT_TRUE(filter.matches(err));
    EXPECT_FALSE(filter.matches(info));
}

TEST(LogFilterTest, SourceFilter) {
    LogFilter filter;
    filter.source("api");
    LogEntry api{"2026-07-18 14:30:05", "INFO", "api", "msg"};
    LogEntry db{"2026-07-18 14:30:05", "INFO", "db", "msg"};
    EXPECT_TRUE(filter.matches(api));
    EXPECT_FALSE(filter.matches(db));
}

TEST(LogFilterTest, ContainsFilter) {
    LogFilter filter;
    filter.contains("timeout");
    LogEntry match{"2026-07-18 14:30:05", "ERROR", "db", "Connection timeout after 5000ms"};
    LogEntry no_match{"2026-07-18 14:30:05", "INFO", "db", "Query OK"};
    EXPECT_TRUE(filter.matches(match));
    EXPECT_FALSE(filter.matches(no_match));
}

TEST(LogFilterTest, CombinedFilters) {
    LogFilter filter;
    filter.level("ERROR").source("db");
    LogEntry match{"2026-07-18 14:30:05", "ERROR", "db", "fail"};
    LogEntry wrong_level{"2026-07-18 14:30:05", "INFO", "db", "fail"};
    LogEntry wrong_source{"2026-07-18 14:30:05", "ERROR", "api", "fail"};
    EXPECT_TRUE(filter.matches(match));
    EXPECT_FALSE(filter.matches(wrong_level));
    EXPECT_FALSE(filter.matches(wrong_source));
}

TEST(LogFilterTest, TimeFilters) {
    LogFilter filter;
    filter.after("2026-07-18 12:00:00").before("2026-07-18 15:00:00");
    LogEntry in_range{"2026-07-18 13:00:00", "INFO", "api", "msg"};
    LogEntry too_early{"2026-07-18 11:00:00", "INFO", "api", "msg"};
    LogEntry too_late{"2026-07-18 16:00:00", "INFO", "api", "msg"};
    EXPECT_TRUE(filter.matches(in_range));
    EXPECT_FALSE(filter.matches(too_early));
    EXPECT_FALSE(filter.matches(too_late));
}

// === LogStats ===

TEST(LogStatsTest, RecordAndCount) {
    LogStats stats;
    stats.record({"t", "ERROR", "db", "msg1"});
    stats.record({"t", "INFO", "api", "msg2"});
    stats.record({"t", "ERROR", "db", "msg1"});
    EXPECT_EQ(stats.total(), 3);
    EXPECT_EQ(stats.count_by_level("ERROR"), 2);
    EXPECT_EQ(stats.count_by_level("INFO"), 1);
    EXPECT_EQ(stats.count_by_source("db"), 2);
}

TEST(LogStatsTest, MostCommon) {
    LogStats stats;
    stats.record({"t", "ERROR", "db", "msg"});
    stats.record({"t", "ERROR", "api", "msg"});
    stats.record({"t", "INFO", "api", "msg"});
    EXPECT_EQ(stats.most_common_level(), "ERROR");
    EXPECT_EQ(stats.most_common_source(), "api");
}

TEST(LogStatsTest, TopErrors) {
    LogStats stats;
    stats.record({"t", "ERROR", "db", "timeout"});
    stats.record({"t", "ERROR", "db", "timeout"});
    stats.record({"t", "ERROR", "db", "timeout"});
    stats.record({"t", "ERROR", "db", "disk full"});
    auto top = stats.top_errors(1);
    ASSERT_EQ(top.size(), 1);
    EXPECT_EQ(top[0], "timeout");
}

TEST(LogStatsTest, ThreadSafety) {
    LogStats stats;
    std::vector<std::thread> threads;
    for (int i = 0; i < 10; ++i) {
        threads.emplace_back([&stats]() {
            for (int j = 0; j < 100; ++j) {
                stats.record({"t", "INFO", "api", "msg"});
            }
        });
    }
    for (auto& t : threads) t.join();
    EXPECT_EQ(stats.total(), 1000);
}

// === LogProcessor ===

TEST(LogProcessorTest, ProcessFile) {
    // Create a temp log file
    fs::path tmp = "test_process.log";
    {
        std::ofstream out(tmp);
        out << "[2026-07-18 14:30:01] [INFO] [api] Request\n";
        out << "[2026-07-18 14:30:02] [ERROR] [db] Timeout\n";
        out << "[2026-07-18 14:30:03] [WARN] [auth] Bad token\n";
        out << "malformed line\n";
        out << "[2026-07-18 14:30:04] [INFO] [api] Response\n";
    }

    LogProcessor proc(2);
    LogFilter no_filter;
    auto stats = proc.process_file(tmp, no_filter);

    EXPECT_EQ(stats->total(), 4);  // malformed line skipped
    EXPECT_EQ(stats->count_by_level("INFO"), 2);
    EXPECT_EQ(stats->count_by_level("ERROR"), 1);

    fs::remove(tmp);
}
