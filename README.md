thread-pool-cpp
=================
[![Build Status](https://travis-ci.org/alfishe/thread-pool-cpp.svg?branch=master)](https://travis-ci.org/alfishe/thread-pool-cpp)
[![Codecov branch](https://img.shields.io/codecov/c/github/alfishe/thread-pool-cpp/master.svg)](https://codecov.io/gh/alfishe/thread-pool-cpp)
[![MIT licensed](https://img.shields.io/badge/license-MIT-blue.svg)](./LICENSE)

 * It is highly scalable and fast.
 * Header only.
 * No external dependencies, only standard library needed.
 * Implements both work-stealing and work-distribution balancing strategies.
 * Implements cooperative scheduling strategy.

Build it:
```
mkdir build
cd build
cmake ..
cmake --build . --parallel 8
```

Benchmark it:
(assuming you just build it and current folder is /build)
```
benchmark/pbenchmark
```

Example run:
Post job to thread pool is much faster than for boost::asio based thread pool.

    Benchmark job reposting
    ***thread pool cpp***
    reposted 1000001 in 61.6754 ms
    reposted 1000001 in 62.0187 ms
    reposted 1000001 in 62.8785 ms
    reposted 1000001 in 70.2714 ms
    ***asio thread pool***
    reposted 1000001 in 1381.58 ms
    reposted 1000001 in 1390.35 ms
    reposted 1000001 in 1391.84 ms
    reposted 1000001 in 1393.19 ms

See benchmark/benchmark.cpp for benchmark code.

All code except [MPMCBoundedQueue](https://github.com/inkooboo/thread-pool-cpp/blob/master/include/thread_pool/mpmc_bounded_queue.hpp)
is under MIT license.

