cmake_minimum_required(VERSION 2.8)

project(thread-pool-cpp CXX)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra")
if(COVERAGE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g --coverage")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage")
endif()

# Default to Release mode
if (NOT CMAKE_BUILD_TYPE)
    set (CMAKE_BUILD_TYPE Release)
endif ()

# Google test
enable_testing()
add_subdirectory(lib/googletest)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib/googletest/googletest/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib/benchmark/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# Tests
add_subdirectory(tests)

# Benchmarks
add_subdirectory(benchmark)

# Install
file(GLOB_RECURSE INSTALL_FILES_LIST "${CMAKE_CURRENT_SOURCE_DIR}/include/*")
set_source_files_properties(${INSTALL_FILES_LIST} PROPERTIES HEADER_FILE_ONLY 1)
install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include/" DESTINATION "include")
