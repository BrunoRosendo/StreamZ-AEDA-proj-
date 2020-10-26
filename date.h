//
// Created by joaog on 10/23/2020.
//

#ifndef PROJETO1_DATE_H
#define PROJETO1_DATE_H

#include <iostream>
#include <string>

using namespace std;

class Date
{
public:
    Date();
    Date(unsigned int year, unsigned int month, unsigned int day);
    Date(const string& yearMonthDay); // yearMonthDay must be in format "yyyy/mm/dd"
    void setDate(unsigned int year, unsigned int month, unsigned int day);
    unsigned int getYear() const;
    unsigned int getMonth() const;
    unsigned int getDay() const;
    string getDate() const; // returns the date in format "yyyy/mm/dd"
    bool isValid();
    unsigned int getAge() const;
    bool operator==(const Date& date);
    bool operator!=(const Date& date);
    bool operator>(const Date& date);
    bool operator<(const Date& date);
    bool operator>=(const Date& date);
    bool operator<=(const Date& date);
private:
    string datestring;
    bool isleap();
    int daysOfMonth();
};

class DateIsNotValid{
private:
    string date;
public:
    DateIsNotValid(string date);
    string what();
};

#endif //PROJETO1_DATE_H
