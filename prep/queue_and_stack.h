//
//  queue.h
//  prep
//
//  Created by Charlie Wang on 9/14/18.
//  Copyright © 2018 Zhaowei Wang. All rights reserved.
//

#ifndef queue_and_stack_h
#define queue_and_stack_h

#include <iostream>
#include <vector>

#include "linkedlist.h"

template <typename T>
struct queue : public LinkedList<T>
{
    void push(T val)
    {
        LinkedList<T>::push_front(val);
    }
    
    T pop()
    {
        return LinkedList<T>::pop_back();
    }
    
    T peek()
    {
        return LinkedList<T>::peek_back();
    }
    
    void print()
    {
        std::cout << "Queue:" << std::endl;
        LinkedList<T>::print_reverse();
    }
};

template <typename T>
struct stack : public LinkedList<T>
{
    void push(T val)
    {
        LinkedList<T>::push_front(val);
    }
    
    T pop()
    {
        return LinkedList<T>::pop_front();
    }
    
    T peek()
    {
        return LinkedList<T>::peek_front();
    }
    
    void print()
    {
        std::cout << "Stack:" << std::endl;
        LinkedList<T>::print_forward();
    }
};

template <typename T,
          size_t MAX_CAPACITY = 3>
class set_of_stacks
{
public:
    set_of_stacks() : _total_elements(0) {}
    
    void push(T val)
    {
        size_t i = _stack_index();
        _total_elements++;
        
        if (i >= _stacks.size())
            _stacks.push_back(stack<T>());
        
        _stacks.at(i).push(val);
    }
    
    T pop()
    {
        _total_elements--;
        size_t i = _stack_index();
        
        T val = _stacks.at(i).pop();
        
        if (i < _stacks.size() - 1)
            _stacks.pop_back();
        
        return val;
    }
    
    void print()
    {
        std::cout << "Set of stacks:" << std::endl;
        for (size_t i = 0; i < _stacks.size(); ++i)
        {
            _stacks.at(i).print();
        }
    }
    
private:
    size_t _stack_index() { return _total_elements / MAX_CAPACITY; }
    
    std::vector<stack<T>> _stacks;
    size_t _total_elements;
};

template <typename T>
class queue_from_two_stacks
{
public:
    void push(T val)
    {
        s1.push(val);
    }
    
    T pop()
    {
        shift_s1_s2();
        T val = s2.pop();
        shift_s2_s1();
        return val;
    }
    
    void print()
    {
        s1.print();
        s2.print();
    }
    
private:
    stack<T> s1, s2;
    
    void shift_s1_s2() { shift(s1, s2); }
    void shift_s2_s1() { shift(s2, s1); }
    
    void shift (stack<T>& s1, stack<T>& s2)
    {
        while (!s1.is_empty())
        {
            s2.push(s1.pop());
        }
    }
};

# pragma mark test queue

void test_queue()
{
    queue<int> q;
    q.push(1);
    q.push(2);
    q.push(3);
    q.print();
    q.pop();
    q.print();
}

#pragma mark test stack

void test_stack()
{
    stack<int> s;
    s.push(1);
    s.push(2);
    s.push(3);
    s.print();
    s.pop();
    s.print();
}

void test_set_of_stacks()
{
    set_of_stacks<int> ss;
    for (int i = 0; i < 10; ++i)
        ss.push(i);
    
    ss.print();
    
    for (int i = 0; i < 5; ++i)
        ss.pop();
    
    ss.print();
    
}

void test_queue_from_stacks()
{
    queue_from_two_stacks<int> q;
    q.push(1);
    q.push(2);
    q.push(3);
    q.print();
    q.pop();
    q.print();
    q.pop();
    q.print();
}

#endif /* queue_and_stack_h */
