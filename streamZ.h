//
// Created by joaog on 10/23/2020.
//

#ifndef PROJETO1_STREAMZ_H
#define PROJETO1_STREAMZ_H

#include "user.h"
#include "date.h"
#include "stream.h"


class Admin;    // forward declaration, in order to only regist one admin

class StreamZ{
    friend class Admin;
private:

    std::map<unsigned int, User*> users;  // access to users by the ID
    std::vector<Stream *> streams;
    std::map<std::string, unsigned int> viewersNickID;  // use this to login
    std::map<std::string, unsigned int> streamersNickID;
    std::vector<PublicStream*> publicStreams;
    std::vector<PrivateStream*> privateStreams;
    std::map<unsigned int, PastStream*> pastStreams;
    Admin* admin;
public:
    StreamZ();
    ~StreamZ();  // we need this because of dynamic memory allocation
    void createStreamer();   //args will be received by input from console
    void createViewer();
    void createAdmin();
    void createStream(Streamer* streamer);
    void deleteStream(Streamer* streamer);  // deletes the stream which the streamer wants to end
    void fetchDataFromFile();
    void storeDataInFile() const;
    std::vector<Stream*> topViews();
    std::vector<Stream*> topLikes();
    std::vector<Stream*> searchStreams(const std::string& language/*, int minAge*/) const;
    std::vector<Stream*> searchStreams(int minAge) const;
    void listStreams(std::vector<Stream *> streams) const;
    void listUsers() const;
    void listUsers(const std::set<unsigned int>& users) const;
    void showStreamHistory(int id) const;
    std::vector<Stream* > searchStreamsByTitle(const std::string& title) const;
    // Menus
    void init();
    void userMenu();
    void watchingOptions(int id);
    void joinStream(int id, vector<Stream*> streams);
    void adminMenu();
    void adminMenu2();  //retirar ou modificar
    void loginViewer();
    void loginStreamer();
    void viewerMenu(int id);
    void streamerMenu(int id);
    void streamingOptions(int id);
    bool viewerSettings(int id);
    bool streamerSettings(int id);
    bool adminSettings();
    vector<Stream*> searchStreamsMenu() const;
};

#endif //PROJETO1_STREAMZ_H
