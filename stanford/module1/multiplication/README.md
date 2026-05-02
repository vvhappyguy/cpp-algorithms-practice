# Multiplication

## Usage

```bash
cmake -S . -B build
cmake --build build
./build/multiplication_tests

./build/multiplication_bench
```

## Next steps

- [x] Create `include/multiplication.hpp`
- [x] Move grade-school multiplication to `src/grade_school.cpp`
- [x] Move recursive multiplication to `src/recursive_integer_multiplication.cpp`
- [x] Move shared digit_list helpers to `src/digit_list.cpp`
- [x] Add tests for grade-school and recursive multiplication
- [x] Update README with recursive multiplication section
- [ ] Implement `operator-` for `digit_list`
- [ ] Implement Karatsuba multiplication
- [ ] Add benchmarks

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
