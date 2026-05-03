#include <iostream>
#include <vector>

void merge(std::vector<int>& arr, int left, int mid, int right) {
  std::vector<int> temp;

  int i = left;
  int j = mid + 1;

  while (i <= mid && j <= right) {
    if (arr[i] <= arr[j]) {
      temp.push_back(arr[i]);
      ++i;
    } else {
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
}

void merge_sort(std::vector<int>& arr, int left, int right) {
  if (left >= right) {
    return;
  }

  int mid = left + (right - left) / 2;

  merge_sort(arr, left, mid);
  merge_sort(arr, mid + 1, right);

  merge(arr, left, mid, right);
}

int main() {
  std::vector<int> arr = {5, 2, 4, 7, 1, 3, 2, 6};

  merge_sort(arr, 0, arr.size() - 1);

  for (int x : arr) {
    std::cout << x << " ";
  }

  std::cout << '\n';
}