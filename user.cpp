//
// Created by bruno on 25/10/2020.
//

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include "user.h"

using namespace std;

// Exceptions

NotOldEnough::NotOldEnough(const string& reason) {
    this->reason = reason;
}

string NotOldEnough::what() const {
    return reason;
}


NotInAStream::NotInAStream(const string& reason) {
    this->reason = reason;
}

string NotInAStream::what() const {
    return reason;
}


AlreadyInAStream::AlreadyInAStream(const string& reason) {
    this->reason = reason;
}

string AlreadyInAStream::what() const {
    return reason;
}


unsigned int User::nextID = 0;

User::User(const std::string& name, const std::string& nick, const Date& birthDate) {
    this->name = name;
    this->nick = nick;
    this->birthDate = birthDate;
    ID = nextID;
    stream = nullptr;
}


User::User(const std::string& name, const std::string& nick, const Date& birthDate, unsigned int id) {
    this->name = name;
    this->nick = nick;
    this->birthDate = birthDate;
    this->ID = id;
    stream = NULL;
}

User::~User() = default;


void User::setStreamHistory(std::set<unsigned int>& pastStreams) {
    for(auto it = pastStreams.begin(); it != pastStreams.end(); it++)
        this->streamHistory.insert(*it);
}

void User::setName(const std::string& name) {
    this->name = name;
}

void User::setNick(const std::string &nick) {
    this->nick = nick;
}

std::string User::getName() const {
    return name;
}

int User::getAge() const {
    return birthDate.getAge();
}

string User::getAgeString() const {
    return birthDate.getDate();
}

std::string User::getNick() const {
    return nick;
}

unsigned int User::getID() const {
    return ID;
}

Stream * User::getStream() const {
    if (stream == nullptr) throw NotInAStream(this->nick + " is currently not in any stream");
    return stream;
}

bool User::inAStream() const {
    return stream != nullptr;
}

std::set<unsigned int>& User::getStreamHistory() {
    return streamHistory;
}


Streamer::Streamer(const std::string& name, const std::string& nick, const Date& birthDate) : User(name, nick, birthDate){
    if (birthDate.getAge() < 15) throw NotOldEnough("You must be at least 15 years old to create a streamer account");
    nextID++;   // only after the check
}


Streamer::Streamer(const std::string& name, const std::string& nick, const Date& birthDate, unsigned int id) : User(name, nick, birthDate, id) {
    if (birthDate.getAge() < 15) throw NotOldEnough("You must be at least 15 years old to create a streamer account");
    nextID++;   // only after the check
}

Streamer::~Streamer() = default;


int Streamer::getNumViewers() const {
    if (stream == nullptr) throw NotInAStream(this->nick + " is currently not streaming");
    return stream->getNumViewers();
}

int Streamer::getNumSubs() const {
    return subscribers.size();
}

std::set<unsigned int>& Streamer::getSubscribers() {
    return this->subscribers;
}

void Streamer::endStream() {
    if (stream == nullptr) throw NotInAStream(this->nick + " is currently not streaming");
    streamHistory.insert(stream->getId());
    stream = nullptr;
}

void Streamer::startStream(Stream *stream) {
    if (this->stream != nullptr) throw AlreadyInAStream(this->nick + " is already streaming");
    this->stream = stream;
}


void Streamer::setSubscribers(set<unsigned int>& subscribers) {
    this->subscribers = subscribers;
}

void Streamer::addSubscriber(unsigned int id) {
    subscribers.insert(id);
}

void Streamer::removeSubscriber(unsigned int id) {
    set<unsigned int>::iterator it = subscribers.find(id);
    if (it == subscribers.end()) throw NotSubscribed("That user is not subscribed to " + this->nick);
    subscribers.erase(it);
}

bool Streamer::isSubscriber(unsigned int id) const {
    return subscribers.find(id) != subscribers.end();
}

void Streamer::showUser() const {
    cout << nick << "( " << name << " )" << endl
        << getAge() << " Years Old" << endl << getNumSubs() << " Subscribers" << endl;
    if (stream != nullptr)
        cout << "Currently streaming " << stream->getTitle() << " with "
            << getNumViewers() << " viewers" << endl;
    else{
        cout << "Currently not streaming" << endl;
    }
}

ostream& operator<<(ostream& out, const Streamer& streamer){
    out << streamer.getNick() << "( " << streamer.getName() << " )" << endl
        << streamer.getAge() << " Years Old" << endl << streamer.getNumSubs() << " Subscribers" << endl;
    if (streamer.inAStream())
        out << "Currently streaming " << streamer.getStream()->getTitle() << " with "
            << streamer.getNumViewers() << " viewers" << endl;
    else{
        out << "Currently not streaming" << endl;
    }
    out << endl;
    return out;
}



Viewer::Viewer(const std::string& name, const std::string& nick, const Date& birthDate) : User(name, nick, birthDate) {
    if (birthDate.getAge() < 12) throw NotOldEnough("You must be at least 12 years old to create an account");
    nextID++;   // only after the check
}


Viewer::Viewer(const std::string& name, const std::string& nick, const Date& birthDate, unsigned int id) : User(name, nick, birthDate, id) {
    if (birthDate.getAge() < 12) throw NotOldEnough("You must be at least 12 years old to create an account");
    nextID++;   // only after the check
}

Viewer::~Viewer() = default;

void Viewer::joinStream(Stream *stream) {
    if (this->stream != nullptr) throw AlreadyInAStream(this->nick + " is already watching a stream");
    if (getAge() < stream->getMinAge())
        throw NotOldEnough(this->name + " is not old enough to watch " + stream->getTitle());
    this->stream = stream;
}

void Viewer::leaveStream() {
    if (stream == nullptr) throw NotInAStream(this->nick + " is currently not watching any stream");
    this->streamHistory.insert(this->stream->getId());
    stream = nullptr;
}

void Viewer::feedback(int like) {
    if (stream == nullptr) throw NotInAStream(this->nick + " can't give feedback because he's not watching any stream");
    stream->feedback(like);
}

void Viewer::message(std::string text) const {
    if (stream == nullptr) throw NotInAStream(this->nick + " can't message because he's not watching any stream");
    PrivateStream* s = (PrivateStream*) stream;
    s->addMessage(name + ": " + text);
}

void Viewer::showUser() const {
    cout << nick << "( " << name << " )" << endl
        << getAge() << " Years Old" << endl;
    if (stream != nullptr)
        cout << "Currently watching " << stream->getTitle() << endl;
    else
        cout << "Currently not watching any stream" << endl;
}

ostream& operator<<(ostream& out, const Viewer& viewer){
    out << viewer.getNick() << "( " << viewer.getName() << " )" << endl
        << viewer.getAge() << " Years Old" << endl;
    if (viewer.inAStream())
        out << "Currently watching " << viewer.getStream()->getTitle() << endl;
    else
        out << "Currently not watching any stream" << endl;
    out << endl;
    return out;
}
