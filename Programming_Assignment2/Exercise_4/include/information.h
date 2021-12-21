#ifndef information_h
#define information_h

#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <cmath>
#include <string>
#include <vector>
#include "../include/dataType.h"
using std::string;
using std::vector;
using std::pair;

template<class T> class person;
template<class T> class patient_queue;
template<class T> class fifo;
template<class T> class registration;
class Report;


// Registration Class
// Contains a person who propose a registration and the registration time
template<class T> class registration {
    friend class person<T>;
public: 
    int day;              // Ex: 20190906 :Setember 9th, 2019
    int time;             // Ex: 2105 : five pass nine pm
};

template<class T> class person {
    friend class Report;
public:
    person() {
        this -> waiting_time = -1;
        this -> priority = 0;
        this -> withdrawal = 0;
        this -> withdraw_date = 0;
        this -> regist = 0;
        this -> treated = 0;
        this -> letter = 0;
        this -> deadline = 0;
        this -> treat_date = 0;
        this -> regist_date = 0;
    }
    registration<T> appoint;
    Treatment treatment;
    void set_name(string name);
    void set_email(string email);
    void profess(int pro);
    void birth(int day);
    void set_risk_status(int status);
    void set_loc(int loc);
    void age(int age);
    void set_regist_date(int date);
    void indentify(int id);
    void information(void);
    int send_registration(int day, int time,int treament_type);
    void send_withdrawal(int day);
    void send_letter(int day);
    int check_registration(void);
    void set_priority(void);
    void set_treat(int date);
    void set_waiting_time(int date);
    pair<int, int> return_withdraw(void);
    int return_id(void);
    string return_name(void);
    int return_bir(void);
    double return_priority(void);
    int return_loc(void);
    int return_treat(void);
    int return_regist_date(void);
    int return_age_group(void);
    int return_treatment_type(void);
    int return_status_risk(void);
    pair<int, int> return_letter();
private:
    int loc;
    string name;
    string email;
    int profession;                 // from 0 to 7; indicate 8 professions
    int birthday;                   // e.g. 20010626
    int identification;             // 8 bits integer
    int risk_status;                // 0: no risk; 1: low risk; 2: medium risk; 3: high risk;
    int age_group;                  // 1: children(<=12); 2: adolencents(<=18); 3: young adults(<=35); 4: adults(<=50) 5: seniors(<=65); 6: elderly people(<=75); 7: old people(>75);
    double priority;                // largest number means top priority
    int withdrawal;                 // 0: no withdrawal record; 1: has withdrawal record
    int letter;                     // 0: no letter has been subitted; 1: a letter has been submitted
    int regist;                     // 0: not send registration; 1: have sent a registration
    int treated;                    // 0: not been treated; 1: have been treated
    int wait;                       // 0: this person hasn't wait in queue; 1: this person has waited in line;
    int deadline;                   // EX: 20190906: setember 9th, 2019; it will be empty if no has letter been submitted 
    int treat_date;                 // yyyymmdd
    int withdraw_date;              // yyyymmdd
    int waiting_time;               // in day
    int regist_date;                // yyyymmdd
    int treatment_type;
};

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
        store a person's info to a file
        p: the person info you want to write. It will write to the
           file named ID.txt where ID is the person's identification.
    */
    bool store_to_file(person<int> p);
    /*
        timenow: the time now
        sort_by: one of "name" "age" or "profession". sorted increasingly
    */
   bool store_to_file_auto(person<int> p);
    bool display_weekly_report(int timenow, string sort_by, bool where);
    bool display_monthly_report(int timenow, string sort_by, bool where);

private:
    /*
        range: either 7 or 30 (days)
    */
    bool _display_report(int timenow, int range, string sort_by, bool is_summary, bool where, bool save);
    static bool sort_by_name(person<int> p1, person<int> p2);
    static bool sort_by_pro(person<int> p1, person<int> p2);
    static bool sort_by_age(person<int> p1, person<int> p2);
    void print_person(int i, vector<person<int>> report_list, bool wait_time, int timenow);
};


struct node {
    person<int>* fib_person;
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