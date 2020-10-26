//
// Created by joaog on 10/25/2020.
//

#include <string>
#include <vector>
#include <map>
#include "stream.h"

using namespace std;

/**
 * Constructor of class Stream
 * @param title
 * @param startDate
 * @param language
 * @param minAge
 */
Stream::Stream(string title, Date startDate, string language, int minAge) {
    this->title = title, this->startDate = startDate, this->language = language, this->minAge = minAge, this->numViewers = 0;
}

/**
 * Remove user from vector that contains all users watching the stream
 * @param user unsigned int that represents a user index on the StreamZ class vector of users
 */
void Stream::removeUser(unsigned int user) {
    this->viewers.erase(user);      //removes the key value 'user' from the map
    this->numViewers--;             // Need to confirm if it is not needed to check if user exists on map
}

int Stream::getNumViewers() const {
    return this->numViewers;
}

string Stream::getTitle() const {
    return this->title;
}

Date Stream::getStartDate() const {
    return this->startDate;
}

string Stream::getLanguage() const {
    return this->language;
}

int Stream::getMinAge() const {
    return this->minAge;
}

int Stream::getNoLikes() const {
    return this->noLikes;
}

map<unsigned int, unsigned int> Stream::getUsers() const {
    return this->viewers;
}

void Stream::feedback(int megaLikezao) {
    this->noLikes += megaLikezao;
}

PrivateStream::PrivateStream(std::string title, Date startDate, std::string language, int minAge,
                             std::vector<unsigned int> &subscribers) : Stream(title, startDate, language, minAge) {
    this->subscribers = subscribers;
}

void PrivateStream::addUser(unsigned int user) {
    this->viewers.insert(pair<unsigned int, unsigned int> (user, user));
    this->numViewers++;
}

void Stream::showStream() const {
    cout << "Title: " << this->title << " Start Date: " << this->startDate.getDate() << " Language: " << this->language << " Min Age: " << this->minAge << " No. Likes: " << this->noLikes << " No. Viewers: " << this->numViewers;
}

ostream& operator<<(ostream& out, Stream& stream){
    out << "Title: " <<  stream.getTitle() << " Start Date: " << stream.getStartDate().getDate() << " Language: " << stream.getLanguage() << " Min Age: " << stream.getMinAge() << " No. Likes: " << stream.getNoLikes() << " No. Viewers: " << stream.getNumViewers();
}

