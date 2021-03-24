#ifndef person_h
#define person_h

#include<string>
#include<vector>
using std::string;


template<class T> class person;
template<class T> class patient_queue;
template<class T> class fifo;
template<class T> class registration;
template<class T> class treatment;


template<class T> class registration
{
    friend class person<T>;

public: 
    int day[];              // Ex: 20190906 :Setember 9th, 2019
    int time[];             // Ex: 2105 : five pass nine pm
};

template<class T> class person
{
    frient class patient_queue<T>;
public:
    double find_priority(void);
    int wait;                           // 0: this person hasn't wait in queue; 1: this person has waited in line;
    vector<int> deadline;               // EX: 20190906: setember 9th, 2019; it will be empty if no has letter been submitted 
    treatment<T> treatment;
    void set_name(string name);
    void set_email(string email);
    void profess(int pro);
    void birth(int day);
    void set_risk_status(int status);
    void age(int age);
    void indentify(int id);
    void information(void);
    int send_registration(int day[8], int time[4]);
    int return_id(void);
    int send_withdrawal(void);
    int check_registration(void);

private:
    int identification;
    string name;
    string email;
    int profession;         // from 0 to 7; indicate 8 professions
    int birthday;           
    int risk_status;        // 0: no risk; 1: low risk; 2: medium risk; 3: high risk;
    registration<T> appoint;
    int age_group;          // 1: children(<=12); 2: adolencents(<=18); 3: young adults(<=35); 4: adults(<=50) 5: seniors(<=65); 6: elderly people(<=75); 7: old people(>75);
    int priority = 0;
    int withdrawal = 0;                     // 0: no withdrawal record; 1: has withdrawal record
    int letter = 0;                         // 0: no letter has been subitted; 1: a letter has been submitted
    int regist = 0;                     // 0: not send registration; 1: have sent a registration
};

template<class T> class patient_queue
{
    friend class person<T>;

public:
    patient_queue(){
        this->patient_numbers = 0;
    };

    void add_patient(person<T> *person);            // each element in the queue is a pointer to person information
    int patient_numbers;
    void check_number(void);
    bool find(int id);
    int registrate_number(void);
    int wait_number;
    int withdrawal_number = 0;
    fifo< person<T>* > local;                          // using a queue to store local patient information

};


template<class T> class fifo
{
public:
    fifo(int size = 10);
//    virtual ~fifo();
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
    T **reprarray;
    void allocate(void);
    void deallocate(void);
};

template<class T> class treatment
{
public:
    vector< pair<int,int,int,int> > day;
    string location;
};


#endif