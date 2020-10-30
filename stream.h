//
// Created by joaog on 10/23/2020.
//

#ifndef PROJETO1_STREAM_H
#define PROJETO1_STREAM_H

#include <map>
#include <fstream>
#include <set>

//#include "user.h"
#include "date.h"
//class User;       TO DO THIS NEED TO DO A FORWARD DECLARATION

class Stream{
protected:
    std::string title;
    Date startDate;
    std::string language;
    int minAge;
    map<unsigned int, unsigned int> viewers;
    //std::vector<unsigned int> viewers;
    int noLikes;
    int numViewers;
public:
    Stream(std::string title, Date startDate, std::string language, int minAge);
    virtual void addUser(unsigned int user) = 0;
    void removeUser(unsigned int user);
    int getNumViewers() const;
    std::string getTitle() const;
    Date getStartDate() const;
    std::string getLanguage() const;
    int getMinAge() const;
    int getNoLikes() const;
    map<unsigned int, unsigned int> getUsers() const;
    void feedback(int megaLikezao);
    /*virtual*/ void showStream() const;
};

class PrivateStream : public Stream{
    int capacity;
    std::set<unsigned int> subscribers;
public:
    PrivateStream(std::string title, Date startDate, std::string language, int minAge, std::set<unsigned int> &subscribers, int capacity);
    virtual void addUser(unsigned int user);
    //virtual void showStream() const;
};

class PublicStream : public Stream{
public:
    PublicStream(std::string title, Date startDate, std::string language, int minAge);
    virtual void addUser(unsigned int user);
    //virtual void showStream() const;
};

ostream& operator<<(ostream& out, Stream& stream );

#endif //PROJETO1_STREAM_H
