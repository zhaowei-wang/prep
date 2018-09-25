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

int clear_least_sig_digits(int a, int n)
{
    int mask = -1 & ~((1 << n) - 1);
    return a & mask;
}

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
}

#endif /* bits_h */
