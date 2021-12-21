#ifndef information_h
#define information_h

#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <cmath>
#include <string>
#include <vector>

#include "../include/map.h"
#include "../include/dataType.h"
#include "../include/BPlus_tree.h"
#include "../src/helper.cpp"
using namespace std;
const int NUM_TREATMENT_TYPE = 3;
const int MAX_TREATMENT_NUM_PER_HALF_DAY = 1;
typedef btree::multimap<int, int> BTree;
enum RELATION {
    RELATION_PERSON,
    RELATION_MEDICALSTATUS,
    RELATION_REGISTRATION,
    RELATION_TREATMENT
};

template<class T> class person;
template<class T> class patient_queue;
template<class T> class fifo;
template<class T> class registration;
template<class T> class Block;
template<class T> class Relation;
template<class T> class RelationBPlusTree;
class Report;
class DatabaseBPlusTree;
class Database;
class information;

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
        this -> waiting_time = 0;
        this -> priority = 0;
        this -> withdrawal = 0;
        this -> withdraw_date = 0;
        this -> regist = 0;
        this -> treated = 0;
        this -> letter = 0;
        this -> deadline = 0;
        this -> treat_date = 0;
        this -> treatment_type = rand()%3;
        // regist_date is now replaced by appoint.day
        //this -> regist_date = 0;
    }
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
    void send_registration(int day, int time, int treament_type);
    void send_withdrawal(int day);
    void send_letter(int day);
    bool check_registration(void);
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
public:
    registration<T> appoint;
    Treatment treatment;
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
    int treatment_type;
};

person<int>* fourToOne(Person pp, MedicalStatus pms, Registration preg, Treatment ptm) {
    person<int>* P          = new person<int>;
    P->name                 = pp.name;
    P->email                = pp.email;
    P->profession           = pp.profession;
    P->birthday             = pp.birthday;
    P->age_group            = pp.age_group;
    // todo: Person address for Ex 4 (optional)

    P->risk_status          = pms.risk_status;

    P->priority             = preg.priority;
    P->treatment_type       = preg.treatment_type;
    P->withdrawal           = preg.withdrawal;
    P->letter               = preg.letter;
    P->regist               = preg.regist;
    P->treated              = preg.treated;
    P->wait                 = preg.wait;
    P->deadline             = preg.deadline;
    P->withdraw_date        = preg.withdraw_date;
    P->waiting_time         = preg.waiting_time;
    (P->appoint).day        = preg.regist_date;
    (P->appoint).time       = preg.regist_time;

    P->treatment.day        = ptm.day;
    P->treatment.location   = ptm.location;  

    P->identification       = pp.getRecordID();
    return P;  
}

void oneToFour(person<int> P, Person& pp, MedicalStatus& pms, Registration& preg, Treatment& ptm) {
    pp.setRecordID(P.identification);
    pms.setRecordID(P.identification);
    preg.setRecordID(P.identification);
    ptm.setRecordID(P.identification);

    pp.name                 = P.name;
    pp.email                = P.email;
    pp.profession           = P.profession;
    pp.birthday             = P.birthday;
    pp.age_group            = P.age_group;
    // todo: Person address for Ex 4 (optional)

    
    pms.risk_status         = P.risk_status;

    preg.priority           = P.priority;
    preg.treatment_type     = P.treatment_type;
    preg.withdrawal         = P.withdrawal;
    preg.letter             = P.letter;
    preg.regist             = P.regist;
    preg.treated            = P.treated;
    preg.wait               = P.wait;
    preg.deadline           = P.deadline;
    preg.withdraw_date      = P.withdraw_date;
    preg.waiting_time       = P.waiting_time;
    preg.regist_date        = P.appoint.day;
    preg.regist_time        = P.appoint.time;

    ptm.day                 = P.treatment.day;
    ptm.location            = P.treatment.location;
}


template<class T> class RelationBPlusTree {
    public:
        int insert(T x) {
            block.push_back(x);
            return block.size()-1;
        }

        int getlength() {
            return block.size();
        }

        T& operator[](int index) {
            return this->block[index];
        }
    private:
        vector<T> block;
};

class DatabaseBPlusTree {
    public:
        void print() {
            int num = personInfo.getlength();
            for (int i=0;i<num;i++)
            cout << i << "\t" << personInfo[i].getRecordID() << "\t" << personInfo[i].name << "\t\t" << registrationInfo[i].priority << endl;
        }

        int insert(person<int> P) {
            Person pp;
            MedicalStatus pms;
            Registration preg;
            Treatment ptm;
            oneToFour(P, pp, pms, preg, ptm);
            int idx = personInfo.insert(pp);
            medicalStatusInfo.insert(pms);
            registrationInfo.insert(preg);
            treatmentInfo.insert(ptm);
            return idx;
        }

        void modify(int idx, person<int>* P) {
            Person pp;
            MedicalStatus pms;
            Registration preg;
            Treatment ptm;
            oneToFour(*P, pp, pms, preg, ptm);
            personInfo[idx] = pp;
            medicalStatusInfo[idx] = pms;
            registrationInfo[idx] = preg;
            treatmentInfo[idx] = ptm;
        }

        void modify(int idx, person<int> P) {
            Person pp;
            MedicalStatus pms;
            Registration preg;
            Treatment ptm;
            oneToFour(P, pp, pms, preg, ptm);
            personInfo[idx] = pp;
            medicalStatusInfo[idx] = pms;
            registrationInfo[idx] = preg;
            treatmentInfo[idx] = ptm;            
        }

        person<int>* retrieve(int idx) {
            return fourToOne(personInfo[idx], medicalStatusInfo[idx], registrationInfo[idx], treatmentInfo[idx]);
        }
    private:
        RelationBPlusTree<Person>           personInfo;
        RelationBPlusTree<MedicalStatus>    medicalStatusInfo;
        RelationBPlusTree<Registration>     registrationInfo;
        RelationBPlusTree<Treatment>        treatmentInfo;
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
    bool display_weekly_report(int timethr, int timenow, string sort_by, DatabaseBPlusTree &database, CBPlusTree &bPlusTree, BTree &registDateBTree, BTree &withdrawDateBTree, BTree &treatDateBTree);
    bool display_monthly_report(int timethr, int timenow, string sort_by, DatabaseBPlusTree &database, CBPlusTree &bPlusTree, BTree &registDateBTree, BTree &withdrawDateBTree, BTree &treatDateBTree);
    /* range: either 7 or 30 (days) */
    bool _display_report(int timethr, int timenow, int range, string sort_by, bool is_monthly, DatabaseBPlusTree &database, CBPlusTree &bPlusTree, BTree &registDateBTree, BTree &withdrawDateBTree, BTree &treatDateBTree, bool save);
    void print_person(int i, vector<person<int>> report_list, bool wait_time, int timenow);
};

bool sort_by_name(person<int> p1, person<int> p2) {
    return p1.name < p2.name;
}

bool sort_by_pro(person<int> p1, person<int> p2) {
    return p1.profession < p2.profession;
}

bool sort_by_age(person<int> p1, person<int> p2) {
    return p1.age_group < p2.age_group;
}

void print_split_line() {
    printf("==============================================\n");
}

void Report::print_person(int i, vector<person<int>> report_list, bool wait_time, int timenow) {
    // print a person's information out
    cout << "name: " << report_list[i].name << endl;
    printf("profession category: %d\n", report_list[i].profession);
    printf("age category: %d\n", report_list[i].age_group);
    printf("risk status: %d\n", report_list[i].risk_status);
    if (wait_time) printf("wait time until now (in day): %d\n", (report_list[i].waiting_time == -1) ? day_between(report_list[i].appoint.day, timenow) : report_list[i].waiting_time);  
    cout << endl;
}

bool Report::_display_report(int timethr, int timenow, int range, string sort_by, bool is_monthly, DatabaseBPlusTree &database, CBPlusTree &bPlusTree, BTree &registDateBTree, BTree &withdrawDateBTree, BTree &treatDateBTree, bool save) {
    int old_stdout = dup(1);
    FILE *fp = NULL;

    if (save) {
        string filename = "";
        if (is_monthly) filename = "./report/" + to_string(timenow) + "monthly_report.txt";
        else filename = "./report/" + to_string(timenow) + "weekly_report.txt";
        fp = freopen(filename.c_str(), "w", stdout);
    }

    if (is_monthly) {
        // if it is monthly report
        int registered_num = 0;
        int waiting_num = 0;
        int appointment_num = 0;
        int withdraw_num = 0;
        double average_waiting_time = 0.0;

        for (BTree::iterator iter=registDateBTree.lower_bound(timethr);iter!=registDateBTree.end();++iter) {
            int key = (*iter).second;
            person<int>* per = database.retrieve(bPlusTree.select(key ,EQ)[0]);
            average_waiting_time += (double)((per->waiting_time == -1) ? day_between(per->appoint.day, timenow) : per->waiting_time);
            registered_num++;
        }

        for (BTree::iterator iter=withdrawDateBTree.lower_bound(timethr);iter!=withdrawDateBTree.end();++iter)
            withdraw_num ++;

        for (BTree::iterator iter=treatDateBTree.lower_bound(timethr);iter!=treatDateBTree.end();++iter)
            appointment_num ++;
        
        waiting_num = max(0, registered_num-withdraw_num-appointment_num);

        // avoid divide zero error
        if (registered_num != 0)
            average_waiting_time /= (double)registered_num;
        else
            average_waiting_time = 0.0;

        print_split_line();
        printf("monthly statistics report\nIn the last 30 days:\n");
        print_split_line();
        printf("number of registered people: %d\n", registered_num);
        printf("number of currently waiting people: %d\n", waiting_num);
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

    vector< person<int> > report_list;
    for (BTree::iterator iter=registDateBTree.lower_bound(timethr);iter!=registDateBTree.end();++iter) {
        int key = (*iter).second;
        person<int>* per = database.retrieve(bPlusTree.select(key ,EQ)[0]);
        report_list.push_back(*per);
    }

    // sort the report_list. default is sorted by name
    if (sort_by == "name")  sort(report_list.begin(), report_list.end(), sort_by_name);
    else if (sort_by == "profession") sort(report_list.begin(), report_list.end(), sort_by_pro);
    else if (sort_by == "age") sort(report_list.begin(), report_list.end(), sort_by_age);
    else sort(report_list.begin(), report_list.end(), sort_by_name); 

    print_split_line();
    printf("weekly statistics report\nIn the last 7 days:\n");
    print_split_line();

    bool empty = true; 
    int cnt = 0;

    print_split_line();
    printf("the people who have been treated\n");
    print_split_line();
    for (int i = 0; i < int(report_list.size()); i++) {
        if (report_list[i].treated && (report_list[i].appoint.day < timenow)) {
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
        if (!report_list[i].treated && !report_list[i].withdrawal && (report_list[i].appoint.day < timenow)) {
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
        if (!report_list[i].withdrawal && !report_list[i].treated && (report_list[i].appoint.day < timenow)) {
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

bool Report::display_weekly_report(int timethr, int timenow, string sort_by, DatabaseBPlusTree &database, CBPlusTree &bPlusTree, BTree &registDateBTree, BTree &withdrawDateBTree, BTree &treatDateBTree) {
    this -> _display_report(timethr, timenow, 7, sort_by, false, database, bPlusTree, registDateBTree, withdrawDateBTree, treatDateBTree, true);
    return this -> _display_report(timethr, timenow, 7, sort_by, false, database, bPlusTree, registDateBTree, withdrawDateBTree, treatDateBTree, false);
}

bool Report::display_monthly_report(int timethr, int timenow, string sort_by, DatabaseBPlusTree &database, CBPlusTree &bPlusTree, BTree &registDateBTree, BTree &withdrawDateBTree, BTree &treatDateBTree) {
    this -> _display_report(timethr, timenow, 30, sort_by, true, database, bPlusTree, registDateBTree, withdrawDateBTree, treatDateBTree, true);
    return this -> _display_report(timethr, timenow, 30, sort_by, true, database, bPlusTree, registDateBTree, withdrawDateBTree, treatDateBTree, false);
}



struct node {
    int fib_person_key;
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
        void Display(int N);
        void print(node* np, node* prev, int direction);
        int return_num(void);
        node *return_H(void);
        node *Dete(double k);
    private:
        int num_node;       // The number of node in the Fibonacc Heap
        node *H;            // The minimum pointer of the whole Fibonacci Heap
};
#endif