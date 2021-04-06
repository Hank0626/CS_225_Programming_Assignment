
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#define random(x) rand() % (x)
using namespace std;

string generate_name() {
    string name;
    string name_list[100] = {"James", "Mary", "John", "Patricia", "Robert", "Jennifer", "Michael", "Linda", "William", "Elizabeth", 
                            "David", "Barbara", "Richard", "Susan", "Joseph", "Jessica", "Thomas", "Sarah", "Charles", "Karen", 
                            "Christopher", "Nancy", "Daniel", "Lisa", "Matthew", "Margaret", "Anthony", "Betty", "Donald", "Sandra", 
                            "Mark", "Ashley", "Paul", "Dorothy", "Steven", "Kimberly", "Andrew", "Emily", "Kenneth", "Donna", 
                            "Joshua", "Michelle", "Kevin", "Carol", "Brian", "Amanda", "George", "Melissa", "Edward", "Deborah", 
                            "Ronald", "Stephanie", "Timothy", "Rebecca", "Jason", "Laura", "Jeffrey", "Sharon", "Ryan", "Cynthia", 
                            "Jacob", "Kathleen", "Gary", "Amy", "Nicholas", "Shirley", "Eric", "Angela", "Jonathan", "Helen", 
                            "Stephen", "Anna", "Larry", "Brenda", "Justin", "Pamela", "Scott", "Nicole", "Brandon", "Samantha", 
                            "Benjamin", "Katherine", "Samuel", "Emma", "Frank", "Ruth", "Gregory", "Christine", "Raymond", "Catherine", 
                            "Alexander", "Debra", "Patrick", "Rachel", "Jack", "Carolyn", "Dennis", "Janet", "Jerry", "Virginia"};
    name = name_list[random(100)];
    return name;
}

int generate_id() {
    int result = 0;
    for (int i = 0; i < 8; i++) {
        result = result * 10 + random(10);
    }
    return result;
}

string generate_email(string name) {
    return name + "@gmail.com";
}

int generate_bir() {
    int result;
    int year = random(85) + 1930;
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

int main () {
    srand((int)time(0));
    string name = generate_name();
    int id = generate_id();
    string email = generate_email(name);
    int bir = generate_bir();
    cout << name << endl;
    cout << id << endl;
    cout << email << endl;
    cout << bir << endl;
    return 0;
}

