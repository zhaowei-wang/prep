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
#include <list>
#include <memory>
#include <math.h>

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
    
    static inline void string_compression(std::string s)
    {
        if (s.length() < 2) std::cout << "string=" << s << " is shortest." << std::endl;
        
        struct char_node
        {
            char c;
            size_t count;
            char_node() = delete;
            char_node(char _c, size_t _count) : c(_c), count(_count) {};
            void inc() { count++; }
        };
        
        std::list<std::unique_ptr<char_node>> l;
        auto it = l.begin();
        for (auto c = s.begin(); c < s.end(); ++c)
        {
            if (l.size() == 0 || (*it)->c != *c)
            {
                l.push_back(std::make_unique<char_node>(*c, 1));
                it++;
            }
            else
            {
                (*it)->inc();
            }
            
        }
        
        std::string result = "";
        for (auto it = l.begin(); it != l.end(); ++it)
        {
            result += (*it)->c;
            result += std::to_string((*it)->count);
        }
        
        if (result.size() > s.size())
        {
            std::cout << "string=" << s << " is shortest." << std::endl;
        }
        else
        {
            std::cout << "string=" << s << " is compressed to " << result << "." << std::endl;
        }
    }
    
    static inline void string_compression2(std::string s)
    {
        if (s.length() < 2) std::cout << "string=" << s << " is shortest." << std::endl;
        
        std::string result = "";
        
        char curr_c = s.at(0);
        size_t count = 0;
        result += curr_c;
        for (size_t i = 0; i < s.length(); ++i)
        {
            if (s.at(i) == curr_c)
            {
                count++;
            }
            else
            {
                result += std::to_string(count);
                curr_c = s.at(i);
                result += curr_c;
                count = 1;
            }
        }
        result += std::to_string(count);
        
        if (result.size() > s.size())
        {
            std::cout << "string=" << s << " is shortest." << std::endl;
        }
        else
        {
            std::cout << "string=" << s << " is compressed to " << result << "." << std::endl;
        }
    }
};

void test_arrays_and_strings()
{
    arrays_and_strings::is_unique("abcadef");
    arrays_and_strings::is_unique("abcef");
    arrays_and_strings::is_permutation("abcd", "b");
    arrays_and_strings::is_permutation("abcd", "bcd a");
    arrays_and_strings::palindrome_permutation("tcao cat");
    arrays_and_strings::string_compression("aaaaaabbc");
    arrays_and_strings::string_compression2("aaaaaabbc");
}

#endif /* arrays_and_strings_h */
