#include <parser_api.h>
#include <node.h>
#include <cctype>
#include <iostream>
#include <stack>
#include <queue>

namespace hkparser
{
class parser::impl {
  private:
    std::vector<node> nodes_;

    int parser_from_formula_to_tokens(std::string formula, std::vector<node> &tokens);
  public:
    impl() = default;
    virtual ~impl() = default;

    int reload_formula(std::string formula);
    int get_value(const std::vector<double> &values, double &result);
    std::vector<node> get_nodes();
};

int parser::impl::parser_from_formula_to_tokens(std::string formula, std::vector<node> &tokens) {
    if (formula.empty()) return -1;
    std::string token {};
    for (size_t i = 0; i < formula.size(); ++i) {
        const char c = formula[i];
        if (std::isdigit(c))
            token.push_back(c);
        else if (token.empty())
            tokens.push_back(node::create_operation_node(std::string{c}));
        else {
            tokens.push_back(node::create_number_node(double(std::stoi(token))));
            tokens.push_back(node::create_operation_node(std::string{c}));
            token.clear();
        }
    }
    if (!token.empty())
        tokens.push_back(node::create_number_node(double(std::stoi(token))));
    return 0;
}

int parser::impl::reload_formula(std::string formula) {
    nodes_.clear();
    std::vector<node> nodes;
    std::stack<node> opt_stack;
    std::queue<node> output;
    int parser_ret = parser_from_formula_to_tokens(formula, nodes) != 0;
    if (parser_ret != 0) return parser_ret;
    for (const node &one : nodes) {
        if (one.get_node_type() == node::node_type::is_number)
            output.push(one);
        else if (one.opt_type() == node::operator_type::left_parenthesis)
            opt_stack.push(one);
        else if (one.opt_type() == node::operator_type::right_parenthesis) {
            while (!opt_stack.empty() && opt_stack.top().opt_type() != node::operator_type::left_parenthesis) {
                output.push(opt_stack.top());
                opt_stack.pop();
            }
            if (!opt_stack.empty()) {
                opt_stack.pop();
            }
        }
        else {
            while (!opt_stack.empty() && opt_stack.top().is_greater(one)) {
                output.push(opt_stack.top());
                opt_stack.pop();
            }
            opt_stack.push(one);
        }
    }
    while (!opt_stack.empty()) {
        output.push(opt_stack.top());
        opt_stack.pop();
    }
    while (!output.empty()) {
        nodes_.push_back(output.front());
        output.pop();
    }
    // log
    std::cout << formula << " -> tokens\n";
    std::cout << "node size:" << nodes_.size() << std::endl;
    for (node &one : nodes_) {
        std::cout << one.debug_info() << std::endl;
    }
    return 0;
}

int parser::impl::get_value(const std::vector<double> &values, double &result) {
    return 0;
}

std::vector<node> parser::impl::get_nodes() {
    return nodes_;
}

parser::parser() : pimpl_(new impl) {}

parser::parser(std::string formula) : parser() {
    reload_formula(formula);
}

parser::~parser() = default;

int parser::reload_formula(std::string formula) {
    return pimpl_->reload_formula(formula);
}

int parser::get_value(const std::vector<double> &values, double &result) {
    return pimpl_->get_value(values, result);
}

std::vector<node> parser::get_nodes() {
    return pimpl_->get_nodes();
}
    
} // namespace hkparser
