#include <cstdlib>
#include <stdlib.h>
#include <iostream>
#include <cstdio>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <cstring>
#include <string>
#include <sys/types.h>
#include <dirent.h>
#include <cmath>
#include <limits>
#include <unistd.h>
#include "../include/information.h"
#include "helper.cpp"
using namespace std;

// ############################### person<T> ###############################
template<class T> void person<T>::birth(int day) {
    this -> birthday = day;
    return;
}

template<class T> void person<T>::indentify(int id) {
    this -> identification = id;
    return;
}


template<class T> void person<T>::set_name(string name) {
    this -> name = name;
    return;
}

template<class T> void person<T>::set_email(string email) {
    this -> email = email;
    return;
}

template<class T> void person<T>::set_risk_status(int status) {
    this -> risk_status = status;
    return;
}

template<class T> void person<T>::set_loc(int local) {
    this -> loc = local;
    return;
}

template<class T> void person<T>::profess(int pro) {
    this -> profession = pro;
    return;
}

template<class T> void person<T>::information(void) {
    cout << "the information of this patient is as below : " << endl;  
    cout << "name: " << this -> name << endl; 
    cout << "identification: " << this -> identification << endl;
    cout << "birthday: " << this -> birthday << endl;
    cout << "email: " << this -> email << endl;
    cout << "risk_status: " << this -> risk_status << endl;
    cout << "age_group: " << this -> age_group << endl;
    if (this -> regist == 1) cout << "this person has registrated" << endl;
    else cout << "this person hasn't registrated" << endl;
    return;
}

template<class T> void person<T>::age(int age) {
    if (age < 0){
        cout << "age cannot less than 0" << endl;
        return;
    }
    if (age <= 12) this -> age_group = 0;
    if (age > 12 && age <= 18) this -> age_group = 1;
    if (age > 18 && age <= 35) this -> age_group = 2;
    if (age > 35 && age <= 50) this -> age_group = 3;
    if (age > 50 && age <= 65) this -> age_group = 4;
    if (age > 65 && age <= 75) this -> age_group = 5;
    if (age > 75) this -> age_group = 6;
    return;
}


template<class T> int person<T>:: return_regist_date(void) {
    return this->regist_date;
}

//this function is used patient information to give a priority.
//INPUT: all information
//BASE: based on profession, age_group, register data with weight 0.5, 0.3, 0.2 to calculate a number;
//  for profession: 7 gets the highest priority; for age_group: oldeest first; for register data: early get first;
//OUTPUT: a priority for sort in the local queue
//SIDE EFFECT: none
//Warning:  high risk status is not considered.
template<class T> void person<T>::set_priority(void) {
    double priority = 0; 
    double year, month, day, hour, minute;
    priority += this -> profession * 10;
    priority += this -> age_group * 5;
    int tday; 
    int ttime;
    tday = this->regist_date;
    ttime = this->regist_time;
    year = year(tday) - 2010;                             
    month = month(tday) - 1;        // start from January
    day = day(tday) - 1;          // start from 1st
    hour = hour(ttime);
    minute = minu(ttime);
    if (this -> risk_status == 2) day += 30;
    else if (this -> risk_status != 3 && this -> withdrawal == 1) day += 14;
    priority += (year + month * 30 + day  + hour / 24 + minute / 1440) / 5000;
    this -> priority = priority;
    return;
}

template<class T> void person<T>::set_treat(int date) {
    this -> treated = 1;
    this -> treat_date = date;
    return;
}

template<class T> void person<T>::set_waiting_time(int date) {
    this -> waiting_time = date;
    return;
}

template<class T> pair<int, int> person<T>::return_withdraw(void) {
    return make_pair(this -> withdrawal, this -> withdraw_date);
}

template<class T> pair<int, int> person<T>::return_letter(void) {
    return make_pair(this -> letter, this -> deadline);
}

template<class T> int person<T>::return_id(void) {
    return this -> identification;
}

template<class T> string person<T>::return_name(void) {
    return this -> name;
}

template<class T> int person<T>::return_age_group(void) {
    return this->age_group;
}

template<class T> int person<T>::return_bir(void) {
    return this -> birthday;
}

template<class T> double person<T>::return_priority(void) {
    return this -> priority;
}


template<class T> int person<T>::return_treat(void) {
    return this -> treated;
}

template<class T> int person<T>::return_treatment_type(void){
    return this -> treatment_type;
}

template<class T> int person<T>::return_status_risk(void){
    return this -> risk_status;
}

template<class T> void person<T>::send_withdrawal(int day) {
    this -> regist = 0;
    this -> withdrawal = 1;
    this -> withdraw_date = day;
    return; 
}

// if a registration is sent, the registration time is recorded.
template<class T> int person<T>::send_registration(int date, int time, int treament) {
    this -> regist = 1;
    this -> treated = 0;
    this -> treatment_type = treament;
    this -> regist_date = date;
    this -> regist_time = time;
    return this -> return_id();
}

template<class T> void person<T>::send_letter(int day) {
    this -> letter = 1;
    this -> deadline = day;
    return;
}

template<class T> int person<T>::check_registration(void) {
    return this -> regist;
}
// ########################################## person<T> end #########################################


// ########################################## patient_queue<T> #########################################
template<class T> void patient_queue<T>::add_patient(person<T> *person) {
    this -> local.pushback(person);
    this -> patient_numbers += 1;
    return;
}

template<class T> void patient_queue<T>::delete_person() {
    this -> patient_numbers -= 1;
    return;
}

template<class T> person<T>* patient_queue<T>::find(int id) {
    for (int i = 1; i <= this -> patient_numbers; i++) {
        if ((this -> local)[i] -> return_id() == id) return (this -> local)[i];
    }
    return NULL;
}

template<class T> int patient_queue<T>::patient_num(void) {
    return this -> patient_numbers;
}

template<class T> void patient_queue<T>::display(void) {
    for (int i = 1; i <= this -> patient_numbers; i++) {
        cout << "----------Person " << i << "----------" << endl;
        cout << "Name: " << ((this -> local)[i]) -> return_name() << endl;
        cout << "ID: " << ((this -> local)[i]) -> return_id() << endl;
        cout << "Bir: " << ((this -> local)[i]) -> return_bir() << endl;
        cout << "Treat type: " << ((this -> local)[i]) -> treatment_type << endl;
    }
    return;
}

// ########################################## patient_queue<T> end #########################################

// ########################################## fifo<T> #########################################
template<class T> fifo<T>::fifo(int size) {
    maxsize = size;
    if (size < 10) minsize = size;
    else minsize = 10;
    numitems = 0;
    first = 0;
    last = -1;
    reprarray = new T[maxsize];
}

template<class T> T &fifo<T>::operator[](int index) {
    if ((1 <= index) && (index <= numitems)) {
        int relindex = (index + first -1) % maxsize;
        return reprarray[relindex];
    }
    else {
        cout << "Error: index " << index << " out of range.\n";
        exit(EXIT_FAILURE);
    }
}

template<class T> int fifo<T>::getlength(void) {
    return numitems;
}

template<class T> bool fifo<T>::isempty(void) {
    if (numitems == 0) return true;
    else return false;
}

template<class T> T fifo<T>::front(void) {
    if (isempty() == false)
        return reprarray[first];
    else {
        cout << "The queue is empty.\n";
        exit(EXIT_FAILURE);
    }
}

template<class T> T fifo<T>::back(void) {
    if (isempty() == false) {
        int relindex = (first + numitems - 1) % maxsize;
        return reprarray[relindex];
    }
    else {
        cout << "The queue is empty.\n";
        exit(EXIT_FAILURE);
    }
}

template<class T> void fifo<T>::pushback(T value) {
    if (numitems == maxsize)
        allocate();
    last = ++last % maxsize;
    reprarray[last] = value;
    ++numitems;
    return;
}

template<class T> T fifo<T>::popfront(void) {
    if ((numitems == maxsize / 4) && (maxsize > minsize))
        deallocate();
    if (isempty() == false) {
        T frontelement = reprarray[first];
        first = ++first % maxsize;
        --numitems;
        return frontelement;
    }
    else {
        cout << "The queue is empty.\n";
        exit(EXIT_FAILURE);
    }
}

template<class T> int fifo<T>::return_first(void) {
    return this -> first;
}

template<class T> void fifo<T>::allocate(void) {
    int newsize = 2 * maxsize;
    T *newarray = new T[newsize];
    for (int i = 0; i < numitems; ++i) {
        int pos = (i + first) % maxsize;
        newarray[i] = reprarray[pos];
    }
    delete[] reprarray;
    reprarray = newarray;
    maxsize = newsize;
    first = 0;
    last = numitems - 1;
    return;
}

template<class T> void fifo<T>::deallocate(void) {
    int newsize = maxsize / 2;
    T *newarray = new T[newsize];
    for (int i = 0; i < numitems; ++i) {
        int pos = (i + first) % maxsize;
        newarray[i] = reprarray[pos];
    }
    delete[] reprarray;
    reprarray = newarray;
    maxsize = newsize;
    first = 0;
    last = numitems - 1;
    return;
}
// ########################################## fifo<T> end #########################################

// ########################################## Report #########################################
bool Report::read_from_file(string filename, person<int> &p) {
    /*
        read a person's information from file.

        filename: string, the file you want to read from
        p: person<int>, the return person

        return value: bool, true for success
    */
    ifstream fin(filename);
    if (!fin.is_open()) {
        cout << "cannot open: " + filename << endl;
        return false;
    }
    fin >> p.identification;
    fin >> p.name;
    fin >> p.email;
    fin >> p.profession;
    fin >> p.birthday;
    fin >> p.risk_status;
    fin >> p.regist_date;
    fin >> p.regist_time;
    fin >> p.age_group;
    fin >> p.withdrawal;
    fin >> p.withdraw_date;
    fin >> p.letter;
    fin >> p.deadline;                
    fin >> p.regist;
    fin >> p.treated;
    fin >> p.treat_date;
    fin >> p.priority;
    fin >> p.waiting_time;
    fin >> p.regist_date;
    fin >> p.treatment_type;
    fin.close();
    return true;
}

void GetFileNames(string path, vector<string> &filenames) {
    /*
        get all the filenames in one directory
    */
    DIR *pDir;
    struct dirent* ptr;
    if(!(pDir = opendir(path.c_str()))) {
        cout << "folder does not exist" << endl;
        return;
    }
    while ((ptr = readdir(pDir)) != 0) {
        if (strcmp(ptr -> d_name, ".") != 0 && strcmp(ptr -> d_name, "..") != 0)
            filenames.push_back(path + "/" + ptr -> d_name);
    }
    closedir(pDir);
}

bool Report::sort_by_name(person<int> p1, person<int> p2) {
    return p1.name < p2.name;
}

bool Report::sort_by_pro(person<int> p1, person<int> p2) {
    return p1.profession < p2.profession;
}

bool Report::sort_by_age(person<int> p1, person<int> p2) {
    return p1.age_group < p2.age_group;
}

void print_split_line() {
    printf("==============================================\n");
}

void Report::print_person(int i, vector< person<int> > report_list, bool wait_time, int timenow) {
    // print a person's information out
    cout << "name: " << report_list[i].name << endl;
    printf("profession category: %d\n", report_list[i].profession);
    printf("age category: %d\n", report_list[i].age_group);
    printf("risk status: %d\n", report_list[i].risk_status);
    if (wait_time) printf("wait time until now (in day): %d\n", (report_list[i].waiting_time == -1) ? day_between(report_list[i].regist_date, timenow) : report_list[i].waiting_time);  
    cout << endl;
}

bool Report::_display_report(int timenow, int range, string sort_by, bool is_summary, Database &database, bool save) {
    vector< person<int> > report_list;

    int old_stdout = dup(1);
    FILE *fp = NULL;

    if (save) {
        string filename = "";
        if (is_summary) filename = "./report/" + to_string(timenow) + "monthly_report.txt";
        else filename = "./report/" + to_string(timenow) + "weekly_report.txt";
        fp = freopen(filename.c_str(), "w", stdout);
    }

    database.getReportList(report_list);

    if (is_summary) {
        // if it is monthly report
        int registered_num = 0;
        int waiting_num = 0;
        int appointment_num = 0;
        int withdraw_num = 0;
        double average_waiting_time = 0.0;
        for (int i = 0; i < int(report_list.size()); i++) {
            // people who registered and with no withdrawal in the last 30 days
            if (day_between(report_list[i].regist_date, timenow) <= range && !report_list[i].withdrawal) {
                average_waiting_time += (double)((report_list[i].waiting_time == -1) ? day_between(report_list[i].regist_date, timenow) : report_list[i].waiting_time);
                registered_num++;
            }
            // people who are waiting
            if (!report_list[i].withdrawal && !report_list[i].treated) {
                waiting_num++;
            }
            // people who have been treated in the last 30 days
            if (day_between(report_list[i].treat_date, timenow) <= range && report_list[i].treated) appointment_num++;
            // people who have withdrew in the last 30 days
            if (day_between(report_list[i].withdraw_date, timenow) <= range && report_list[i].withdrawal) withdraw_num++;
        }

        // avoid divide zero error
        if (registered_num != 0)
            average_waiting_time /= (double)registered_num;
        else
            average_waiting_time = 0.0;

        print_split_line();
        printf("monthly statistics report\nIn the last 30 days:\n");
        print_split_line();
        printf("number of registered people: %d\n", registered_num);
        printf("number of waiting people: %d\n", waiting_num);
        printf("number of treatment appointments: %d\n", appointment_num);
        printf("average waiting time (in day): %.3lf\n", average_waiting_time);
        printf("number of people who withdrew their registration: %d\n", withdraw_num);
        cout << endl;

        if (save) {
            fflush(fp);
            dup2(old_stdout, 1);
        }
        return true;
    }

    // sort the report_list. default is sorted by name
    if (sort_by == "name")  sort(report_list.begin(), report_list.end(), this -> sort_by_name);
    else if (sort_by == "profession") sort(report_list.begin(), report_list.end(), this -> sort_by_pro);
    else if (sort_by == "age") sort(report_list.begin(), report_list.end(), this -> sort_by_age);
    else sort(report_list.begin(), report_list.end(), this -> sort_by_name); 

    print_split_line();
    printf("weekly statistics report\nIn the last 7 days:\n");
    print_split_line();

    bool empty = true; 
    int cnt = 0;

    print_split_line();
    printf("the people who have been treated\n");
    print_split_line();
    for (int i = 0; i < int(report_list.size()); i++) {
        if (day_between(report_list[i].treat_date, timenow) <= range && report_list[i].treated && (report_list[i].regist_date < timenow)) {
            cnt ++;
            cout << "********* Person" << cnt << " *********" << endl;
            print_person(i, report_list, false, timenow);
            empty = false;
        }
    }
    if (empty) cout << "Empty" << endl;

    empty = true;
    cnt = 0;

    print_split_line();
    printf("the registered people in the last 7 days\n");
    print_split_line();
    for (int i = 0;i < int(report_list.size()); i++) {
        if (day_between(report_list[i].regist_date, timenow) <= range && !report_list[i].treated && !report_list[i].withdrawal && (report_list[i].regist_date < timenow)) {
            cnt ++;
            cout << "********* Person" << cnt << " *********" << endl;            
            print_person(i, report_list, true, timenow);
            empty = false;
        }
        
    }

    if (empty) cout << "Empty" << endl;

    empty = true;
    cnt = 0;

    print_split_line();
    printf("the total queueing people\n");
    print_split_line();
    for (int i = 0; i < int(report_list.size()); i++) {
        if (!report_list[i].withdrawal && !report_list[i].treated && (report_list[i].regist_time < timenow)) {
            cnt ++;
            cout << "********* Person" << cnt << " *********" << endl;
            print_person(i, report_list, true, timenow);
            empty = false;

        }
        
    }

    if (empty) cout << "Empty" << endl;
    if (save) {
        fflush(fp);
        dup2(old_stdout, 1);
    }
    return true;
}

bool Report::display_weekly_report(int timenow, string sort_by, Database &database) {
    this -> _display_report(timenow, 7, sort_by, false, database, true);
    return this -> _display_report(timenow, 7, sort_by, false, database, false);
}

bool Report::display_monthly_report(int timenow, string sort_by, Database &database) {
    this -> _display_report(timenow, 30, sort_by, true, database, true);
    return this -> _display_report(timenow, 30, sort_by, true, database, false);
}


// ########################################## Report end #########################################

// ########################################## Fibonacci Heap #########################################
// Constructer
template <class T> FibonacciHeap<T>::FibonacciHeap() {
    node* np;                           // Set a new node np
    np = NULL;                          // Let this np to be the null pointer
    this -> H = np;                     // Let the node H in the heap to be null at first
    this -> num_node = 0;
}

// Inseert Node
template <class T> void FibonacciHeap<T>::Insert(node* x) {
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
    node* ptr;
    do {
        dete++;                                     // Calculate the origin number of roots
        x = x -> right;
    } while (x != H);
    do {
        ptr = x -> right;
        degree = x -> degree;                       // Set the degree to the current node of degree
        while (NULL != A[degree]) {                 // If A[degree] is not NULL
            y = A[degree];                          // y equals to A[degree]
            if (x -> n > y -> n) {                  // If the value in x is greater than y, exhange them
                temp = x;                           
                x = y;
                y = temp;
            }                 
            Fibonacci_link(y, x);                   // Let the y to be the child of x
            dete--;                                 // Delete the number of roots
            A[degree] = NULL;       
            det--;                                  // Calculate the number in the array
            degree++;
        }
        A[degree] = x;
        det++;                                      // Calculate the number in the array
        x = ptr;
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
template <class T> int FibonacciHeap<T>::Decrease_key(double x, double k) {
    node* y;
    if (NULL == H) {                                    // If H is NULL, meaning that the Fibonacci Heap is empty
        //cout << "The Heap is Empty" << endl;
        return 0;
    }
    node* ptr = Find(H, x);                             // Find the pointer of the value x
    if (NULL == ptr) {                                  // If pointer is NULL, meaning that the Fibonacci Heap doesn't contain this value
        //cout << "Node not found in the Heap" << endl;
        return 0;
    }
    if (ptr -> n < k) {                                 // If k is greater than x, then it is an invalid input
        //cout<< "Entered key greater than current key" << endl;
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
template <class T> node* FibonacciHeap<T>::Find(node* H1, double k) {
    if (NULL == H1) return NULL;
    node* p = NULL;
    node* q = NULL;
    H1 -> find = true;                                // Set x -> C equals to Y
    if (fabs(H1 -> n - k) < 0.01) {                    // If x equals to k
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
template <class T> int FibonacciHeap<T>::Delete_key(double k) {             
    node* np = NULL;
    int dete = Decrease_key(k, numeric_limits<T>::min());
    if (dete == 1) np = Extract_Min();  
    if (NULL != np) {
        //cout << "Key Deleted" << endl;
        return 1;
    }
    //else cout << "Key not Deleted" << endl;
    return 0;
}


template <class T> void FibonacciHeap<T>::print(node* np, node* prev, int direction) {
    node* start = np;
    if (NULL == np) return;
    do {
    if (direction == 1) {
        // cout << (np -> fib_person) -> return_name() << "(degree: " << np -> degree << ") is " << (prev -> fib_person) -> return_name() << "'s child";
        // cout << " (Priority: " << (np -> fib_person) -> return_priority() << endl;
    }
    else {
        // cout << (np -> fib_person) -> return_name() << "(degree: " << np -> degree << ") is " << (prev -> fib_person) -> return_name() << "'s next";
        // cout << " (Priority: " << (np -> fib_person) -> return_priority() << endl;
    }
    if (NULL != np -> child) print(np -> child, np, 1);
    prev = np;
    np = np -> right;
    direction = 2;
    } while(np != start);
}

template <class T> void FibonacciHeap<T>::Display() {
    cout << endl << endl << "The central registry now have " << this -> num_node << " patients" << endl << endl;
    int i = 0;
    node* p;
    if (NULL == H) return ;
    p = H;
    do {
        i++;
        cout << "#########################" << endl;
        cout << i << ". " << (p -> id) << " (degree: " << p -> degree << ") is root.";
        cout << " (Priority: " << (p -> n) << endl;
        print(p -> child, p, 1);
        p = p -> right;
    } while (p != H);
    cout << endl;
}

template <class T> int FibonacciHeap<T>::return_num(void) {
    return this -> num_node;
}

template <class T> node* FibonacciHeap<T>::return_H(void) {
    return this -> H;
}

template <class T> node* FibonacciHeap<T>::Dete(double k) {
    return this -> Find(this -> H, k);
}
// ########################################## Fibonacci Heap end #########################################