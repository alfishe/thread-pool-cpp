#include <benchmark/benchmark.h>

#include <thread_pool.hpp>
#include <thread>
#include <vector>
#include <future>

using namespace tp;

static const size_t CONCURRENCY = 16;
static const size_t REPOST_COUNT = 1000000;

static void BM_PoolInsert(benchmark::State& state)
{
  // Perform setup here
  std::promise<void> waiters[CONCURRENCY];
  ThreadPool thread_pool;
  
  for (auto _ : state)
  {
    // This code gets timed
    ;
  }
}

// Register the function as a benchmark
BENCHMARK(BM_PoolInsert);
