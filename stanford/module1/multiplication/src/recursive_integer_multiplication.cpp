#include <cassert>
#include <cstddef>
#include <functional>
#include <iostream>
#include <limits>
#include <list>
#include <stdexcept>
#include <tuple>
#include <vector>

#include "multiplication.hpp"

void trim_leading_zeroes(digit_list& n) {
  while (n.size() > 1 && n.front() == 0) {
    n.pop_front();
  }
}

digit_list recursive_product_impl(const digit_list& num1,
                                  const digit_list& num2);

// recursive divide-and-conquer multiplication
digit_list recursive_product(const digit_list& num1, const digit_list& num2) {
  validate_digit_list(num1);
  validate_digit_list(num2);
  return recursive_product_impl(num1, num2);
}

digit_list recursive_product_impl(const digit_list& num1,
                                  const digit_list& num2) {
  if (num1.empty() || num2.empty()) {
    throw std::invalid_argument("empty digit_list is not a valid number");
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
  //   std::cout << "1: " << num1_copy << std::endl
  //             << a << std::endl
  //             << b << std::endl;

  digit_list c, d;
  mid = num2_copy.begin();
  std::advance(mid, num2_copy.size() / 2);
  std::copy(num2_copy.begin(), mid, std::back_inserter(c));
  std::copy(mid, num2_copy.end(), std::back_inserter(d));
  //   std::cout << "1: " << num2_copy << std::endl
  //             << c << std::endl
  //             << d << std::endl;

  // x * y = 10^(2m) * ac + 10^m * (ad + bc) + bd
  auto m = numbers_count / 2;
  //   std::cout << "ac: ";
  digit_list ac = recursive_product_impl(a, c);
  //   std::cout << "bd: ";
  digit_list bd = recursive_product_impl(b, d);
  //   std::cout << "ad: ";
  digit_list ad = recursive_product_impl(a, d);
  //   std::cout << "bc: ";
  digit_list bc = recursive_product_impl(b, c);

  // 10^(2m) * ac
  for (size_t i = 0; i < 2 * m; ++i) {
    ac.push_back(0);
  }

  // (ad + bc)
  digit_list ad_plus_bc = ad + bc;
  // 10^m
  for (size_t i = 0; i < m; ++i) {
    ad_plus_bc.push_back(0);
  }

  digit_list result = ac + ad_plus_bc + bd;
  trim_leading_zeroes(result);
  return result;
}