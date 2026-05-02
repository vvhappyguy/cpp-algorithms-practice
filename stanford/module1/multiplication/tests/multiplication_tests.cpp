#include <algorithm>
#include <cassert>
#include <vector>
#include <iostream>

#include "multiplication.hpp"

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

void test_digit_list_subtraction() {
  assert(to_digit_list(1000) - to_digit_list(1) == to_digit_list(999));
  assert(to_digit_list(999) - to_digit_list(999) == to_digit_list(0));
  assert(to_digit_list(12345) - to_digit_list(123) == to_digit_list(12222));
  assert(to_digit_list(5000) - to_digit_list(4999) == to_digit_list(1));
  assert(to_digit_list(10) - to_digit_list(9) == to_digit_list(1));
  assert(to_digit_list(100000) - to_digit_list(1) == to_digit_list(99999));

  bool thrown = false;
  try {
    auto result = to_digit_list(100) - to_digit_list(999);
    (void)result;
  } catch (const std::invalid_argument&) {
    thrown = true;
  }

  assert(thrown);
}

int main() {
  for (const auto& test : tests) {
    test_multiplication(grade_school_product, to_digit_list(std::get<0>(test)),
                        to_digit_list(std::get<1>(test)),
                        to_digit_list(std::get<2>(test)));
    test_multiplication(recursive_product, to_digit_list(std::get<0>(test)),
                        to_digit_list(std::get<1>(test)),
                        to_digit_list(std::get<2>(test)));
    test_multiplication(karatsuba_product, to_digit_list(std::get<0>(test)),
                        to_digit_list(std::get<1>(test)),
                        to_digit_list(std::get<2>(test)));                        
  }
  test_digit_list_subtraction();

  std::cout << "All multiplication tests passed\n";
}