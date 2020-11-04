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
#include <vector>
//class User;       TO DO THIS NEED TO DO A FORWARD DECLARATION

class Stream{
protected:
    std::string title;
    Date startDate;
    std::string language;
    int minAge;
    std::set<unsigned int> viewers;
    int noLikes;
    int numViewers;
    string streamerNick;
    unsigned int id;
    static unsigned int nextID;
public:
    Stream(const string& title, const Date& startDate, const string& language, int minAge, const string& streamerNick);
    virtual ~Stream();
    virtual void addUser(unsigned int user) = 0;
    void removeUser(unsigned int user);
    int getNumViewers() const;
    std::string getTitle() const;
    Date getStartDate() const;
    std::string getLanguage() const;
    int getMinAge() const;
    int getNoLikes() const;
    string getStreamerNick() const;
    std::set<unsigned int>& getViewers();
    set<unsigned int> getUsers() const;
    void feedback(int megaLikezao);
    virtual void showStream() const;
    unsigned int getId();
};

class PrivateStream : public Stream{
    int capacity;
    std::set<unsigned int> subscribers;
    std::vector<std::string> messages;
public:
    PrivateStream(const string& title, const Date& startDate, const string& language, int minAge, const string& streamerNick,
                  std::set<unsigned int> &subscribers, int capacity);
    virtual ~PrivateStream();
    virtual void addUser(unsigned int user);
    virtual void showStream() const;
    void showMessages() const;
    void addMessage(std::string message); // the message includes the name of the user
};

class PublicStream : public Stream{
public:
    PublicStream(const string& title, const Date& startDate, const string& language, int minAge, const string& streamerNick);
    virtual ~PublicStream();
    virtual void addUser(unsigned int user);
    virtual void showStream() const;
};

ostream& operator<<(ostream& out, Stream& stream );

// Exceptions

class noCapacity{
private:
    string reason;
public:
    noCapacity(const string& reason);
    string what();
};

class NotSubscribed{
private:
    string reason;
public:
    NotSubscribed(const string& reason);
    string what() const;
};

#endif //PROJETO1_STREAM_H
