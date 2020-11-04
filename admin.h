//
// Created by joaog on 10/23/2020.
//

#ifndef PROJETO1_ADMIN_H
#define PROJETO1_ADMIN_H

#include <string>
#include "user.h"
#include "streamZ.h"


class Admin{
private:
    std::string name;
    StreamZ* site;   //change to pointer so we can delete admin?
public:
    Admin(const std::string& name, StreamZ* site);
    int getNumStreams() const;
    int getNumCreatedStreams(Date& from, const Date& to) const;
    float getAvgViews() const;
    float getAvgViews(Date& from, const Date& to) const;
    int getNumPublicStreams() const;
    int getNumPublicStreams(Date& from, const Date& to) const;
    int getNumPrivateStreams() const;
    int getNumPrivateStreams(Date& from, const Date& to) const;
    string getName() const;
    void setName(const std::string& name);
    std::string getPreferredLanguage(std::vector<Stream*>& streams) const;
    std::string getPreferredStreamType() const;
    Streamer* getMostViewedStreamer() const;
};

class badDateComp{
private:
    string reason;
public:
    badDateComp(const string& reason);
    string what() const;
};

class noActiveStreams{
private:
    string reason;
public:
    noActiveStreams(const string& reason);
    string what() const;
};

#endif //PROJETO1_ADMIN_H
