cmake_minimum_required(VERSION 3.20)

project(multiplication_algorithms
    VERSION 0.1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(multiplication
    src/digit_list.cpp
    src/grade_school.cpp
    src/recursive_integer_multiplication.cpp
    src/karatsuba.cpp
)

target_include_directories(multiplication
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_options(multiplication
    PRIVATE
        -Wall
        -Wextra
        -Wpedantic
)

add_executable(multiplication_tests
    tests/multiplication_tests.cpp
)

target_link_libraries(multiplication_tests
    PRIVATE
        multiplication
)

target_compile_options(multiplication_tests
    PRIVATE
        -Wall
        -Wextra
        -Wpedantic
)

add_executable(multiplication_bench
    benchmarks/multiplication_bench.cpp
)

target_link_libraries(multiplication_bench
    PRIVATE
        multiplication
)

target_compile_options(multiplication_bench
    PRIVATE
        -Wall
        -Wextra
        -Wpedantic
)