# Benchmark before adding cutoff for karatsuba throw grade_school

# Reasons

std::list<size_t>
a lot of copying digit_list
std::advance on list — O(n)
std::copy for every splitting
push_front / push_back
operator+ и operator- creates new lists
recursion cause manu small allocations

## Results

```
Digits: 1
grade_school: 0.95 us/op
recursive: 0.3 us/op
karatsuba: 0.32 us/op

Digits: 2
grade_school: 0.96 us/op
recursive: 4.63 us/op
karatsuba: 10.67 us/op

Digits: 4
grade_school: 1.59 us/op
recursive: 19.72 us/op
karatsuba: 33.24 us/op

Digits: 8
grade_school: 2.45 us/op
recursive: 55.57 us/op
karatsuba: 107.8 us/op

Digits: 16
grade_school: 3.55 us/op
recursive: 200.79 us/op
karatsuba: 363.53 us/op

Digits: 32
grade_school: 8.94 us/op
recursive: 819.11 us/op
karatsuba: 1264.54 us/op

Digits: 64
grade_school: 25.67 us/op
recursive: 3265.9 us/op
karatsuba: 3707.61 us/op

Digits: 128
grade_school: 105.17 us/op
recursive: 13434.7 us/op
karatsuba: 12104.3 us/op
```
