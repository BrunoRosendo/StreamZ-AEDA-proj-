//
// Created by joaog on 10/23/2020.
//

#ifndef PROJETO1_STREAM_H
#define PROJETO1_STREAM_H

#include "user.h"

class Stream{
    std::string title;
    Date startDate;
    std::string langugage;
    int minAge;
    std::vector<User *> viewers;
    int noLikes;
public:
    Stream(std::string title, Date startDate, std::string language, int minAge);
    int addUser(User* user);
    int removeUser(User* user);
    int getNumViewers();
    std::vector<User *> getUsers();
    void feedback(int megaLikezao);
};

class PrivateStream : public Stream{
    int capacity;
    std::vector<Viewer *> subscribers;
public:
    PrivateStream(std::string title, Date startDate, std::string language, int minAge, std::vector<Viewer *>& subscribers);
};

class PublicStream : public Stream{
public:
    PublicStream(std::string title, Date startDate, std::string language, int minAge);
};

#endif //PROJETO1_STREAM_H
