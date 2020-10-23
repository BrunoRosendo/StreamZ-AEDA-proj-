//
// Created by joaog on 10/23/2020.
//

#ifndef PROJETO1_USER_H
#define PROJETO1_USER_H

#include <string>
#include <vector>
#include "date.h"
#include "stream.h"
#include "streamHistory.h"

class User{
    std::string name;
    std::string nick;
    Date birthDate;
    Stream* stream;
    std::vector<StreamHistory *> streamHistory;
public:
    User(std::string name, std::string nick, Date birthDate);
    int setStreamerHistory(vector<struct streamHistory> pastStreams);
};

class Streamer : public User{
    std::vector<std::string> subscribers;
public:
    Streamer(std::string name, std::string nick, Date birthDate);
    int getNumViewers();
    int endStream();
    int startStream(std::string title, Date startDate, std::string language, int minAge);
    int setSubscribers(vector<std::string> subscribers);
};

class Viewer : public User{

public:
    Viewer(std::string name, std::string nick, Date birthDate);
    int joinStream(Stream* stream);
    int leaveStream();
    void message(std::string text);
    void feedback(int megaLikezao);
};

#endif //PROJETO1_USER_H
