//
// Created by joaog on 10/23/2020.
//

#ifndef PROJETO1_USER_H
#define PROJETO1_USER_H

#include <string>
#include <vector>
#include "date.h"
#include "stream.h"
#include "pastStream.h"

using namespace std;

class User{
private:
    std::string name;
    std::string nick;
    Date birthDate;
    Stream* stream;
    std::vector<PastStream *> streamHistory;
public:
    User(std::string name, std::string nick, Date birthDate);
    virtual void setStreamHistory(std::vector<struct PastStream> pastStreams);
    std::string getName() const;
    std::string getNick() const;
    int getAge() const;
    Stream* getStream() const;
    std::vector<PastStream*> getStreamHistory() const;
    virtual void showUser() const;
};

class Streamer : public User{
private:
    std::vector<User*> subscribers;
public:
    Streamer(std::string name, std::string nick, Date birthDate);
    int getNumViewers() const;
    int endStream();
    void startStream(std::string title, Date startDate, std::string language, int minAge);
    void setSubscribers(vector<User*> subscribers);
    virtual void setStreamHistory(std::vector<struct PastStream> pastStreams);
    virtual void showUser() const;
};

class Viewer : public User{

public:
    Viewer(std::string name, std::string nick, Date birthDate);
    void joinStream(Stream* stream);
    void leaveStream();
    void message(std::string text) const;
    void feedback(int megaLikezao);
    virtual void setStreamHistory(std::vector<struct PastStream> pastStreams);
    virtual void showUser() const;
};

#endif //PROJETO1_USER_H
