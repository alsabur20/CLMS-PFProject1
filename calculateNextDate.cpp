#include <iostream>
#include <time.h>
using namespace std;

string getNextDate(int offset);
string currentDateTime();

int main() {
    int day;
    cout << "Days To Add: ";
    cin >> day;
    cout << "Current Date: " << currentDateTime() << endl;
    cout << "After Date: " << getNextDate(day) << endl;
}

string currentDateTime() {
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    // Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
    // for more information about date/time format
    strftime(buf, sizeof(buf), "%Y-%m-%d", &tstruct);

    return buf;
}

string getNextDate(int offset) {
    string date = currentDateTime();
    int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    string stringYear = { date[0], date[1], date[2], date[3], '\0' };
    string stringMonth = { date[5], date[6], '\0' };
    string stringDay = { date[8], date[9], '\0' };

    int year = stoi(stringYear);
    int month = stoi(stringMonth);
    int day = stoi(stringDay);

    day += offset;
    if (day > days[month]) {
        day = 1;
        month += 1;
        if (month > 12) {
            month = 1;
            year += 1;
        }
    }

    if (day < 10) {
        stringDay = "0" + to_string(day);
    } else {
        stringDay = to_string(day);
    }

    if (month < 10) {
        stringMonth = "0" + to_string(month);
    } else {
        stringMonth = to_string(month);
    }

    stringYear = to_string(year);

    return stringYear + "-" + stringMonth + "-" + stringDay;
}