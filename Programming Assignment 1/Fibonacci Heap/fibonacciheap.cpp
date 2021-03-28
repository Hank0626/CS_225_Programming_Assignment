/*
 * Implement of the fibonacci heap
 */

// Include the library
#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <limits>
#include "fibonacciheap.h"
using namespace std;

// Constructer
template <class T> FibonacciHeap<T>::FibonacciHeap() {
    node* np;                           // Set a new node np
    np = NULL;                          // Let this np to be the null pointer
    this -> H = np;                     // Let the node H in the heap to be null at first
}

// Inseert Node
template <class T> void FibonacciHeap<T>::Insert(int value) {
    node* x = new node; 
    x -> n = value;
    x -> degree = 0;                      // Initialize the information of the node x
    x -> parent = NULL;
    x -> child = NULL;
    x ->left = x;                        // Since x has no parent or child, x.left and x.right are all x itself
    x -> right = x;
    x -> mark = false;
    x -> find = false;
    if (NULL != H) {                    // Check whether the heap is empty
        (H -> left) -> right = x;       // Insert x to the right of the H
        x -> right = H;
        x -> left = H -> left;
        H -> left = x;
        if (x -> n < H -> n) H = x;         // Check whether x is smaller than the smallest value of the heap
    }
    else H = x; 
    num_node++;                            // Increment the number of node 
}

// Link Nodes in Fibonacci Heap
template <class T> void FibonacciHeap<T>::Fibonacci_link(node* x, node* y) {
    // Let x to a child of y and update the degree of the y
    (x -> left) -> right = x -> right;          // Link x -> left to x -> right
    (x -> right) -> left = x -> left;
    if (y -> right == y) H = y;                 // If this is only y left, set the min pointer to y   
    x -> left = x;                              // Set x to its single node
    x -> right = x;     
    x -> parent = y;                            // Set x's parent to be y                    
    if (NULL == y -> child) y -> child = x;     // If y doesn't have child, then x is the y's child
    x -> right = y -> child;                    // Link x to the left of the y's child
    x -> left = (y -> child) -> left;
    ((y -> child) -> left) -> right = x;
    (y -> child) -> left = x;
    if (x -> n < (y -> child) -> n) y -> child = x;   // If x is smaller than the y child, then set x to the y child
    y -> degree++;
}

// Union in Fibonacci Heap
template <class T> node* FibonacciHeap<T>::Union(node* H1, node* H2) {
    node* np;                                   // Create new node
    node* H0 = NULL;                                 
    H0 = H1;                                         
    (H0 -> left) -> right = H2;                 // link the H1 and the H2
    (H2 -> left) -> right = H0;
    np = H0 -> left;
    H0 -> left = H2 -> left;
    H2 -> left = np;                                
    if (H2 -> n < H0 -> n) return H2;           // Return the min pointer
    return H0;                                       
}

// Extract min of the Fibonacci Heap
template <class T> node* FibonacciHeap<T>::Extract_Min() {
    if (NULL == H) return NULL;                 // If the Fibonacci Heap is empty, then return NULL
    node* p = H;                                // Use p to store the original pointer         
    node* z = H;                                
    node* x = NULL;
    node* ptr;
    node* np;
    if (NULL != z -> child) x = z -> child;     // Let x to be the child of the z (minimum node)
    if (NULL != x) {
        ptr = x;                      
        do {
            np = x -> right;
            (H -> left) -> right = x;           // Link x to the left of the minimum pointer  
            x -> right = H;
            x -> left = H -> left;
            H -> left = x;
            //if (x -> n < H -> n) H = x;
            x -> parent = NULL;
            x = np;
            cout << x -> n << endl;
        } while (np != ptr);                     // Go through all the leave of the z
    }
    (H -> left) -> right = H -> right;          // Extract the minimum
    (H -> right) -> left = H -> left;
    if (z == z -> right && NULL == z -> child) H = NULL; 
    else {
        H = H -> right;
        Consolidate();
    }
    num_node--;                                 // Decrease the number of node by 1
    return p;
}

// Consolidation operation for Fibonacci Heap
template <class T> void FibonacciHeap<T>::Consolidate() {
    int num = (log(num_node)) / (log(2)) + 1;       // Determine the max degree
    node* A[++num];                                 // Construct a series of node to store the degree
    int dete = 0;
    int det = 0;
    for (int i = 0; i < num; i++) A[i] = NULL;      // Initialize them to be 0
    int degree;                                     // Used to store the current degree of the node
    node* x = H;                                    // Set x to be the initial position of the H pointer
    node* y;                                        // Set y to store the A[degree]
    node* temp;                                     // Used to exchange x and y
    do {
        dete++;                                     // Calculate the origin number of roots
        x = x -> right;
    } while (x != H);
    do {
        degree = x -> degree;                       // Set the degree to the current node of degree
        while (NULL != A[degree]) {                 // If A[degree] is not NULL
            y = A[degree];                          // y equals to A[degree]
            if (x -> n > y -> n) {                  // If the value in x is greater than y, exhange them
                temp = x;                           
                x = y;
                y = temp;
            }
            if (y == H) H = x;                      
            Fibonacci_link(y, x);                   // Let the y to be the child of x
            dete--;                                 // Delete the number of roots
            if (x -> right == x) H = x; 
            A[degree] = NULL;       
            det--;                                  // Calculate the number in the array
            degree++;
        }
        A[degree] = x;
        det++;                                      // Calculate the number in the array
        x = x -> right;
    } while (dete != det);                               // Go through all the root list
    H = NULL;   
    for (int j = 0; j < num; j++) {                 // Link all the degree
        if (NULL != A[j]) {                      
            A[j] -> left = A[j];
            A[j] -> right = A[j];
            if (NULL != H) {
                (H -> left) -> right = A[j];
                A[j] -> right = H;
                A[j] -> left = H -> left;
                H -> left = A[j];
                if (A[j] -> n < H -> n) H = A[j];
            }
            else H = A[j];   
        }
    }
}

// Decrease a node of value x to value k
template <class T> int FibonacciHeap<T>::Decrease_key(int x, int k) {
    node* y;
    if (NULL == H) {                                    // If H is NULL, meaning that the Fibonacci Heap is empty
        cout << "The Heap is Empty" << endl;
        return 0;
    }
    node* ptr = Find(H, x);                             // Find the pointer of the value x
    if (NULL == ptr) {                                  // If pointer is NULL, meaning that the Fibonacci Heap doesn't contain this value
        cout << "Node not found in the Heap" << endl;
        return 0;
    }
    if (ptr -> n < k) {                                 // If k is greater than x, then it is an invalid input
        cout<< "Entered key greater than current key" << endl;
        return 0;
    }
    ptr -> n = k;                                       // Set the value of ptr from x to k
    y = ptr -> parent;                                  // Let node y equals to the parent of ptr
    if (NULL != y && ptr -> n < y -> n) {               // If ptr has parent and its value is smaller its parent
        Cut(ptr, y);                                    // Do the cut operation
        Cont_cut(y);
    }
    if (ptr -> n < H -> n) H = ptr;                     // If ptr is the smallest value in the heap, set H to ptr
    return 1;                                           // Return 1 for success
}

// Cut operation for Fibonacci Heap
template <class T> void FibonacciHeap<T>::Cut(node* x, node* y) {
    // y is the parent and x is the child
    if (x == x -> right) y -> child = NULL;         // If y has only a child x, just set y -> child = NULL 
    (x -> left) -> right = x -> right;              // Link x's left to x's right
    (x -> right) -> left = x -> left;
    if (x == y -> child) y -> child = x -> right;   // If x is the smallest value of the child list, set the child to be the right of x
    y -> degree--;                                  // Decrease the degree of y
    x -> right = x;                                 // Update x's left and right to be itself
    x -> left = x;
    (H -> left) -> right = x;                       // Let x to be the left of H                
    x -> right = H;                             
    x -> left = H -> left;              
    H -> left = x;
    x -> parent = NULL;                             // Now x is in the root list, set its parent to be NULL    
    x -> mark = false;                              // Set x -> mark equals to false
}

// Continue to cut the node
template <class T> void FibonacciHeap<T>::Cont_cut(node* y) {
    node* z = y -> parent;                          // Set z to the parent of the node y
    if (NULL != z) {
        if (y -> mark == false) y -> mark = true;   // If y is not marked, then mark y
        else {                                      // If y is marked
            Cut(y, z);                              // Cut y 
            Cont_cut(z);                            // Then repeating this method
        }
    }
}

// Find operation for Fibonacci Heap
template <class T> node* FibonacciHeap<T>::Find(node* H1, int k) {
    node* p = NULL;
    node* q = NULL;
    H1 -> find = true;                                // Set x -> C equals to Y
    if (H1 -> n == k) {                               // If x equals to k
        H1 -> find = false;                           // Let x -> C equals to N
        return H1;                                    // Return the pointer
    }
    else {                                 // If the value in x is not equals to k
        if (NULL != H1 -> child) {
            p = Find(H1 -> child, k); 
        }
        if (((H1 -> right) -> find) == false) {
            q = Find(H1 -> right, k);            // Find the right of x
        }
    }
    H1 -> find = false;
    if (NULL != p) return p;
    else if (NULL != q) return q;
    else return NULL; 
}

// Delete operation for Fibonacci Heap
template <class T> int FibonacciHeap<T>::Delete_key(int k) {             
    node* np = NULL;
    int dete = Decrease_key(k, numeric_limits<T>::min());
    if (dete == 1) np = Extract_Min();  
    if (NULL != np) {
        cout << "Key Deleted" << endl;
        return 1;
    }
    else cout << "Key not Deleted" << endl;
    return 0;
}


template <class T> void FibonacciHeap<T>::print(node* np, node* prev, int direction) {
    node* start = np;
    if (NULL == np) return;
    do {
    if (direction == 1) cout << np -> n << "(" << np -> degree << ") is " << prev -> n << "'s child" << endl;
    else cout << np -> n << "(" << np -> degree << ") is " << prev -> n << "'s next" << endl;
    if (NULL != np -> child) print(np -> child, np, 1);
    prev = np;
    np = np -> right;
    direction = 2;
    } while(np != start);
}

template <class T> void FibonacciHeap<T>::Display() {
    int i = 0;
    node* p;
    if (NULL == H) return ;
    p = H;
    do {
        i++;
        cout << "#########################" << endl;
        cout << i << ". " << p -> n << "(" << p -> degree << ") is root" << endl;
        print(p -> child, p, 1);
        p = p -> right;
    } while (p != H);
    cout << endl;
}

// Display for Fibonacci Heap
// template <class T> void FibonacciHeap<T>::Display() {
//     node* p = H;
//     if (NULL == p) {
//         cout << "The Fibonacci Heap is empty" << endl;
//         return;
//     }
//     cout << "The roots node of Fibonacci Heap are:" << endl;
//     do {
//         cout << p -> n;
//         p = p -> right;
//         if (p != H) cout << "-->";   
//     } while (p != H && NULL != p -> right);
//     cout << endl;
// }