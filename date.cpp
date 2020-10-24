//
// Created by bruno on 24/10/2020.
//

#include <iostream>
#include <string>
#include <sstream>
#include <ctime>
#include "date.h"

using namespace std;

bool Date::isValid() {
    int year = stoi(datestring.substr(0, 4));
    int month = stoi(datestring.substr(4, 2));
    int day = stoi(datestring.substr(6, 2));
    if (month > 12 || month < 1) return false;
    if (day > daysOfMonth() || day < 1) return false;
    if (year < 0) return false;
    return true;
}

void Date::setDate(unsigned int year, unsigned int month, unsigned int day) {
    string years, months, days;
    if (year < 10) years = "000" + to_string(year);
    else if (year < 100) years = "00" + to_string(year);
    else if (year < 1000) years = "0" + to_string(year);
    else years = to_string(year);
    if (month < 10) months = "0" + to_string(month);
    else months = to_string(month);
    if (day < 10) days = "0" + to_string(day);
    else days = to_string(day);
    datestring = years + months + days;
    if (!isValid()) throw DateIsNotValid(getDate());
}

Date::Date() {
    time_t now = time(NULL);
    struct tm times = *localtime(&now);
    int year = times.tm_year + 1900;
    int month = times.tm_mon + 1;
    int day = times.tm_mday;
    setDate(year, month, day);
}

Date::Date(unsigned int year, unsigned int month, unsigned int day) {
    int year1 = year;
    int month1 = month;
    int day1 = day;
    setDate(year1, month1, day1);
}

Date::Date(const string& yearMonthDay) {
    istringstream datesstring;
    datesstring.str(yearMonthDay);
    int year, month, day;
    char c;
    datesstring >> year >> c >> month >> c >> day;
    int year1 = year;
    int month1 = month;
    int day1 = day;
    setDate(year1, month1, day1);
}

unsigned int Date::getYear() const {
    return stoi(datestring.substr(0, 4));
}

unsigned int Date::getMonth() const {
    return stoi(datestring.substr(4, 2));
}

unsigned int Date::getDay() const {
    return stoi(datestring.substr(6, 2));
}

string Date::getDate() const {
    string data = datestring.substr(0, 4) + "/" + datestring.substr(4, 2) + "/" + datestring.substr(6, 2);
    return data;
}

bool Date::isleap() {
    int year = stoi(datestring.substr(0, 4));
    if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) return true;
    return false;
}

int Date::daysOfMonth() {
    int month = stoi(datestring.substr(4, 2));
    if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) return 31;
    else if (month == 4 || month == 6 || month == 9 || month == 11) return 30;
    else {
        if (isleap()) return 29;
        else return 28;
    }
}

unsigned int Date::getAge() const {
    Date today;
    if (this->getMonth() < today.getMonth()){
        return today.getYear() - this->getYear() - 1;
    }
    else if (this->getMonth() == today.getMonth()) {
        if (this->getDay() < today.getDay())
            return today.getYear() - this->getYear() - 1;
    }
    return today.getYear() - this->getYear();
}


DateIsNotValid::DateIsNotValid(string date){
    this->date = date;
}

string DateIsNotValid::what(){
    return "The date " + date + " is not valid!";
}