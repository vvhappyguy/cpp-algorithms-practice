#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

void qsort(std::vector<int>& vec, int start, int end) {
  if (start >= end) {
    return;
  }

  int pivot = start;
  int i = start + 1;
  for (int j = start + 1; j < end; ++j) {
    if (vec[j] < vec[pivot]) {
      std::swap(vec[j], vec[i]);
      i++;
    }
  }
  std::swap(vec[pivot], vec[i - 1]);
  pivot = i - 1;
  qsort(vec, start, pivot);
  qsort(vec, pivot + 1, end);
}

int main() {
  std::vector<int> vec = {1, 3, 5, 2, 4, 6};
  qsort(vec, 0, vec.size());
  for (auto i : vec) {
    std::cout << i << ' ';
  }
  std::cout << std::endl;
  return 0;
}