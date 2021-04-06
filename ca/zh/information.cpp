#include <cstdlib>
#include <stdlib.h>
#include <iostream>
#include <cstdio>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <cstring>
#include <sys/types.h>   
#include <dirent.h>
#include "information.h"
#define newline() printf("\n")
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
    double priority = 0; 
    double year, month, day, hour, minute;
    priority += this -> profession * 10;
    priority += this -> age_group * 5;
    int tday; 
    int ttime;
    tday = this -> appoint -> day;
    ttime = this -> appoint -> time;
    year = tday / 10000 - 2015;     // start from 2015, no registration will be earlier than 2015
    month = (tday - tday / 10000 * 10000) / 100 - 1;        // start from January
    day = (tday - tday / 100 * 100) - 1;          // start from 1st
    hour = ttime / 100;
    minute = ttime - ttime / 100 * 100;
    if (this -> risk_status == 2) day += 30;
    else if (this -> risk_status != 3 && this -> withdrawal == 1) day += 14;
    priority -= (year + month * 30 + day  + hour / 24 + minute / 1440) / 5000;
    this -> priority = priority;
    return priority;
}

template<class T> int person<T>::return_id(void) {
    return this -> identification;
}

template<class T> int person<T>::send_withdrawal(void) {
    if (this -> regist == 0){
        cout << "this person hasn't registrated yet" << endl;
        return 0;
    }
    this -> regist = 0;
    this -> withdrawal = 1;
    return this -> return_id(); 
}

// if a registration is sent, the registration time is recorded.
template<class T> int person<T>::send_registration(int day, int time) {
    if (this -> regist == 1){
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
// ########################################## person<T> end #########################################


// ########################################## patient_queue<T> #########################################
template<class T> void patient_queue<T>::add_patient(person<T> *person) {
    this -> patient.pushback(person);
    this -> patient_numbers += 1;
    return;
}

template<class T> person<T>* patient_queue<T>::find(int id) {
    for (int i = 0; i < this -> patient_numbers; i++) {
        if (this -> local -> reprarray[i] -> return_id() == id) {
            cout << "this person is in this hospital" << endl;
            return this -> local -> reprarray[i];
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
    for (int i = 0; i < this -> patient_numbers; i++) {
        if ((this -> local) -> reprarray[i] -> check_registration() == 1) registrate++;
    }
    return registrate;
}

template<class T> bool patient_queue<T>::withdrawal_update(int id, Report file) {
    person<T>* now = new person<T>;
    now = this -> find(id);
    if (NULL == now) {
        cout << "this person isn't in the queue" << endl;
        return false;
    }
    else {
        now -> send_withdrawal();
        file.store_to_file(*now);
        return true;
    }
    
}

template<class T> bool patient_queue<T>::regist_update(int day, int time, int id, Report file) {
    person<T>* now = new person<T>;
    now = this -> find(id);
    if (NULL == now) {
        cout << "this person isn't in the queue" << endl;
        return false;
    }
    else {
        now -> send_registration(day,time);
        file.store_to_file(*now);
        return true;
    }
}

template<class T> bool patient_queue<T>::letter_update(int up_day, int id, Report file) {
    person<T>* now = new person<T>;
    now = this -> find(id);
    if (NULL == now) {
        cout << "this person isn't in the queue" << endl;
        return false;
    }
    else if (now -> regist == 0) {
        cout << "this person havn't send a registration" << endl;
    }
    else {
        now -> deadline = up_day;
        now -> letter = 1;
        file.store_to_file(*now);
        return true;
    }
}

template<class T> bool patient_queue<T>::treat_update(int id, Report file) {
    person<T>* now = new person<T>;
    now = this -> find(id);
    if (NULL == now) {
        cout << "this person isn't in the queue" << endl;
        return false;
    }
    else {
        now -> treated = 1;
        now -> regist = 0;
        file.store_to_file(*now);
        return true;
    }
}
// ########################################## patient_queue<T> end #########################################

// ########################################## Report #########################################
bool Report::read_from_file(string filename, person<int> &p) {
    ifstream fin(filename);
    if (!fin.is_open()) {
        fin.close();
        cout << "cannot open: " + filename << endl;
        return false;
    }
    fin >> p.identification;
    fin >> p.name;
    fin >> p.email;
    fin >> p.profession;
    fin >> p.birthday;
    fin >> p.risk_status;
    fin >> p.appoint.day;
    fin >> p.appoint.time;
    fin >> p.age_group;
    fin >> p.withdrawal;
    fin >> p.deadline;                
    fin >> p.letter;
    fin >> p.regist;
    fin >> p.treated;
    fin.close();
    return true;
}

bool Report::store_to_file(person<int> p) {
    string filename = to_string(p.identification);
    filename += ".txt";
    ofstream fout(filename, ios::trunc);
    if (!fout.is_open()) {
        cout << "cannot open: " + filename << endl;
        return false;
    }
    fout << p.identification << "\n";
    fout << p.name << "\n";
    fout << p.email << "\n";
    fout << p.profession << "\n";
    fout << p.birthday << "\n";
    fout << p.risk_status << "\n";
    fout << p.appoint.day << "\n";
    fout << p.appoint.time << "\n";
    fout << p.age_group << "\n";
    fout << p.withdrawal << "\n";
    fout << p.deadline << "\n";
    fout << p.letter << "\n";
    fout << p.regist << "\n";
    fout << p.treated << "\n";
    fout.close();
    return true;
}

void GetFileNames(string path, vector<string> &filenames) {
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

void Report::print_person(int i, vector<person<int>> report_list, bool wait_time) {
    newline();
    cout << "name: " << report_list[i].name << endl;
    printf("profession category: %d\n", report_list[i].profession);
    printf("age category: %d\n", report_list[i].age_group);
    printf("risk status: %d\n", report_list[i].risk_status);
    if (wait_time) printf("wait time until now: %f\n", -1.0); // todo 
    newline();
}

bool Report::_display_report(int timenow, int range, string sort_by, bool is_summary) {
    vector<person<int>> report_list;
    vector<string> filenames;
    GetFileNames("./database", filenames);
    for (int i = 0; i < filenames.size(); i++) {
        person<int> p;
        this -> read_from_file(filenames[i], p);
        report_list.push_back(p);
    }
    if (is_summary) {
        int registered_num = report_list.size();
        int waiting_num = 0;
        int appointment_num = 0;
        int withdraw_num = 0;
        int average_waiting_time = -1.0; // todo
        for (int i = 0; i < report_list.size(); i++) {
            if (!report_list[i].withdrawal && !report_list[i].regist && !report_list[i].treated) waiting_num++;
            if (report_list[i].regist) appointment_num++;
            if (report_list[i].withdrawal) withdraw_num++;
        }
        print_split_line();
        printf("monthly statistics report\n");
        print_split_line();
        printf("number of registered people: %d\n", registered_num);
        printf("number of waiting people: %d\n", waiting_num);
        printf("number of treatment appointments: %d\n", appointment_num);
        printf("average waiting time: %d\n", average_waiting_time);
        printf("number of people who withdrew their registration: %d\n", withdraw_num);
        newline();
        return true;
    }

    if (sort_by == "name")  sort(report_list.begin(), report_list.end(), this -> sort_by_name);
    else if (sort_by == "profession") sort(report_list.begin(), report_list.end(), this -> sort_by_pro);
    else if (sort_by == "age") sort(report_list.begin(), report_list.end(), this -> sort_by_age);
    else sort(report_list.begin(), report_list.end(), this -> sort_by_name); 

    print_split_line();
    printf("the people who have been treated\n");
    print_split_line();
    for (int i = 0; i < int(report_list.size()); i++) {
        if (report_list[i].treated) print_person(i, report_list, false);
    }

    print_split_line();
    printf("the registered people with a set appointment\n");
    print_split_line();
    for (int i = 0;i < int(report_list.size()); i++) {
        if (report_list[i].regist && !report_list[i].treated && !report_list[i].withdrawal) print_person(i, report_list, true);
    }
    print_split_line();
    printf("the queueing people without a set appointment\n");
    print_split_line();
    for (int i = 0; i < int(report_list.size()); i++) {
        if (!report_list[i].regist && !report_list[i].withdrawal && !report_list[i].treated) print_person(i, report_list, true);
    }
    return true;

}

bool Report::display_weekly_report(int timenow, string sort_by) {
     return this -> _display_report(timenow, -1, sort_by, false);
}

bool Report::display_monthly_report(int timenow, string sort_by) {
    return this -> _display_report(timenow, -1, sort_by, true);
}