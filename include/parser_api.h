#pragma once

#include <string>
#include <memory>
#include <vector>

namespace hkparser
{
class parser {
  private:
    class impl;
    std::unique_ptr<impl> pimpl_;
  public:
    parser();
    parser(std::string formula);
    ~parser();

    int reload_formula(std::string formula);
    int get_value(const std::vector<double> &values, double &result);
};
} // namespace hkparser
