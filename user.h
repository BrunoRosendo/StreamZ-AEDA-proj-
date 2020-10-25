//
// Created by joaog on 10/23/2020.
//

#ifndef PROJETO1_USER_H
#define PROJETO1_USER_H

#include <string>
#include <vector>
#include <set>
#include "date.h"
#include "stream.h"
#include "pastStream.h"

using namespace std;

class User{
protected:
    std::string name;
    std::string nick;
    Date birthDate;
    Stream* stream;
    std::vector<PastStream *> streamHistory;
    unsigned int ID;
    static unsigned int nextID;
public:
    User(std::string name, std::string nick, const Date& birthDate);
    virtual void setStreamHistory(std::vector<struct PastStream>& pastStreams);
    std::string getName() const;
    std::string getNick() const;
    int getAge() const;
    Stream* getStream() const;
    std::vector<PastStream*> getStreamHistory() const;
};

class Streamer : public User{
private:
    std::set<unsigned int> subscribers;
public:
    Streamer(std::string name, std::string nick, const Date& birthDate);
    int getNumViewers() const;
    int getNumSubs() const;
    void endStream();
    void startStream(Stream* stream);
    void setSubscribers(set<unsigned int>& subscribers);
    void addSubscriber(unsigned int id);
    void removeSubscriber(unsigned int id);
    friend ostream& operator<<(ostream& out, const Streamer& streamer);
};

class Viewer : public User{

public:
    Viewer(std::string name, std::string nick, const Date& birthDate);
    void joinStream(Stream* stream);
    void leaveStream();
    void message(std::string text) const;
    void feedback(int like);
    friend ostream& operator<<(ostream& out, const Viewer& viewer);
};


ostream& operator<<(ostream& out, const Streamer& streamer);
ostream& operator<<(ostream& out, const Viewer& viewer);


// Exceptions related to the user

class NotOldEnough{
private:
    string reason;
public:
    NotOldEnough(string reason);
    string what() const;
};

class NotInAStream{
private:
    string reason;
public:
    NotInAStream(string reason);
    string what() const;
};

class AlreadyStreaming{
private:
    string reason;
public:
    AlreadyStreaming(string reason);
    string what() const;
};

class NotSubscribed{
private:
    string reason;
public:
    NotSubscribed(string reason);
    string what() const;
};

#endif //PROJETO1_USER_H
