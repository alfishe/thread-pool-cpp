#pragma once

#ifndef THREAD_POOL_CPP_H
#define THREAD_POOL_CPP_H

#ifdef WITH_ASIO
#include <asio_thread_pool.hpp>
#endif

#include <thread_pool.hpp>
#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
#include <future>

#define CONCURRENCY 16
#define REPOST_COUNT 1000000

using namespace tp;

struct Heavy
{
    bool verbose;
    std::vector<char> resource;

    Heavy(bool verbose = false) : verbose(verbose), resource(100 * 1024 * 1024)
    {
        if(verbose)
        {
            std::cout << "heavy default constructor" << std::endl;
        }
    }

    Heavy(const Heavy& o) : verbose(o.verbose), resource(o.resource)
    {
        if(verbose)
        {
            std::cout << "heavy copy constructor" << std::endl;
        }
    }

    Heavy(Heavy&& o) : verbose(o.verbose), resource(std::move(o.resource))
    {
        if(verbose)
        {
            std::cout << "heavy move constructor" << std::endl;
        }
    }

    Heavy& operator==(const Heavy& o)
    {
        verbose = o.verbose;
        resource = o.resource;
        if(verbose)
        {
            std::cout << "heavy copy operator" << std::endl;
        }
        return *this;
    }

    Heavy& operator==(const Heavy&& o)
    {
        verbose = o.verbose;
        resource = std::move(o.resource);
        if(verbose)
        {
            std::cout << "heavy move operator" << std::endl;
        }
        return *this;
    }

    ~Heavy()
    {
        if(verbose)
        {
            std::cout << "heavy destructor. "
                      << (resource.size() ? "Owns resource"
                                          : "Doesn't own resource")
                      << std::endl;
        }
    }
};


struct RepostJob
{
    // Heavy heavy;

    ThreadPool* thread_pool;
#ifdef WITH_ASIO
    AsioThreadPool* asio_thread_pool;
#endif

    volatile size_t counter;
    long long int begin_count;
    std::promise<void>* waiter;

    RepostJob(ThreadPool* thread_pool, std::promise<void>* waiter)
        : thread_pool(thread_pool)
#ifdef WITH_ASIO
          ,
          asio_thread_pool(0)
#endif
          ,
          counter(0), waiter(waiter)
    {
        begin_count = std::chrono::high_resolution_clock::now()
                          .time_since_epoch()
                          .count();
    }

#endif

#ifdef WITH_ASIO
    RepostJob(AsioThreadPool* asio_thread_pool, std::promise<void>* waiter)
        : thread_pool(0), asio_thread_pool(asio_thread_pool), counter(0),
          waiter(waiter)
    {
        begin_count = std::chrono::high_resolution_clock::now()
                          .time_since_epoch()
                          .count();
    }
#endif

    void operator()()
    {
        if (++counter < REPOST_COUNT)
        {
#ifdef WITH_ASIO
            if(asio_thread_pool)
            {
                asio_thread_pool->post(*this);
                return;
            }
#endif
            if (thread_pool)
            {
                thread_pool->post(*this);
                return;
            }
        }
        else
        {
            long long int end_count = std::chrono::high_resolution_clock::now()
                                          .time_since_epoch()
                                          .count();
            std::cout << "reposted " << counter << " in "
                      << (double)(end_count - begin_count) / (double)1000000
                      << " ms" << std::endl;
            waiter->set_value();
        }
    }
};