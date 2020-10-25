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
private:
    std::vector<User *> users;  // access to users by the ID. Access to streamers using pointers
    std::vector<Stream *> streams;
    Admin* admin;
public:
    //StreamZ();
    void createStreamer();   //args will be received by input from console
    void createViewer();
    void createAdmin();
    void createStream(Streamer* streamer);
    void deleteStream(Streamer* streamer);  // deletes the stream which the streamer wants to end
    void fetchDataFromFile();
    void storeDataInFile() const;
    std::vector<Stream*> topViews() const;
    std::vector<Stream*> topLikes() const;
    std::vector<Stream*> searchStreams(std::string language, int minAge) const;
    void listStreams(std::vector<Stream*> streams) const;
    void listUsers() const;
    // Menus
    void init();
    void userMenu();
    void adminMenu();
    void viewerMenu();
    void streamerMenu();
};

#endif //PROJETO1_STREAMZ_H