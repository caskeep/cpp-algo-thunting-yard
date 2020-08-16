#pragma once

#include <string>
#include <vector>

namespace hkparser
{
class parser {
  public:
    parser() = default;
    parser(std::string formula);

    int reload_formula(std::string formula);
    int get_value(const std::vector<double> &values, double &result);
};
} // namespace hkparser
