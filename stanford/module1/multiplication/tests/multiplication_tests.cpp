#include <vector>
#include <algorithm>
#include <cassert>

#include "../include/multiplication.hpp"

void test_multiplication(
    std::function<digit_list(const digit_list&, const digit_list&)> f,
    const digit_list& num1, const digit_list& num2, const digit_list& result) {
  assert(f(num1, num2) == result);
}

// clang-format off
const std::vector<std::tuple<size_t, size_t, size_t>> tests = {
    {0, 0, 0},         
    {0, 123, 0},           
    {1, 99999, 99999},  
    {9, 9, 81},
    {10, 10, 100},     
    {99, 99, 9801},        
    {999, 999, 998001}, 
    {12, 34, 408},
    {123, 456, 56088}, 
    {1234, 5678, 7006652},
};
// clang-format on

int main() {
  for (const auto& test : tests) {
    test_multiplication(grade_school_product, to_digit_list(std::get<0>(test)),
                        to_digit_list(std::get<1>(test)),
                        to_digit_list(std::get<2>(test)));
    test_multiplication(recursive_product, to_digit_list(std::get<0>(test)),
                        to_digit_list(std::get<1>(test)),
                        to_digit_list(std::get<2>(test)));
  }
}