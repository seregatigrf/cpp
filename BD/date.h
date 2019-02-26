#pragma once

#include <iostream>
using namespace std;

struct Day;
struct Month;
struct Year;


class Date {
    int year;
    int month;
    int day;
public:
    Date(Year, Month, Day);
    Date(int, int, int);
    int GetYear() const;
    int GetMonth() const;
    int GetDay() const;
};
ostream& operator<<(ostream& stream, const Date& date);

bool operator<(const Date& lhs, const Date& rhs);
bool operator<=(const Date& lhs, const Date& rhs);
bool operator>(const Date& lhs, const Date& rhs);
bool operator>=(const Date& lhs, const Date& rhs);
bool operator==(const Date& lhs, const Date& rhs);
bool operator!=(const Date& lhs, const Date& rhs);

Date ParseDate(istream& stream);
