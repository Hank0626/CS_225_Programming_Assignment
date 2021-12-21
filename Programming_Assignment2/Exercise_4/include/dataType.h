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

class BaseDataType {
    private:
        int _recordID;
    public:
        void setRecordID(int recordID) {
            this->_recordID = recordID;
            return;
        }
        int getRecordID() {
            return this->_recordID;
        }
};

/*
struct pair {
    int first;
    int second;
};
*/

class Person: public BaseDataType {
    public:
        string name;
        string email;
        int profession;
        int birthday;
        int age_group;
        pair<int, int> address;
};


class MedicalStatus: public BaseDataType {
    public:
        int risk_status;
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
};


class Treatment: public BaseDataType {
    public:
        int day;
        string location;
};


#endif