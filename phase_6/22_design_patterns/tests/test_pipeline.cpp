#include <gtest/gtest.h>
#include "pipeline.h"
#include "stages.h"

// === Stage tests ===

TEST(StagesTest, PassthroughReturnsRecord) {
    PassthroughStage stage;
    Record r;
    r.set("key", "value");
    auto result = stage.process(r);
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result->get("key"), "value");
}

TEST(StagesTest, RequireFieldDropsMissing) {
    RequireFieldStage stage("email");
    Record with_email;
    with_email.set("email", "test@test.com");
    Record without_email;
    without_email.set("name", "Alice");

    EXPECT_TRUE(stage.process(with_email).has_value());
    EXPECT_FALSE(stage.process(without_email).has_value());
}

TEST(StagesTest, FilterMatchesCorrectValue) {
    FilterStage stage("role", "engineer");
    Record match;
    match.set("role", "engineer");
    Record no_match;
    no_match.set("role", "manager");

    EXPECT_TRUE(stage.process(match).has_value());
    EXPECT_FALSE(stage.process(no_match).has_value());
}

TEST(StagesTest, AddFieldAddsNewField) {
    AddFieldStage stage("status", "active");
    Record r;
    r.set("name", "Alice");
    auto result = stage.process(r);
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result->get("status"), "active");
    EXPECT_EQ(result->get("name"), "Alice");
}

TEST(StagesTest, RenameFieldMovesValue) {
    RenameFieldStage stage("role", "position");
    Record r;
    r.set("role", "engineer");
    auto result = stage.process(r);
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result->get("position"), "engineer");
    EXPECT_FALSE(result->has("role"));
}

TEST(StagesTest, TransformFieldAppliesFunction) {
    TransformFieldStage stage("name", [](const std::string& s) {
        std::string upper = s;
        std::transform(upper.begin(), upper.end(), upper.begin(), ::toupper);
        return upper;
    });
    Record r;
    r.set("name", "alice");
    auto result = stage.process(r);
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result->get("name"), "ALICE");
}

// === Factory tests ===

TEST(FactoryTest, CreateRegisteredStage) {
    StageFactory factory;
    factory.register_stage("passthrough", [](const auto&) {
        return std::make_unique<PassthroughStage>();
    });
    auto stage = factory.create("passthrough");
    ASSERT_NE(stage, nullptr);
    EXPECT_EQ(stage->name(), "passthrough");
}

TEST(FactoryTest, CreateUnregisteredReturnsNull) {
    StageFactory factory;
    EXPECT_EQ(factory.create("nonexistent"), nullptr);
}

TEST(FactoryTest, AvailableListsRegistered) {
    StageFactory factory;
    factory.register_stage("a", [](const auto&) { return std::make_unique<PassthroughStage>(); });
    factory.register_stage("b", [](const auto&) { return std::make_unique<PassthroughStage>(); });
    auto names = factory.available();
    EXPECT_EQ(names.size(), 2);
}

// === Pipeline tests ===

TEST(PipelineTest, EmptyPipelinePassesThrough) {
    auto pipeline = Pipeline::Builder().build();
    std::vector<Record> input = {Record{{{ "a", "1" }}}};
    auto output = pipeline.run(input);
    EXPECT_EQ(output.size(), 1);
}

TEST(PipelineTest, StagesAppliedInOrder) {
    auto pipeline = Pipeline::Builder()
        .add_stage(std::make_unique<AddFieldStage>("x", "1"))
        .add_stage(std::make_unique<AddFieldStage>("y", "2"))
        .build();

    auto output = pipeline.run({Record{}});
    ASSERT_EQ(output.size(), 1);
    EXPECT_EQ(output[0].get("x"), "1");
    EXPECT_EQ(output[0].get("y"), "2");
}

TEST(PipelineTest, FilterDropsRecords) {
    auto pipeline = Pipeline::Builder()
        .add_stage(std::make_unique<FilterStage>("role", "engineer"))
        .build();

    std::vector<Record> input = {
        Record{{{ "role", "engineer" }}},
        Record{{{ "role", "manager" }}},
        Record{{{ "role", "engineer" }}},
    };

    auto output = pipeline.run(input);
    EXPECT_EQ(output.size(), 2);
}

TEST(PipelineTest, ObserverNotified) {
    class TestObserver : public PipelineObserver {
    public:
        int processed = 0, dropped = 0, completed = 0;
        void on_record_processed(const std::string&, const Record&) override { ++processed; }
        void on_record_dropped(const std::string&, const Record&) override { ++dropped; }
        void on_pipeline_complete(int, int) override { ++completed; }
    };

    auto obs = std::make_shared<TestObserver>();
    auto pipeline = Pipeline::Builder()
        .add_stage(std::make_unique<RequireFieldStage>("email"))
        .add_observer(obs)
        .build();

    std::vector<Record> input = {
        Record{{{ "email", "a@b.com" }}},
        Record{{{ "name", "no email" }}},
    };

    pipeline.run(input);
    EXPECT_EQ(obs->processed, 1);
    EXPECT_EQ(obs->dropped, 1);
    EXPECT_EQ(obs->completed, 1);
}
