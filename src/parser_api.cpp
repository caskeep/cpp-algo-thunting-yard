#include <parser_api.h>
#include <node.h>
#include <cctype>
#include <iostream>

namespace hkparser
{
class parser::impl {
  private:
    std::vector<internal::node> nodes_;

    int parser_from_formula_to_tokens(std::string formula, std::vector<std::string> &tokens);
  public:
    impl() = default;
    virtual ~impl() = default;

    int reload_formula(std::string formula);
    int get_value(const std::vector<double> &values, double &result);
};

int parser::impl::parser_from_formula_to_tokens(std::string formula, std::vector<std::string> &tokens) {
    if (formula.empty()) return -1;
    std::string token {};
    for (size_t i = 0; i < formula.size(); ++i) {
        const char c = formula[i];
        if (std::isdigit(c)) token.push_back(c);
        else if (token.empty()) tokens.push_back(std::string{c});
        else {
            tokens.push_back(token);
            tokens.push_back(std::string{c});
            token.clear();
        }
    }
    if (!token.empty()) tokens.push_back(token);
    std::cout << formula << " -> tokens\n";
    for (const auto& single_token : tokens) {
        std::cout << single_token << std::endl;
    }
    return 0;
}

int parser::impl::reload_formula(std::string formula) {
    std::vector<std::string> tokens;
    int parser_ret = parser_from_formula_to_tokens(formula, tokens) != 0;
    if (parser_ret != 0) return parser_ret;
    return 0;
}

int parser::impl::get_value(const std::vector<double> &values, double &result) {
    return 0;
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
    
} // namespace hkparser
