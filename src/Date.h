#ifndef OOP_HOTEL_MANAGEMENT_SYSTEM_DATE_H
#define OOP_HOTEL_MANAGEMENT_SYSTEM_DATE_H
#include <iostream>
class Date {
private :
    int day;
    int month;
    int year;
    public :
    Date();
    Date(int day, int month, int year);
    Date(const Date &obj);
    Date &operator=(const Date &obj);
    ~Date();

    int getDay() const;
    int getMonth() const;
    int getYear() const;

    void setDay(int day);
    void setMonth(int month);
    void setYear(int year);

    bool operator < (const Date &other) const;
    bool operator > (const Date &other) const;
    bool operator == (const Date &other) const;
    bool operator <= (const Date &other) const;
    bool operator >= (const Date &other) const;
    int operator - (const Date &other) const;

    friend std::ostream &operator<<(std::ostream &out, const Date &obj);
    friend std::istream &operator>>(std::istream &in, Date &obj);
};
#endif //OOP_HOTEL_MANAGEMENT_SYSTEM_DATE_H