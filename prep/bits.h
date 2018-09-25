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
//    return a ^ 
}

void test_bits()
{
    std::bitset<sizeof(int) * 8> x(set_bit(0, 5));
    std::cout << x << std::endl;
    
    x = clear_bit(-1, 5);
    std::cout << x << std::endl;
}

#endif /* bits_h */
