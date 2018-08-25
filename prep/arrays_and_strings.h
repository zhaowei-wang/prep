//
//  arrays_and_strings.h
//  prep
//
//  Created by Zhaowei Wang on 8/23/18.
//  Copyright © 2018 Zhaowei Wang. All rights reserved.
//

#ifndef arrays_and_strings_h
#define arrays_and_strings_h

#include <iostream>
#include <string>
#include <set>
#include <unordered_map>

// C string library
#include "string.h"

class arrays_and_strings
{
public:
    static inline void is_unique(std::string s)
    {
        std::set<char> set;
        for (std::string::iterator it = s.begin(); it < s.end(); ++it)
        {
            if (set.find(*it) == set.end())
            {
                set.insert(*it);
            }
            else
            {
                std::cout << "string=" << s << " is not unique" << std::endl;
                return;
            }
        }
        std::cout << "string=" << s << " is unique" << std::endl;
    }
    
    static inline void is_permutation(std::string a, std::string b)
    {
        if (a.size() != b.size())
        {
            std::cout << "(" << a << "," << b << ") are not permuatations." << std::endl;
            return;
        }
        std::unordered_map<char, int> m;
        for (auto c = a.begin(); c < a.end(); ++c)
            m[*c] = (m.find(*c) == m.end()) ? 1 : m[*c] + 1;
        
        
        for (auto c = b.begin(); c < b.end(); ++c)
            m[*c] = (m.find(*c) == m.end()) ? 1 : m[*c] - 1;
        
        for (auto it = m.begin(); it != m.end(); ++it)
        {
            if (it->second != 0)
            {
                std::cout << "(" << a << "," << b << ") are not permuatations." << std::endl;
                return;
            }
        }
        
        std::cout << "(" << a << "," << b << ") are permuatations." << std::endl;
    }
    
    static inline void palindrome_permutation(std::string s)
    {
        std::unordered_map<char, size_t> m;
        for (auto c = s.begin(); c < s.end(); ++c)
            if (*c != ' ')
                m[*c] = (m.find(*c) == m.end()) ? 1 : (m[*c] + 1) % 2;

        size_t count = 0;
        for (auto it = m.begin(); it != m.end(); ++it)
            count += it->second;
        
        if (count < 2)
        {
            std::cout << "string=" << s << " is a permutation of a palindrome." << std::endl;
        }
        else
        {
            std::cout << "string=" << s << " is not a permutation of a palindrome." << std::endl;
        }
        
    }
};

#endif /* arrays_and_strings_h */
