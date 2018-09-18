//
//  trees_and_graphs.h
//  prep
//
//  Created by Charlie Wang on 9/17/18.
//  Copyright © 2018 Zhaowei Wang. All rights reserved.
//

#ifndef trees_and_graphs_h
#define trees_and_graphs_h

#include <vector>
#include <unordered_map>

#pragma mark binary tree
// binary tree node

template <class T>
struct tree_node
{
    T data;
    tree_node *left, *right;
    
    tree_node() : left(nullptr), right(nullptr) {}
    tree_node(T val) : data(val), left(nullptr), right(nullptr) {}
    tree_node(T val, tree_node *lp, tree_node *rp) : data(val), left(lp), right(rp) {}
};

// simple binary tree implemented through stl.
template <typename T>
class binary_tree
{
public:
    binary_tree() : _root(nullptr) {}
    binary_tree(tree_node<T> *r) : _root(r) {}
    
    binary_tree(const binary_tree& tree)
    {
        copy_tree(tree._root, _root);
    }
    
    binary_tree& operator=(binary_tree tree)
    {
        copy_tree(tree._root, _root);
        return *this;
    }
    
    ~binary_tree()
    {
        auto f = [&](tree_node<T> *r) {
            delete r;
        };
        
        auto p = [](tree_node<T> *r) -> bool {
            return true;
        };
        
        post_order_traversal(_root, f, p);
    }
    
    void print()
    {
        std::vector<T> traversal;
        
        auto f = [&](tree_node<T> *r) {
            traversal.push_back(r->data);
        };
        
        auto p = [](tree_node<T> *r) -> bool {
            return true;
        };
        
        in_order_traversal(_root, f, p);
        
        std::cout << "binary tree traversal: ";
        for (const auto& n : traversal)
            std::cout << "(" << n << ")";
        std::cout << std::endl;
    }
protected:
    tree_node<T> *_root;
    
private:
    template <class func, class pred>
    void post_order_traversal(tree_node<T> *root, func f, pred p)
    {
        if (!root)
            return;
        
        post_order_traversal(root->left, f, p);
        post_order_traversal(root->right, f, p);
        if (p(root))
            f(root);
    }
    
    template <class func, class pred>
    void in_order_traversal(tree_node<T> *root, func f, pred p)
    {
        if (!root)
            return;
        
        in_order_traversal(root->left, f, p);
        if (p(root))
            f(root);
        in_order_traversal(root->right, f, p);
    }
    
    template <class func, class pred>
    void pre_order_traversal(tree_node<T> *root, func f, pred p)
    {
        if (!root)
            return;
        
        if (p(root))
            f(root);
        pre_order_traversal(root->left, f, p);
        pre_order_traversal(root->right, f, p);
    }
    
    // copies a to b
    void copy_tree(const tree_node<T> *a, tree_node<T> *&b)
    {
        if (!a)
            return;

        b = new tree_node<T>(a->data);
        copy_tree(a->left, b->left);
        copy_tree(a->right, b->right);
    }
};

template <class T>
class binary_search_tree : public binary_tree<T>
{
public:
    binary_search_tree() : binary_tree<T>() {}
    binary_search_tree(tree_node<T> *r) : binary_tree<T>(r) {}
    
    void insert(T val)
    {
        insert_internal(binary_tree<T>::_root, val);
    }
    
    void remove(T val)
    {
        std::unordered_map<tree_node<T> *, tree_node<T> *> prev;
        prev.insert({binary_tree<T>::_root, nullptr});
        tree_node<T> *n = find_internal(binary_tree<T>::_root, &prev, val);
        if (n)
            remove_internal(n, prev);
    }
    
    bool find(T val)
    {
        tree_node<T> *n = find_internal(binary_tree<T>::_root, nullptr, val);
         if (!n)
             return false;
        
        return true;
    }
    
private:
    void insert_internal(tree_node<T> *&curr, T val)
    {
        if (!curr)
        {
            curr = new tree_node<T>(val);
            return;
        }
        
        if (curr->data > val)
        {
            insert_internal(curr->left, val);
        }
        else if (curr->data < val)
        {
            insert_internal(curr->right, val);
        }
    }
    
    // finds val in tree, returns if found or not
    tree_node<T> * find_internal(tree_node<T> *root,
                                 std::unordered_map<tree_node<T> *, tree_node<T> *> *prev,
                                 T val) const
    {
        if (!root)
            return nullptr;
        
        if (root->data == val)
        {
            return root;
        }
        else if (root->data > val)
        {
            if (prev)
                (*prev)[root->left] = root;
            return find_internal(root->left, prev, val);
        }
        else if (root->data < val)
        {
            if (prev)
                (*prev)[root->right] = root;
            return find_internal(root->right, prev, val);
        }
        
        return nullptr;
    }
    
    // helper function, given a node to delete r, set the left or right child
    // pointer from r's ancestor to next
    void set_ancestor(tree_node<T> *r,
                          const std::unordered_map<tree_node<T> *, tree_node<T> *> prev,
                          tree_node<T> *next)
    {
        tree_node<T> *ancestor = prev.at(r);
        if (ancestor)
        {
            bool is_left_child = (ancestor->left == r) ? true : false;
            if (is_left_child)
            {
                ancestor->left = next;
            }
            else
            {
                ancestor->right = next;
            }
        }
    }
    
    // deletes curr from tree
    void remove_internal(tree_node<T> *r,
                         const std::unordered_map<tree_node<T> *, tree_node<T> *> prev)
    {
        if (!r->left && !r->right)
        {
            // delete r and fix dangling pointer
            set_ancestor(r, prev, nullptr);
            delete r;
        }
        else if (r->left && !r->right)
        {
            // delete r and make ancestor left or right point to r->left
            set_ancestor(r, prev, r->left);
            delete r;
        }
        else
        {
            // find min of right subtree, swap it with r and delete it
            std::unordered_map<tree_node<T> *, tree_node<T> *> prev2;
            prev2.insert({r->right, r});
            tree_node<T> *min_node = min_node_internal(r->right, &prev2);
            r->data = min_node->data;
            remove_internal(min_node, prev2);
        }
    }
    
    tree_node<T> * min_node_internal(tree_node<T> *r,
                                     std::unordered_map<tree_node<T> *, tree_node<T> *> *prev)
    {
        if (!r)
            return nullptr;
        
        while (r->left)
        {
            (*prev).at(r->left) = r;
            r = r->left;
        }
        
        return r;
    }
    
    // returns pointer to next largest value from val, otherwise returns nullptr
    // if no node has value larger than val
    tree_node<T> * next_largest_internal(T val)
    {
        
        return nullptr;
    }
};

void test_trees_and_graphs()
{
    tree_node<int> *r = new tree_node<int>(10);
    r->left = new tree_node<int>(5);
    r->right = new tree_node<int>(15);
    r->left->left = new tree_node<int>(4);
    r->left->left->left = new tree_node<int>(2);
    
    binary_search_tree<int> btree(r);
    btree.print();
    
    binary_search_tree<int> btree2;
    btree2.insert(10);
    btree2.insert(5);
    btree2.insert(15);
    btree2.insert(4);
    btree2.insert(2);
    btree2.print();
    
    std::cout << btree.find(3) << std::endl;
    
    btree2.remove(10);
    btree2.print();
}

#endif /* trees_and_graphs_h */
