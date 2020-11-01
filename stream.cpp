//
// Created by joaog on 10/25/2020.
//

#include <string>
#include "stream.h"

using namespace std;

unsigned int Stream::nextID= 0;

NotSubscribed::NotSubscribed(const string& reason) {
    this->reason = reason;
}

string NotSubscribed::what() const {
    return reason;
}

noCapacity::noCapacity(const string& reason) {
    this->reason = reason;
}

string noCapacity::what() {
    return reason;
}



/**
 * Constructor of class Stream
 * @param title
 * @param startDate
 * @param language
 * @param minAge
 */
Stream::Stream(const string& title, const Date& startDate, const string& language, int minAge, const string& streamerNick) {
    this->title = title, this->startDate = startDate, this->language = language, this->minAge = minAge, this->numViewers = 0;
    this->streamerNick = streamerNick; noLikes = 0;
    this->id = nextID, nextID++;
}

Stream::~Stream() = default;

/**
 * Remove user from vector that contains all users watching the stream
 * @param user unsigned int that represents a user index on the StreamZ class vector of users
 */
void Stream::removeUser(unsigned int user) {
    this->viewers.erase(viewers.find(user));
    this->numViewers--;             // Need to confirm if it is not needed to check if user exists on set
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

string Stream::getStreamerNick() const {
    return streamerNick;
}

std::set<unsigned int> & Stream::getViewers() {
    return viewers;
}

set<unsigned int> Stream::getUsers() const {
    return this->viewers;
}

void Stream::feedback(int megaLikezao) {
    this->noLikes += megaLikezao;
}

PrivateStream::PrivateStream(const string& title, const Date& startDate, const string& language, int minAge, const string& streamerNick,
                             std::set<unsigned int> &subscribers, int capacity) : Stream(title, startDate, language, minAge, streamerNick) {
    this->subscribers = subscribers;
    this->capacity = capacity;
}

PrivateStream::~PrivateStream() = default;

void PrivateStream::addUser(unsigned int user) {
    if (numViewers >= capacity) throw noCapacity("The stream is full. Try again later");
    if (subscribers.find(user) == subscribers.end()) throw NotSubscribed("You are not subscribed to this streamer");
    this->viewers.insert(user);
    this->numViewers++;
}

void Stream::showStream() const {
    cout << "Title: " << this->title << ", Start Date: " << this->startDate.getDate() << ", Language: "
         << this->language << ", Min Age: " << this->minAge << ", No. Likes: " << this->noLikes << ", No. Viewers: "
         << this->numViewers << endl << "Being streamed by " << streamerNick;
}

PublicStream::PublicStream(const string& title, const Date& startDate, const string& language, int minAge,
                           const string& streamerNick) : Stream(title, startDate, language, minAge, streamerNick) {}

PublicStream::~PublicStream() = default;

void PublicStream::showStream() const {
    Stream::showStream();
    cout << endl << "This stream is accessible to everyone" << endl;
}

void PublicStream::addUser(unsigned int user) {
    this->viewers.insert(user);
    this->numViewers++;
}

void PrivateStream::showStream() const {
    Stream::showStream();
    cout << endl << "This stream is only accessible to subscribers and has " << capacity - numViewers
    << " spaces available" << endl << " and " << subscribers.size() << " subscribers" << endl;
}

ostream& operator<<(ostream& out, Stream& stream){
    out << "Title: " <<  stream.getTitle() << " Start Date: " << stream.getStartDate().getDate()
    << " Language: " << stream.getLanguage() << " Min Age: " << stream.getMinAge() << " No. Likes: "
    << stream.getNoLikes() << " No. Viewers: " << stream.getNumViewers();
    return out;
}

unsigned int Stream::getId() {
    return this->id;
}