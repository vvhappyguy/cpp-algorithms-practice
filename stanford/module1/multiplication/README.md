# Multiplication

This module compares several integer multiplication algorithms implemented in C++:

- Grade-school multiplication
- Recursive divide-and-conquer multiplication
- Karatsuba multiplication

The goal is to study algorithmic complexity and compare practical performance on large decimal numbers.

The current implementation uses:

```cpp
using digit_list = std::list<size_t>;
```

Each list node stores one decimal digit.

## Usage

```bash
cmake -S . -B build
cmake --build build

./build/multiplication_tests
./build/multiplication_bench
```

## Project structure

```text
multiplication/
  include/
    multiplication.hpp
  src/
    digit_list.cpp
    grade_school.cpp
    recursive_integer_multiplication.cpp
    karatsuba.cpp
  tests/
    multiplication_tests.cpp
  benchmarks/
    multiplication_bench.cpp
  README.md
```

## Progress

- [x] Create `include/multiplication.hpp`
- [x] Move grade-school multiplication to `src/grade_school.cpp`
- [x] Move recursive multiplication to `src/recursive_integer_multiplication.cpp`
- [x] Move shared `digit_list` helpers to `src/digit_list.cpp`
- [x] Add tests for grade-school and recursive multiplication
- [x] Implement `operator-` for `digit_list`
- [x] Implement Karatsuba multiplication
- [x] Add benchmarks
- [x] Document benchmark results

## Complexity

| Algorithm | Time Complexity |
|---|---:|
| Grade-school | O(n²) |
| Recursive divide-and-conquer | O(n²) |
| Karatsuba | O(n^log₂3) ≈ O(n^1.585) |

## Module 1 — Week 1

### Grade-school multiplication

Implemented in:

[`src/grade_school.cpp`](src/grade_school.cpp)

Time complexity: O(n * m)  
Space complexity: O(n + m)

This is the classic multiplication algorithm taught in school. Each digit of one number is multiplied by each digit of the other number.

### Recursive divide-and-conquer multiplication

Implemented in:

[`src/recursive_integer_multiplication.cpp`](src/recursive_integer_multiplication.cpp)

Formula:

```text
x = 10^m * a + b
y = 10^m * c + d

x * y = 10^(2m) * ac + 10^m * (ad + bc) + bd
```

This version recursively splits both numbers into high and low halves. It still performs four recursive multiplications, so its asymptotic complexity remains O(n²).

Time complexity: O(n²)  
Space complexity: uses additional temporary digit lists during recursion.

### Karatsuba multiplication

Implemented in:

[`src/karatsuba.cpp`](src/karatsuba.cpp)

Formula:

```text
x = 10^m * a + b
y = 10^m * c + d

x * y = 10^(2m) * ac + 10^m * ((a + b)(c + d) - ac - bd) + bd
```

Karatsuba reduces the number of recursive multiplications from four to three:

```text
ac
bd
(a + b)(c + d)
```

The middle term is computed as:

```text
ad + bc = (a + b)(c + d) - ac - bd
```

Time complexity: O(n^log₂3) ≈ O(n^1.585)  
Space complexity: uses additional temporary digit lists during recursion.

A cutoff threshold is used so that small subproblems fall back to grade-school multiplication.

## Benchmark results

The benchmark compares three multiplication algorithms using the current
`digit_list = std::list<size_t>` decimal representation.

| Digits | Grade-school, us/op | Recursive, us/op | Karatsuba, us/op |
|---:|---:|---:|---:|
| 1 | 0.391 | 0.167 | 0.515 |
| 2 | 0.539 | 1.958 | 0.610 |
| 4 | 0.838 | 9.907 | 0.909 |
| 8 | 1.544 | 46.446 | 1.710 |
| 16 | 3.482 | 197.810 | 3.743 |
| 32 | 9.036 | 796.021 | 9.878 |
| 64 | 29.860 | 3300.040 | 91.620 |
| 128 | 106.350 | 13047.400 | 518.670 |
| 256 | 374.800 | skipped | 1992.300 |
| 512 | 1526.500 | skipped | 6253.500 |

Although Karatsuba has better asymptotic complexity, this implementation is
slower than grade-school multiplication in practice. The main reason is the
current `std::list<size_t>` representation: recursive splitting, copying,
temporary lists, and memory allocations dominate the theoretical advantage.

A cutoff threshold was added so that Karatsuba falls back to grade-school
multiplication for small subproblems. This significantly improves performance,
but grade-school multiplication still remains faster for the tested input sizes.

## Conclusion

This experiment demonstrates the difference between asymptotic complexity and
practical performance. Karatsuba reduces the number of recursive multiplications,
but its benefit depends heavily on representation and implementation details.

A future optimized version should use a contiguous representation such as
`std::vector<uint32_t>` or `std::vector<uint64_t>` with a larger numeric base
instead of storing one decimal digit per `std::list` node.

## Future work

- Implement a vector-based big integer representation.
- Store digits in a larger base, for example `10^4` or `10^9`.
- Reduce temporary allocations in recursive algorithms.
- Tune the Karatsuba cutoff threshold.
- Add more stable benchmarking with multiple input samples per size.
