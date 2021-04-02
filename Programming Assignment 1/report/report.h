#ifndef report_h
#define report_h

#include "../Part 1/person.h"
#include <string>

class Report {
    public:
    /*
        read a person's info from a file
        filename: the file you want to read the person info from
        p: the returned person info
    */
    bool read_from_file(string filename, person<int> &p);
    /*
        store a person's info to a file
        p: the person info you want to write. It will write to the
           file named ID.txt where ID is the person's identification.
    */
    bool store_to_file(person<int> p);
    /*
        timenow: the time now
        sort_by: one of "name" "age" or "profession". sorted increasingly
    */
    bool display_weekly_report(int timenow, string sort_by);
    bool display_monthly_report(int timenow, string sort_by);

    private:
    /*
        range: 统计的时段
    */
    bool _display_report(int timenow, int range, string sort_by, bool is_summary);
    static bool sort_by_name(person<int> p1, person<int> p2);
    static bool sort_by_pro(person<int> p1, person<int> p2);
    static bool sort_by_age(person<int> p1, person<int> p2);
    void print_person(int i, vector<person<int>> report_list, bool wait_time);
};
#endif