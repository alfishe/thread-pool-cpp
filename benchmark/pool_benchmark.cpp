#include <benchmark/benchmark.h>

#include "benchmark.h"
#include <thread_pool.hpp>
#include <thread>
#include <vector>
#include <future>

static void BM_PoolInsert(benchmark::State& state)
{
  // Perform setup here
  std::promise<void> waiters[CONCURRENCY];
  ThreadPool thread_pool;
  
  for (auto _ : state)
  {
    // This code gets timed
    //thread_pool.post(RepostJob(&thread_pool, &waiters[0]));
    //waiters[0].get_future().wait();
  }
}

// Register the function as a benchmark
BENCHMARK(BM_PoolInsert);
