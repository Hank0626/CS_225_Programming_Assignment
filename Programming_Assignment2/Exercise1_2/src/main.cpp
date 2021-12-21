#include "information.cpp"
#include "helper.cpp"
#include <iostream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <ctime>
#include <time.h>
#include <unistd.h>
#include <vector>

#include "../include/database.h"
using namespace std;

int main () {
    // Test
    Database database;
    // database.person.sort(RELATION_PERSON);
    // database.medicalStatus.sort(RELATION_MEDICALSTATUS);
    // database.treatment.sort(RELATION_TREATMENT);
    // database.registration.sort(RELATION_REGISTRATION);
    // srand(unsigned(time(NULL)));
    patient_queue<int> queue1; 
    patient_queue<int> queue2; 
    patient_queue<int> queue3;
    FibonacciHeap<int> central1;
    FibonacciHeap<int> central2;
    FibonacciHeap<int> central3;
    vector< pair<int, int> > deadline_list;
    Report patient_report;
    vector< person<int>* > today_treat;
    newline();
    newline();
    cout << "--------- Welcome to the registration, queueing and reporting system ---------" << endl;
    newline();
    newline();
    cout << "!!! Before the simulation, please make sure your directory \"database\" is empty !!! " << endl;
    // system("rm ./database/*.txt");
    newline();
    newline();
    cout << "When do you want to start simulating?" << endl;
    int m_date;
    bool dete = true;
    while (dete) {
        cout << "Please entering a year: (between 19000101 and 20201231) (e.g. 20110708)" << endl << endl;
        cout << "!!! If you want to see all the report automatically, please enter 777 !!!" << endl;
        cin >> m_date;
        if (check_valid(m_date) || m_date == 777) dete = false;
        else cout << endl << "Sorry, the input is invalid" << endl << endl;
    }
    newline();
// ############################################################################## auto simulation part ##############################################################################
    if (m_date == 777) {
        cout << endl << "-------------- The simulation will begin soon --------------" << endl;
        sleep(1);
        cout << endl << "******** The information of the simulation is listed below ********" << endl; 
        cout << "The total patient is 250" << endl;
        cout << "The total simulation day is 50" << endl;
        cout << "The simulation will start at 20190901" << endl;
        cout << "**********************************************" << endl;
        int sim = 140;
        int day1 = 1;
        int dete_day1 = 0;
        int date1 = 20190901;
        sleep(1);
        vector<string> filename;
        GetFileNames("./database", filename);
        while (sim-- > 0) {
            cout << endl << "----------------------Day " << day1 << "----------------------" << endl;
            if (dete_day1 == 0) cout << "--------------Now is " << date1 << " Morning----------------" << endl;
            else if (dete_day1 == 1) cout << "--------------Now is " << date1 << " Afternoon----------------" << endl << endl;   

            sleep(1);
            cout << "-------The following are the patient be added today------" << endl;
            int numbb = 0;
            bool yo = true;
            for (int i = 0; i < int(filename.size()); i++) {
                person<int> *per = new person<int>;
                patient_report.read_from_file(filename[i], *per);
                if (per->regist_date == date1 && ((dete_day1 == 0 && check_time((per->regist_time))) || (dete_day1 == 1 && !check_time((per->regist_time))))) {
                    queue1.add_patient(per);
                    database.insert(per);
                    numbb++;
                    usleep(250000);
                    cout << "********* Person " << numbb << " *********" << endl;
                    cout << "Name: " << per -> return_name() << endl;
                    cout << "ID: " << per -> return_id() << endl;
                    cout << "Bir: " << per -> return_bir() << endl;
                    cout << "Treatment Type: " << per -> treatment_type << endl;
                    cout << "Letter: ";
                    if ((per -> return_letter()).first == 0) cout << "No letter is sent" << endl;
                    else cout << "The deadline of treatment is " << (per -> return_letter()).second << endl;
                    cout << endl;
                    if ((per -> return_letter()).first == 1) deadline_list.push_back(make_pair(per -> return_id(), (per -> return_letter()).second));
                    yo = false;
                }
            }     

            if (yo) cout << "None people register" << endl << endl;
            sleep(1);
            srand((int)time(NULL));
            bool yo1 = true;
            if (random(3) == 1) {
                cout << "------ The following are the patient sent withdraw today ------" << endl;
                vector < person<int> > list;
                database.getReportList(list);
                int numm = 1;
                for (int i = 0; i < int(list.size()); i++) {
                    person<int> per = list[i];
                    if (per.regist_date < date1 && per.return_withdraw().first == 0 && per.return_treat() == 0) {
                        per.send_withdrawal(date1);
                        //patient_report.store_to_file_auto(per);
                        database.modify(per.return_id(), per);
                        cout << per.return_name() << " (" << per.return_id() << ")";
                        cout << " sends a withdrawal today. (Register at " << per.regist_date << "}" << endl;
                        numm--;
                        yo1 = false;
                        if (numm == 0) break;
                    }
                }
            }  
            if (yo1) cout << "None people withdraw" << endl << endl;
            int numm = queue1.patient_num();
            for (int i = 0; i < numm; i++) {
                node* np = new node;
                person<int>* per;
                per = queue1.local.popfront();
                (np -> id) = per -> return_id();
                (np -> n) = per -> return_priority();
                if ((per -> return_withdraw()).first == 0 && (per -> treatment_type == 1) ) central1.Insert(np);
                if ((per -> return_withdraw()).first == 0 && (per -> treatment_type == 2) ) central2.Insert(np);
                if ((per -> return_withdraw()).first == 0 && (per -> treatment_type == 3) ) central3.Insert(np);
                queue1.delete_person();
            } 

            vector< pair<int, int> > current_dead;
            for (int i = 0; i < int(deadline_list.size()); i++) {
                int dead = deadline_list[i].second;
                if (date1 == dead) current_dead.push_back(deadline_list[i]);
            }

            sleep(1);
            bool yo3 = true;
            if(int(current_dead.size() != 0)) cout << endl << "------ The following is the treated people due to the deadline ------" << endl;
            for (int i = 0; i < int(current_dead.size()); i++) {
                person<int> temp = database.retrieve(current_dead[i].first);
                if (temp.return_treat() == 1) continue;
                int prio = temp.return_priority();
                central1.Delete_key(prio);
                central2.Delete_key(prio);
                central3.Delete_key(prio);
                temp.set_treat(date1);
                cout << "********* Person " << i + 1 << " *********" << endl;
                cout << "Name: " << temp.return_name() << endl;
                cout << "ID: " << temp.return_id() << endl;
                cout << "Waiting time: " << day_between(date1, temp.regist_date) << " days" << endl << endl;
                temp.set_waiting_time(day_between(date1, temp.regist_date));
                database.modify(current_dead[i].first, temp);
                //patient_report.store_to_file_auto(*temp);
                today_treat.push_back(&temp);
                yo3 = false;
            }
            if (yo3) cout << "No treated people due to the deadline" << endl << endl;
            current_dead.clear();
            numm = central1.return_num() + central1.return_num() + central1.return_num();
            today_treat.clear();
            sleep(1);
            if (numm != 0) cout << endl << "------- The following is regular treated people -------" << endl;
            for (int i = 0; i < min(2, numm); i++) {
                node *H1 = new node;
                node *H2 = new node;
                node *H3 = new node;
                H1 = central1.return_H();
                H2 = central2.return_H();
                H3 = central3.return_H();
                int iden = 0;
                if (H1 -> n <= H2 -> n && H1 -> n <= H3 -> n) iden = H1 -> id;
                else if (H2 -> n <= H1 -> n && H2 -> n <= H3 -> n) iden = H2 -> id;
                else if (H3 -> n <= H1 -> n && H3 -> n <= H2 -> n) iden = H3 -> id;
                person<int> temp = database.retrieve(iden); 

                temp.set_treat(date1);
                temp.set_waiting_time(day_between(date1, temp.regist_date));
                temp.treatment_loc = generate_location();
                
                cout << "********* Person " << i + 1 << " *********" << endl;
                cout << "Name: " << temp.return_name() << endl;
                cout << "ID: " << temp.return_id() << endl;
                cout << "Waiting time: " << day_between(date1, temp.regist_date) << " days" << endl;
                cout << "Location: " << temp.treatment_loc << endl << endl;

                database.modify(iden, temp);
                today_treat.push_back(&temp);

                if (iden == H1 -> id) central1.Extract_Min();
                if (iden == H2 -> id) central2.Extract_Min();
                if (iden == H3 -> id) central3.Extract_Min();
            }

            if (day1 > 2 && (day1 - 1) % 7 == 0 && dete_day1 == 0) {
                cout << endl << "---- Now you have simulated for a week, the weekly report will be presented (may be long) ----" << endl << endl;
                sleep(1);
                patient_report.display_weekly_report(date1, "name", database);
                cout << endl << endl;
            }
            if (day1 > 2 && (day1 - 1) % 30 == 0 && dete_day1 == 0) {
                cout << endl << "---- Now you have simulated for a month, the weekly report will be presented (may be long) ----" << endl << endl;
                sleep(1);
                patient_report.display_monthly_report(date1, "name", database);
                cout << endl << endl;
            }
            sleep(2);
            if (dete_day1 == 0) dete_day1 = 1;
            else dete_day1 = 0;
            if (dete_day1 == 0) {
                date1 = update_date(date1);
                day1++;
            }
        }
        return 0;
    }
// ############################################################################## auto simulation part end ##############################################################################

// ############################################################################## day by day simulation #################################################################################
    int m_day;
    dete = true;
    while (dete) {
        cout << "Please entering how long you want to simulate (in day)" << endl;
        cin >> m_day;
        if (m_day > 0) dete = false;
        else cout << endl << "Sorry, the input is invalid" << endl << endl;
        m_day *= 2;
    }
    newline();
    cout << "Now the simulation is begin from " << m_date << endl << endl;
    int sim_day = 1;
    int loop_day = m_date;
    int dete_day = 0;
    while (m_day-- > 0) {
        char l;
        dete = false;
        while (true) {
            cout << endl << "----------------------Day " << sim_day << "----------------------" << endl;
            if (dete_day == 0) cout << "--------------Now is " << loop_day << " Morning----------------" << endl;
            else if (dete_day == 1) cout << "--------------Now is " << loop_day << " Afternoon----------------" << endl;
            newline();
            cout << "Please select the operation" << endl;
            cout << "1: Manually enter a patient's information" << endl;
            cout << "2: Add n patients (information randomly generated by the program)" << endl;
            cout << "3: Display the local registry" << endl;
            cout << "4: Send a withdrawal of a person" << endl;
            cout << "5: Update a person's information" << endl;
            cout << "6: Display information about the person treated of the last half day" << endl;
            cout << "7: Display the central registry" << endl;
            cout << "8: Display weekly report (You have to simulate it for longer than 7 days)" << endl;
            cout << "9: Display monthly report (You have to simulate it for longer than 30 days)" << endl;
            cout << "n: Jump to the next half day" << endl;
            cout << "q: Terminate the whole simulation" << endl;
            cin >> l;
            switch (l) {
                // Add patient manually
                case '1':
                {
                    newline();
                    person<int> person_hand;
                    string name1; string email1; int birthday1; int identification1; int profession1; int risk_status1;
                    cout << "Please enter the person's name:" << endl;
                    cin >> name1;
                    person_hand.set_name(name1);
                    newline();
                    cout << "Please enter the person's email:" << endl;
                    cin >> email1;
                    person_hand.set_email(email1);
                    newline();
                    bool dete1 = true;
                    while (dete1) {
                        cout << "Please enter the person's birthday: (e.g. 20010626):" << endl;
                        cin >> birthday1;
                        if (!check_valid(birthday1)) 
                            cout << "Invalid input. Please input the birthday again" << endl;
                        else {
                            if (check_prior(loop_day, birthday1)) 
                                cout << "Birthday must be prior to the simulate year" << endl;
                            else {
                                person_hand.birth(birthday1);
                                dete1 = false;
                            }
                        }
                    }
                    newline();
                    dete1 = true;
                    bool dete2 = false;
                    while (dete1) {
                        cout << "Please enter the identification (8 bits integer)" << endl;
                        cin >> identification1;
                        if (((identification1 / 10000000) >= 10) || ((identification1 / 10000000) == 0)) 
                            cout << "Please input a 8 bits integer" << endl;
                        else {
                                if (database.search(identification1)) {
                                    person<int> per = database.retrieve(identification1);
                                    if (per.return_withdraw().first == 0) cout << "The person is already in the local registry" << endl;
                                    else if (per.return_withdraw().first == 1 && day_between(loop_day, per.return_withdraw().second) <= 14) {
                                        cout << "The patient had been withdrawn for less than 14 days and could not be re-registered" << endl;
                                    } 
                                    else if (per.return_withdraw().first == 1 && day_between(loop_day, per.return_withdraw().second) > 14){
                                        cout << "This patient has been withdrawn for more than 14 days and is now re-registered" << endl;
                                        bool dete3 = true;
                                        int time1;
                                        int treatment1;
                                        while (dete3) {
                                            cout << "Please enter the new register time: (e.g. 2105)" << endl;
                                            cin >> time1;
                                            cout << "Please enter the new treatment type" << endl;
                                            cin >> treatment1;
                                            if (time1 / 100 == 0 || time1 / 1000 >= 10)
                                                cout << "Invalid input" << endl;
                                            else {
                                                if (minu(time1) <= 0 || minu(time1) > 60 || hour(time1) < 0 || hour(time1) >= 24)
                                                    cout << "Invalid input" << endl; 
                                                else {
                                                    per.send_registration(loop_day, time1, treatment1);
                                                    dete3 = false;
                                                }
                                            }
                                        }
                                    }
                        
                                    // use -1 to denote no available waiting time yet
                                    per.set_waiting_time(-1);
                                    per.regist_date = loop_day;
                                    database.modify(identification1, per);
                                    dete2 = true;
                                }
                                if (dete2) break;
                                person_hand.indentify(identification1);
                                dete1 = false;
                            }
                    }
                    newline();
                    dete1 = true;
                    while (dete1) {
                        cout << "Please enter the profession number of the person (from 0 to 7)" << endl;
                        cin >> profession1;
                        if (profession1 < 0 || profession1 > 7)
                            cout << "Please input an integer from 0 to 7" << endl;
                        else {
                            person_hand.profess(profession1);
                            dete1 = false;
                        }
                    }
                    newline();
                    dete1 = true;
                    while (dete1) {
                        cout << "Please enter the risk status of the persion: " << endl;
                        cout << "0: no risk; 1: low risk; 2: medium risk; 3: high risk" << endl;
                        cin >> risk_status1;
                        if (risk_status1 < 0 || risk_status1 > 3) 
                            cout << "Please input an integer from 0 to 3" << endl;
                        else {
                            person_hand.set_risk_status(risk_status1);
                            dete1 = false;
                        }
                    }
                    newline();
                    dete1 = true;
                    int time1;
                    int treatment1;
                    while (dete1) {
                        cout << "Please enter the regetister time: (e.g. 2105)" << endl;
                        cin >> time1;
                        if (time1 / 100 == 0 || time1 / 1000 >= 10)
                            cout << "Invalid input" << endl;
                        else {
                            if (minu(time1) <= 0 || minu(time1) > 60 || hour(time1) < 0 || hour(time1) >= 24)
                                cout << "Invalid input" << endl; 
                            else {
                                dete1 = false;
                            }
                        }
                    }
                    dete1 = true;
                    newline();
                    while (dete1) {
                        cout << "Please enter the treatment type (1, 2 or 3)" << endl;
                        cin >> treatment1;
                        if (treatment1 <= 0 || treatment1 > 3)
                            cout << "Invalid input" << endl;
                        else dete1 = false;
                    }
                    person_hand.send_registration(loop_day, time1, treatment1);
                    int age1 = year(loop_day) - year(birthday1) + 1;
                    person_hand.age(age1);
                    person_hand.set_priority();
                    newline();
                    dete1 = true;
                    while (dete1) {
                        char d;
                        cout << "Please decide if you want to set a deadline for this patient (y/n)" << endl;
                        cin >> d;
                        switch (d) {
                            case 'y':
                                {
                                    int dete2 = true;
                                    int dead_line;
                                    while (dete2) {
                                        cout << "Please input the deadline of the treatment: (e.g 20110720)" << endl;
                                        cin >> dead_line;
                                        if (!check_valid(dead_line))
                                            cout << "Please input a vaild date" << endl << endl;
                                        else {
                                            if (check_prior(dead_line, loop_day)) 
                                                cout << "The deadline cannot be prior to current day" << endl << endl;
                                            else {
                                                deadline_list.push_back(make_pair(person_hand.return_id(), dead_line));
                                                person_hand.send_letter(dead_line);
                                                dete2 = false;
                                            }
                                        }
                                    }
                                    dete1 = false;
                                }
                                break;
                            case 'n':
                                dete1 = false;
                                break;
                            default:
                                cout << "Invalid input. Please input again." << endl;
                                break;
                        }
                    }
                    int choose;
                    newline();
                    dete1 = true;
                    while (dete1) {
                        cout << "Please select which local registry you want to add this patient to? (1, 2 or 3)" << endl;
                        cin >> choose;
                        if (choose <= 0 || choose > 3) cout << "Invalid input" << endl;
                        else {
                            if (choose == 1) {
                                person_hand.set_loc(1);
                                queue1.add_patient(&person_hand);
                            }
                            else if (choose == 2) {
                                person_hand.set_loc(2);
                                queue2.add_patient(&person_hand);
                            }
                            else if (choose == 3) {
                                person_hand.set_loc(3);
                                queue3.add_patient(&person_hand);
                            }
                            dete1 = false;
                        }
                    }
                    // 记得存入数据库
                    database.insert(person_hand);
                }
                    break;
                // Add patient by the program
                case '2':
                    {   
                        newline();
                        int n;
                        cout << "Please input how many patient you want to add" << endl;
                        cin >> n;
                        while (n-- > 0) {
                            int treatment_type = n % 3 + 1; //
                            person<int>* person_com = new person<int>;
                            srand(n * 10000 * rand() * int(time(0)));
                            string name_com = generate_name();
                            person_com -> set_name(name_com);
                            person_com -> set_email(generate_email(name_com));
                            int bir_com = generate_bir(year(loop_day));
                            person_com -> birth(bir_com);
                            person_com -> indentify(generate_id());
                            srand(n * 10000 * rand() * int(time(0)));
                            person_com -> profess(rand() % 7);
                            srand(n * 100 * rand() * int(time(0)));
                            person_com -> set_risk_status(rand() % 3);
                            person_com -> send_registration(loop_day, generate_time(), treatment_type);
                            int age1 = year(loop_day) - year(bir_com) + 1;
                            person_com -> age(age1);
                            person_com -> set_priority();
                            int choose = rand() % 3 + 1;
                            if (choose == 1) {
                                person_com -> set_loc(1);
                                queue1.add_patient(person_com);
                            }
                            else if (choose == 2) {
                                person_com -> set_loc(2);
                                queue2.add_patient(person_com);
                            }
                            else if (choose == 3) {
                                person_com -> set_loc(3);
                                queue3.add_patient(person_com);
                            }
                            // 
                            database.insert(person_com);
                        }
                    }
                    break;
                // Display the local
                case '3':
                    {
                        newline();
                        cout << "Please enter which local registry you want to display:" << endl;
                        cout << "1: Registry(1)     2: Registry(2)     3: Registry(3)     4: Show all" << endl;
                        int choose;
                        cin >> choose;
                        newline();
                        switch(choose) {
                            case 1:
                                {
                                    cout << "************ Registry(1) ************" << endl;
                                    queue1.display();
                                }
                                break;
                            case 2:
                                {
                                    cout << "************ Registry(2) ************" << endl;
                                    queue2.display();
                                }
                                break;
                            case 3:
                                {
                                    cout << "************ Registry(3) ************" << endl;
                                    queue3.display();
                                }
                                break;
                            case 4:
                                {
                                    cout << "************ Registry(1) ************" << endl;
                                    queue1.display();
                                    newline();
                                    cout << "************ Registry(2) ************" << endl;
                                    queue2.display();
                                    newline();
                                    cout << "************ Registry(3) ************" << endl;
                                    queue3.display();
                                    newline();
                                }
                                break;
                        }
                    }
                    break;
                // Send withdrawal
                case '4':
                    {
                        int identification1;
                        cout << "Please enter the patient ID number you want to modify" << endl;
                        cin >> identification1;
                        if (0 == database.search(identification1)) cout << "The person has not register yet" << endl;
                        else {
                            person<int> per;
                            if (per.return_withdraw().first == 1 || per.return_treat() == 1) {
                                cout << "The person has already withdraw or treated" << endl;
                                break;
                            }
                            else if (per.regist_date == loop_day) {
                                cout << "You cannot withdraw at the same day with the registration" << endl;
                                break;
                            }
                            per.send_withdrawal(loop_day);
                            database.modify(identification1, per);
                        }
                    }
                    break;
                case '5':
                // 记得从数据库读
                // Update the information
                    {
                        int identification1;
                        cout << "Please enter the patient ID number you want to modify" << endl;
                        cin >> identification1;
                        bool dete1 = true;
                        if (0 == database.search(identification1)) cout << "The person has not register yet" << endl;
                        else {
                            person<int> per = database.retrieve(identification1);
                            while (dete1) {
                                    cout << "Please select which information you want to change for " << per.return_name() << " (ID: " << per.return_id() << ")" << endl;
                                    cout << "profession or risk (input : p/r)" << endl;
                                    char in;
                                    bool dete2 = true;
                                    cin >> in;
                                    if (in == 'p') {
                                        int profession1;
                                        while (dete2) {
                                            cout << "Please enter the profession number of the person (from 0 to 7)" << endl;
                                            cin >> profession1;
                                            if (profession1 < 0 || profession1 > 7)
                                                cout << "Please input an integer from 0 to 7" << endl;
                                            else {
                                                per.profess(profession1);
                                                dete2 = false;
                                            }
                                        }
                                        double pri = per.return_priority();
                                        per.set_priority();
                                        database.modify(identification1, per);
                                        int de = 0;
                                        if (NULL != central1.Find(central1.return_H(), pri)) de = 1;
                                        else if (NULL != central2.Find(central2.return_H(), pri)) de = 2;
                                        else if (NULL != central3.Find(central3.return_H(), pri)) de = 3;
                                        if (de == 1) {
                                            central1.Delete_key(pri);
                                            node* np = new node;
                                            np -> id = per.return_id();
                                            np -> n = per.return_priority();
                                            central1.Insert(np);
                                        }
                                        if (de == 2) {
                                            central2.Delete_key(pri);
                                            node* np = new node;
                                            np -> id = per.return_id();
                                            np -> n = per.return_priority();
                                            central2.Insert(np);
                                        }
                                        if (de == 3) {
                                            central3.Delete_key(pri);
                                            node* np = new node;
                                            np -> id = per.return_id();
                                            np -> n = per.return_priority();
                                            central3.Insert(np);
                                        }
                                        dete1 = false;
                                    }
                                    else if (in == 'r') {
                                        int risk_status1;
                                        while (dete2) {
                                            cout << "Please enter the risk status of the persion: " << endl;
                                            cout << "0: no risk; 1: low risk; 2: medium risk; 3: high risk" << endl;
                                            cin >> risk_status1;
                                            if (risk_status1 < 0 || risk_status1 > 3) 
                                                cout << "Please input an integer from 0 to 3" << endl;
                                            else {
                                                per.set_risk_status(risk_status1);
                                                dete2 = false;
                                            }
                                        }
                                        double pri = per.return_priority();
                                        per.set_priority();
                                        database.modify(identification1, per);
                                        int de = 0;
                                        if (NULL != central1.Find(central1.return_H(), pri)) de = 1;
                                        else if (NULL != central2.Find(central2.return_H(), pri)) de = 2;
                                        else if (NULL != central3.Find(central3.return_H(), pri)) de = 3;
                                        if (de == 1) {
                                            central1.Delete_key(pri);
                                            node* np = new node;
                                            np -> id = per.return_id();
                                            np -> n = per.return_priority();
                                            central1.Insert(np);
                                        }
                                        if (de == 2) {
                                            central2.Delete_key(pri);
                                            node* np = new node;
                                            np -> id = per.return_id();
                                            np -> n = per.return_priority();
                                            central2.Insert(np);
                                        }
                                        if (de == 3) {
                                            central3.Delete_key(pri);
                                            node* np = new node;
                                            np -> id = per.return_id();
                                            np -> n = per.return_priority();
                                            central3.Insert(np);
                                        }
                                        dete1 = false;
                                    }
                                    else cout << "Invalid input. Please enter it again." << endl;
                                }
                        }
                    }
                    break;
                // Display the treated people
                case '6':
                    {
                        if (sim_day == 1 && dete_day == 0) {
                            cout << endl << "!!! This is the first half day of simulation. No person has been treated yet !!!" << endl;
                            break;
                        }
                        cout << endl << "-----The following is the people be treated yesterday-----" << endl << endl;
                        cout << int(today_treat.size()) << "lpysb\n";
                        for (int i = 0; i < int(today_treat.size()); i++) {
                            cout << "********* Person" << i + 1 << " *********" << endl;
                            cout << "Name: " << today_treat[i] -> return_name() << endl;
                            cout << "ID: " << today_treat[i] -> return_id() << endl;
                            cout << "Bir: " << today_treat[i] -> return_bir() << endl;
                            cout << "Treated date: " << today_treat[i] -> treat_date << endl;
                            cout << "Treated location: " << today_treat[i] -> treatment_loc << endl << endl;
                        }
                    }
                    break;
                // Display the central
                case '7':
                    {
                    bool cho = true;
                    int choo;
                    while (cho) {
                        cout << "Please input which treating central registry you want to display (1, 2 or 3)" << endl;
                        cout << "----- You can also input 4 to display all three central resgistry -----" << endl; 
                        cin >> choo;
                        if (choo <= 0 || choo > 4) cout << "Invalid input" << endl;
                        else {
                            if (choo == 1) central1.Display();
                            if (choo == 2) central2.Display();
                            if (choo == 3) central3.Display();
                            if (choo == 4) {
                                central1.Display();
                                cout << "===============================================" << endl;
                                central2.Display();
                                cout << "===============================================" << endl;
                                central3.Display();
                                cout << "===============================================" << endl;
                            }
                            cho = false;
                        } 
                    }
                    }
                    break;
                // Display weekly reort
                case '8':
                    {
                        cout << "sort by name, profession category or age group: (enter name, age, or profession) " << endl;
                        string sort_by = "None";
                        while (true) {
                            cin >> sort_by;
                            if (sort_by != "name" && sort_by != "age" && sort_by != "profession") {
                                cout << "Invalid input (enter name, age, or profession)" << endl;
                                continue;
                            }
                            break;
                        }
                        patient_report.display_weekly_report(loop_day, sort_by, database);
                    }
                    break;
                // Display monthly report
                case '9':
                    {
                        patient_report.display_monthly_report(loop_day, "name", database);
                    }
                    break;
                // Jump to the next half day
                case 'n':
                    dete = true;
                    break;
                // Quit the whole program
                case 'q':
                    exit(1);
            }
            // Set the treat and the appointment
            if (dete) {
                // From queue1, queue2, queue3 to the central
                int numb = queue1.patient_num();
                for (int i = 0; i < numb; i++) {
                    node* np = new node;
                    person<int>* person_add = queue1.local.popfront();
                    (np -> id) = person_add -> return_id();
                    (np -> n) = person_add -> return_priority();
                    if ((person_add -> return_withdraw()).first == 0) {
                        if (person_add -> treatment_type == 1) central1.Insert(np);
                        if (person_add -> treatment_type == 2) central2.Insert(np);
                        if (person_add -> treatment_type == 3) central3.Insert(np);
                    }
                    queue1.delete_person();
                }
                numb = queue2.patient_num();
                for (int i = 0; i < numb; i++) {
                    node* np = new node;
                    person<int>* person_add = queue2.local.popfront();
                    (np -> id) = person_add -> return_id();
                    (np -> n) = person_add -> return_priority();
                    if ((person_add -> return_withdraw()).first == 0) {
                        if (person_add -> treatment_type == 1) central1.Insert(np);
                        if (person_add -> treatment_type == 2) central2.Insert(np);
                        if (person_add -> treatment_type == 3) central3.Insert(np);
                    }
                    queue2.delete_person();
                }
                numb = queue3.patient_num();
                for (int i = 0; i < numb; i++) {
                    node* np = new node;
                    person<int>* person_add = queue3.local.popfront();
                    (np -> id) = person_add -> return_id();
                    (np -> n) = person_add -> return_priority();
                    if ((person_add -> return_withdraw()).first == 0) {
                        if (person_add -> treatment_type == 1) central1.Insert(np);
                        if (person_add -> treatment_type == 2) central2.Insert(np);
                        if (person_add -> treatment_type == 3) central3.Insert(np);
                    }
                    queue3.delete_person();
                }
                // Determine whether the deadline is presented
                vector< pair<int, int> > current_dead;
                today_treat.clear();
                for (int i = 0; i < int(deadline_list.size()); i++) {
                    int dead = deadline_list[i].second;
                    if (loop_day == dead) current_dead.push_back(deadline_list[i]);
                }
                for (int i = 0; i < int(current_dead.size()); i++) {
                    person<int> temp = database.retrieve(current_dead[i].first);
                    int prio = temp.return_priority();
                    central1.Delete_key(prio);
                    central2.Delete_key(prio);
                    central3.Delete_key(prio);
                    temp.set_treat(loop_day);
                    temp.set_waiting_time(day_between(loop_day, temp.regist_date));
                    database.modify(current_dead[i].first, temp);
                    today_treat.push_back(&temp);
                }
                // Everyday at most two patients are treated
                numb = central1.return_num() + central2.return_num() + central3.return_num();
                cout << numb << endl;
                for (int i = 0; i < min(2, numb); i++) {
                    int iden = 0;
                    node *H1 = new node;
                    node *H2 = new node;
                    node *H3 = new node;
                    H1 = central1.return_H();
                    H2 = central2.return_H();
                    H3 = central3.return_H();
                    if (H1 -> n <= H2 -> n && H1 -> n <= H3 -> n) iden = H1 -> id;
                    else if (H2 -> n <= H1 -> n && H2 -> n <= H3 -> n) iden = H2 -> id;
                    else if (H3 -> n <= H1 -> n && H3 -> n <= H2 -> n) iden = H3 -> id;
                    person<int> temp = database.retrieve(iden);
                    temp.set_treat(loop_day);
                    temp.set_waiting_time(day_between(loop_day, temp.regist_date));
                    database.modify(iden, temp);
                    today_treat.push_back(&temp);
                    if (iden == H1 -> id) central1.Extract_Min();
                    else if (iden == H2 -> id) central2.Extract_Min();
                    else if (iden == H3 -> id) central3.Extract_Min();
                }
                cout << int(today_treat.size()) << "lpyyyyyyyy" << endl;
                for (int i = 0; i < int(today_treat.size()); i++) {
                    srand(i * 100000);
                    today_treat[i] -> treat_date = loop_day;
                    today_treat[i] -> treatment_loc = generate_location();
                }
                // Update the date, jump to the next half day
                if (dete_day == 0) dete_day = 1;
                else if (dete_day == 1) dete_day = 0;
                if (dete_day == 0) {
                    loop_day = update_date(loop_day);
                    sim_day++;
                }
                break;
            }
        }
    }

// ############################################################################## day by day simulation end #################################################################################
    return 0;
}





