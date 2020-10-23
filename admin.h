//
// Created by joaog on 10/23/2020.
//

#ifndef PROJETO1_ADMIN_H
#define PROJETO1_ADMIN_H

#include <string>
#include "user.h"

class Admin{

public:
    int getNumStreams();
    float getAverageViews();
    int getNoPublicStreams();
    int getNoPrivateStreams();
    std::string getPreferredLanguage();
    std::string getPreferredStreamType();
    Streamer* getMostViewedStreamer();
};

#endif //PROJETO1_ADMIN_H
