#ifndef information_h
#define information_h

#include <string>
#include <vector>
using std::string;
using std::vector;
using std::pair;

template<class T> class person;
template<class T> class patient_queue;
template<class T> class fifo;
template<class T> class registration;
class Report;

class Treatment {
public:
    vector<int> day;
    string location;
};

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
    int wait;                           // 0: this person hasn't wait in queue; 1: this person has waited in line;
    int deadline;               // EX: 20190906: setember 9th, 2019; it will be empty if no has letter been submitted 
    Treatment treatment;
    void set_name(string name);
    void set_email(string email);
    void profess(int pro);
    void birth(int day);
    void set_risk_status(int status);
    void age(int age);
    void indentify(int id);
    void information(void);
    int send_registration(int day, int time);
    int return_id(void);
    string return_name(void);
    int return_bir(void);
    int send_withdrawal(void);
    int check_registration(void);
    double find_priority(void);
    registration<T> appoint;
private:
    string name;
    string email;
    int profession;                 // from 0 to 7; indicate 8 professions
    int birthday;           
    int identification;
    int risk_status;                // 0: no risk; 1: low risk; 2: medium risk; 3: high risk;
    int age_group;                  // 1: children(<=12); 2: adolencents(<=18); 3: young adults(<=35); 4: adults(<=50) 5: seniors(<=65); 6: elderly people(<=75); 7: old people(>75);
    double priority = 0;            // largest number means top priority
    int withdrawal = 0;             // 0: no withdrawal record; 1: has withdrawal record
    int letter = 0;                 // 0: no letter has been subitted; 1: a letter has been submitted
    int regist = 0;                 // 0: not send registration; 1: have sent a registration
    int treated = 0;                // 0: not been treated; 1: have been treated
};

template<class T> class patient_queue {
public:
    patient_queue() {
        this -> patient_numbers = 0;
    };
    void add_patient(person<T> *person);                // each element in the queue is a pointer to person information
    int patient_numbers;
    void check_number(void);
    person<T>* find(int id);
    int registrate_number(void);
    int wait_number;
    int withdrawal_number = 0;
    fifo <person<T>*> local;                            // using a queue to store local patient information
    void display(void);

    // Update information
    bool withdrawal_update(int id, Report file);
    bool regist_update(int day, int time, int id, Report file);
    bool letter_update(int day, int id, Report file);
    bool treat_update(int id, Report file);
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
    bool display_weekly_report(int timenow, string sort_by);
    bool display_monthly_report(int timenow, string sort_by);

private:
    /*
        range: 统计的时段
    */
    bool _display_report(int timenow, int range, string sort_by, bool is_summary);
    static bool sort_by_name(person<int> p1, person<int> p2);
    static bool sort_by_pro(person<int> p1, person<int> p2);
    static bool sort_by_age(person<int> p1, person<int> p2);
    void print_person(int i, vector< person<int> > report_list, bool wait_time);
};

#endif