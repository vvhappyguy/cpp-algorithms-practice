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

bool less_than(digit_list left, digit_list right) {
  trim_leading_zeroes(left);
  trim_leading_zeroes(right);

  if (left.size() != right.size()) {
    return left.size() < right.size();
  }

  auto l = left.begin();
  auto r = right.begin();

  while (l != left.end()) {
    if (*l != *r) {
      return *l < *r;
    }

    ++l;
    ++r;
  }

  return false;
}

void trim_leading_zeroes(digit_list& n) {
  while (n.size() > 1 && n.front() == 0) {
    n.pop_front();
  }
}

digit_list operator-(const digit_list& left, const digit_list& right) {
  if (less_than(left, right)) {
    throw std::invalid_argument("right is bigger than left");
  }

  auto l = left.rbegin();
  auto r = right.rbegin();

  digit_list result;

  int borrow = 0;
  while (l != left.rend()) {
    int left_digit = static_cast<int>(*l);
    int right_digit = 0;

    if (r != right.rend()) {
      right_digit = static_cast<int>(*r);
      ++r;
    }

    int diff = left_digit - (right_digit + borrow);
    if (diff < 0) {
      borrow = 1;
      diff += 10;
    } else {
      borrow = 0;
    }
    result.push_front(static_cast<size_t>(diff));

    l++;
  }

  trim_leading_zeroes(result);
  return result;
}