#benchmark

# Project named 'benchmark' on C++
project(pbenchmark LANGUAGES CXX)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Build Google Benchmark
option(BENCHMARK_ENABLE_TESTING "Disabling self-testing & benchmarking" OFF)
get_filename_component(GOOGLEBENCHMARK_DIR ../lib/benchmark ABSOLUTE BASE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
add_subdirectory(${GOOGLEBENCHMARK_DIR} ${CMAKE_CURRENT_BINARY_DIR}/googlebenchmark)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${GOOGLEBENCHMARK_DIR}/include)

add_executable(${PROJECT_NAME} benchmark.cpp pool_benchmark.cpp)
#target_link_directories(${PROJECT_NAME} PRIVATE ${GOOGLEBENCHMARK_DIR})
target_link_libraries(${PROJECT_NAME} pthread benchmark)

