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

digit_list grade_school_product(const digit_list& num1,
                                const digit_list& num2) {
  if (num1.empty() || num2.empty()) {
    return {};
  }

  for (size_t d : num1) {
    if (d > 9) {
      throw std::invalid_argument("num1 contains non-digit value");
    }
  }

  for (size_t d : num2) {
    if (d > 9) {
      throw std::invalid_argument("num2 contains non-digit value");
    }
  }

  std::vector<size_t> a(num1.begin(), num1.end());
  std::vector<size_t> b(num2.begin(), num2.end());

  std::vector<size_t> result(a.size() + b.size(), 0);

  for (int i = static_cast<int>(a.size()) - 1; i >= 0; --i) {
    for (int j = static_cast<int>(b.size()) - 1; j >= 0; --j) {
      size_t product = a[i] * b[j];

      size_t pos_low = static_cast<size_t>(i + j + 1);
      size_t pos_high = static_cast<size_t>(i + j);

      size_t sum = result[pos_low] + product;

      result[pos_low] = sum % 10;
      result[pos_high] += sum / 10;
    }
  }

  digit_list answer;

  bool zeroes = true;
  for (size_t digit : result) {
    if (digit > 9) {
      throw std::logic_error("internal carry propagation failed");
    }
    if (zeroes && digit == 0) {
      continue;
    }
    zeroes = false;

    answer.push_back(digit);
  }

  if (answer.empty()) {
    answer.push_back(0);
  }

  return answer;
}
