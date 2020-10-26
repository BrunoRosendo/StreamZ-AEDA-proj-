#include <iostream>
#include <fstream>
#include <vector>

#include "streamZ.h"
#include "pastStream.h"
#include "date.h"
#include "user.h"
#include "admin.h"

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
    int cnt = 0;
    vector<Stream*>::iterator it;
    for (it = streams.begin();it != streams.end(); it++){
        if ((*it)->startDate >= from && (*it)->startDate <= to)
            cnt ++;
    }
    return cnt;
}

float Admin::getAvgViews() const {
    int sum = 0;
    float avg = 0;
    vector<Stream *>::iterator it;
    for (it = streams.begin(); it != streams.end(); it++){
            sum += (*it)->getNumViewers();
    }
    avg = sum/getNumStreams();
    return avg;
}

float Admin::getAvgViews(Date from, Date to) const {
    int sum = 0;
    float avg = 0;
    vector<Stream *>::iterator it;
    for (it = streams.begin(); it != streams.end(); it++){
        if ((*it)->startDate >= from && (*it)->startDate <= to)
            sum += (*it)->getNumViewers();
    }
    avg = sum/getNumStreams();
    return avg;
}

int Admin::getNumPublicStreams() const {

}

int Admin::getNumPublicStreams(Date from, Date to) const {

}

int Admin::getNumPrivateStreams() const {

}

int Admin::getNumPrivateStreams(Date from, Date to) const {

}

string Admin::getPreferredLanguage(std::vector<Stream*>& streams) const {
    int cnt = 0, max_cnt = 0, max_pos = 0;
    for (int i=0;i<streams.size();i++){
        for (int j=i+1;j<streams.size();j++){
            if (streams[i]->language == streams[j]->language)
                cnt++;
        }
        if (cnt > max_cnt){
            max_cnt = cnt;
            max_pos = i;
        }
    }
    return streams[max_pos]->language;
}

string Admin::getPreferredStreamType() const {

}

Streamer * Admin::getMostViewedStreamer() const {
    //Streamer s;
    int cnt = 0, max_cnt = 0;
    vector<Stream *>::iterator it;
    for (it = streams.begin(); it != streams.end(); it++){
        if ((*it)->getNumViewers() > max_cnt){
            max_cnt = (*it)->getNumViewers();
            //MostViewedStreamer = s;
        }
    }
    //return s;
}