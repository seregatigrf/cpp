#include <iostream>
#include <iomanip>
#include "date.h"

using namespace std;
struct Day{
    int value;
     explicit Day(int new_value){
        if (new_value < 1 || new_value > 31) {throw invalid_argument("Day value is invalid: " + to_string(new_value));}
        value = new_value;}
};
struct Month{
    int value;
     explicit Month(int new_value){
        if (new_value < 1 || new_value > 12) throw invalid_argument("Month value is invalid: " + to_string(new_value));
        value = new_value;
    }
};
struct Year{
    int value;
     explicit Year(int new_value){value = new_value;}
};

std::ostream& operator<<(std::ostream& out, const Date& date){
    out << setfill('0');
    out << setw(4) << date.GetYear() << "-" << setw(2) << date.GetMonth() << "-" << setw(2) << date.GetDay();
    return out;
};
Date::Date(Year y, Month m, Day d) {
    year = y.value;
    month = m.value;
    day = d.value;
}
Date::Date(int y, int m, int d){
    year = y;
    month = m;
    day = d;
}

int Date::GetYear() const {return year;}
int Date::GetMonth() const {return month;}
int Date::GetDay() const {return day;}

bool operator<(const Date& lhs, const Date& rhs){
    if(lhs.GetYear()!= rhs.GetYear()) return lhs.GetYear() < rhs.GetYear();
    else if(lhs.GetMonth()!= rhs.GetMonth()) return lhs.GetMonth() < rhs.GetMonth();
    return lhs.GetDay() < rhs.GetDay();
};

bool operator>=(const Date& lhs, const Date& rhs){
    return ! (lhs < rhs);
}
bool operator == (const Date& lhs, const Date& rhs){
    return lhs.GetDay()==rhs.GetDay() && lhs.GetMonth() == rhs.GetMonth() && lhs.GetYear() == rhs.GetYear();
}
bool operator!=(const Date& lhs, const Date& rhs){
    return ! (lhs == rhs);
}
bool operator> (const Date& lhs, const Date& rhs){
    return rhs < lhs;
}
bool operator <= (const Date& lhs, const Date& rhs){
    return !(lhs > rhs);
}


Date ParseDate(istream& stream) {
    int day_, month_, year_;
    char ch1, ch2;
    string date_;
    stream >> date_;
    stringstream new_input(date_);
    new_input >> year_;
    new_input >> ch1;
    new_input >> month_;
    new_input >> ch2;
    new_input >> day_;
    if (ch1 != '-' || ch2 != '-') {
        stringstream ss;
        ss << "Wrong date format: " << date_;
        throw invalid_argument(ss.str());
    }
    return { Year(year_), Month(month_), Day(day_)};
}
