//
//  recursion_dynamic_programming.h
//  prep
//
//  Created by Zhaowei Wang on 9/25/18.
//  Copyright © 2018 Zhaowei Wang. All rights reserved.
//

#ifndef recursion_dynamic_programming_h
#define recursion_dynamic_programming_h

/*
 Triple Step: A child is running up a staircase with n steps and can hop either 1 step, 2 steps, or 3 steps at a time. Implement a method to count how many possible ways the child can run up the stairs.
 */

size_t triple_step_internal(size_t n, std::vector<size_t> &memo)
{
    if (n < 1) return 0;
    if (n == 1) return 1;
    if (n == 2) return 2;
    if (n == 3) return 4;
    
    if (memo[n-1] == 0)
    {
        memo[n-1] += triple_step_internal(n-1, memo);
        memo[n-1] += triple_step_internal(n-2, memo);
        memo[n-1] += triple_step_internal(n-3, memo);
    }
    
    return memo[n-1];
}
        
size_t triple_step(int n)
{
    std::vector<size_t> v(n, 0);
    return triple_step_internal(n, v);
}

/*
 Robot in a Grid: Imagine a robot sitting on the upper left corner of grid with r rows and c columns. The robot can only move in two directions, right and down, but certain cells are "off limits" such that the robot cannot step on them. Design an algorithm to find a path for the robot from the top left to the bottom right.
 */

void test_rdp()
{
    int n = 10;
    std::cout << "# ways to climb " << n << " stairs in {1,2,3} steps is " << \
                triple_step(n) << std::endl;
}

#endif /* recursion_dynamic_programming_h */
