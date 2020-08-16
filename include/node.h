#pragma once

#include <string>

namespace hkparser
{
class node {
  public:
    enum class node_type { is_number, is_operator, };
    enum class operator_type { none, plus, minus, multipy, division, left_parenthesis, right_parenthesis, };
  private:
    node_type node_type_;
    operator_type opt_type_;
    double value_;
  public:
    node(node_type node_type, operator_type opt_type, double value);
    static node create_number_node(double value);
    static node create_operation_node(const std::string &token);

    bool is_greater(const node &other);
    bool is_equal(const node &other);
    static operator_type get_operator_from_token(const std::string &token);

    node_type get_node_type() const { return node_type_; }
    operator_type opt_type() const { return opt_type_; }
    double value() const { return value_; }

    std::string debug_info() const;
};
    
} // namespace hkparser
