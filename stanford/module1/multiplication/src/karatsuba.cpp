#include <algorithm>
#include <cstddef>
#include <iterator>
#include <stdexcept>

#include "multiplication.hpp"

namespace {

bool is_zero(const digit_list& n) {
  for (size_t d : n) {
    if (d != 0) {
      return false;
    }
  }
  return true;
}

digit_list karatsuba_product_impl(const digit_list& num1,
                                  const digit_list& num2);

digit_list karatsuba_product_impl(const digit_list& num1,
                                  const digit_list& num2) {
  if (num1.empty() || num2.empty()) {
    throw std::invalid_argument("empty digit_list is not a valid number");
  }

  if (is_zero(num1) || is_zero(num2)) {
    return {0};
  }

  constexpr size_t karatsuba_cutoff = 32;

  if (std::max(num1.size(), num2.size()) <= karatsuba_cutoff) {
    return grade_school_product(num1, num2);
  }

  // Simple production one digit
  if (num1.size() == 1 && num2.size() == 1) {
    size_t simple_prod = num1.front() * num2.front();

    if (simple_prod == 0) {
      return {0};
    }

    digit_list result;
    while (simple_prod > 0) {
      result.push_front(simple_prod % 10);
      simple_prod /= 10;
    }

    return result;
  }

  // Find amount of numbers in lists and make them the same size
  size_t numbers_count = std::max(num1.size(), num2.size());
  if (numbers_count % 2 != 0) {
    ++numbers_count;
  }
  auto num1_copy = num1;
  auto num2_copy = num2;
  while (num1_copy.size() < numbers_count) {
    num1_copy.push_front(0);
  }
  while (num2_copy.size() < numbers_count) {
    num2_copy.push_front(0);
  }

  digit_list a, b;
  auto mid = num1_copy.begin();
  std::advance(mid, num1_copy.size() / 2);
  std::copy(num1_copy.begin(), mid, std::back_inserter(a));
  std::copy(mid, num1_copy.end(), std::back_inserter(b));

  digit_list c, d;
  mid = num2_copy.begin();
  std::advance(mid, num2_copy.size() / 2);
  std::copy(num2_copy.begin(), mid, std::back_inserter(c));
  std::copy(mid, num2_copy.end(), std::back_inserter(d));

  // x * y = 10^(2m) * ac + 10^m * ((a + b)(c + d) - ac - bd) + bd
  auto m = numbers_count / 2;
  digit_list ac = karatsuba_product_impl(a, c);
  digit_list bd = karatsuba_product_impl(b, d);

  digit_list a_plus_b = a + b;
  digit_list c_plus_d = c + d;

  digit_list p = karatsuba_product_impl(a_plus_b, c_plus_d);

  digit_list middle = p - ac - bd;

  // 10^(2m) * ac
  for (size_t i = 0; i < 2 * m; ++i) {
    ac.push_back(0);
  }

  // 10^m
  for (size_t i = 0; i < m; ++i) {
    middle.push_back(0);
  }

  digit_list result = ac + middle + bd;
  trim_leading_zeroes(result);
  return result;
}
}  // namespace

// Karatsuba multiplication
digit_list karatsuba_product(const digit_list& num1, const digit_list& num2) {
  validate_digit_list(num1);
  validate_digit_list(num2);
  return karatsuba_product_impl(num1, num2);
}