//
//  concurrency.h
//  prep
//
//  Created by Zhaowei Wang on 9/30/18.
//  Copyright © 2018 Zhaowei Wang. All rights reserved.
//

#ifndef concurrency_h
#define concurrency_h

#include <vector>
#include <assert.h>
#include <ctime>
#include <pthread.h>

#define NUM_THREADS 4

static int sum = 0;
pthread_mutex_t sum_mutex;

// functor that contains work for concurrent dot product
template <class T>
struct dot_product
{
    std::vector<T> *a;
    std::vector<T> *b;
    
    dot_product(std::vector<T> *a, std::vector<T> *b)
    : a(a), b(b)
    {
        assert(a->size() == b->size());
    }
    
    T operator()()
    {
        T ret = 0;
        for (size_t i = 0; i < a->size(); ++i)
            ret += (*a)[i] * (*b)[i];
        return ret;
    }
    
    T operator()(size_t begin, size_t end)
    {
        T ret = 0;
        for (size_t i = begin; i < end; ++i)
            ret += (*a)[i] * (*b)[i];
        return ret;
    }
};

template <class T>
struct dot_product_job
{
    dot_product<T> *prod;
    size_t begin;
    size_t end;
    T result;
    
    dot_product_job() {}
    dot_product_job(dot_product<T> *prod, size_t b, size_t e)
    : prod(prod), begin(b), end(e), result(0) {}
    
    void operator()()
    {
        result = (*prod)(begin, end);
    }
};

void * dot_product_entry_point(void *arg)
{
    dot_product_job<int> *job = (dot_product_job<int> *) arg;
    (*job)();
    
    pthread_mutex_lock(&sum_mutex);
    sum += job->result;
    pthread_mutex_unlock(&sum_mutex);
    
    pthread_exit(nullptr);
    return nullptr;
}

void concurrent_dot_product(std::vector<int> *a, std::vector<int> *b)
{
    clock_t t1, t2;
    t1 = clock();
    pthread_t threads[NUM_THREADS];
    int rc;
    long t, start, end, step_size;
    start = 0;
    end = 0;
    step_size = a->size() / NUM_THREADS;
    
    dot_product_job<int> jobs[NUM_THREADS];
    dot_product<int> *prod = new dot_product<int>(a, b);
    
    // make jobs
    for (t = 0; t < NUM_THREADS; ++t)
    {
        start = t * step_size;
        end = (t + 1) * step_size;
        jobs[t] = dot_product_job<int>(prod, start, end);
    }
    t2 = clock();
    std::cout << "Thread setup time = " << ((double) t2 - t1) / CLOCKS_PER_SEC << std::endl;
    
    t1 = clock();
    for (t = 0; t < NUM_THREADS; ++t)
    {
        rc = pthread_create(&threads[t], nullptr, dot_product_entry_point, &jobs[t]);
        if (rc)
            exit(-1);
    }
    
    for (t = 0; t < NUM_THREADS; ++t)
    {
        rc = pthread_join(threads[t], nullptr);
        if (rc)
            exit(-1);
    }
    
    // handle the leftover of the array due to round-down, if any
    sum += (*prod)(step_size * NUM_THREADS, a->size());
    t2 = clock();
    std::cout << "All thread computation time = " << ((double) t2 - t1) / CLOCKS_PER_SEC << std::endl;
    
    delete prod;
}

void singlethread_dot_product(std::vector<int> *a, std::vector<int> *b)
{
    for (size_t i = 0; i < a->size(); ++i)
        sum += (*a)[i] * (*b)[i];
}

void test_concurrency()
{
    int N = 1000000017;
    std::vector<int> ones(N, 1);
    clock_t t1, t2;
    
    sum = 0;
    t1 = clock();
    concurrent_dot_product(&ones, &ones);
    t2 = clock();
    
    std::cout << "Dot product = " << sum << std::endl;
    std::cout << "# threads = " << NUM_THREADS << std::endl;
    std::cout << "Concurrent dot product time: " << ((double)(t2-t1)) / CLOCKS_PER_SEC << "s." << std::endl;
    
    sum = 0;
    t1 = clock();
    singlethread_dot_product(&ones, &ones);
    t2 = clock();
    
    std::cout << "Dot product = " << sum << std::endl;
    std::cout << "Single-threaded dot product time: " << ((double)(t2-t1)) / CLOCKS_PER_SEC << "s." << std::endl;
}

#endif /* concurrency_h */
