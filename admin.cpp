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

Admin::Admin(std::string name, StreamZ& site) {
    this-> name = name;
    this->site = site;
}

int Admin::getNumStreams() const {
    return site.streams.size();
}

int Admin::getNumCreatedStreams(Date from, Date to) const {
    if (from > to) throw badDateComp("ERROR: Start date is after end date");
    int cnt = 0;
    Date d;
    vector<Stream*>::const_iterator it;
    for (it = site.streams.begin();it != site.streams.end(); it++){
        d = (*it)->getStartDate();
        if (d >= from && d <= to)
            cnt ++;
    }
    return cnt;
}

float Admin::getAvgViews() const {
    if (site.streams.size()<=0) throw noActiveStreams("ERROR: There are currently no active streams");
    int sum = 0;
    float avg = 0;
    vector<Stream *>::const_iterator it;
    for (it = site.streams.begin(); it != site.streams.end(); it++){
        sum += (*it)->getNumViewers();
    }
    avg = (float) sum/getNumStreams();
    return avg;
}

float Admin::getAvgViews(Date from, Date to) const {
    if (from > to) throw badDateComp("ERROR: Start date is after end date");
    if (site.streams.size()<=0) throw noActiveStreams("ERROR: There are currently no active streams");
    int sum = 0;
    float avg = 0;
    Date d;
    vector<Stream *>::const_iterator it;
    for (it = site.streams.begin(); it != site.streams.end(); it++){
        d = (*it)->getStartDate();
        if (d >= from && d <= to)
            sum += (*it)->getNumViewers();
    }
    avg = (float) sum/getNumStreams();
    return avg;
}

int Admin::getNumPublicStreams() const {
    return site.publicStreams.size();
}

int Admin::getNumPublicStreams(Date from, Date to) const {
    if (from > to) throw badDateComp("ERROR: Start date is after end date");
    int cnt = 0;
    Date d;
    vector<PublicStream *>::const_iterator it;
    for (it = site.publicStreams.begin(); it != site.publicStreams.end(); it++){
        d = (*it)->getStartDate();
        if (d >= from && d <= to)
            cnt++;
    }
    return cnt;
}

int Admin::getNumPrivateStreams() const {
    return site.privateStreams.size();
}

int Admin::getNumPrivateStreams(Date from, Date to) const {
    if (from > to) throw badDateComp("ERROR: Start date is after end date");
    int cnt = 0;
    Date d;
    vector<PrivateStream *>::const_iterator it;
    for (it = site.privateStreams.begin(); it != site.privateStreams.end(); it++){
        d = (*it)->getStartDate();
        if (d >= from && d <= to)
            cnt++;
    }
    return cnt;

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
    if (site.streams.size()<=0) throw noActiveStreams("ERROR: There are currently no active streams");
    if (site.privateStreams.size() > site.publicStreams.size()) return "Private Streams are the preferred type of stream";
    else if (site.privateStreams.size() < site.publicStreams.size()) return "Public Streams are the preferred type of stream";
    else return "There is no preference in the type of stream";

}

Streamer * Admin::getMostViewedStreamer() const {   // this will be different
    if (site.streams.size()<=0) throw noActiveStreams("ERROR: There are currently no active streams");
    Streamer* best;
    int maxViews = 0;
    for (std::map<std::string, unsigned int>::const_iterator it = site.streamersNickID.begin(); it != site.streamersNickID.end(); ++it){
        unsigned int id = it->second;
        Streamer* streamer = (Streamer*) site.users.at(id);
        int views = streamer->getNumViewers();
        if (views > maxViews){
            maxViews = views;
            best = streamer;
        }
    }
    return best;
}
