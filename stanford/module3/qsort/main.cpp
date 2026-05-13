#include <algorithm>
#include <chrono>
#include <iostream>
#include <random>
#include <string>
#include <utility>
#include <vector>

long long unsigned first = 0;
long long unsigned last = 0;
long long unsigned mot = 0;

void qsort_first(std::vector<int>& vec, int start, int end) {
  if (end - start <= 1) {
    return;
  }

  int pivot = start;
  int i = start + 1;

  for (int j = start + 1; j < end; ++j) {
    first++;
    if (vec[j] < vec[pivot]) {
      std::swap(vec[j], vec[i]);
      ++i;
    }
  }

  std::swap(vec[pivot], vec[i - 1]);
  pivot = i - 1;

  qsort_first(vec, start, pivot);
  qsort_first(vec, pivot + 1, end);
}

void qsort_last(std::vector<int>& vec, int start, int end) {
  if (end - start <= 1) {
    return;
  }

  std::swap(vec[start], vec[end - 1]);

  int pivot = start;
  int i = start + 1;

  for (int j = start + 1; j < end; ++j) {
    last++;
    if (vec[j] < vec[pivot]) {
      std::swap(vec[j], vec[i]);
      ++i;
    }
  }

  std::swap(vec[pivot], vec[i - 1]);
  pivot = i - 1;

  qsort_last(vec, start, pivot);
  qsort_last(vec, pivot + 1, end);
}

int median_of_three_index(const std::vector<int>& vec, int start, int end) {
  int first = start;
  int len = end - start;
  int middle = start + (len - 1) / 2;
  int last = end - 1;

  int a = vec[first];
  int b = vec[middle];
  int c = vec[last];

  if ((a <= b && b <= c) || (c <= b && b <= a)) {
    return middle;
  }

  if ((b <= a && a <= c) || (c <= a && a <= b)) {
    return first;
  }

  return last;
}

void qsort_median_of_three(std::vector<int>& vec, int start, int end) {
  if (end - start <= 1) {
    return;
  }

  int pivot_index = median_of_three_index(vec, start, end);
  std::swap(vec[pivot_index], vec[start]);

  int pivot = start;
  int i = start + 1;

  for (int j = start + 1; j < end; ++j) {
    mot++;
    if (vec[j] < vec[pivot]) {
      std::swap(vec[j], vec[i]);
      ++i;
    }
  }

  std::swap(vec[pivot], vec[i - 1]);
  pivot = i - 1;

  qsort_median_of_three(vec, start, pivot);
  qsort_median_of_three(vec, pivot + 1, end);
}

void qsort_middle(std::vector<int>& vec, int start, int end) {
  if (end - start <= 1) {
    return;
  }

  std::swap(vec[start + (end - start) / 2], vec[start]);

  int pivot = start;
  int i = start + 1;

  for (int j = start + 1; j < end; ++j) {
    if (vec[j] < vec[pivot]) {
      std::swap(vec[j], vec[i]);
      ++i;
    }
  }

  std::swap(vec[pivot], vec[i - 1]);
  pivot = i - 1;

  qsort_middle(vec, start, pivot);
  qsort_middle(vec, pivot + 1, end);
}

void qsort_middle(std::vector<int>& vec, int start, int end);
void qsort_first(std::vector<int>& vec, int start, int end);

using Clock = std::chrono::high_resolution_clock;

std::vector<int> make_random_vector(std::size_t n) {
  std::vector<int> vec(n);

  std::mt19937 rng(42);
  std::uniform_int_distribution<int> dist(0, static_cast<int>(n));

  for (int& x : vec) {
    x = dist(rng);
  }

  return vec;
}

std::vector<int> make_sorted_vector(std::size_t n) {
  std::vector<int> vec(n);

  for (std::size_t i = 0; i < n; ++i) {
    vec[i] = static_cast<int>(i);
  }

  return vec;
}

std::vector<int> make_reversed_vector(std::size_t n) {
  std::vector<int> vec = make_sorted_vector(n);
  std::reverse(vec.begin(), vec.end());
  return vec;
}

std::vector<int> make_many_duplicates_vector(std::size_t n) {
  std::vector<int> vec(n);

  std::mt19937 rng(42);
  std::uniform_int_distribution<int> dist(0, 10);

  for (int& x : vec) {
    x = dist(rng);
  }

  return vec;
}

bool is_sorted_correctly(const std::vector<int>& vec) {
  return std::is_sorted(vec.begin(), vec.end());
}

template <typename SortFunc>
long long benchmark_once(const std::vector<int>& input, SortFunc sort_func) {
  std::vector<int> vec = input;

  auto start_time = Clock::now();

  if (!vec.empty()) {
    sort_func(vec, 0, static_cast<int>(vec.size()));
  }

  auto end_time = Clock::now();

  if (!is_sorted_correctly(vec)) {
    std::cerr << "Sort failed!\n";
    std::exit(1);
  }

  return std::chrono::duration_cast<std::chrono::microseconds>(end_time -
                                                               start_time)
      .count();
}

template <typename SortFunc>
long long benchmark_average(const std::vector<int>& input, SortFunc sort_func,
                            int iterations) {
  long long total = 0;

  for (int i = 0; i < iterations; ++i) {
    total += benchmark_once(input, sort_func);
  }

  return total / iterations;
}

void run_case(const std::string& name, const std::vector<int>& input,
              int iterations) {
  long long middle_time = benchmark_average(input, qsort_middle, iterations);

  long long first_time = benchmark_average(input, qsort_first, iterations);

  std::cout << name << "\n";
  std::cout << "  qsort_middle: " << middle_time << " us\n";
  std::cout << "  qsort_first:  " << first_time << " us\n";
  std::cout << "\n";
}

// int main() {
//   const std::size_t n = 100000;
//   const int iterations = 5;

//   std::cout << "n = " << n << "\n";
//   std::cout << "iterations = " << iterations << "\n\n";

//   run_case("random", make_random_vector(n), iterations);
//   run_case("sorted", make_sorted_vector(n), iterations);
//   run_case("reversed", make_reversed_vector(n), iterations);
//   run_case("many duplicates", make_many_duplicates_vector(n), iterations);

//   return 0;
// }

int main() {
  std::vector<int> input;
  int x;

  while (std::cin >> x) {
    input.push_back(x);
  }

  auto vec = input;

  qsort_first(vec, 0, vec.size());
  if (!is_sorted_correctly(vec)) {
    std::cerr << "First sort failed!\n";
  }
  vec = input;
  qsort_last(vec, 0, vec.size());
  if (!is_sorted_correctly(vec)) {
    std::cerr << "First sort failed!\n";
  }
  vec = input;
  qsort_median_of_three(vec, 0, vec.size());
  if (!is_sorted_correctly(vec)) {
    std::cerr << "First sort failed!\n";
  }

  std::cout << first << std::endl << last << std::endl << mot << std::endl;

  // std::cout << result << '\n';

  return 0;
}

// int main() {
//   std::vector<int> vec = {1, 3, 5, 2, 4, 6};
//   qsort_first(vec, 0, vec.size());
//   for (auto i : vec) {
//     std::cout << i << ' ';
//   }
//   std::cout << std::endl;

//   qsort_middle(vec, 0, vec.size());
//   for (auto i : vec) {
//     std::cout << i << ' ';
//   }
//   std::cout << std::endl;
//   return 0;
// }