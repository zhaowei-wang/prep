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

template <typename T>
struct Node
{
    T data;
    Node *next;
    
    Node(T d) : data(d), next(nullptr) { std::cout << "Node()!" << std::endl; };
};

template <typename T>
class LinkedList
{
public:
    LinkedList() : head(nullptr) { std::cout << "LinkedList()!" << std::endl; };
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
        if (!head)
        {
            head = new Node<T>(d);
            return;
        }
        
        Node<T> *n = head;
        while (n->next)
            n = n->next;
        
        n->next = new Node<T>(d);
    }
    
    inline void push_front(T d)
    {
        Node<T> *n = new Node<T>(d);
        n->next = head;
        head = n;
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
    
    inline void print()
    {
        Node<T> *n = head;
        while (n)
        {
            std::cout << "(" << n->data << ")";
            n = n->next;
        }
        std::cout << std::endl;
    }
    
private:
    Node<T> *head;
    
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
};

void test_linked_list()
{
    LinkedList<int> l;
//    l.push_back(1);
//    l.push_front(2);
//    l.push_front(3);
//    l.push_back(0);
//    l.print();
//    l.remove(3);
//    l.remove(1);
//    l.remove(0);
//    l.print();
    
    l.push_back(0);
    l.push_front(1);
    l.push_front(0);
    l.push_back(0);
    l.push_back(2);
    l.push_back(0);
    l.push_back(1);
    l.push_back(1);
    l.print();
    l.remove_dup_inplace();
    l.print();
    
    size_t k = 3;
    Node<int> *node = l.kth_to_last(k);
    std::cout << k << " to last = " << node->data << std::endl;
    
}

#endif /* linkedlist_h */
