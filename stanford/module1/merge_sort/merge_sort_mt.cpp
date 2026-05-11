#include <algorithm>
#include <chrono>
#include <iostream>
#include <random>
#include <thread>
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

constexpr int THREAD_THRESHOLD = 10'000;

void merge_sort_mt(std::vector<int>& arr, int left, int right) {
  if (left >= right) {
    return;
  }

  int mid = left + (right - left) / 2;

  int size = right - left + 1;
  if (size >= THREAD_THRESHOLD) {
    std::thread t1(merge_sort_mt, std::ref(arr), left, mid);
    std::thread t2(merge_sort_mt, std::ref(arr), mid + 1, right);

    t1.join();
    t2.join();
  } else {
    merge_sort_mt(arr, left, mid);
    merge_sort_mt(arr, mid + 1, right);
  }

  merge(arr, left, mid, right);
}

std::vector<int> generate_random_vector(std::size_t size) {
  std::vector<int> data;
  data.reserve(size);

  std::mt19937 rng(42);
  std::uniform_int_distribution<int> dist(-1'000'000, 1'000'000);

  for (std::size_t i = 0; i < size; ++i) {
    data.push_back(dist(rng));
  }

  return data;
}

template <typename Func>
long long benchmark_ms(Func&& func) {
  auto start = std::chrono::high_resolution_clock::now();

  func();

  auto end = std::chrono::high_resolution_clock::now();

  return std::chrono::duration_cast<std::chrono::milliseconds>(end - start)
      .count();
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
  const std::size_t size = 1'000'000;

  auto original = generate_random_vector(size);

  auto data_merge = original;
  auto data_std = original;

  auto merge_mt_time = benchmark_ms(
      [&]() { merge_sort_mt(data_merge, 0, data_merge.size() - 1); });

  auto merge_time =
      benchmark_ms([&]() { merge_sort(data_merge, 0, data_merge.size() - 1); });

  auto std_sort_time =
      benchmark_ms([&]() { std::sort(data_std.begin(), data_std.end()); });

  bool correct = data_merge == data_std;

  std::cout << "Elements: " << size << '\n';
  std::cout << "Merge sort MT time: " << merge_mt_time << " ms\n";
  std::cout << "Merge sort time: " << merge_time << " ms\n";
  std::cout << "std::sort time:  " << std_sort_time << " ms\n";
  std::cout << "Correct: " << std::boolalpha << correct << '\n';

  return 0;
}