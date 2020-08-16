
#include <parser_api.h>
#include <iostream>
#include <cassert>

void test_1() {
    hkparser::parser parser_1;
    assert(parser_1.reload_formula("1+2") == 0 && "formula 1+2 load fail");
    auto nodes = parser_1.get_nodes();
    std::cout << nodes.size() << std::endl;
    assert(nodes.size() == 3 && "formual 1+2 must has 3 nodes");
    assert(nodes[0].get_node_type() == hkparser::node::node_type::is_number && "formula 1+2 [0] is not number");
}

void test_2() {
    hkparser::parser parser_1;
    assert(parser_1.reload_formula("1+2") == 0);
    std::vector<double> values = {1.0, 2.0};
    double result = .0;
    assert(parser_1.get_value(values, result) == 0);
    assert(result == 3.0);
    values = {1};
    assert(parser_1.get_value(values, result) == -1);
    hkparser::parser parser_2 {std::string("3+4*2")};
}

int main() {
    std::cout << "start shunting yard test" << std::endl;
    test_1();
    // test_2();
    return 0;
}
