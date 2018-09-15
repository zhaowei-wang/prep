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
#include "linkedlist.h"

template <typename T>
struct queue : protected LinkedList<T>
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
struct stack : protected LinkedList<T>
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

#endif /* queue_and_stack_h */
