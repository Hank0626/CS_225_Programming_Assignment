#include "report.h"
#include "../Part 1/person.h"
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <cstring>

#include <sys/types.h>   
#include <dirent.h>
#define newline() printf("\n")
using namespace std;

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
    while((ptr = readdir(pDir))!=0) {
        if (strcmp(ptr->d_name, ".") != 0 && strcmp(ptr->d_name, "..") != 0)
            filenames.push_back(path + "/" + ptr->d_name);
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
    if (wait_time) 
    printf("wait time until now: %f\n", -1.0); // todo 
    newline();
}

bool Report::_display_report(int timenow, int range, string sort_by, bool is_summary) {
    vector<person<int>> report_list;
    vector<string> filenames;
    GetFileNames("./database", filenames);
    for (int i=0;i<filenames.size();i++) {
        person<int> p;
        this->read_from_file(filenames[i], p);
        report_list.push_back(p);
    }

    if (is_summary) {
        int registered_num = report_list.size();
        int waiting_num = 0;
        int appointment_num = 0;
        int withdraw_num = 0;
        bool average_waiting_time = -1.0; // todo
        for (int i=0;i<report_list.size();i++) {
            if (!report_list[i].withdrawal && !report_list[i].regist && !report_list[i].treated)
            waiting_num ++;
            if (report_list[i].regist) 
            appointment_num ++;
            if (report_list[i].withdrawal)
            withdraw_num ++;
        }
        print_split_line();
        printf("monthly statistics report\n");
        print_split_line();
        printf("number of registered people: %d\n", registered_num);
        printf("number of waiting people: %d\n", waiting_num);
        printf("number of treatment appointments: %d\n", appointment_num);
        printf("average waiting time: %d", average_waiting_time);
        printf("number of people who withdrew their registration: %d\n", withdraw_num);
        newline();
        return true;
    }

    if (sort_by == "name") 
    sort(report_list.begin(), report_list.end(), this->sort_by_name);
    else if (sort_by == "profession")
    sort(report_list.begin(), report_list.end(), this->sort_by_pro);
    else if (sort_by == "age")
    sort(report_list.begin(), report_list.end(), this->sort_by_age);
    else
    sort(report_list.begin(), report_list.end(), this->sort_by_name); 

    print_split_line();
    printf("the people who have been treated\n");
    print_split_line();
    for (int i=0;i<report_list.size();i++)
    if (report_list[i].treated)
    print_person(i, report_list, false);

    print_split_line();
    printf("the registered people with a set appointment\n");
    print_split_line();
    for (int i=0;i<report_list.size();i++)
    if (report_list[i].regist && !report_list[i].treated && !report_list[i].withdrawal)
    print_person(i, report_list, true);

    print_split_line();
    printf("the queueing people without a set appointment\n");
    print_split_line();
    for (int i=0;i<report_list.size();i++)
    if (!report_list[i].regist && !report_list[i].withdrawal && !report_list[i].treated)
    print_person(i, report_list, true);
    return true;

}

bool Report::display_weekly_report(int timenow, string sort_by) {
    return this->_display_report(timenow, -1, sort_by, false);
}

bool Report::display_monthly_report(int timenow, string sort_by) {
    return this->_display_report(timenow, -1, sort_by, true);
}
