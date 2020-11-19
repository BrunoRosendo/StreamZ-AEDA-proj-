//
// Created by joaog on 10/23/2020.
//

#ifndef PROJETO1_DATE_H
#define PROJETO1_DATE_H

#include <iostream>
#include <string>

using namespace std;

/**
 * @brief Auxiliary class used to store, manipulate and read dates
 */
class Date
{
public:

    /**
     * @brief Creates an object containing today's date
     */
    Date();

    /**
     * @brief Creates a date with given year, month and day by calling the setDate() method
     * @param year Year of the date
     * @param month Month of the date
     * @param day Dar of the date
     */
    Date(unsigned int year, unsigned int month, unsigned int day);

    /**
     * @brief Creates a date using the given string in the format "yyyy/mm/dd". Calls the setDate() method
     * @param yearMonthDay String containing the date in the format "yyyy/mm/dd"
     */
    Date(const string& yearMonthDay); // yearMonthDay must be in format "yyyy/mm/dd"

    /**
     * @brief Sets the date to the given year, month and day. Throws a DateIsNotValid exceptions if the parameters
     * aren't valid
     * @param year Year of the date
     * @param month Month of the date
     * @param day Day of the date
     */
    void setDate(unsigned int year, unsigned int month, unsigned int day);

    /**
     * @brief Gets the year of the date
     * @throw DateIsNotValid If the date is not valid
     * @return Unsigned int containing the year
     */
    unsigned int getYear() const;

    /**
     * @brief Gets the month of the date
     * @return Unsigned int containing the month
     */
    unsigned int getMonth() const;

    /**
     * @brief Gets the day of the date
     * @return Unsigned int containing the day
     */
    unsigned int getDay() const;

    /**
     * @brief Gets the date in the format "yyyy/mm/dd"
     * @return String containing the date
     */
    string getDate() const; // returns the date in format "yyyy/mm/dd"

    /**
     * @brief Checks if the date is valid
     * @return Returns true if the date is valid and false otherwise
     */
    bool isValid() const;

    /**
     * @brief Gets how many years have passed since the date's day
     * @return Unsigned int containing the age of the date
     */
    unsigned int getAge() const;

    /**
     * @brief Checks if two dates are equal
     * @param date Date used for comparison
     * @return Returns true if the dates are equal and false otherwise
     */
    bool operator==(const Date& date) const;

    /**
     * @brief Checks if two dates are different
     * @param date Date used for comparison
     * @return Returns true if the dates are different and false otherwise
     */
    bool operator!=(const Date& date) const;

    /**
     * @brief Checks if this date is after a given date
     * @param date Date used for comparison
     * @return Returns true if this date is after the second one and false otherwise
     */
    bool operator>(const Date& date);

    /**
     * @brief Checks if this date is before a given date
     * @param date Date used for comparison
     * @return Returns true if this date is before the second one and false otherwise
     */
    bool operator<(const Date& date);

    /**
     * @brief Checks if this date is after or equal to a given date
     * @param date Date used for comparison
     * @return Returns true if this date is after or equal to the second one and false otherwise
     */
    bool operator>=(const Date& date);

    /**
     * @brief Checks if this date is before or equal to a given date
     * @param date Date used for comparison
     * @return Returns true if this date is before or equal to the second one and false otherwise
     */
    bool operator<=(const Date& date);
private:
    /**
     * @brief String containing the information of the Date in the format yyyy/mm/dd
     */
    string datestring;

    /**
     * @brief Checks if the date's year is leap
     * @return Returns true if the year is leap and false otherwise
     */
    bool isleap() const;

    /**
     * @brief Calculates how many days the date's month (in the date's year) should have
     * @return Integer containing the number of days this month should have
     */
    int daysOfMonth() const;
};

/**
 * @brief Exception which should be thrown when a date is not valid
 */
class DateIsNotValid{
private:
    /**
     * @brief String containing the date in the format yyyy/mm/dd
     */
    string date;
public:
    /**
     * @brief Creates a DateIsNotValid exception with a given date
     * @param date Date which was invalid
     */
    DateIsNotValid(const string& date);

    /**
     * @brief Gets the date which was invalid
     * @return String containing the invalid date (format not guarenteed)
     */
    string what();
};

#endif //PROJETO1_DATE_H
