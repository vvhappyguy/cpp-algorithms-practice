#include <functional>

#include "multiplication.hpp"

void validate_digit_list(const digit_list& num) {
  if (num.empty()) {
    throw std::invalid_argument("digit_list is empty");
  }

  for (size_t d : num) {
    if (d > 9) {
      throw std::invalid_argument("digit_list contains non-digit value");
    }
  }
}

digit_list to_digit_list(size_t value) {
  if (value == 0) {
    return {0};
  }

  digit_list result;
  while (value > 0) {
    result.push_front(value % 10);
    value /= 10;
  }
  return result;
}

std::ostream& operator<<(std::ostream& os, const digit_list& lst) {
  os << "[";
  for (auto it = lst.begin(); it != lst.end(); ++it) {
    os << *it;
    if (std::next(it) != lst.end()) {
      os << ", ";  // Добавляем запятую только между элементами
    }
  }
  os << "]";
  return os;
}

digit_list operator+(const digit_list& l1, const digit_list& l2) {
  digit_list result;

  auto it1 = l1.rbegin();
  auto it2 = l2.rbegin();

  size_t carry = 0;

  while (it1 != l1.rend() || it2 != l2.rend() || carry != 0) {
    size_t sum = carry;

    if (it1 != l1.rend()) {
      sum += *it1;
      ++it1;
    }

    if (it2 != l2.rend()) {
      sum += *it2;
      ++it2;
    }

    result.push_front(sum % 10);
    carry = sum / 10;
  }

  return result;
}