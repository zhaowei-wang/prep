//
//  graphs.h
//  prep
//
//  Created by Zhaowei Wang on 9/21/18.
//  Copyright © 2018 Zhaowei Wang. All rights reserved.
//

#ifndef graphs_h
#define graphs_h

#include <vector>
#include <unordered_map>

template <class T>
struct GraphNode
{
    T n;
    GraphNode(T t) : n(t) {}
};

template <class T, class K>
struct Edge
{
    GraphNode<T> n;
    K w;
    
    Edge(T t, K k) : n(t), w(k) {}
};

template <class T, class K>
using AdjList = std::unordered_map<GraphNode<T>, std::vector<Edge<T, K>>>;

void test_graphs()
{
    AdjList<int, int> l(5);
}
#endif /* graphs_h */
