#include <node.h>
#include <cassert>
#include <sstream>

namespace hkparser
{

node::node(node_type node_type, operator_type opt_type, double value)
    : node_type_(node_type)
    , opt_type_(opt_type)
    , value_(value)
{}

node node::create_number_node(double value) {
    return node { node::node_type::is_number, node::operator_type::none, value };
}

node node::create_operation_node(const std::string &token) {
    return node { node::node_type::is_operator, node::get_operator_from_token(token), .0 };
}

bool node::is_greater(const node &other) {
    return static_cast<int>(this->opt_type_) > static_cast<int>(other.opt_type_);
}

bool node::is_equal(const node &other) {
    return static_cast<int>(this->opt_type_) == static_cast<int>(other.opt_type_);
}

node::operator_type node::get_operator_from_token(const std::string &token) {
    if (token == "+") {
        return node::operator_type::plus;
    } else if (token == "-") {
        return node::operator_type::minus;
    } else if (token == "*") {
        return node::operator_type::multipy;
    } else if (token == "/") {
        return node::operator_type::division;
    } else {
        return node::operator_type::none;
    }
}

std::string node::debug_info() const {
    std::ostringstream oss;
    if (node_type_ == node_type::is_operator) {
        oss << "type:opt, opt:";
        switch (opt_type_)
        {
        case operator_type::division:
            oss << "/";
        break;
        case operator_type::minus:
            oss << "-";
        break;
        case operator_type::plus:
            oss << "+";
        break;
        case operator_type::multipy:
            oss << "*";
        break;
        }
    }
    else {
        oss << "type:num, val:" << value_;
    }
    return oss.str();
}

} // namespace hkparser