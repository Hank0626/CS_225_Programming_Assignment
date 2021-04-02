#include "report.h"
#include "../Part 1/person.h"
#include <iostream>
#include <cstdio>

using namespace std;

int main() {
    Report report;
    report.display_weekly_report(0, "name");
    report.display_monthly_report(0, "name");
    return 0;
}