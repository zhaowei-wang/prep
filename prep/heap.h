//
//  heap.h
//  prep
//
//  Created by Charlie Wang on 9/22/18.
//  Copyright © 2018 Zhaowei Wang. All rights reserved.
//

#ifndef heap_h
#define heap_h

#include <unordered_map>
#include <vector>
#include <utility>

// priority queue implementation from heap with hash table look-up for IDs with
// non-integer type

template <class IDType, class PriorityType>
struct HeapElementType
{
    PriorityType val;
    IDType key;
    
    HeapElementType(IDType key, PriorityType val) : key(key), val(val) {}
};

template <class PriorityType>
struct MinHeapCompare
{
    bool operator() (PriorityType a, PriorityType b) { return a > b; }
};

template <class IDType,
          class PriorityType,
          class HeapCompare = MinHeapCompare<PriorityType>>
class Heap
{
public:
    void insert(IDType key, PriorityType val)
    {
        _binary_heap.push_back(HeapElement(key, val));
        _index_map[key] = _binary_heap.size() - 1;
        
        percolate_up(_index_map[key]);
    }
    
    void update(IDType key, PriorityType val)
    {
        size_t index = _index_map.at(key);
        PriorityType old = _binary_heap[key].val;
        _binary_heap[index] = HeapElement(key, val);
        if (compare(val, old))
            percolate_down(index);
        else
            percolate_up(index);
    }
    
    std::pair<IDType, PriorityType> peek()
    {
        return {_binary_heap[root()].key, _binary_heap[root()].val};
    }
    
    void extract()
    {
        swap(root(), _binary_heap.size() - 1);
        _index_map.erase(_binary_heap[_binary_heap.size() - 1].key);
        _binary_heap.pop_back();
        percolate_down(root());
    }
    
    void print()
    {
        std::cout << "Heap:" << std::endl;
        for (const auto& a : _binary_heap)
            std::cout << "(" << a.key << "," << a.val << ")";
        
        std::cout << std::endl << "Index Map:" << std::endl;
        for (const auto& a : _index_map)
            std::cout << "(" << a.first << "," << a.second << ")";
        std::cout << std::endl;
    }
    
    size_t size()
    {
        return _binary_heap.size();
    }
    
private:
    using HeapElement = HeapElementType<IDType, PriorityType>;
    std::vector<HeapElement> _binary_heap;
    std::unordered_map<IDType, size_t> _index_map;
    HeapCompare compare;
    
    void percolate_up(size_t start)
    {
        for (size_t i = start; i != 0; i = parent(i))
            heapify(i);
        // since the above loop doesn't hit 0
        heapify(0);
    }
    
    void percolate_down(size_t start)
    {
        if (start >= _binary_heap.size())
            return;
        
        size_t next = heapify(start);
        if (start != next)
            percolate_down(heapify(next));
    }
    
    size_t heapify(size_t i)
    {
        size_t root = i;
        size_t l = left(i);
        size_t r = right(i);
        size_t hsize = _binary_heap.size();
        
        if (l < hsize && compare(_binary_heap[root].val, _binary_heap[l].val))
            root = l;
            
        if (r < hsize && compare(_binary_heap[root].val, _binary_heap[r].val))
            root = r;
        
        if (root != i)
            swap(root, i);
        
        return root;
    }
    
    void swap(size_t i, size_t j)
    {
        _index_map[_binary_heap[i].key] = j;
        _index_map[_binary_heap[j].key] = i;
        
        HeapElement a = _binary_heap[i];
        _binary_heap[i] = _binary_heap[j];
        _binary_heap[j] = a;
    }
    
    size_t root() { return 0; }
    size_t left(size_t i) { return 2*(i+1) - 1; }
    size_t right(size_t i) { return 2*(i+1); }
    size_t parent(size_t i) { return (i-1) / 2; }
};

void test_heap()
{
    Heap<char, int> h;
    h.insert('a', 10);
    h.insert('b', 2);
    h.insert('c', 32);
    h.insert('d', 5);
    h.insert('e', 11);
    h.insert('f', 15);
    h.insert('g', 9);
    h.insert('h', 1);
    h.print();
    h.update('h', 99);
    h.print();
    
//    while (h.size() > 0)
//    {
//        auto keyval = h.peek();
//        std::cout << "Removing (" << keyval.first << "," << keyval.second << ")" << std::endl;
//        h.extract();
//        h.print();
//    }
}

#endif /* heap_h */
