#include "Date.h"
#include <iostream>
#include <iomanip>
 
Date::Date(int year, int month, int day) : _year{year}, _month{month}, _day{day} {};

std::ostream& operator<<(std::ostream& ost, const Date& date) {
    ost << date._year << "/" <<std::setw(2) << std::setfill('0') << date._month << "/" << std::setw(2) << std::setfill('0') << date._day;
    return ost;
}

std::istream& operator>>(std::istream& ist, Date& date) {
    int yr, mt, dy;
    char slash1, slash2;
    ist >> yr >> slash1 >> mt >> slash2 >> dy;

    if(ist && slash1 == '/' && slash2 == '/') {
        date._year = yr;
        date._month = mt;
        date._day = dy;
    } else {
        ist.setstate(std::ios::failbit);
    }
    return ist;
}