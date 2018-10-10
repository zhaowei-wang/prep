//
//  recursion_dynamic_programming.h
//  prep
//
//  Created by Zhaowei Wang on 9/25/18.
//  Copyright © 2018 Zhaowei Wang. All rights reserved.
//

#ifndef recursion_dynamic_programming_h
#define recursion_dynamic_programming_h

#include <vector>
#include <utility>
#include <algorithm>

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

// grid, true if valid location, false if not
using grid1d = std::vector<bool>;
using grid2d = std::vector<grid1d>;
using path = std::vector<std::pair<size_t, size_t>>;

bool grid_at(const grid2d &grid, size_t i, size_t j)
{
    if (i >= grid.size() || j >= grid.at(0).size())
        return false;
    
    return grid.at(i).at(j);
}

void grid_set(grid2d &grid, size_t i, size_t j, bool val)
{
    grid.at(i).at(j) = val;
}

void print_grid(const grid2d &grid)
{
    std::cout << "Grid:" << std::endl;
    for (const auto& row : grid)
    {
        for (const auto col : row)
            std::cout << col << " ";
        std::cout << std::endl;
    }
}

void print_path(const path &p)
{
    for (const auto& ele : p)
        std::cout << "(" << ele.first << "," << ele.second << ") ";
    std::cout << std::endl;
}

void robot_in_a_grid_internal(const grid2d &grid, size_t i, size_t j, path p)
{
    if (i == grid.size() - 1 && j == grid[0].size() - 1)
    {
        p.push_back({i, j});
        print_path(p);
        return;
    }
    
    if (!grid_at(grid, i+1, j) && !grid_at(grid, i, j+1))
        return;
    
    // update path
    p.push_back({i, j});
    
    // go down
    if (grid_at(grid, i+1, j))
        robot_in_a_grid_internal(grid, i+1, j, p);
    
    // go right
    if (grid_at(grid, i, j+1))
        robot_in_a_grid_internal(grid, i, j+1, p);
}

void robot_in_a_grid(const grid2d &grid)
{
    path p;
    robot_in_a_grid_internal(grid, 0, 0, p);
}

/*
 Magic Index: A magic index in an array A[0... n-1] is defined to be an index such that A[ i] = i. Given a sorted array of distinct integers, write a method to find a magic index, if one exists, in array A.
 FOLLOW UP
 What if the values are not distinct?
 */

int binary_search_for_magic_index1(const std::vector<int> &v, int i, int j)
{
    if (i == j)
        return (v.at(i) == i) ? i : -1;
    
    int n = i + (j-i) / 2;
    
    if (v.at(n) == n)
        return n;
    else if (v.at(n) > n)
        return binary_search_for_magic_index1(v, i, n);
    else
        return binary_search_for_magic_index1(v, n+1, j);
}

int magic_index_distinct(std::vector<int> v)
{
    return binary_search_for_magic_index1(v, 0, v.size());
}

int binary_search_for_magic_index2(const std::vector<int> &v, int i, int j)
{
    if (i == j)
        return (v.at(i) == i) ? i : -1;
    
    int n = (i + j) / 2;
    if (v.at(n) == n)
        return n;
    
    // search both left right since we only have weak ordering in this case
    int ret = binary_search_for_magic_index2(v, i, n);
    if (ret == -1)
        ret = binary_search_for_magic_index2(v, n+1, j);
    
    return ret;
}

int magic_index(std::vector<int> v)
{
    return binary_search_for_magic_index2(v, 0, v.size());
}

/*
 Power Set: Write a method to return all subsets of a set.
 */

// |S| = 1
// {}, {a1}
// |S| = 2
// {}, {a1}, {a2}, {a1, a2} = P(1) + (P(1)U{a2})

void power_set_internal(const std::vector<int> &v,
                        std::vector<std::vector<int>> &subsets,
                        int n)
{
    if (n < 0)
    {
        subsets.push_back(std::vector<int>());
        return;
    }
    
    power_set_internal(v, subsets, n-1);
    
    std::vector<std::vector<int>> nth_subsets;
    for (const auto& subset : subsets)
    {
        int val = v.at(n);
        std::vector<int> curr_subset = subset;
        curr_subset.push_back(val);
        nth_subsets.push_back(curr_subset);
    }
    subsets.insert(subsets.end(), nth_subsets.begin(), nth_subsets.end());
}

void power_set(const std::vector<int> &v)
{
    std::vector<std::vector<int>> subsets;
    power_set_internal(v, subsets, v.size()-1);
    
    for (const auto &subset : subsets)
    {
        std::cout << "{";
        for (const auto &val : subset)
            std::cout << val << ",";
        std::cout << "}" << std::endl;
    }
}

/*
<<<<<<< HEAD
 Towers of Hanoi: In the classic problem of the Towers of Hanoi, you have 3 towers and N disks of different sizes which can slide onto any tower.The puzzle starts with disks sorted in ascending order of size from top to bottom (Le., each disk sits on top of an even larger one). You have the following constraints:
     (1) Only one disk can be moved at a time.
     (2) A disk is slid off the top of one tower onto another tower.
     (3) A disk cannot be placed on top of a smaller disk.
     Write a program to move the disks from the first tower to the last using Stacks.
 */

void hanoi(int n, std::vector<int> &source, std::vector<int> &destination, std::vector<int> &buffer)
{
    if (n < 0)
        return;
    
    hanoi(n-1, source, buffer, destination);
    destination.push_back(source.back());
    source.pop_back();
    hanoi(n-1, buffer, destination, source);
}

/*
 Permutations without Dups: Write a method to compute all permutations of a string of unique characters.
 */

void string_perm_internal(std::string current, std::string left, std::vector<std::string> &all)
{
    if (left.length() == 0)
    {
        all.push_back(current);
        return;
    }
    
    for (size_t i = 0; i < left.length(); ++i)
    {
        std::string s = left;
        string_perm_internal(current + left.at(i), s.erase(i,1), all);
    }
}

void string_permutations(std::string s)
{
    std::vector<std::string> all;
    string_perm_internal("", s, all);
    std::cout << "Printing all permutations of " << s << std::endl;
    for (const auto& ss : all)
        std::cout << ss << std::endl;
}

/*
 Coins: Given an infinite number of quarters (25 cents), dimes (10 cents), nickels (5 cents), and
 pennies (1 cent), write code to calculate the number of ways of representing n cents.
 */

int coins(int n, const std::vector<int> &denoms)
{
    if (n < 0)
        return 0;
    if (n == 0)
        return 1;
    
    int ret = 0;
    for (const auto& denom : denoms)
        ret += coins(n - denom, denoms);
    
    return ret;
}

void test_rdp()
{
    int n = 10;
    std::cout << "# ways to climb " << n << " stairs in {1,2,3} steps is " << \
                triple_step(n) << std::endl;
    
    std::cout << "paths to reach bottom right corner:" << std::endl;
    int gridn, gridm;
    gridn = 4;
    gridm = 4;
    grid2d grid(gridn, grid1d(gridm, true));
    grid_set(grid, 1, 2, false);
    grid_set(grid, 1, 3, false);
    grid_set(grid, 1, 1, false);
    print_grid(grid);
    robot_in_a_grid(grid);
    
    std::cout << "looking for magic index in:" << std::endl;
    std::vector<int> v = {-10, 9, 8, 1, 1, 1, 4, 20, 15};
    std::sort(v.begin(), v.end());
    for (const auto& ele : v)
        std::cout << ele << " ";
    std::cout << std::endl;
    std::cout << "magic index = " << std::endl;
    int ret = magic_index(v);
    std::cout << ret << std::endl;
    
    std::cout << "power set" << std::endl;
    std::vector<int> vv = {0, 1, 2, 3};
    power_set(vv);
    
    std::cout << "hanoi" << std::endl;
    std::vector<int> a, b, c;
    a = {5, 4, 3, 2, 1};
    
    std::cout << "initial state" << std::endl;
    for (auto const &ele : a)
        std::cout << ele << " ";
    std::cout << std::endl;
    
    for (auto const &ele : c)
        std::cout << ele << " ";
    std::cout << std::endl;
    hanoi(a.size() - 1, a, c, b);
    std::cout << "final state" << std::endl;
    for (auto const &ele : a)
        std::cout << ele << " ";
    std::cout << std::endl;
    
    for (auto const &ele : c)
        std::cout << ele << " ";
    std::cout << std::endl;
    
    string_permutations("abcd");

    std::vector<int> denoms = {1, 5, 10, 25};
    int value = 11;
    std::cout << "# ways to count " << value << " is " << coins(value, denoms) << std::endl;
}

#endif /* recursion_dynamic_programming_h */
