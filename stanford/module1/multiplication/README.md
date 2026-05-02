# Multiplication

## Usage

```bash
cmake -S . -B build
cmake --build build
./build/multiplication_tests

./build/multiplication_bench
```

## Next steps

- [+] Create `include/multiplication.hpp`
- [+] Move grade-school multiplication to `src/grade_school.cpp`
- [+] Move recursive multiplication to `src/recursive_integer_multiplication.cpp`
- [+] Move shared digit_list helpers to `src/digit_list.cpp`
- [+] Add tests for grade-school and recursive multiplication
- [+] Update README with recursive multiplication section
- [+] Implement `operator-` for `digit_list`
- [+] Implement Karatsuba multiplication
- [+] Add benchmarks

# Integer Multiplication Algorithms

This module compares several integer multiplication algorithms implemented in C++:

- Grade-school multiplication
- Recursive divide-and-conquer multiplication
- Karatsuba multiplication

The goal is to study algorithmic complexity and compare practical performance on large decimal numbers.

## Complexity

| Algorithm | Time Complexity |
|---|---:|
| Grade-school | O(n²) |
| Recursive divide-and-conquer | O(n²) |
| Karatsuba | O(n^log₂3) ≈ O(n^1.585) |

## module 1 - week 1

### Grade-school multiplication

[grade_school_multiplication.cpp](grade_school_multiplication.cpp)

Time complexity: O(n * m)  
Space complexity: O(n + m)

### Recursive divide-and-conquer multiplication

Implemented in:

[recursive_integer_multiplication.cpp](src/recursive_integer_multiplication.cpp)

Formula:

x = 10^m * a + b  
y = 10^m * c + d  

x * y = 10^(2m) * ac + 10^m * (ad + bc) + bd

Time complexity: O(n²)  
Space complexity: O(n log n) approximately because of recursive calls and temporary digit lists.


### Benchmark results

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

### Conclusion

This experiment demonstrates the difference between asymptotic complexity and
practical performance. Karatsuba reduces the number of recursive multiplications,
but its benefit depends heavily on representation and implementation details.

A future optimized version should use a contiguous representation such as
`std::vector<uint32_t>` or `std::vector<uint64_t>` with a larger numeric base
instead of storing one decimal digit per `std::list` node.