#include <iostream>
#include <fstream>
#include <vector>

#include "streamZ.h"
#include "pastStream.h"
#include "date.h"
#include "user.h"
#include "admin.h"
#include "stream.h"

using namespace std;

badDateComp::badDateComp(string reason){
    this->reason = reason;
}

string badDateComp::what() const {
    return reason;
}

noActiveStreams::noActiveStreams(string reason) {
    this->reason = reason;
}

string noActiveStreams::what() const {
    return reason;
}

Admin::Admin(std::string name, std::vector<User *> &users, std::vector<Stream *> &streams) {
    this-> name = name;
    this->users = users;
    this->streams = streams;
}

int Admin::getNumStreams() const {
    return streams.size();
}

int Admin::getNumCreatedStreams(Date from, Date to) const {
    if (from > to) throw badDateComp("ERROR: Start date is after end date");
    int cnt = 0;
    Date d;
    vector<Stream*>::const_iterator it;
    for (it = streams.begin();it != streams.end(); it++){
        d = (*it)->getStartDate();
        if (d >= from && d <= to)
            cnt ++;
    }
    return cnt;
}

float Admin::getAvgViews() const {
    if (streams.size()<=0) throw noActiveStreams("ERROR: There are currently no active streams");
    int sum = 0;
    float avg = 0;
    vector<Stream *>::const_iterator it;
    for (it = streams.begin(); it != streams.end(); it++){
        sum += (*it)->getNumViewers();
    }
    avg = sum/getNumStreams();
    return avg;
}

float Admin::getAvgViews(Date from, Date to) const {
    if (from > to) throw badDateComp("ERROR: Start date is after end date");
    if (streams.size()<=0) throw noActiveStreams("ERROR: There are currently no active streams");
    int sum = 0;
    float avg = 0;
    Date d;
    vector<Stream *>::const_iterator it;
    for (it = streams.begin(); it != streams.end(); it++){
        d = (*it)->getStartDate();
        if (d >= from && d <= to)
            sum += (*it)->getNumViewers();
    }
    avg = sum/getNumStreams();
    return avg;
}

int Admin::getNumPublicStreams() const {

}

int Admin::getNumPublicStreams(Date from, Date to) const {
    if (from > to) throw badDateComp("ERROR: Start date is after end date");

}

int Admin::getNumPrivateStreams() const {

}

int Admin::getNumPrivateStreams(Date from, Date to) const {
    if (from > to) throw badDateComp("ERROR: Start date is after end date");

}

string Admin::getPreferredLanguage(std::vector<Stream*>& streams) const {
    if (streams.size()<=0) throw noActiveStreams("ERROR: There are currently no active streams");
    int cnt = 0, max_cnt = 0, max_pos = 0;
    string li, lj;
    for (int i=0;i<streams.size();i++){
        li = streams[i]->getLanguage();
        for (int j=i+1;j<streams.size();j++){
            lj = streams[j]->getLanguage();
            if (li == lj)
                cnt++;
        }
        if (cnt > max_cnt){
            max_cnt = cnt;
            max_pos = i;
        }
    }
    return streams[max_pos]->getLanguage();
}

string Admin::getPreferredStreamType() const {
    if (streams.size()<=0) throw noActiveStreams("ERROR: There are currently no active streams");

}

Streamer * Admin::getMostViewedStreamer() const {
    int cnt = 0, max_cnt = 0;
    vector<Stream *>::const_iterator it;
    for (it = streams.begin(); it != streams.end(); it++){
        if ((*it)->getNumViewers() > max_cnt){
            max_cnt = (*it)->getNumViewers();
            //MostViewedStreamer = s;
        }
    }
    //return s;
}