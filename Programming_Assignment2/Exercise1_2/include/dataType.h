#ifndef DATATYPE_H
#define DATATYPE_H

#include <string>
#include <typeinfo>
#include <vector>
using namespace std;

class BaseDataType;
class Person;
class MedicalStatus;
class Registration;
class Treatment;

template<class T> class person;
template<class T> class registration;

class BaseDataType {
    private:
        int _recordID;
    public:
        bool operator< (const BaseDataType& data) const{
            return this->_recordID < data._recordID;
        }

        void setRecordID(int recordID) {
            this->_recordID = recordID;
            return;
        }
        int getRecordID() {
            return this->_recordID;
        }
};


class Person: public BaseDataType {
    public:
        string name;
        string email;
        int profession;
        int birthday;
        int age_group;
        pair<int, int> address;
        void print() {
            cout.setf(std::ios::left);
            cout.width(20);
            cout << this->getRecordID() << "|";
            cout.width(20);
            cout << name << "|";
            cout.width(20);
            cout << email << "|";
            cout.width(20);
            cout << profession << "|";
            cout.width(10);
            cout << birthday << "|";
            cout.width(5);
            cout << age_group << endl;
        }
};


class MedicalStatus: public BaseDataType {
    public:
        int risk_status;
        void print() {
            cout.setf(std::ios::left);
            cout.width(20);
            cout << this->getRecordID() << "|";
            cout << risk_status << endl;
        }
};


class Registration: public BaseDataType {
    public:
        double priority;
        int treatment_type;
        int withdrawal;
        int letter;
        int regist;
        int treated;
        int wait;
        int deadline;
        int withdraw_date;
        int waiting_time;
        int regist_date;
        int regist_time;
        void print() {
            cout.setf(std::ios::left);
            cout.width(20);
            cout << this->getRecordID() << "|";
            cout << priority << endl;
        }
};


class Treatment: public BaseDataType {
    public:
        int day;
        string location;
        void print() {
            cout.setf(std::ios::left);
            cout.width(20);
            cout << this->getRecordID() << "|";
            cout << location << endl;
        }
};


template<class T> class person {
    friend class Report;
    friend class Database;
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
    void set_name(string name);
    void set_email(string email);
    void profess(int pro);
    void birth(int day);
    void set_risk_status(int status);
    void set_loc(int loc);
    void age(int age);
    void indentify(int id);
    void information(void);
    int send_registration(int day, int time, int treament_type);
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
    int return_treat(void);
    int return_regist_date(void);
    int return_age_group(void);
    int return_treatment_type(void);
    int return_status_risk(void);
    pair<int, int> return_letter();

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
    int regist_time;
    int treatment_type;
    string treatment_loc;
    int loc;
};

#endif