//
//  linkedlist.h
//  prep
//
//  Created by Zhaowei Wang on 9/11/18.
//  Copyright © 2018 Zhaowei Wang. All rights reserved.
//

#ifndef linkedlist_h
#define linkedlist_h

#include <iostream>
#include <set>
#include <stdexcept>

template <typename T>
struct Node
{
    T data;
    Node *next;
    Node *prev;
    
    Node(T d) : data(d), next(nullptr), prev(nullptr) { std::cout << "Node()!" << std::endl; };
    Node(T d, Node *next, Node *prev) : data(d), next(next), prev(prev) { std::cout << "Node()!" << std::endl; };
};

template <typename T>
class LinkedList
{
public:
    LinkedList() : head(nullptr), tail(nullptr) { std::cout << "LinkedList()!" << std::endl; };
    ~LinkedList()
    {
        Node<T> *n;
        while (head)
        {
            n = head;
            head = head->next;
            delete n;
        }
    }
    
    inline void push_back(T d)
    {
        if (!tail)
        {
            tail = new Node<T>(d);
            if (!head)
                head = tail;
            return;
        }
        
        Node<T> *n = new Node<T>(d, nullptr, tail);
        tail->next = n;
        tail = n;
    }
    
    inline void push_front(T d)
    {
        if (!head)
        {
            head = new Node<T>(d);
            if (!tail)
                tail = head;
            return;
        }
        
        Node<T> *n = new Node<T>(d, head, nullptr);
        head->prev = n;
        head = n;
    }
    
    inline T pop_front()
    {
        if (!head)
            throw std::out_of_range("Trying to pop_front from empty head.");
        
        if (tail == head)
            tail = nullptr;
        
        T val = head->data;
        Node<T> *n = head;
        head = head->next;
        head->prev = nullptr;
        delete n;
        
        return val;
    }
    
    inline T pop_back()
    {
        if (!tail)
            throw std::out_of_range("Trying to pop_back from empty tail.");
        
        T val = tail->data;
        Node<T> *n = tail;
        tail = tail->prev;
        tail->next = nullptr;
        delete n;
        
        return val;
    }
    
    inline T peek_front()
    {
        return head->data;
    }
    
    inline T peek_back()
    {
        return tail->data;
    }
    
    inline bool remove(T d)
    {
        if (!head)
            return false;
        
        Node<T> *to_del = nullptr;
        if (head->data == d)
        {
            to_del = head;
            head = head->next;
            delete to_del;
            return true;
        }
        
        Node<T> *node_runner = head;
        Node<T> *node_runner_prev = nullptr;
        
        while (node_runner)
        {
            if (node_runner->data == d)
            {
                to_del = node_runner;
                node_runner = node_runner->next;
                node_runner_prev->next = node_runner;
                delete to_del;
                return true;
            }
            else
            {
                node_runner_prev = node_runner;
                node_runner = node_runner->next;
            }
        }
        
        return false;
    }
    
    inline void remove_dup()
    {
        if (!head || !head->next)
            return;
        
        Node<T> *node_runner = head;
        Node<T> *node_runner_prev = nullptr;
        Node<T> *to_del = nullptr;
        std::set<T> s;
        
        while (node_runner)
        {
            if (s.find(node_runner->data) == s.end())
            {
                s.insert(node_runner->data);
                node_runner_prev = node_runner;
            }
            else
            {
                to_del = node_runner;
                node_runner_prev->next = node_runner->next;
                node_runner->next->prev = node_runner_prev;
                delete to_del;
            }
            
            node_runner = node_runner->next;
        }
    }
    
    inline void remove_dup_inplace()
    {
        if (!head || !head->next)
            return;
        
        Node<T> *current = head;
        Node<T> *node_runner = nullptr;
        Node<T> *node_runner_prev = nullptr;
        Node<T> *to_del = nullptr;
        
        while (current)
        {
            node_runner_prev = node_runner;
            node_runner = current->next;
            
            while (node_runner)
            {
                if (node_runner->data == current->data)
                {
                    to_del = node_runner;
                    node_runner_prev->next = node_runner->next;
                    node_runner->next->prev = node_runner_prev;
                    delete to_del;
                }
                else
                {
                    node_runner_prev = node_runner;
                }
                
                node_runner = node_runner->next;
            }
            
            current = current->next;
        }
    }
    
    
    
    inline Node<T> * kth_to_last(size_t k)
    {
        size_t c = 0;
        return kth_to_last_internal(head, k, c);
    }
    
    inline bool delete_middle_node(Node<T> *node)
    {
        if (!node || !node->next)
            return false;
        
        Node<T> *to_del = node->next;
        
        node->data = to_del->data;
        node->next = to_del->next;
        delete to_del;
        
        return true;
    }
    
    inline void partition(T pivot)
    {
        if (!head || !head->next)
            return;
        
        Node<T> *new_head = head;
        Node<T> *tail = new_head;
        Node<T> *next = nullptr;
        head = head->next;
        
        while (head)
        {
            next = head->next;
            
            if (head->data < pivot)
            {
                move_to_front(head, new_head);
            }
            else if (head->data >= pivot)
            {
                move_to_back(head, tail);
            }
            
            head = next;
        }
        
        head = new_head;
    }
    
    inline T sum_lists_reverseorder(LinkedList *l)
    {
        T sum = 0;
        size_t mag = 0;
        size_t s1, s2;
        
        Node<T> *n1 = l->head;
        Node<T> *n2 = head;
        
        while (n1 || n2)
        {
            s1 = 0;
            s2 = 0;
            
            if (n1)
            {
                s1 = n1->data + 10 * mag;
                n1 = n1->next;
            }
            
            if (n2)
            {
                s2 = n2->data + 10 * mag;
                n2 = n2->next;
            }
            
            sum += s1 + s2;
            mag++;
        }
        
        return sum;
    }
    
    inline bool is_palindrome()
    {
        size_t count = 0;
        return is_palindrome_internal(head, count);
    }
    
    inline void print_forward()
    {
        Node<T> *n = head;
        while (n)
        {
            std::cout << "(" << n->data << ")";
            n = n->next;
        }
        std::cout << std::endl;
    }
    
    inline void print_reverse()
    {
        Node<T> *n = tail;
        while (n)
        {
            std::cout << "(" << n->data << ")";
            n = n->prev;
        }
        std::cout << std::endl;
    }
    
protected:
    Node<T> *head;
    Node<T> *tail;
    
private:
    
    
    inline Node<T> * kth_to_last_internal(Node<T> *node, size_t k, size_t& counter)
    {
        if (!node)
            return nullptr;
        
        Node<T> *ret = kth_to_last_internal(node->next, k, counter);
        
        if (ret)
            return ret;
        if (k == counter)
            return node;
        
        counter++;
        return nullptr;
    }
    
    inline void move_to_front(Node<T> *node, Node<T> *&head)
    {
        node->next = head;
        head = node;
    }
    
    inline void move_to_back(Node<T> *node, Node<T> *&tail)
    {
        tail->next = node;
        tail = node;
    }
    
    inline bool is_palindrome_internal(Node<T> *node, size_t& count)
    {
        if (!node)
        {
            count = 0;
            return true;
        }
        
        bool is_pal = is_palindrome_internal(node->next, count);
        
        if (!is_pal)
            return false;
        
        Node<T> *runner = head;
        for (size_t i = 0; i < count; ++i)
            runner = runner->next;
        
        count++;
        if (runner->data == node->data)
        {
            return true;
        }
        else
        {
            return false;
        }
        
    }
};

void test_linked_list()
{
    LinkedList<int> l;
//    l.push_back(1);
//    l.push_front(2);
//    l.push_front(3);
//    l.push_back(0);
//    l.print_forward();
//    l.remove(3);
//    l.remove(1);
//    l.remove(0);
//    l.print_forward();
    
    l.push_back(0);
    l.push_front(1);
    l.push_front(0);
    l.push_back(0);
    l.push_back(2);
    l.push_back(0);
    l.push_back(1);
    l.push_back(1);
    l.push_back(8);
    l.push_back(4);
    l.push_back(32);
    l.push_back(15);
    l.push_back(29);
    l.print_forward();
    l.remove_dup_inplace();
    l.print_forward();
    l.print_reverse();
    l.pop_back();
    l.pop_front();
    l.print_forward();
    l.print_reverse();
    
    size_t k = 1;
    Node<int> *node = l.kth_to_last(k);
    std::cout << k << " to last = " << node->data << std::endl;

    l.print_forward();
    l.partition(15);
    l.print_forward();

    LinkedList<int> l1;
    l1.push_back(0);
    l1.push_back(1);

    LinkedList<int> l2;
    l2.push_back(0);

    std::cout << "Sum of lists = " << l1.sum_lists_reverseorder(&l2) << std::endl;

    LinkedList<char> l3;
    l3.push_back('c');
    l3.push_back('a');
    l3.push_back('b');
    l3.push_back('b');
    l3.push_back('a');
    l3.push_back('c');

    std::cout << "Is palindrome = " << l3.is_palindrome() << std::endl;
    
}

#endif /* linkedlist_h */
