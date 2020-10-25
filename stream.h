//
// Created by joaog on 10/23/2020.
//

#ifndef PROJETO1_STREAM_H
#define PROJETO1_STREAM_H

class User;

#include "user.h"

class Stream{
protected:
    std::string title;
    Date startDate;
    std::string language;
    int minAge;
    std::vector<unsigned int> viewers;
    int noLikes;
public:
    Stream(std::string title, Date startDate, std::string language, int minAge);
    virtual void addUser(unsigned int user) = 0;
    void removeUser(unsigned int user);
    int getNumViewers() const;
    std::string getTitle() const;
    Date getStartData() const;
    std::string getLanguage() const;
    int getMinAge() const;
    int getNoLikes() const;
    std::vector<unsigned int> getUsers() const;
    void feedback(int megaLikezao);
    virtual void showStream() const;
};

class PrivateStream : public Stream{
    int capacity;
    std::vector<unsigned int> subscribers;
public:
    PrivateStream(std::string title, Date startDate, std::string language, int minAge, std::vector<unsigned int>& subscribers);
    virtual void addUser(unsigned int user);
    virtual void showStream() const;
};

class PublicStream : public Stream{
public:
    PublicStream(std::string title, Date startDate, std::string language, int minAge);
    virtual void addUser(unsigned int user);
    virtual void showStream() const;
};

#endif //PROJETO1_STREAM_H
