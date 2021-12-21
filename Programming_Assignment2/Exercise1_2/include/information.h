#ifndef information_h
#define information_h

#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <cmath>
#include <string>
#include <vector>
#include "dataType.h"
#include "database.h"
using std::string;
using std::vector;
using std::pair;

template<class T> class patient_queue;
template<class T> class fifo;
class Report;

template<class T> class patient_queue {
public:
    patient_queue() {
        this -> patient_numbers = 0;
        this -> withdrawal_number = 0;
    };
    fifo <person<T>*> local;                            // using a queue to store local patient information
    void add_patient(person<T> *person);                // each element in the queue is a pointer to person information
    void delete_person();
    person<T>* find(int id);
    int patient_num(void);
    void display(void);

private:    
    int patient_numbers;
    int wait_number;
    int withdrawal_number;
};


template<class T> class fifo {
    friend class patient_queue<T>;
public:
    fifo(int size = 10);
    T &operator[](int index);
    int getlength(void);
    bool isempty(void);
    T back(void);
    T front(void);
    void pushback(T value);
    T popfront(void);
    int return_first(void);
private:
    int maxsize, minsize;
    int first, last;
    int numitems;
    T *reprarray;
    void allocate(void);
    void deallocate(void);
};

class Report {
    friend class patient_queue<int>;
public:
    /*
        read a person's info from a file
        filename: the file you want to read the person info from
        p: the returned person info
    */
    bool read_from_file(string filename, person<int> &p);
    /*
        timenow: the time now
        sort_by: one of "name" "age" or "profession". sorted increasingly
    */
    bool display_weekly_report(int timenow, string sort_by, Database &database);
    bool display_monthly_report(int timenow, string sort_by, Database &database);

private:
    /*
        range: either 7 or 30 (days)
    */
    bool _display_report(int timenow, int range, string sort_by, bool is_summary, Database &database, bool save);
    static bool sort_by_name(person<int> p1, person<int> p2);
    static bool sort_by_pro(person<int> p1, person<int> p2);
    static bool sort_by_age(person<int> p1, person<int> p2);
    void print_person(int i, vector< person<int> > report_list, bool wait_time, int timenow);
};


struct node {
    int id;
    double n;          // The value stored in the node
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
        void Insert(node* x);
        void Fibonacci_link(node* x, node* y);
        node *Extract_Min();
        void Consolidate();
        int Decrease_key(double x, double k);
        void Cut(node* x, node* y);
        void Cont_cut(node* y);
        node *Find(node* H1, double k);
        int Delete_key(double k);
        void Display();
        void print(node* np, node* prev, int direction);
        int return_num(void);
        node *return_H(void);
        node *Dete(double k);
    private:
        int num_node;       // The number of node in the Fibonacc Heap
        node *H;            // The minimum pointer of the whole Fibonacci Heap
};
#endif