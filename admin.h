//
// Created by joaog on 10/23/2020.
//

#ifndef PROJETO1_ADMIN_H
#define PROJETO1_ADMIN_H

#include <string>
#include "user.h"

class Admin{
private:
    std::string name;
    std::vector<User *> users;  // These vectors are the vectors of the class StreamZ (by reference)
    std::vector<Stream *> streams;
public:
    Admin(std::string name, std::vector<User*>& users, std::vector<Stream*>& streams);
    int getNumStreams() const;
    float getAverageViews() const;
    int getNoPublicStreams() const;
    int getNoPrivateStreams() const;
    std::string getPreferredLanguage() const;
    std::string getPreferredStreamType() const;
    Streamer* getMostViewedStreamer() const;
};

#endif //PROJETO1_ADMIN_H
