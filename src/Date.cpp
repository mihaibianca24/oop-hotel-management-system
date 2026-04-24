#include "Date.h"
#include <iostream>
using namespace std;
Date::Date() {
    this->day =1;
    this->month =1;
    this->year =2026;
}
Date::Date(int day,int month,int year) {
    this->day=day;
    this->month=month;
    this->year=year;
}
Date::Date(const Date &obj) {
    this->day = obj.day;
    this->month = obj.month;
    this->year = obj.year;
}
Date & Date ::operator=(const Date &obj) {
    if (this == &obj)
        return *this;
    this->day = obj.day;
    this->month = obj.month;
    this->year = obj.year;
    return *this;
}
Date::~Date(){}

int Date::getDay() const{
    return day;
}
int Date::getMonth() const{
    return month;
}
int Date::getYear() const {
    return year;
}
void Date::setDay(int day) {
    if (day >=1 && day <= 31)
        this->day = day;
}
void Date::setMonth(int month) {
    if (month >=1 && month<=12)
    this->month = month;
}
void Date::setYear(int year) {
    if (year>=2026)
    this->year = year;
}

bool Date::operator<(const Date &other) const {
    if (this->year < other.year)
        return true;
    else if (this->year == other.year && this->month < other.month)
        return true;
    else if (this->year == other.year && this->month == other.month && this->day < other.day)
        return true;
    return false;
}
bool Date::operator>(const Date &other) const {
    if (this->year > other.year)
        return true;
    else if (this->year == other.year && this->month > other.month)
        return true;
    else if (this->year == other.year && this->month == other.month && this->day > other.day)
        return true;
    return false;
}
bool Date::operator<=(const Date &other) const {
    if (this->year < other.year)
        return true;
    if (this->year == other.year && this->month < other.month)
        return true;
    if (this->year == other.year && this->month == other.month && this->day <= other.day)
        return true;
    return false;
}
bool Date::operator>=(const Date &other) const {
    if (this->year > other.year)
        return true;
    else if (this->year == other.year && this->month > other.month)
        return true;
    else if (this->year == other.year && this->month == other.month && this->day >= other.day)
        return true;
    return false;
}
bool Date::operator == (const Date &other) const {
    if (this->year == other.year && this->month == other.month && this->day == other.day)
        return true;
    return false;
}

int Date::operator-(const Date &other) const {
    return (this->year - other.year) * 365 + (this->month - other.month) * 30 + (this->day - other.day);
}
std::ostream &operator<<(std::ostream &out, const Date &obj) {
    out << obj.day << "-" << obj.month << "-" << obj.year;
    return out;
}

std::istream &operator>>(std::istream &in, Date &obj) {
    cout << "Day: ";
    in >> obj.day;
    cout << "Month: ";
    in >> obj.month;
    cout << "Year: ";
    in >> obj.year;
    return in;
}