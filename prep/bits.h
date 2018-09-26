//
//  bits.h
//  prep
//
//  Created by Zhaowei Wang on 9/24/18.
//  Copyright © 2018 Zhaowei Wang. All rights reserved.
//

#ifndef bits_h
#define bits_h

# include <bitset>

// set bit
// clear bit
// toggle bit
// check bit
// changing nth bit to x

int set_bit(int a, int n)
{
    return a | (1 << (n-1));
}

int clear_bit(int a, int n)
{
    return a & ~(1 << (n-1));
}

int toggle_bit(int a, int n)
{
    return a ^ (1 << (n-1));
}

int update_bit_to(int a, int n, bool pred)
{
    return (pred) ? set_bit(a, n) : clear_bit(a, n);
}

// clears all MSB to nth bit
int clear_sig_digits(int a, int n)
{
    int mask = (1 << n) - 1;
    return a & mask;
}

// sets all MSB to nth bit
int set_sig_digits(int a, int n)
{
    int mask = (1 << n) - 1;
    return a | ~mask;
}

// clear all LSB to nth bit
int clear_least_sig_digits(int a, int n)
{
    int mask = -1 & ~((1 << n) - 1);
    return a & mask;
}

int set_least_sig_digits(int a, int n)
{
    int mask = (1 << n) - 1;
    return a | mask;
}

/*
 
 Insertion: You are given two 32-bit numbers, Nand M, and two bit positions, i and j. Write a method to insert Minto N such that M starts at bit j and ends at bit i. You can assume that the bits j through i have enough space to fit all of M. That is, if M= 10011, you can assume that there are at least 5 bits between j and i. You would not, for example, have j = 3 and i = 2, because Mcould not fully fit between bit 3 and bit 2.
 EXAMPLE
 Input: N 10011, i 2, j 6
 Output: N 10001001100
 
 */

int insertion(int n, int m, int j, int i)
{
    int mask = set_sig_digits(0, j);
    mask = set_least_sig_digits(mask, i);
    return (m & mask) ^ (n << (i-1));
}

/*
 
 Binary to String: Given a real number between 0 and 1 (e.g., 0.72) that is passed in as a double, print the binary representation.Ifthe number cannot be represented accurately in binary with at most 32 characters, print "ERROR:'
 
 */

void test_bits()
{
    std::bitset<sizeof(int) * 8> x(set_bit(0, 5));
    std::cout << x << std::endl;
    
    x = clear_bit(-1, 5);
    std::cout << x << std::endl;
    
    x = toggle_bit(-1, 5);
    std::cout << x << std::endl;
    x = toggle_bit((int)x.to_ulong(), 5);
    std::cout << x << std::endl;
    
    x = update_bit_to(-1, 5, false);
    std::cout << x << std::endl;
    
    x = update_bit_to(0, 5, true);
    std::cout << x << std::endl;
    
    x = clear_sig_digits(-1, 30);
    std::cout << x << std::endl;
    
    x = set_sig_digits(0, 30);
    std::cout << x << std::endl;
    
    x = clear_least_sig_digits(-1, 5);
    std::cout << x << std::endl;
    
    x = set_least_sig_digits(0, 5);
    std::cout << x << std::endl;
    
    x = insertion(15, (1 << 20) + 3, 10, 7);
    std::cout << x << std::endl;
}

#endif /* bits_h */
