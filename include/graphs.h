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
#include <unordered_set>
#include <deque>

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
    
    bool contains(NODE_TYPE n)
    {
        return !(_l.find(n) == _l.end());
    }
    
    virtual void add_edge(NODE_TYPE from, NODE_TYPE to, EDGE_TYPE weight)
    {
        if (!contains(from))
            add_node(from);
        
        if (!contains(to))
            add_node(to);
        
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
    
    void print_bfs_from(NODE_TYPE s)
    {
        std::vector<NODE_TYPE> paths;
        std::unordered_map<NODE_TYPE, NODE_TYPE> parent;
        auto track = [&] (NODE_TYPE s) { paths.push_back(s); };
        auto true_pred = [] (NODE_TYPE s) { return true; };
        auto false_pred = [] (NODE_TYPE s) { return false; };
        std::unordered_set<NODE_TYPE> visited;
        
        bfs_visit(s, visited, parent, track, true_pred, false_pred);
        
        std::cout << "BFS from " << s << ":" << std::endl;
        for (const auto& n : paths)
            std::cout << n << " ";
        std::cout << std::endl;
    }
    
    void print_dfs()
    {
        std::cout << "DFS print:";
        auto post = [] (NODE_TYPE s) { std::cout << " " << s; };
        auto pre = [] (NODE_TYPE s) {};
        dfs(pre, post);
        std::cout << std::endl;
    }
    
    bool connected(NODE_TYPE from, NODE_TYPE to)
    {
        return shortest_path_unweighted(from, to) != INT_MAX;
    }
    
    int shortest_path_unweighted(NODE_TYPE from, NODE_TYPE to)
    {
        if (!contains(from) || !contains(to))
            return INT_MAX;
        
        std::unordered_map<NODE_TYPE, NODE_TYPE> parent;
        parent.insert({from, from});
        std::unordered_set<NODE_TYPE> visited;
        
        // initialize a distance hashtable for all nodes to infinity
        std::unordered_map<NODE_TYPE, int> dist;
        for (const auto& keyval : _l)
            dist.insert({keyval.first, INT_MAX});
        
        dist[from] = -1;
        auto update_dist = [&] (NODE_TYPE s) { dist[s] = 1 + dist[parent[s]]; };
        
        auto true_pred = [] (NODE_TYPE s) { return true; };
        auto stop_pred = [=] (NODE_TYPE s) { return s == to; };
        
        bfs_visit(from, visited, parent, update_dist, true_pred, stop_pred);
        
        return dist[to];
    }
    
    bool has_cycle()
    {
        std::unordered_set<NODE_TYPE> history;
        std::unordered_set<NODE_TYPE> visited;
        for (const auto& keyval : _l)
        {
            if (visited.find(keyval.first) == visited.end())
            {
                visited.insert(keyval.first);
                bool ok = has_cycle_internal(keyval.first, visited, history);
                if (ok)
                    return true;
            }
        }
        return false;
    }
    
    void topological_sort()
    {
        if (has_cycle())
        {
            std::cout << "Graph has cycle. No valid topological sort." << std::endl;
            return;
        }
        
        std::deque<NODE_TYPE> q;
        auto pre = [] (NODE_TYPE s) {};
        auto post = [&] (NODE_TYPE s) { q.push_front(s); };
        dfs(pre, post);
        
        std::cout << "Topological sort: ";
        for (const auto& v : q)
            std::cout << v << " ";
        std::cout << std::endl;
    }
    
    // an implementation of Dijkstra, assume non-negative edge weights
    void shortest_path()
    {
        
    }
    
private:
    using GraphEdge = GraphEdgeType<NODE_TYPE, EDGE_TYPE>;
    using EdgeList = std::vector<GraphEdge>;
    using GraphAdjList = std::unordered_map<NODE_TYPE, EdgeList>;
    GraphAdjList _l;
    
    // breadth first search from node s
    template <class func,
              class process_pred,
              class stop_pred>
    void bfs_visit(NODE_TYPE s,
                   std::unordered_set<NODE_TYPE> &visited,
                   std::unordered_map<NODE_TYPE, NODE_TYPE> &parent,
                   func f,
                   process_pred pp,
                   stop_pred sp)
    {
        if (!contains(s))
            return;
        
        std::deque<NODE_TYPE> q;
        q.push_back(s);
        
        while (q.size() > 0)
        {
            NODE_TYPE curr = q.front();
            q.pop_front();
            
            if (!(visited.find(curr) == visited.end()))
                continue;
            
            if (pp(curr))
                f(curr);
            
            visited.insert(curr);
            
            for (const auto& edge : _l[curr])
            {
                parent.insert({edge.to, edge.from});
                q.push_back(edge.to);
            }
            
            if (sp(curr))
                break;
        }
    }
    
    bool has_cycle_internal(NODE_TYPE s,
                            std::unordered_set<NODE_TYPE> &visited,
                            std::unordered_set<NODE_TYPE> history)
    {
        if (visited.find(s) == visited.end())
            visited.insert(s);
        
        if (history.find(s) != history.end())
            return true;
        else
            history.insert(s);
        
        for (const auto& n : _l[s])
        {
            bool ok = has_cycle_internal(n.to, visited, history);
            if (ok)
                return true;
        }
        
        return false;
    }
    
    template <class pre_f, class post_f>
    void dfs(pre_f pre, post_f post)
    {
        std::unordered_map<NODE_TYPE, NODE_TYPE> prev;
        for (const auto& keyval : _l)
        {
            if (prev.find(keyval.first) == prev.end())
            {
                prev.insert({keyval.first, keyval.first});
                dfs_visit(keyval.first, prev, pre, post);
            }
        }
    }
    
    template <class pre_f, class post_f>
    void dfs_visit(NODE_TYPE s,
                   std::unordered_map<NODE_TYPE, NODE_TYPE> &prev,
                   pre_f pre,
                   post_f post)
    {
        pre(s);
        for (const auto& edge : _l[s])
        {
            if (prev.find(edge.to) != prev.end())
                continue;
            
            prev.insert({edge.to, s});
            dfs_visit(edge.to, prev, pre, post);
        }
        post(s);
    }
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

//// prints the shortest path
//void shortest_path(NODE_TYPE from, NODE_TYPE to)
//{
//
//}


void test_graphs()
{
    DGraph<char, int> g;
    g.add_edge('S', 'A', 1);
    g.add_edge('S', 'B', 2);
    g.add_edge('A', 'C', 5);
    g.add_edge('A', 'E', 2);
    g.add_edge('C', 'E', 3);
    g.add_edge('E', 'F', 4);
    g.add_edge('D', 'F', 1);
    g.add_edge('D', 'C', 2);
    g.add_edge('B', 'D', 1);
    g.add_edge('B', 'A', 1);
    
    // back edges
    g.add_edge('E', 'D', 1);
    g.add_edge('A', 'B', 3);
    
    g.print();
    
//    g.print_bfs_from('S');
    char from = 'S';
    char to = 'F';
    std::cout << from << "->" << to << " is connected = " << g.connected(from, to) << std::endl;
    std::cout << "Shortest unweighted path length from " << from << "->" \
        << to << " is " << g.shortest_path_unweighted(from, to) << std::endl;
    
    std::cout << "Has cycle = " << g.has_cycle() << std::endl;
    
    g.print_dfs();
    g.topological_sort();
}
#endif /* graphs_h */
