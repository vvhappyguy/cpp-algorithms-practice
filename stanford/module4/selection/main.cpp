#include <algorithm>
#include <chrono>
#include <iostream>
#include <random>
#include <string>
#include <utility>
#include <vector>

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

int select_qsort_median_of_three(std::vector<int>& vec, int start, int end,
                                 int aim) {
  if (end - start <= 1) {
    return 0;
  }

  int pivot_index = median_of_three_index(vec, start, end);
  std::swap(vec[pivot_index], vec[start]);

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
  if (vec[pivot] == aim) {
    return pivot;
  } else if (aim < vec[pivot]) {
    return select_qsort_median_of_three(vec, start, pivot, aim);
  } else if (aim > vec[pivot]) {
    return select_qsort_median_of_three(vec, pivot + 1, end, aim);
  }
}

int main() {
  std::vector<int> vec = {1, 3, 5, 2, 4, 6};

  int idx = select_qsort_median_of_three(vec, 0, vec.size(), 3);
  for (auto i : vec) {
    std::cout << i << ' ';
  }
  std::cout << std::endl << idx << std::endl;
  return 0;
}