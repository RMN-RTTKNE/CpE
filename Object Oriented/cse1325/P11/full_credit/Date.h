#ifndef __DATE_H
#define __DATE_H

#include <iostream>

class Date {
    private:
    int _year;
    int _month;
    int _day;

    public:
    Date(int year = 1970, int month = 1, int day = 1);
    auto operator <=> (const Date& date) const = default;
    friend std::ostream& operator<<(std::ostream& ost, const Date& date);
};
#endif 