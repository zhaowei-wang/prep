//
//  concurrency.h
//  prep
//
//  Created by Zhaowei Wang on 9/30/18.
//  Copyright © 2018 Zhaowei Wang. All rights reserved.
//

#ifndef concurrency_h
#define concurrency_h

#include <pthread.h>
#include <vector>

#define NUM_THREADS     5

static int sum = 0;
pthread_mutex_t sum_mutex;

template <class T>
struct dot_product_work
{
    std::vector<T> a;
    std::vector<T> b;
    dot_product_work(std::vector<T> a, std::vector<T> b) : a(a), b(b) {}
    
};

void * dot_product(void *dot_product_work)
{
    return nullptr;
}

void test_concurrency()
{
    pthread_t threads[NUM_THREADS];
    int rc;
    long t;
    for(t=0; t<NUM_THREADS; t++){
        printf("In main: creating thread %ld\n", t);
//        rc = pthread_create(&threads[t], NULL, dot_product(), (void *)t);
        if (rc){
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
    }
    
    pthread_exit(NULL);
}

#endif /* concurrency_h */
