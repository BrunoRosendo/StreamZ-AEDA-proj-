//
// Created by bruno on 25/10/2020.
//

#include <iostream>
#include <string>
#include <stack>
#include <iomanip>

#include "purchase.h"
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

int Streamer::merchSalesLimit = 50;

User::User(const std::string& name, const std::string& nick, const Date& birthDate, const int activity) {
    this->name = name;
    this->nick = nick;
    this->birthDate = birthDate;
    ID = nextID;
    stream = nullptr;
    this->active = activity;
}


User::User(const std::string& name, const std::string& nick, const Date& birthDate, const int activity, unsigned int id) {
    this->name = name;
    this->nick = nick;
    this->birthDate = birthDate;
    this->ID = id;
    stream = nullptr;
    this->active = activity;
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

unsigned int User::getAge() const {
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

int User::getActivity() {
    return this->active;
}

void User::setActivity(int activity) {
    this->active = activity;
}


Streamer::Streamer(const std::string& name, const std::string& nick, const Date& birthDate, const int activity) : User(name, nick, birthDate, activity){
    if (birthDate.getAge() < 15) throw NotOldEnough("You must be at least 15 years old to create a streamer account");
    nextID++;   // only after the check
    this->soldMerch = 0;
}


Streamer::Streamer(const std::string& name, const std::string& nick, const Date& birthDate, const int activity, unsigned int id, int soldMerch) : User(name, nick, birthDate, activity, id) {
    if (birthDate.getAge() < 15) throw NotOldEnough("You must be at least 15 years old to create a streamer account");
    nextID++;   // only after the check
    this->soldMerch = soldMerch;
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
    cout << nick << " (" << name << ")" << endl
        << getAge() << " Years Old" << endl << getNumSubs() << " Subscriber";
    if (getNumSubs() != 1) cout << "s"; cout << endl;
    if (!active){
        cout << "This Streamer has his account deleted" << endl;
        return;
    }
    if (stream != nullptr) {
        cout << "Currently streaming " << stream->getTitle() << " with "
             << getNumViewers() << " viewer";
        if (getNumViewers() != 1) cout << "s";
        cout << endl;
    }
    else{
        cout << "Currently not streaming" << endl;
    }
}

priority_queue<Purchase>& Streamer::getPurchases(){
    return this->purchases;
}

bool Streamer::hasPurchase(string name){
    priority_queue<Purchase> aux = this->getPurchases();
    while(!aux.empty()){
        if( aux.top().getName() == name )
            return true;
        aux.pop();
    }
    return false;
}

void Streamer::removePurchase(string name) {
    priority_queue<Purchase> aux;
    while(!this->purchases.empty()){
        if(this->purchases.top().getName() == name){
            this->purchases.pop();
            break;
        }
        else
            aux.push(this->purchases.top());
        this->purchases.pop();
    }
    while(!aux.empty()){
        this->purchases.push(aux.top());
        aux.pop();
    }
}

void Streamer::addPurchase(string name, int numProducts, int availability){
    Purchase p(name, numProducts, availability);
    this->purchases.push(p);
}

void Streamer::setPurchases(priority_queue<Purchase>& purchases){
    this->purchases = purchases;
}

void Streamer::showMerchPurchases(){
    priority_queue<Purchase> aux = this->purchases;
    cout << setfill(' ') << setw(15) <<  "Name"  << " |" << setw(10) <<  "No. Items" << " |" <<  setw(10) << " Availability" << endl;
    while(!aux.empty()){
        cout << aux.top();
        aux.pop();
    }
}

int Streamer::getSoldMerch(){
    return this->soldMerch;
}

int Streamer::getMerchSalesLimit() {
    return this->merchSalesLimit;
}

void Streamer::addSoldMerch(int numOfMerch) {
    this->soldMerch += numOfMerch;
}

void Streamer::setNewSalesLimit(int newLimit) {
    Streamer::merchSalesLimit = newLimit;
}

ostream& operator<<(ostream& out, const Streamer& streamer){
    out << streamer.getNick() << "( " << streamer.getName() << " )" << endl
        << streamer.getAge() << " Years Old" << endl << streamer.getNumSubs() << " Subscriber";
    if (streamer.getNumSubs() != 1) cout << "s"; cout << endl;
    if (streamer.inAStream()) {
        out << "Currently streaming " << streamer.getStream()->getTitle() << " with "
            << streamer.getNumViewers() << " viewer";
        if (streamer.getNumViewers() != 1) cout << "s";
        cout << endl;
    }
    else{
        out << "Currently not streaming" << endl;
    }
    out << endl;
    return out;
}



Viewer::Viewer(const std::string& name, const std::string& nick, const Date& birthDate, const int activity) : User(name, nick, birthDate, activity) {
    if (birthDate.getAge() < 12) throw NotOldEnough("You must be at least 12 years old to create an account");
    nextID++;   // only after the check
}


Viewer::Viewer(const std::string& name, const std::string& nick, const Date& birthDate, const int activity, unsigned int id) : User(name, nick, birthDate, activity, id) {
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

void Viewer::message(const std::string& text) const {
    if (stream == nullptr) throw NotInAStream(this->nick + " can't message because he's not watching any stream");
    PrivateStream* s = (PrivateStream*) stream;
    s->addMessage(nick + ": " + text);
}

void Viewer::showUser() const {
    cout << nick << " (" << name << ")" << endl
        << getAge() << " Years Old" << endl;
    if (!active){
        cout << "This Viewer has his account deleted" << endl;
    }
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
