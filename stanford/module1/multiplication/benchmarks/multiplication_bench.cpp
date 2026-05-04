#include <chrono>
#include <cstddef>
#include <functional>
#include <iostream>
#include <random>
#include <string>
#include <vector>

#include "multiplication.hpp"

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

size_t iterations_for_size(size_t digits_count) {
  if (digits_count <= 32) {
    return 1000;
  }

  if (digits_count <= 128) {
    return 100;
  }

  if (digits_count <= 512) {
    return 10;
  }

  return 3;
}

long long measure_microseconds(multiplication_fn f, const digit_list& left,
                               const digit_list& right, size_t iterations) {
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

void run_benchmark(const std::string& name, multiplication_fn f,
                   const digit_list& left, const digit_list& right,
                   size_t iterations) {
  const long long total_us = measure_microseconds(f, left, right, iterations);
  const double average_us = static_cast<double>(total_us) / iterations;

  std::cout << name << ": " << average_us << " us/op" << '\n';
}

int main() {
  // assessment 
  {
    digit_list n1 = {3,1,4,1,5,9,2,6,5,3,5,8,9,7,9,3,2,3,8,4,6,2,6,4,3,3,8,3,2,7,9,5,0,2,8,8,4,1,9,7,1,6,9,3,9,9,3,7,5,1,0,5,8,2,0,9,7,4,9,4,4,5,9,2};
    digit_list n2 = {2,7,1,8,2,8,1,8,2,8,4,5,9,0,4,5,2,3,5,3,6,0,2,8,7,4,7,1,3,5,2,6,6,2,4,9,7,7,5,7,2,4,7,0,9,3,6,9,9,9,5,9,5,7,4,9,6,6,9,6,7,6,2,7};


    digit_list n = grade_school_product(n1, n2);
    for(auto l: n)
    {
      std::cout << l;
    }
  }

  const std::vector<size_t> sizes = {
      1, 2, 4, 8, 16, 32, 64, 128, 256, 512,
  };

  for (size_t digits_count : sizes) {
    const size_t iterations = iterations_for_size(digits_count);

    const digit_list left = random_digit_list(digits_count);
    const digit_list right = random_digit_list(digits_count);

    std::cout << "\nDigits: " << digits_count << ", iterations: " << iterations
              << '\n';

    run_benchmark("grade_school", grade_school_product, left, right,
                  iterations);

    if (digits_count <= 128) {
      run_benchmark("recursive", recursive_product, left, right, iterations);
    } else {
      std::cout << "recursive: skipped\n";
    }

    run_benchmark("karatsuba", karatsuba_product, left, right, iterations);
  }

  return 0;
}