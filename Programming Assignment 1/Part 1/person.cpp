
#include<stdlib.h>
#include<iostream>
#include<cstdlib>
#include "person.h"
using namespace std;

//member function of person:

//the following function is used to set the patient iformation:
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


// output all the information of the patient;

template<class T> void person<T>::information(void) {
    cout << "the information of this patient is as below : " << endl;  
    cout << "name: " << this -> name << endl; 
    cout << "identification: " << this -> identification << endl;
    cout << "birthday: " << this -> birthday << endl;
    cout << "email: " << this -> email << endl;
    cout << "risk_status: " << this -> risk_status << endl;
    cout << "age_group: " << this -> age_group << endl;
    if(this -> regist == 1){
        cout << "this person has registrated" << endl;
    }else{
        cout << "this person hasn't registrated" << endl;
    }
    return;
}

template<class T> void person<T>::age(int age) {
    if(age < 0){
        cout << "age cannot less than 0" << endl;
        return ;
    }
    if (age <= 12) this -> age_group = 0;
    if (age > 12 && age <= 18) this -> age_group = 1;
    if (age > 18 && age <= 35) this -> age_group = 2;
    if (age > 35 && age <= 50) this -> age_group = 3;
    if (age > 50 && age <= 65) this -> age_group = 4;
    if (age > 65 && age <= 75) this -> age_group = 5;
    if (age > 75) this -> age = 6;
    return;
}


//this function is used patient information to give a priority.
//INPUT: all information
//BASE: based on profession, age_group, register data with weight 0.5, 0.3, 0.2 to calculate a number;
//  for profession: 7 gets the highest priority; for age_group: oldeest first; for register data: early get first;
//OUTPUT: a priority for sort in the local queue
//SIDE EFFECT: none
//Warning:  high risk status is not considered.
template<class T> double person<T>::find_priority(void) {
    double priority = 0; double year, month, day, hour, minute;
    priority += this -> profession * 10;
    priority += this -> age_group * 5;
    int tday[8]; int ttime[4] ;
    tday = this -> appoint -> day;
    ttime = this -> appoint -> time;
    year = tday[0] * 1000 + tday[1] * 100 + tday[2] * 10 + tday[3] - 2015;     // start from 2015, no registration will be earlier than 2015
    month = tday[4] * 10 + tday[5] - 1;        // start from January
    day = tday[6] * 10 + tday[7] - 1;          // start from 1st
    hour = ttime[0] * 10 + ttime[1];
    minute = ttime[2] + ttime[3] - 30;
    if(this -> risk_status == 2){
        day += 30;
    }else if(this -> risk_status != 3 && this -> withdrawal == 1){
        day += 14;
    }
    priority += (year + month * 30 + day  + hour / 24 + minute / 1440) / 5000;

    this -> priority = priority;
    return priority;
}


template<class T> int person<T>::return_id(void) {
    return this -> identification;
}

template<class T> int person<T>::send_withdrawal(void) {
    if(this -> regist == 0){
        cout << "this person hasn't registrate" << endl;
        return 0;
    }
    this -> regist = 0;
    this -> withdrawal = 1;
    return this -> return_id(); 
}


// if a registration is sent, the registration time is recorded.
template<class T> int person<T>::send_registration(int day[8], int time[4]) {
    if(this -> regist == 1){
        cout << "this person has already sent a registration" << endl;
    }
    (this -> appoint) -> day = day;
    (this -> appoint) -> time = time;
    this -> regist = 1;
    this -> treated = 0;
    this -> letter = 0;
    return this -> return_id();
}

template<class T> int person<T>::check_registration(void) {
    return this -> regist;
}

//member function of patient_queue:

template<class T> void patient_queue<T>::add_patient(person<T> *person) {
    this -> patient.pushback(person);
    this -> patient_numbers += 1;
    return;
}

template<class T> person<T>* patient_queue<T>::find(int id) {
    for(int i = 0; i < this -> patient_numbers; i++) {
        if(this -> local -> reprarray[i] -> return_id() == id) {
            cout << "this person is in this hospital" << endl;
            return this->local->reprarray[i];
        }
    }
    cout << "this person is not in this hospital" << endl;
    return NULL;
}

template<class T> void patient_queue<T>::check_number(void) {
    cout << "the patient number in this hospital is " << this -> patient_numbers << endl;
}


template<class T> int patient_queue<T>::registrate_number(void) {   
    int registrate = 0;
    for(int i = 0; i < this -> patient_numbers; i++) {
        if((this -> local) -> reprarray[i] -> check_registration() == 1){
            registrate += 1;
        }
    }
    return registrate;
}

template<class T> bool patient_queue<T>::withdrawal_update(int id, Report file)
{
    person<T>* now = new person<T>;
    now = this->find(id);
    if(now == NULL){
        cout << "this person isn't in the queue" << endl;
        return false;
    }else{
        now->send_withdrawal();
        file.store_to_file(*now);
        return true;
    }
    
}

template<class T> bool patient_queue<T>::regist_update(int day[8], int time[4], int id, Report file)
{
    person<T>* now = new person<T>;
    now = this->find(id);
    if(now == NULL){
        cout << "this person isn't in the queue" << endl;
        return false;
    }else{
        now->send_registration(day,time);
        file.store_to_file(*now);
        return true;
    }
}

template<class T> bool patient_queue<T>::letter_update(int day[8], int id, Report file)
{
    person<T>* now = new person<T>;
    now = this->find(id);
    if(now == NULL){
        cout << "this person isn't in the queue" << endl;
        return false;
    }else if(now->regist == 0){
        cout << "this person havn't send a registration" << endl;
    }else{
        now->deadline = day;
        now->letter = 1;
        file.store_to_file(*now);
        return true;
    }
}

template<class T> bool patient_queue<T>::treat_update(int id, Report file)
{
    person<T>* now = new person<T>;
    now = this->find(id);
    if(now == NULL){
        cout << "this person isn't in the queue" << endl;
        return false;
    }else{
        now -> treated = 1;
        now -> regist = 0;
        file.store_to_file(*now);
        return true;
    }
}