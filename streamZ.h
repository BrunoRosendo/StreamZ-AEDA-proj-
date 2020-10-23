//
// Created by joaog on 10/23/2020.
//

#ifndef PROJETO1_STREAMZ_H
#define PROJETO1_STREAMZ_H

#include "user.h"
#include "date.h"
#include "stream.h"
#include "admin.h"

class StreamZ{
    std::vector<User *> users;
    std::vector<Stream *> streams;
    Admin* admin;
public:
    StreamZ();
    int createStreamer();   //args will be received by input from console
    int createViewer();     //args will be received by input from console
    int createAdmin();      //args will be received by input from console
    int fetchDataFromFile();
    int storeDataInFile();
};

#endif //PROJETO1_STREAMZ_H
