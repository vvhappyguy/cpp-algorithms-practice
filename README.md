# C++ Algorithms Practice

This repository contains my C++ implementations, tests, benchmarks, and notes while studying algorithms for technical interviews and systems/software engineering job transition.

The main goals are:

- practice classic algorithms in modern C++;
- connect theory with real implementation details;
- write small tests and benchmarks for every non-trivial topic;
- document complexity, trade-offs, and practical performance observations.

## Current focus

- Stanford Algorithms Specialization
- Divide and conquer algorithms
- LeetCode-style practice in C++
- Classic algorithm implementations with tests and benchmarks

## Repository structure

```text
stanford/
  module1/
    multiplication/
      include/
      src/
      tests/
      benchmarks/
      README.md
```

## Implemented modules

### Integer multiplication

Path: [`stanford/module1/multiplication/`](./stanford/module1/multiplication/)

Module documentation: [`stanford/module1/multiplication/README.md`](./stanford/module1/multiplication/README.md)

Implemented algorithms:

- Grade-school multiplication
- Recursive divide-and-conquer multiplication
- Karatsuba multiplication

The module includes:

- CMake build
- unit-style correctness tests
- benchmarks
- benchmark result table
- practical performance analysis

Key takeaway: although Karatsuba has better asymptotic complexity, the current implementation is slower than grade-school multiplication for the tested input sizes because it uses `std::list<size_t>` with one decimal digit per node. The overhead from recursion, copying, temporary lists, and allocations dominates the theoretical advantage.

## Planned topics

- Sorting algorithms
  - merge sort
  - inversion counting
  - quicksort
- Divide and conquer
  - closest pair of points
  - matrix multiplication
- Graph algorithms
- Greedy algorithms
- Dynamic programming
- LeetCode practice by topic

## Build and run

Each module is intended to be buildable independently.

Example for the multiplication module:

```bash
cd stanford/module1/multiplication
cmake -S . -B build
cmake --build build

./build/multiplication_tests
./build/multiplication_bench
```

## Development approach

For each algorithmic topic, the preferred workflow is:

1. implement a simple working version;
2. add correctness tests;
3. add benchmark tests when performance matters;
4. document time and space complexity;
5. compare theory with practical results;
6. write down limitations and possible improvements.

## Notes

This repository is primarily a learning and interview-preparation project. Code is intentionally written in a clear style first, then optimized when the optimization teaches something useful.
