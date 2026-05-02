#pragma once

#include <cstddef>
#include <list>
#include <ostream>

using digit_list = std::list<size_t>;

digit_list grade_school_product(const digit_list& num1, const digit_list& num2);

digit_list recursive_product(const digit_list& num1, const digit_list& num2);

digit_list karatsuba_product(const digit_list& num1, const digit_list& num2);

digit_list to_digit_list(size_t value);

void validate_digit_list(const digit_list& num);

std::ostream& operator<<(std::ostream& os, const digit_list& lst);

digit_list operator+(const digit_list& l1, const digit_list& l2);

void trim_leading_zeroes(digit_list& n);

digit_list operator-(const digit_list& left, const digit_list& right);