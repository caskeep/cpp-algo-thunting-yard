#include <parser_api.h>
#include <node.h>

namespace hkparser
{
class parser::impl {
  private:
    std::vector<internal::node> nodes_;
  public:
    impl() = default;
    virtual ~impl() = default;

    int reload_formula(std::string formula);
    int get_value(const std::vector<double> &values, double &result);
};

int parser::impl::reload_formula(std::string formula) {
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
    // return impl_->reload_formula(formula);
    return 0;
}

int parser::get_value(const std::vector<double> &values, double &result) {
    return .0;
}
    
} // namespace hkparser
