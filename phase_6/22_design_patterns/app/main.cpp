#include "pipeline.h"
#include "stages.h"
#include <iostream>

// A simple observer that logs pipeline activity
class LoggingObserver : public PipelineObserver {
public:
    void on_record_processed(const std::string& stage_name, const Record& record) override {
        std::cout << "  [" << stage_name << "] processed: " << record << "\n";
    }
    void on_record_dropped(const std::string& stage_name, const Record& record) override {
        std::cout << "  [" << stage_name << "] DROPPED: " << record << "\n";
    }
    void on_pipeline_complete(int total_in, int total_out) override {
        std::cout << "Pipeline complete: " << total_in << " in, " << total_out << " out\n";
    }
};

// A counting observer (no output, just counts)
class CountingObserver : public PipelineObserver {
public:
    void on_record_processed(const std::string&, const Record&) override { ++processed_; }
    void on_record_dropped(const std::string&, const Record&) override { ++dropped_; }
    void on_pipeline_complete(int, int) override {}

    int processed() const { return processed_; }
    int dropped() const { return dropped_; }
private:
    int processed_ = 0;
    int dropped_ = 0;
};

int main() {
    // Sample data
    std::vector<Record> data = {
        {{{ "name", "Alice" }, { "email", "alice@example.com" }, { "role", "engineer" }}},
        {{{ "name", "Bob" }, { "role", "manager" }}},  // no email
        {{{ "name", "Carol" }, { "email", "carol@example.com" }, { "role", "engineer" }}},
        {{{ "name", "Dan" }, { "email", "DAN@EXAMPLE.COM" }, { "role", "designer" }}},
        {{{ "name", "Eve" }, { "email", "eve@example.com" }, { "role", "engineer" }}},
    };

    // === Pipeline 1: Filter engineers with emails ===
    std::cout << "=== Pipeline 1: Engineers with emails ===\n";
    auto observer = std::make_shared<LoggingObserver>();

    auto pipeline = Pipeline::Builder()
        .add_stage(std::make_unique<RequireFieldStage>("email"))
        .add_stage(std::make_unique<FilterStage>("role", "engineer"))
        .add_stage(std::make_unique<AddFieldStage>("status", "active"))
        .add_observer(observer)
        .build();

    auto results = pipeline.run(data);

    std::cout << "\nResults:\n";
    for (const auto& r : results) {
        std::cout << "  " << r << "\n";
    }

    // === Pipeline 2: Transform and rename ===
    std::cout << "\n=== Pipeline 2: Transform emails to lowercase, rename role ===\n";
    auto counter = std::make_shared<CountingObserver>();

    auto pipeline2 = Pipeline::Builder()
        .add_stage(std::make_unique<RequireFieldStage>("email"))
        .add_stage(std::make_unique<TransformFieldStage>("email", [](const std::string& s) {
            std::string lower = s;
            std::transform(lower.begin(), lower.end(), lower.begin(),
                [](unsigned char c) { return std::tolower(c); });
            return lower;
        }))
        .add_stage(std::make_unique<RenameFieldStage>("role", "position"))
        .add_observer(counter)
        .build();

    auto results2 = pipeline2.run(data);

    std::cout << "Results:\n";
    for (const auto& r : results2) {
        std::cout << "  " << r << "\n";
    }
    std::cout << "Processed: " << counter->processed() << ", Dropped: " << counter->dropped() << "\n";

    // === Factory demo ===
    std::cout << "\n=== Factory Demo ===\n";
    StageFactory factory;
    factory.register_stage("passthrough", [](const auto&) {
        return std::make_unique<PassthroughStage>();
    });
    factory.register_stage("require", [](const auto& config) {
        return std::make_unique<RequireFieldStage>(config.at("field"));
    });
    factory.register_stage("filter", [](const auto& config) {
        return std::make_unique<FilterStage>(config.at("field"), config.at("value"));
    });

    std::cout << "Available stages: ";
    for (const auto& name : factory.available()) {
        std::cout << name << " ";
    }
    std::cout << "\n";

    // Create stages from config (simulating loading from a config file)
    auto stage1 = factory.create("require", {{"field", "name"}});
    auto stage2 = factory.create("filter", {{"field", "role"}, {"value", "engineer"}});

    auto pipeline3 = Pipeline::Builder()
        .add_stage(std::move(stage1))
        .add_stage(std::move(stage2))
        .build();

    auto results3 = pipeline3.run(data);
    std::cout << "Factory pipeline results: " << results3.size() << " records\n";
}
