//
// Created by joaog on 10/25/2020.
//

#include <string>
#include <vector>
#include "stream.h"

/**
 * Constructor of class Stream
 * @param title
 * @param startDate
 * @param language
 * @param minAge
 */
Stream::Stream(std::string title, Date startDate, std::string language, int minAge) {
    this->title = title, this->startDate = startDate, this->language = language, this->minAge = minAge;
}

/**
 * Remove user from vector that contains all users watching the stream
 * @param user unsigned int that represents a user index on the StreamZ class vector of users
 */
void Stream::removeUser(unsigned int user) {

}

