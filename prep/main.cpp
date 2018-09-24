//
//  main.cpp
//  prep
//
//  Created by Zhaowei Wang on 8/5/18.
//  Copyright © 2018 Zhaowei Wang. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>


#include "arrays_and_strings.h"
#include "peak_finding.h"
#include "linkedlist.h"
#include "queue_and_stack.h"
#include "trees.h"
#include "graphs.h"
#include "heap.h"

void longest_word_in_string()
{
    std::string search_string = "abppplee";
    std::vector<std::string> candidate_words = {"able", "ale", "apple", "bale",\
        "kangaroo"};
    
    std::unordered_map<std::string, int> index_tracker;
    for (auto word : candidate_words)
    {
        index_tracker[word] = 0;
    }
    
    printf("search_string=%s\n", search_string.c_str());
    printf("candidate words=");
    for (auto s : candidate_words)
    {
        printf("%s ", s.c_str());
    }
    printf("\n");
    
    int j = 0;
    std::string longest_word = "";
    for (size_t i = 0; i < search_string.length(); ++i)
    {
        char curr_char = search_string[i];
        for (auto word : candidate_words)
        {
            j = index_tracker[word];
            if (curr_char == word[j])
            {
                index_tracker[word] += 1;
                
                if (index_tracker[word] == word.length()
                    && longest_word.length() < word.length())
                {
                    longest_word = word;
                }
            }
        }
    }
    
    printf("The longest word in search string is: %s.\n", longest_word.c_str());
}

void stringSplosion()
{
    std::string s = "Code";
    std::string result_string = "";
    for (size_t i = 0; i < s.length(); ++i) {
        result_string += s.substr(0, i+1);
    }
    printf("result=%s\n", result_string.c_str());
}

u_long span_from_vector(std::vector<size_t> v)
{
    return v.back() - v.front() + 1;
}

void maxSpan()
{
    std::vector<int> arr = {1, 4, 2, 1, 4, 4, 4};
    
    std::unordered_map<int, std::vector<size_t>> umap;
    for (size_t i = 0; i < arr.size(); ++i)
    {
        if (umap.find(arr[i]) != umap.end())
        {
            umap[arr[i]].push_back(i);
        }
        else
        {
            umap[arr[i]] = {i};
        }
    }
    
    u_long max_span = 0;
    u_long max_span_int = arr[0];
    for (auto it : umap)
    {
        u_long current_span = span_from_vector(it.second);
        if (max_span < current_span)
        {
            max_span = current_span;
            max_span_int = it.first;
        }
    }
    
    printf("arr=");
    for (auto v : arr)
        printf("%d ", v);
    printf("\nThe longest span length is %ld, of number %ld.\n", max_span, max_span_int);
}

int count_pairs(std::string s)
{
    int count = 0;
    for (int i = 0; i < s.length(); ++i) for (int j = i+1; j < s.length(); ++j)
        if (s[i] == 'A' && s[j] == 'B')
            count += 1;
    
    return count;
}

std::string createString(int N, int K)
{
    int max_pairs = (N % 2) ? N/2 * (N/2 + 1) : N*N/4;
    if (K > max_pairs) return "";
    if (K == max_pairs)
        return (N % 2) ? std::string(N/2, 'A') + std::string(N/2+1, 'B') \
                       : std::string(N/2, 'A') + std::string(N/2, 'B');
    
    std::string s = std::string(N, 'B');
    int i = 0;
    while (K != count_pairs(s))
    {
        s[i++] = 'A';
        if (K < count_pairs(s)) s[i-1] = 'B';
    }
        
    return s;
}

int main(int argc, const char * argv[]) {
//    test_arrays_and_strings();
//    test_peak_finding_1d();
//    test_linked_list();
//    test_queue();
//    test_stack();
//    test_set_of_stacks();
//    test_queue_from_stacks();
//    test_trees();
//    test_graphs();
    test_heap();
    
    return 0;
}























