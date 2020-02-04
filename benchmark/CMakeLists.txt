# Benchmark

# Project named 'benchmark' on C++
project(pbenchmark LANGUAGES CXX)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Build Google Benchmark
option(BENCHMARK_ENABLE_TESTING "Disabling self-testing & benchmarking" OFF)
get_filename_component(GOOGLEBENCHMARK_DIR ../lib/benchmark ABSOLUTE BASE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
add_subdirectory(${GOOGLEBENCHMARK_DIR} ${CMAKE_CURRENT_BINARY_DIR}/googlebenchmark)

# Add folders to compiler include path
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${GOOGLEBENCHMARK_DIR}/include)

# Build 'pbenchmark' executable out of .cpp sources
add_executable(${PROJECT_NAME} benchmark.cpp pool_benchmark.cpp)

# Include Boost::ASIO part of tests if available
find_package (Boost)
if (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS}) 
    add_definitions( -DWITH_ASIO)
    target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})
endif (Boost_FOUND)

target_link_libraries(${PROJECT_NAME} pthread benchmark)

