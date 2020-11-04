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
    std::set<unsigned int> streamHistory;
    unsigned int ID;
    static unsigned int nextID;
public:
    User(const std::string& name, const std::string& nick, const Date& birthDate);
    User(const std::string& name, const std::string& nick, const Date& birthDate, unsigned int id);
    virtual ~User();
    void setStreamHistory(std::set<unsigned int>& pastStreams);
    void setName(const std::string& name);
    void setNick(const std::string& nick);
    std::string getName() const;
    std::string getNick() const;
    int getAge() const;
    string getAgeString() const;
    unsigned int getID() const;
    Stream* getStream() const;
    bool inAStream() const;
    void addPastStream(unsigned int pastStreamId); // useless?
    std::set<unsigned int>& getStreamHistory();
    virtual void showUser() const = 0;
};

class Streamer : public User{
private:
    std::set<unsigned int> subscribers;
public:
    Streamer(const std::string& name, const std::string& nick, const Date& birthDate);
    Streamer(const std::string& name, const std::string& nick, const Date& birthDate, unsigned int id);
    virtual ~Streamer();
    int getNumViewers() const;
    int getNumSubs() const;
    std::set<unsigned int>& getSubscribers();
    void endStream();
    void startStream(Stream* stream);
    void setSubscribers(set<unsigned int>& subscribers);
    void addSubscriber(unsigned int id);
    void removeSubscriber(unsigned int id);
    bool isSubscriber(unsigned int id) const;
    friend ostream& operator<<(ostream& out, const Streamer& streamer);
    virtual void showUser() const;
};

class Viewer : public User{

public:
    Viewer(const std::string& name, const std::string& nick, const Date& birthDate);
    Viewer(const std::string& name, const std::string& nick, const Date& birthDate, unsigned int id);
    virtual ~Viewer();
    void joinStream(Stream* stream);
    void leaveStream();
    void message(std::string text) const;
    void feedback(int like);
    friend ostream& operator<<(ostream& out, const Viewer& viewer);
    virtual void showUser() const;
};


ostream& operator<<(ostream& out, const Streamer& streamer);
ostream& operator<<(ostream& out, const Viewer& viewer);


// Exceptions related to the user

class NotOldEnough{
private:
    string reason;
public:
    NotOldEnough(const string& reason);
    string what() const;
};

class NotInAStream{
private:
    string reason;
public:
    NotInAStream(const string& reason);
    string what() const;
};

class AlreadyStreaming{
private:
    string reason;
public:
    AlreadyStreaming(const string& reason);
    string what() const;
};

#endif //PROJETO1_USER_H
