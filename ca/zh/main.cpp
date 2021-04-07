#include "information.cpp"
#include <iostream>
#include <cstdlib>
#include <string>
#include <ctime>
#include <time.h>
#include <unistd.h>
//#define newline() printf("\n");
#define random(x) rand() % (x)
#define year(x) x / 10000
#define month(x) (x % 10000) / 100
#define day(x) x % 100
#define hour(x) x / 100
#define minu(x) x % 100
using namespace std;

// Generate a random name
string generate_name() {
    string name;
    string name_list[140] = {"James", "Mary", "John", "Patricia", "Robert", "Jennifer", "Michael", "Linda", "William", "Elizabeth", 
                            "David", "Barbara", "Richard", "Susan", "Joseph", "Jessica", "Thomas", "Sarah", "Charles", "Karen", 
                            "Christopher", "Nancy", "Daniel", "Lisa", "Matthew", "Margaret", "Anthony", "Betty", "Donald", "Sandra", 
                            "Mark", "Ashley", "Paul", "Dorothy", "Steven", "Kimberly", "Andrew", "Emily", "Kenneth", "Donna", 
                            "Joshua", "Michelle", "Kevin", "Carol", "Brian", "Amanda", "George", "Melissa", "Edward", "Deborah", 
                            "Ronald", "Stephanie", "Timothy", "Rebecca", "Jason", "Laura", "Jeffrey", "Sharon", "Ryan", "Cynthia", 
                            "Jacob", "Kathleen", "Gary", "Amy", "Nicholas", "Shirley", "Eric", "Angela", "Jonathan", "Helen", 
                            "Stephen", "Anna", "Larry", "Brenda", "Justin", "Pamela", "Scott", "Nicole", "Brandon", "Samantha", 
                            "Benjamin", "Katherine", "Samuel", "Emma", "Frank", "Ruth", "Gregory", "Christine", "Raymond", "Catherine", 
                            "Alexander", "Debra", "Patrick", "Rachel", "Jack", "Carolyn", "Dennis", "Janet", "Jerry", "Virginia"
                            "Tyler", "Maria", "Aaron", "Heather", "Jose", "Diane", "Henry", "Julie", "Adam", "Joyce", 
                            "Douglas", "Victoria", "Nathan", "Kelly", "Peter", "Christina", "Zachary", "Lauren", "Kyle", "Joan",
                            "Walter", "Evelyn", "Harold", "Olivia", "Jeremy", "Judith", "Ethan", "Megan", "Carl", "Cheryl",
                            "Keith", "Martha", "Roger", "Andrea", "Gerald", "Frances", "Christian", "Hannah", "Terry", "Jacqueline"};
    name = name_list[random(140)];
    return name;
}

// Generate a random identity (8 bits integer)
int generate_id() {
    int result = 0;
    for (int i = 0; i < 8; i++) {
        if (i == 0) result = result + random(9) + 1;
        else result = result * 10 + random(10);
    }
    return result;
}

// Generate the email, according to the name
string generate_email(string name) {
    return name + "@gmail.com";
}

// Generate the birday, according to the simulate time
int generate_bir(int time) {
    int result;
    int year = random(85) + time - 85;
    int month = random(12) + 1;
    int day;
    if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) 
        day = random(31) + 1;
    else if (month == 2 && ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)) 
        day = random(29) + 1;
    else if (month == 2 && !((year % 4 == 0 && year % 100 != 0) || year % 400 == 0))
        day = random(28) + 1;
    else 
        day = random(30) + 1;
    result = year * 10000 + month * 100 + day;
    return result;
}

int generate_time() {
    int hour;
    int minu;
    hour = rand() % 24;
    minu = rand() % 60;
    return hour * 100 + minu;
}

bool check_runnian(int y) {
    return ((y % 4 == 0 && y % 100 != 0) || y % 400 == 0);
}

// Update function of the date
int update_date(int date) {
    int y = year(date);
    int m = month(date);
    int d = day(date);
    if (m == 12 && d == 31) {
        y++;
        return y * 10000 + 101;
    }
    if (d <= 27) return ++date;
    else if (d == 31) return y * 10000 + (++m) * 100 + 1;
    else if (d == 28 && m == 2 && check_runnian(y)) return ++date;
    else if (d == 29 && m == 2 && check_runnian(y)) return y * 10000 + 301;
    else if (d == 28 && m == 2 && !check_runnian(y)) return y * 10000 + 301;
    else {
        if (d <= 29) return ++date;
        else if (d == 30 && (m == 1 || m == 3 || m == 5 || m == 7 || m == 8 || m == 10 || m == 12)) return ++date;
        else if (d == 30 && (m == 4 || m == 6 || m == 9 || m == 11)) return y * 10000 + (++m) * 100 + 1;
    }
    return 0;
}

bool check_valid(int date) {
    if (date / 10000000 == 0 || date / 10000000 >= 10) return false;
    else {
        int y = year(date);
        int m = month(date);
        int d = day(date);
        if (y < 1900 || y > 2020) return false;
        else {
            if (m <= 0 || m > 12) return false;
            else {
                if (d <= 0 || d > 31) return false;
                else {
                    if ((m == 4 || m == 6 || m == 9 || m == 11) && d > 30) return false;
                    else if (m == 2 && d > 29) return false;
                    else if (m == 2 && !check_runnian(y) && d == 29) return false;
                }
            }
        }
    }
    return true;
}

int prior_day(int date, string n) {
    if (n == "month") {
        if (month(date) != 1) return date - 100;
        else {
            return (year(date) - 1) * 10000 + 1200 + day(date);
        }
    } 
    else if (n == "week") {
        if (day(date) >= 8) return date - 7;
        else {
            int m = month(date);
            if ((m == 2 || m == 4 || m == 6 || m == 8 || m == 9 || m == 11)) return date - 100 + 24;
            else if (m == 5 || m == 7 || m == 10 || m == 12) return date - 100 + 23;
            else if (m == 1) return (year(date) - 1) * 10000 + 1224 + day(date);
            else if (m == 3) {
                if (check_runnian(year(date))) return date - 100 + 22;
                else return date - 100 + 21;
            }
        }
    }
    return -1;
}

bool check_prior(int day1, int day2) {
    int y1 = year(day1);
    int y2 = year(day2);
    int m1 = month(day1);
    int m2 = month(day2);
    int d1 = day(day1);
    int d2 = day(day2);
    if (y1 < y2) return true;
    else if (y1 == y2) {
        if (m1 < m2) return true;
        else if (m1 == m2) {
            if (d1 <= d2) return true;
        }
    }
    return false;
}

int main () {
    srand(unsigned(time(NULL)));
    newline();
    cout << "Simulation for the registration, queueing and reporting system" << endl;
    newline();
    newline();
    cout << "When do you want to start simulating?" << endl;
    int m_date;
    bool dete = true;
    while (dete) {
        cout << "Please entering a year: (between 19000101 and 20201231) (e.g. 20110708)" << endl;
        cin >> m_date;
        if (check_valid(m_date)) dete = false;
        else cout << "Sorry, the input is invalid" << endl;
    }
    newline();
    int m_day;
    dete = true;
    while (dete) {
        cout << "Please entering how long you want to simulate (in day)" << endl;
        cin >> m_day;
        if (m_day > 0) dete = false;
        else cout << "Sorry, the input is invalid" << endl;
    }
    newline();
    patient_queue<int> queue1; 
    patient_queue<int> queue2; 
    patient_queue<int> queue3;
    Report patient_report;
    cout << "Now the simulation is begin from " << m_date << endl << endl;
    int sim_day = 1;
    int loop_day = m_date;
    while (m_day-- > 0) {
        cout << "-------------------Day " << sim_day++ << "-------------------" << endl;
        cout << "--------------Today is " << loop_day << "----------------" << endl;
        char l;
        dete = false;
        while (true) {
            newline();
            cout << "Please select the operation" << endl;
            cout << "1: Manually enter a patient's information" << endl;
            cout << "2: Add n patients (information randomly generated by the program)" << endl;
            cout << "3: Display the local registry" << endl;
            cout << "4: Send a withdrawal of a person" << endl;
            cout << "8: Display weekly report (You have to simulate it for longer than 7 days)" << endl;
            cout << "9: Display monthly report (You have to simulate it for longer than 30 days)" << endl;
            cout << "n: Jump to the next day" << endl;
            cout << "q: Terminate the whole simulation" << endl;
            cin >> l;
            switch (l) {
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
                    while (dete1) {
                        cout << "Please enter the identification (8 bits integer)" << endl;
                        cin >> identification1;
                        if (((identification1 / 10000000) >= 10) || ((identification1 / 10000000) == 0)) 
                            cout << "Please input a 8 bits integer" << endl;
                        else {
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
                    while (dete1) {
                        cout << "Please enter the regetister time: (e.g. 2105)" << endl;
                        cin >> time1;
                        if (time1 / 100 == 0 || time1 / 1000 >= 10)
                            cout << "Invalid input" << endl;
                        else {
                            if (minu(time1) <= 0 || minu(time1) > 60 || hour(time1) < 0 || hour(time1) >= 24)
                                cout << "Invalid input" << endl; 
                            else {
                                person_hand.send_registration(loop_day, time1);
                                dete1 = false;
                            }
                        }
                    }
                    int age1 = year(loop_day) - year(birthday1) + 1;
                    person_hand.age(age1);
                    person_hand.find_priority();
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
                    dete1 = true;
                    int choose;
                    while (dete1) {
                        cout << "Please select which local registry you want to add this patient to? (1, 2 or 3)" << endl;
                        cin >> choose;
                        if (choose <= 0 || choose > 3) cout << "Invalid input" << endl;
                        else {
                            if (choose == 1) {
                                queue1.add_patient(&person_hand);
                                patient_report.store_to_file(person_hand, "Registry_1");
                            }
                            else if (choose == 2) {
                                queue2.add_patient(&person_hand);
                                patient_report.store_to_file(person_hand, "Registry_2");
                            }
                            else if (choose == 3) {
                                queue3.add_patient(&person_hand);
                                patient_report.store_to_file(person_hand, "Registry_3");
                            }
                            dete1 = false;
                        }
                    }
                }
                    break;
                case '2':
                    {   
                        newline();
                        int n;
                        cout << "Please input how many patient you want to add" << endl;
                        cin >> n;
                        while (n-- > 0) {
                            person<int>* person_com = new person<int>;
                            srand(n * 1000000 * rand());
                            string name_com = generate_name();
                            person_com -> set_name(name_com);
                            person_com -> set_email(generate_email(name_com));
                            int bir_com = generate_bir(year(loop_day));
                            person_com -> birth(bir_com);
                            person_com -> indentify(generate_id());
                            srand(n * 10000 * rand());
                            person_com -> profess(rand() % 7);
                            srand(n * 100 * rand());
                            person_com -> set_risk_status(rand() % 3);
                            person_com -> send_registration(loop_day, generate_time());
                            int age1 = year(loop_day) - year(bir_com) + 1;
                            person_com -> age(age1);
                            person_com -> find_priority();
                            int choose = rand() % 3 + 1;
                            if (choose == 1) {
                                queue1.add_patient(person_com);
                                patient_report.store_to_file(*person_com, "Registry_1");
                            }
                            else if (choose == 2) {
                                queue2.add_patient(person_com);
                                patient_report.store_to_file(*person_com, "Registry_2");
                            }
                            else if (choose == 3) {
                                queue3.add_patient(person_com);
                                patient_report.store_to_file(*person_com, "Registry_3");
                            }
                        }
                    }
                    break;
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
                case '4':
                    {
                        newline();
                        int with_id;
                        cout << "Please enter the ID number of the patient you wish to withdraw:" << endl;
                        cin >> with_id;
                        if (NULL == queue1.find(with_id) && NULL == queue1.find(with_id) && NULL == queue1.find(with_id)) {
                            cout << endl << "This person is not in the registration queue yet" << endl;
                            break;
                        }
                        else {
                            person<int> *with_person;
                            int n = 0;
                            if (NULL != queue1.find(with_id)) {with_person = queue1.find(with_id); n = 1; }
                            else if (NULL != queue2.find(with_id)) {with_person = queue2.find(with_id); n = 2; }
                            else if (NULL != queue3.find(with_id)) {with_person = queue3.find(with_id); n = 3; }
                            cout << endl << "This person is in the local registration " << n << endl;
                            //with_person -> send_withdrawal();
                        }
                    }
                case '8':
                    {
                        if (sim_day <= 7) {
                            cout << endl << "!!! You haven't simulated a week yet !!!" << endl;
                            break;
                        }
                        // else patient_report.display_weekly_report();
                    }
                    break;
                case '9':
                    {
                        if (sim_day <= 30) {
                            cout << endl << "!!! You haven't simulated a month yet !!!" << endl;
                            break;
                        }
                        // else patient_report.display_monthly_report();
                    }
                case 'n':
                    dete = true;
                    break;
                case 'q':
                    exit(1);
            }
            if (dete) {
                loop_day = update_date(loop_day);
                break;
            }
        }
    }
    return 0;
}