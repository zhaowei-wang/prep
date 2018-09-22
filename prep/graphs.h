//
//  graphs.h
//  prep
//
//  Created by Zhaowei Wang on 9/21/18.
//  Copyright © 2018 Zhaowei Wang. All rights reserved.
//

#ifndef graphs_h
#define graphs_h

#include <iostream>
#include <vector>
#include <unordered_map>

template <class T, class K>
struct GraphEdgeType
{
    T from;
    T to;
    K weight;
    GraphEdgeType() {}
    GraphEdgeType(T f, T t, K v) : from(f), to(t), weight(v) {}
};

template <class NODE_TYPE, class EDGE_TYPE>
class DGraph
{
public:
    DGraph() {}
    ~DGraph() {}
    
    virtual void add_node(NODE_TYPE name)
    {
        if (_l.find(name) == _l.end())
            _l.insert({name, EdgeList()});
    }
    
    virtual void add_edge(NODE_TYPE from, NODE_TYPE to, EDGE_TYPE weight)
    {
        if (_l.find(from) == _l.end())
            _l.insert({from, EdgeList()});
        
        _l[from].push_back(GraphEdge(from, to, weight));
    }
    
    virtual void print()
    {
        std::cout << "Graph:" << std::endl;
        for (const auto& keyval : _l)
        {
            std::cout << keyval.first << " : ";
            for (const auto& val : keyval.second)
            {
                std::cout << "(" << val.to << "," << val.weight << ")";
            }
            std::cout << std::endl;
        }
    }
    
private:
    using GraphEdge = GraphEdgeType<NODE_TYPE, EDGE_TYPE>;
    using EdgeList = std::vector<GraphEdge>;
    using GraphAdjList = std::unordered_map<NODE_TYPE, EdgeList>;
    GraphAdjList _l;
};

template <class NODE_TYPE, class EDGE_TYPE>
class UGraph : public DGraph<NODE_TYPE, EDGE_TYPE>
{
public:
   void add_edge(NODE_TYPE from, NODE_TYPE to, EDGE_TYPE weight)
    {
        DGraph<NODE_TYPE, EDGE_TYPE>::add_edge(from, to, weight);
        DGraph<NODE_TYPE, EDGE_TYPE>::add_edge(to, from, weight);
    }
    
private:
};

void test_graphs()
{
    UGraph<int, int> g;
    g.add_node(1);
    g.add_node(2);
    g.add_node(3);
    g.add_edge(1,2,1);
    g.add_edge(1,3,1);
    g.print();
}
#endif /* graphs_h */
