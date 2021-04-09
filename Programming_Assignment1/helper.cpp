#ifndef helper_cpp
#define helper_cpp

#define newline() printf("\n");
#define random(x) rand() % (x)
#define year(x) x / 10000
#define month(x) (x % 10000) / 100
#define day(x) x % 100
#define hour(x) x / 100
#define minu(x) x % 100

// Generate a random name
string generate_name() {
    string name;
    string name_list[140] = {"James", "Mary", "John", "Patricia", "Robert", "Jennifer", "Michael",  "Linda", "William", "Elizabeth", 
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
    name = name_list[random(100)];
    return name;
}

// Generate a random location
string generate_location() {
    string loc;
    string loc_list[10] = {"Mayo Clinic", "Cleveland Clinic", "Massachusetts General Hospital", "Toronto General Hospital",
                            "Charité Hospital", "The Johns Hopkins Hospital", "UniversitätsSpital Zürich", "Singapore Gnernal Hospital",
                            "Sheba Medical Center", "Karolinska University Hospital"};
    loc = loc_list[random(10)];
    return loc;
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

// Generate a random time
int generate_time() {
    int hour;
    int minu;
    hour = rand() % 24;
    minu = rand() % 60;
    return hour * 100 + minu;
}

// Check the leap year
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

// Check whether a date is valid
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

// Calculate the prior date
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

// Check whether the day is prior to the other day
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


int getday(int year, int month, int day) {
	int m[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	if (check_runnian(year)) m[2]++;
	int result = 0;
	for (int i = 1; i < year; i++) {
		result += 365;
		if (check_runnian(i)) result++;
	}
	for (int i = 1; i < month; i++) result += m[i];
	result += day;
	return result;
}

// determine how many days between two dates
int day_between (int date1, int date2) {
    int year1 = year(date1);
    int year2 = year(date2);
    int month1 = month(date1);
    int month2 = month(date2);
    int day1 = day(date1);
    int day2 = day(date2);
	return abs(getday(year2, month2, day2) - getday(year1, month1, day1));
}

// Check whether it is morning or afternoon 
bool check_time (int time1) {
    int h = hour(time1);
    if (0 <= h && h < 12) return true;
    else return false;
}

#endif