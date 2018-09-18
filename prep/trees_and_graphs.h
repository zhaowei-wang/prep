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
    
    bool remove(T val)
    {
        tree_node<T> *ret = nullptr;
        bool ok = find_internal(binary_tree<T>::_root, &ret, val);
        if (!ok)
            return false;
        
        
    }
    
    bool find(T val)
    {
        return find_internal(binary_tree<T>::_root, nullptr, val);
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
    bool find_internal(tree_node<T> *root, tree_node<T> **ret, T val) const
    {
        if (!root)
            return false;
        
        if (root->data == val)
        {
            if (ret) *ret = root;
            return true;
        }
        else if (root->data > val)
        {
            return find_internal(root->left, ret, val);
        }
        else if (root->data < val)
        {
            return find_internal(root->right, ret, val);
        }
        
        return false;
    }
    
    // deletes curr from tree
    void remove_internal(tree_node<T> *&curr)
    {
       
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
    
    std::cout << btree.find(8) << std::endl;
}

#endif /* trees_and_graphs_h */
