#include <functional>
#include <stdexcept>
#include <tuple>
#include <cassert>
#include <vector>
#include <iostream>

#include "multiplication.hpp"

using multiplication_fn =
    std::function<digit_list(const digit_list&, const digit_list&)>;

void test_multiplication(multiplication_fn f,
                         const digit_list& num1,
                         const digit_list& num2,
                         const digit_list& expected) {
  assert(f(num1, num2) == expected);
}

// clang-format off
const std::vector<std::tuple<size_t, size_t, size_t>> tests = {
    {0, 0, 0},         
    {0, 123, 0},
    {123, 0, 0},           
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

void test_digit_list_addition() {
  assert(to_digit_list(0) + to_digit_list(0) == to_digit_list(0));
  assert(to_digit_list(1) + to_digit_list(0) == to_digit_list(1));
  assert(to_digit_list(0) + to_digit_list(1) == to_digit_list(1));

  assert(to_digit_list(2) + to_digit_list(3) == to_digit_list(5));
  assert(to_digit_list(9) + to_digit_list(1) == to_digit_list(10));
  assert(to_digit_list(99) + to_digit_list(1) == to_digit_list(100));
  assert(to_digit_list(999) + to_digit_list(1) == to_digit_list(1000));

  assert(to_digit_list(123) + to_digit_list(456) == to_digit_list(579));
  assert(to_digit_list(12345) + to_digit_list(67890) == to_digit_list(80235));
  assert(to_digit_list(99999) + to_digit_list(99999) == to_digit_list(199998));
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

  // assessment 
  {
    digit_list n1 = {3,1,4,1,5,9,2,6,5,3,5,8,9,7,9,3,2,3,8,4,6,2,6,4,3,3,8,3,2,7,9,5,0,2,8,8,4,1,9,7,1,6,9,3,9,9,3,7,5,1,0,5,8,2,0,9,7,4,9,4,4,5,9,2};
    digit_list n2 = {2,7,1,8,2,8,1,8,2,8,4,5,9,0,4,5,2,3,5,3,6,0,2,8,7,4,7,1,3,5,2,6,6,2,4,9,7,7,5,7,2,4,7,0,9,3,6,9,9,9,5,9,5,7,4,9,6,6,9,6,7,6,2,7};
    digit_list r = {8,5,3,9,7,3,4,2,2,2,6,7,3,5,6,7,0,6,5,4,6,3,5,5,0,8,6,9,5,4,6,5,7,4,4,9,5,0,3,4,8,8,8,5,3,5,7,6,5,1,1,4,9,6,1,8,7,9,6,0,1,1,2,7,0,6,7,7,4,3,0,4,4,8,9,3,2,0,4,8,4,8,6,1,7,8,7,5,0,7,2,2,1,6,2,4,9,0,7,3,0,1,3,3,7,4,8,9,5,8,7,1,9,5,2,8,0,6,5,8,2,7,2,3,1,8,4};
    test_multiplication(grade_school_product, n1, n2, r);
  }
  
  test_digit_list_subtraction();
  test_digit_list_addition();

  std::cout << "All multiplication tests passed\n";
}