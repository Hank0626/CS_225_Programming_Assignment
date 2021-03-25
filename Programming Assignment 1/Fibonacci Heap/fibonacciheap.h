/*
 * This is the header file of the Fibonacci Heap
 */

// Include the library
#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <cmath>

// Node Declaration
struct node {
    int n;          // The value stored in the node
    int degree;     // The degree of the node
    node* parent;   // The pointer of the parent node
    node* child;    // The pointer of the child node
    node* left;     // The pointer of the left point
    node* right;    // The pointer of the right point
    bool mark;      // mark characteristic of the node
    bool find;      // find characteristic of the node
};

// Class Declaration
template <class T> class FibonacciHeap {
    public:
        // Below is basic operation for the Fibonacci Heap
        FibonacciHeap();                
        node *Create_node(int value);
        void Insert(node* x);
        void Fibonacci_link(node* x, node* y);
        node *Union(node* H1, node* H2);
        void Display();
        node *Extract_Min();
        void Consolidate();
        int Decrease_key(int x, int k);
        void Cut(node* x, node* y);
        void Cont_cut(node* y);
        node *Find(node* H1, int k);
        int Delete_key(int k);
    private:
        int num_node;       // The number of node in the Fibonacc Heap
        node *H;            // The minimum pointer of the whole Fibonacci Heap
};
