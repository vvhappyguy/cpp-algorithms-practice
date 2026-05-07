#include <vector>
#include <iostream>

using namespace std;

vector<int> numbers = {1, 3, 6, 2, 4, 6};

int merge_and_count(std::vector<int>& arr, int left, int mid, int right) {
  std::vector<int> temp;

  int i = left;
  int j = mid + 1;

  int inversions = 0;

  while (i <= mid && j <= right) {
    if (arr[i] <= arr[j]) {
      temp.push_back(arr[i]);
      ++i;
    } else {
      inversions += (mid - i + 1);
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

  for (int k = 0; k < temp.size(); ++k) {
    arr[left + k] = temp[k];
  }
  return inversions;
}

int sort_and_count(std::vector<int>& arr, int left, int right) {
  if (left >= right) {
    return 0;
  }

  int mid = left + (right - left) / 2;

  int x = sort_and_count(arr, left, mid);
  int y = sort_and_count(arr, mid + 1, right);
  int z = merge_and_count(arr, left, mid, right);

  std::cout << x << ' ' << y << ' ' << z << std::endl;

  return x + y + z;
}

long long count_inversions(std::vector<int>& arr) {
  if (arr.empty()) {
    return 0;
  }

  return sort_and_count(arr, 0, static_cast<int>(arr.size()) - 1);
}

int main() {
  std::vector<int> arr = {5, 2, 4, 7, 1, 3, 2, 6};
  arr = {1, 2, 3, 4, 5, 6, 7, 8};
  arr = {2, 1, 3, 4, 5, 6, 7, 8};
  arr = {1, 3, 5, 2, 4, 6};

  int res = count_inversions(arr);
  std::cout << "inversions=" << res << std::endl;

  for (int x : arr) {
    std::cout << x << " ";
  }

  std::cout << '\n';
}