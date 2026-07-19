#pragma once

#include "pipeline.h"
#include <algorithm>
#include <cctype>

// Built-in pipeline stages — implement each one.
// These demonstrate the Strategy pattern: each is a different algorithm
// behind the same Stage interface.

// Passes all records through unchanged. Useful as a base case.
class PassthroughStage : public Stage {
public:
    std::optional<Record> process(const Record& record) override;
    std::string name() const override { return "passthrough"; }
};

// Drops records that don't have a required field.
class RequireFieldStage : public Stage {
public:
    explicit RequireFieldStage(const std::string& field) : field_(field) {}
    std::optional<Record> process(const Record& record) override;
    std::string name() const override { return "require:" + field_; }
private:
    std::string field_;
};

// Drops records where a field doesn't match an expected value.
class FilterStage : public Stage {
public:
    FilterStage(const std::string& field, const std::string& value)
        : field_(field), value_(value) {}
    std::optional<Record> process(const Record& record) override;
    std::string name() const override { return "filter:" + field_ + "=" + value_; }
private:
    std::string field_, value_;
};

// Adds a new field with a fixed value to every record.
class AddFieldStage : public Stage {
public:
    AddFieldStage(const std::string& field, const std::string& value)
        : field_(field), value_(value) {}
    std::optional<Record> process(const Record& record) override;
    std::string name() const override { return "add:" + field_; }
private:
    std::string field_, value_;
};

// Renames a field.
class RenameFieldStage : public Stage {
public:
    RenameFieldStage(const std::string& from, const std::string& to)
        : from_(from), to_(to) {}
    std::optional<Record> process(const Record& record) override;
    std::string name() const override { return "rename:" + from_ + "->" + to_; }
private:
    std::string from_, to_;
};

// Transforms a field's value using a function.
class TransformFieldStage : public Stage {
public:
    TransformFieldStage(const std::string& field,
                        std::function<std::string(const std::string&)> transform)
        : field_(field), transform_(std::move(transform)) {}
    std::optional<Record> process(const Record& record) override;
    std::string name() const override { return "transform:" + field_; }
private:
    std::string field_;
    std::function<std::string(const std::string&)> transform_;
};
