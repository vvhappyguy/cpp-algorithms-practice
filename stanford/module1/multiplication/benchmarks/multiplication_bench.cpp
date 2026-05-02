#include "multiplication.hpp"

#include <chrono>
#include <cstddef>
#include <functional>
#include <iostream>
#include <random>
#include <string>
#include <vector>

using multiplication_fn =
    std::function<digit_list(const digit_list&, const digit_list&)>;

digit_list random_digit_list(size_t digits_count) {
  if (digits_count == 0) {
    return {0};
  }

  static std::mt19937 gen(42);
  std::uniform_int_distribution<size_t> first_digit_dist(1, 9);
  std::uniform_int_distribution<size_t> digit_dist(0, 9);

  digit_list result;
  result.push_back(first_digit_dist(gen));

  for (size_t i = 1; i < digits_count; ++i) {
    result.push_back(digit_dist(gen));
  }

  return result;
}

long long measure_microseconds(multiplication_fn f,
                               const digit_list& left,
                               const digit_list& right,
                               size_t iterations) {
  using clock = std::chrono::steady_clock;

  auto start = clock::now();

  for (size_t i = 0; i < iterations; ++i) {
    auto result = f(left, right);
    volatile size_t result_size = result.size();
    (void)result_size;
  }

  auto end = clock::now();

  return std::chrono::duration_cast<std::chrono::microseconds>(end - start)
      .count();
}

void run_benchmark(const std::string& name,
                   multiplication_fn f,
                   const digit_list& left,
                   const digit_list& right,
                   size_t iterations) {
  long long total_us = measure_microseconds(f, left, right, iterations);
  double average_us = static_cast<double>(total_us) / iterations;

  std::cout << name << ": " << average_us << " us/op" << '\n';
}

int main() {
  const std::vector<size_t> sizes = {
      1,
      2,
      4,
      8,
      16,
      32,
      64,
      128,
  };

  const size_t iterations = 100;

  for (size_t digits_count : sizes) {
    digit_list left = random_digit_list(digits_count);
    digit_list right = random_digit_list(digits_count);

    std::cout << "\nDigits: " << digits_count << '\n';

    run_benchmark("grade_school", grade_school_product, left, right, iterations);
    run_benchmark("recursive", recursive_product, left, right, iterations);
    run_benchmark("karatsuba", karatsuba_product, left, right, iterations);
  }

  return 0;
}