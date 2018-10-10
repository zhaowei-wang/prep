//
//  peak_finding.h
//  prep
//
//  Created by Zhaowei Wang on 8/25/18.
//  Copyright © 2018 Zhaowei Wang. All rights reserved.
//

#ifndef peak_finding_h
#define peak_finding_h

#include <iostream>
#include <vector>
#include <ctime>
#include <random>
#include <algorithm>

class peak_finding
{
public:
    // returns true if index s is a peak
    static bool find_peak_1d_internal(const std::vector<int>& v, size_t& n,
                               size_t ll, size_t ul)
    {
        if (ul - ll == 1)
        {
            n = ll;
            return true;
        }
        
        n = (size_t) ll + (ul - ll) / 2;
        
        // edges
        if (n - 1 < ll && v.at(n) >= v.at(n + 1)) return true;
        if (n + 1 >= ul && v.at(n) >= v.at(n - 1)) return true;
        
        if (v.at(n) <= v.at(n - 1))
        {
            return find_peak_1d_internal(v, n, ll, n);
        }
        else if (v.at(n) <= v.at(n + 1))
        {
            return find_peak_1d_internal(v, n, n, ul);
        }
        else
        {
            return true;
        }
    }
    
    // find a peak where element b is >= than both its neighbours
    static inline bool find_peak_1d(const std::vector<int>& v, size_t& n)
    {
        return find_peak_1d_internal(v, n, 0, v.size());
        
    }
};

void test_peak_finding_1d()
{
    // generate random numbers
    // First create an instance of an engine.
    std::random_device rnd_device;
    // Specify the engine and distribution.
    std::mt19937 mersenne_engine {rnd_device()};  // Generates random integers
    std::uniform_int_distribution<int> dist {1, 52};
    
    auto gen = [&dist, &mersenne_engine](){
        return dist(mersenne_engine);
    };
    
    std::vector<int> v(10000000);
    std::generate(begin(v), end(v), gen);
    
    size_t n = 0;
    clock_t t1 = std::clock();
    bool ret = peak_finding::find_peak_1d(v, n);
    clock_t t2 = std::clock();
    if (ret)
    {
        std::cout << "Found peak at index=" << std::to_string(n) << std::endl;
        
        std::cout << std::to_string(v.at(n-1)) << "," << std::to_string(v.at(n)) << "," << std::to_string(v.at(n+1)) << std::endl;
    }
    else
    {
        std::cout << "Did not find peak.";
    }
    std::cout << "peak finding took: " << std::to_string((double)(t2-t1) / CLOCKS_PER_SEC) << std::endl;
}

#endif /* peak_finding_h */
