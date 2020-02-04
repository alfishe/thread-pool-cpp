#include <benchmark/benchmark.h>

#include "benchmark.h"

void customBenchmark()
{
    std::cout << "Benchmark job reposting" << std::endl;

    {
        std::cout << "***thread pool cpp***" << std::endl;

        std::promise<void> waiters[CONCURRENCY];
        ThreadPool thread_pool;
        for(auto& waiter : waiters)
        {
            thread_pool.post(RepostJob(&thread_pool, &waiter));
        }

        for(auto& waiter : waiters)
        {
            waiter.get_future().wait();
        }
    }

#ifdef WITH_ASIO
    {
        std::cout << "***asio thread pool***" << std::endl;

        size_t workers_count = std::thread::hardware_concurrency();
        if(0 == workers_count)
        {
            workers_count = 1;
        }

        AsioThreadPool asio_thread_pool(workers_count);

        std::promise<void> waiters[CONCURRENCY];
        for(auto& waiter : waiters)
        {
            asio_thread_pool.post(RepostJob(&asio_thread_pool, &waiter));
        }

        for(auto& waiter : waiters)
        {
            waiter.get_future().wait();
        }
    }
#endif
}

int main(int argc, char** argv)
{
    std::cout << "Custom benchmarks: " << std::endl;
    customBenchmark();
    std::cout << std::endl;

    std::cout << "Google benchmarks: " << std::endl;
    ::benchmark::Initialize(&argc, argv);
    ::benchmark::RunSpecifiedBenchmarks();

    return 0;
}
