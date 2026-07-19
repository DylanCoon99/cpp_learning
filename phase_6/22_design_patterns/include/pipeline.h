#pragma once

#include <string>
#include <vector>
#include <map>
#include <memory>
#include <functional>
#include <iostream>
#include <optional>

// A data processing pipeline that uses multiple design patterns:
//   - Factory: register and create pipeline stages by name
//   - Strategy: stages are interchangeable processing steps
//   - Builder: construct pipelines fluently
//   - Observer: notify listeners on pipeline events
//   - Command: stages are executable/undoable operations on data
//   - Decorator: stages can wrap other stages

// The data type flowing through the pipeline
struct Record {
    std::map<std::string, std::string> fields;

    std::string get(const std::string& key) const {
        auto it = fields.find(key);
        return (it != fields.end()) ? it->second : "";
    }

    void set(const std::string& key, const std::string& value) {
        fields[key] = value;
    }

    bool has(const std::string& key) const {
        return fields.contains(key);
    }

    friend std::ostream& operator<<(std::ostream& os, const Record& r) {
        os << "{";
        bool first = true;
        for (const auto& [k, v] : r.fields) {
            if (!first) os << ", ";
            os << k << ": " << v;
            first = false;
        }
        os << "}";
        return os;
    }
};


// === Strategy Pattern: Pipeline Stage interface ===
class Stage {
public:
    virtual std::optional<Record> process(const Record& record) = 0;
    // Returns nullopt to drop the record, or a modified record to keep it
    virtual std::string name() const = 0;
    virtual ~Stage() = default;
};


// === Factory Pattern: Stage registry ===
class StageFactory {
public:
    using Creator = std::function<std::unique_ptr<Stage>(const std::map<std::string, std::string>& config)>;

    void register_stage(const std::string& name, Creator creator);
    std::unique_ptr<Stage> create(const std::string& name,
                                  const std::map<std::string, std::string>& config = {}) const;
    std::vector<std::string> available() const;

private:
    std::map<std::string, Creator> creators_;
};


// === Observer Pattern: Pipeline events ===
class PipelineObserver {
public:
    virtual void on_record_processed(const std::string& stage_name, const Record& record) = 0;
    virtual void on_record_dropped(const std::string& stage_name, const Record& record) = 0;
    virtual void on_pipeline_complete(int total_in, int total_out) = 0;
    virtual ~PipelineObserver() = default;
};


// === Builder Pattern: Pipeline construction ===
class Pipeline {
public:
    class Builder {
    public:
        Builder& add_stage(std::unique_ptr<Stage> stage);
        Builder& add_observer(std::shared_ptr<PipelineObserver> observer);
        Pipeline build();

    private:
        std::vector<std::unique_ptr<Stage>> stages_;
        std::vector<std::shared_ptr<PipelineObserver>> observers_;
    };

    // Run all records through all stages in order
    std::vector<Record> run(const std::vector<Record>& input);

    int stages_count() const;

private:
    Pipeline(std::vector<std::unique_ptr<Stage>> stages,
             std::vector<std::shared_ptr<PipelineObserver>> observers);

    std::vector<std::unique_ptr<Stage>> stages_;
    std::vector<std::shared_ptr<PipelineObserver>> observers_;

    void notify_processed(const std::string& stage, const Record& r);
    void notify_dropped(const std::string& stage, const Record& r);
    void notify_complete(int in, int out);
};
