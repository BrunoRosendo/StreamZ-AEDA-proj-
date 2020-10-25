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

NotOldEnough::NotOldEnough(string reason) {
    this->reason = reason;
}

string NotOldEnough::what() const {
    return reason;
}


NotInAStream::NotInAStream(string reason) {
    this->reason = reason;
}

string NotInAStream::what() const {
    return reason;
}


AlreadyStreaming::AlreadyStreaming(string reason) {
    this->reason = reason;
}

string AlreadyStreaming::what() const {
    return reason;
}


NotSubscribed::NotSubscribed(string reason) {
    this->reason = reason;
}

string NotSubscribed::what() const {
    return reason;
}



unsigned int User::nextID = 0;

User::User(std::string name, std::string nick, const Date& birthDate) {
    this->name = name;
    this->nick = nick;
    this->birthDate = birthDate;
    ID = nextID;
    stream = NULL;
}

void User::setStreamHistory(std::vector<struct PastStream> &pastStreams) {
    for (size_t i = 0; i < pastStreams.size(); ++i)
        streamHistory.push_back(&pastStreams.at(i));
}

std::string User::getName() const {
    return name;
}

int User::getAge() const {
    return birthDate.getAge();
}

std::string User::getNick() const {
    return nick;
}

Stream * User::getStream() const {
    if (stream == NULL) throw NotInAStream(this->nick + " is currently not in any stream");
    return stream;
}

std::vector<PastStream *> User::getStreamHistory() const {
    return streamHistory;
}




Streamer::Streamer(std::string name, std::string nick, const Date& birthDate) : User(name, nick, birthDate){
    if (birthDate.getAge() < 15) throw NotOldEnough("You must be at least 15 years old to create a streamer account");
    nextID++;   // only after the check
}

int Streamer::getNumViewers() const {
    if (stream == NULL) throw NotInAStream(this->nick + " is currently not streaming");
    return stream->getNumViewers();
}

int Streamer::getNumSubs() const {
    return subscribers.size();
}

void Streamer::endStream() {
    if (stream == NULL) throw NotInAStream(this->nick + " is currently not streaming");
    PastStream* p = new PastStream;
    p->name = stream->getTitle();
    p->noViewers = stream->getNumViewers();
    streamHistory.push_back(p);
    stream == NULL;
}

void Streamer::startStream(Stream *stream) {
    if (stream != NULL) throw AlreadyStreaming(this->nick + " is already streaming");
    this->stream = stream;
}


void Streamer::setSubscribers(vector<unsigned int>& subscribers) {
    this->subscribers = subscribers;
}

void Streamer::addSubscriber(unsigned int id) {
    subscribers.push_back(id);
}

void Streamer::removeSubscriber(unsigned int id) {
    vector<unsigned int>::iterator it = find(subscribers.begin(), subscribers.end(), id);
    if (it == subscribers.end()) throw NotSubscribed("That user is not subscribed to " + this->nick);
    subscribers.erase(it);
}

ostream& operator<<(ostream& out, const Streamer& streamer){
    out << streamer.getNick() << "( " << streamer.getName() << " )" << endl
        << streamer.getAge() << " Years Old" << endl << streamer.getNumSubs() << " Subscribers" << endl;
    if (streamer.getStream() != NULL)
        out << "Currently streaming " << streamer.getStream()->getTitle() << " with "
            << streamer.getNumViewers() << " viewers" << endl;
    else{
        out << "Currently not streaming" << endl;
    }
    out << endl;
    return out;
}



Viewer::Viewer(std::string name, std::string nick, const Date& birthDate) : User(name, nick, birthDate) {
    if (birthDate.getAge() < 12) throw NotOldEnough("You must be at least 12 years old to create an account");
    nextID++;   // only after the check
}

void Viewer::joinStream(Stream *stream) {
    if (stream != NULL) throw AlreadyStreaming(this->nick + " is already watching a stream");
    if (getAge() < stream->getMinAge())
        throw NotOldEnough(this->name + " is not old enough to watch " + stream->getTitle());
    this->stream = stream;
}

void Viewer::leaveStream() {
    if (stream == NULL) throw NotInAStream(this->nick + " is currently not watching any stream");
    PastStream* p = new PastStream;
    p->name = stream->getTitle();
    p->noViewers = stream->getNumViewers();
    streamHistory.push_back(p);
    stream == NULL;
}

void Viewer::feedback(int like) {
    if (stream == NULL) throw NotInAStream(this->nick + " can't give feedback because he's not watching any stream");
    stream->feedback(like);
}

void Viewer::message(std::string text) const {
    if (stream == NULL) throw NotInAStream(this->nick + " can't message because he's not watching any stream");
    cout << text << endl;
}

ostream& operator<<(ostream& out, const Viewer& viewer){
    out << viewer.getNick() << "( " << viewer.getName() << " )" << endl
        << viewer.getAge() << " Years Old" << endl;
    if (viewer.getStream() != NULL)
        out << "Currently watching " << viewer.getStream()->getTitle() << endl;
    else
        out << "Currently not watching any stream" << endl;
    out << endl;
    return out;
}