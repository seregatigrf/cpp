#pragma once

#include "date.h"
#include <memory>

enum class Comparison {
    Less,
    LessOrEqual,
    Greater,
    GreaterOrEqual,
    Equal,
    NotEqual
};

enum class LogicalOperation {
    And,
    Or
};

template<typename T>
bool compare(Comparison cmp, const T &lhs, const T &rhs);

class Node {
public:
    virtual bool Evaluate(const Date &cmp_date, const string &cmp_event) const = 0;
};

class EmptyNode : public Node {
public:
    EmptyNode() = default;
    bool Evaluate(const Date &cmp_date, const string &cmp_event) const override;
};

class DateComparisonNode : public Node {
public:
    DateComparisonNode(const Comparison &comparison, const Date &date);

    bool Evaluate(const Date &cmp_date, const string &cmp_event) const override;
private:
    const Comparison comparison;
    const Date date;
};

class EventComparisonNode : public Node {
public:
    EventComparisonNode(const Comparison &comparison, const string &event);
    bool Evaluate(const Date &cmp_date, const string &cmp_event) const override;

private:
    const Comparison comparison;
    const string event;
};

class LogicalOperationNode : public Node {
public:
    LogicalOperationNode(LogicalOperation logical_operation, const shared_ptr<Node> &lhs, const shared_ptr<Node> &rhs);
    bool Evaluate(const Date &cmp_date, const string &cmp_event) const override;
private:
    LogicalOperation logical_operation;
    shared_ptr<Node> lhs;
    shared_ptr<Node> rhs;
};
