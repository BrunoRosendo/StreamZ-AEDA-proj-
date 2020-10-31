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

    std::map<unsigned int, User*> users;  // access to users by the ID
    std::vector<Stream *> streams;
    std::map<std::string, unsigned int> viewersNickID;  // use this to login
    std::map<std::string, unsigned int> streamersNickID;
    std::vector<PublicStream*> publicStreams;
    std::vector<PrivateStream*> privateStreams;
    Admin* admin;
public:
    StreamZ();
    //~StreamZ();  // we need this because of dynamic memory allocation
    void createStreamer();   //args will be received by input from console
    void createViewer();
    void createAdmin();
    void createStream(Streamer* streamer);
    void deleteStream(Streamer* streamer);  // deletes the stream which the streamer wants to end
    void fetchDataFromFile();
    void storeDataInFile() const;
    std::vector<Stream*> topViews() const;
    std::vector<Stream*> topLikes() const;
    std::vector<Stream*> searchStreams(std::string language/*, int minAge*/) const;
    std::vector<Stream*> searchStreams(int minAge) const;
    void listStreams(std::vector<Stream *> streams) const;
    void listUsers() const;
    void showTopStreams();
    std::vector<Stream* > searchStreamsByTitle(std::string title);
    // Menus
    void init();
    void userMenu();
    void adminMenu();
    void adminMenu2();
    void viewerMenu();
    void streamerMenu(int index);
    void searchStreamsMenu();
};

#endif //PROJETO1_STREAMZ_H
