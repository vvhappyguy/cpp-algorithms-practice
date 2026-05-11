#include <iostream>
#include <vector>

long long merge_and_count(std::vector<int>& arr, int left, int mid, int right) {
  std::vector<int> temp;
  temp.reserve(right - left + 1);

  int i = left;
  int j = mid + 1;

  long long inversions = 0;

  while (i <= mid && j <= right) {
    if (arr[i] <= arr[j]) {
      temp.push_back(arr[i]);
      ++i;
    } else {
      inversions += static_cast<long long>(mid - i + 1);
      temp.push_back(arr[j]);
      ++j;
    }
  }

  while (i <= mid) {
    temp.push_back(arr[i]);
    ++i;
  }

  while (j <= right) {
    temp.push_back(arr[j]);
    ++j;
  }

  for (size_t k = 0; k < temp.size(); ++k) {
    arr[left + static_cast<int>(k)] = temp[k];
  }

  return inversions;
}

long long sort_and_count(std::vector<int>& arr, int left, int right) {
  if (left >= right) {
    return 0;
  }

  int mid = left + (right - left) / 2;

  long long left_inversions = sort_and_count(arr, left, mid);
  long long right_inversions = sort_and_count(arr, mid + 1, right);
  long long split_inversions = merge_and_count(arr, left, mid, right);

  return left_inversions + right_inversions + split_inversions;
}

long long count_inversions(std::vector<int>& arr) {
  if (arr.empty()) {
    return 0;
  }

  return sort_and_count(arr, 0, static_cast<int>(arr.size()) - 1);
}

int main() {
  std::vector<int> input;
  int x;

  while (std::cin >> x) {
    input.push_back(x);
  }

  long long result = count_inversions(input);
  std::cout << result << '\n';

  return 0;
}