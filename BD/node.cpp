#include "node.h"

template<typename T>
bool compare(Comparison cmp, const T &lhs, const T &rhs) {
    switch (cmp) {
        case Comparison::Less: return lhs < rhs;
        case Comparison::LessOrEqual: return lhs <= rhs;
        case Comparison::Greater: return lhs > rhs;
        case Comparison::GreaterOrEqual: return lhs >= rhs;
        case Comparison::Equal: return lhs == rhs;
        case Comparison::NotEqual: return lhs != rhs;
        default: throw logic_error("Wrong comparison type");
    }
}

bool EmptyNode::Evaluate(const Date &cmp_date, const string &cmp_event) const {
    return true;
}

DateComparisonNode::DateComparisonNode(const Comparison &comparison, const Date &date) :
        comparison(comparison), date(date) {
}
bool DateComparisonNode::Evaluate(const Date &cmp_date, const string &cmp_event) const {
    return compare(comparison, cmp_date, date);
}

EventComparisonNode::EventComparisonNode(const Comparison &comparison, const string &event) :
        comparison(comparison), event(event) {
}
bool EventComparisonNode::Evaluate(const Date &cmp_date, const string &cmp_event) const {
    return compare(comparison, cmp_event, event);
}

LogicalOperationNode::LogicalOperationNode(LogicalOperation logical_operation,
                                           const shared_ptr<Node> &lhs,
                                           const shared_ptr<Node> &rhs
) :
        lhs(lhs), rhs(rhs), logical_operation(logical_operation) {
}
bool LogicalOperationNode::Evaluate(const Date &cmp_date, const string &cmp_event) const {
    bool left = lhs->Evaluate(cmp_date, cmp_event);
    bool right = rhs->Evaluate(cmp_date, cmp_event);
    if (logical_operation == LogicalOperation::And) {
        return left && right;
    } else if (logical_operation == LogicalOperation::Or) {
        return left || right;
    } else {
        throw logic_error("Wrong logic operation");
    }
}

