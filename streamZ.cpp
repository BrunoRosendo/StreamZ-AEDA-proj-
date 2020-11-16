#include <iostream>
#include <vector>
#include <sstream>
#include <map>
#include <algorithm>

#include "streamZ.h"
#include "admin.h"

using namespace std;

/**
 * StreamZ class constructor
 */
StreamZ::StreamZ() {
    try{
        fetchDataFromFile();
    }
    catch(runtime_error& e){
        cerr << e.what() << endl;
    }
}

StreamZ::~StreamZ() {
    delete admin;
    for (int i = 0; i < streams.size(); ++i)
        delete streams.at(i);
    map<unsigned int, User*>::iterator it;
    for (it = users.begin(); it != users.end(); ++it)
        delete it->second;
    for(auto it2 = this->pastStreams.begin(); it2 != this->pastStreams.end(); it2++){
        delete it2->second;
    }
}

/**
 * Reads data from files that contain the registered users, past streams, etc.
 */

void StreamZ::fetchDataFromFile() {
    string streamersFile = "streamers.txt";
    string viewersFile = "viewers.txt";
    string pastStreamsFile = "pastStreams.txt";
    string adminFile = "admin.txt";
    fstream fin;
    string line, line2, name, nick, date;
    unsigned int id, pastStreamId;
    std::set<unsigned int> pastStreams;
    int counter = 0;

    fin.open(viewersFile);              // START TO READ VIEWERS
    if(!fin.is_open()){
        cout << "Couldn't open " << viewersFile << " file!" << endl;
        throw runtime_error("Couldn't open " + viewersFile + " file!");
    }
    while(getline(fin, line )){
        switch(counter){
            case 0:
                name = line;
                counter++;
                break;
            case 1:
                nick = line;
                counter++;
                break;
            case 2:
                date = line;
                counter++;
                break;
            case 3:
                id = stoi(line);
                counter++;
                break;
            default:
                if(line[0] == '*'){     //stream history member
                    line = line.substr(1); // slice the 1st char of the string
                    pastStreamId = stoi(line);
                    pastStreams.insert(pastStreamId);
                }
                else{                      // transition to new streamer
                    Date birthDate(date);   // create object of class Date with the string date
                    Viewer* viewer = new Viewer(name, nick, birthDate, id);
                    viewer->setStreamHistory(pastStreams);
                    this->users.insert({id, viewer});
                    this->viewersNickID.insert({viewer->getNick(), viewer->getID()});

                    name = line;            //saves the name of the next user
                    counter = 1;
                    pastStreams.clear();
                }
                break;
        }
    }
    Date birthDate(date);   // create object of class Date with the string date
    Viewer* viewer = new Viewer(name, nick, birthDate, id);
    viewer->setStreamHistory(pastStreams);
    this->users.insert({id, viewer});
    this->viewersNickID.insert({viewer->getNick(), viewer->getID()});
    fin.close();

    fin.open(streamersFile);            // START TO READ STREAMERS
    if(!fin.is_open()){
        cout << "Couldn't open " << streamersFile << " file!" << endl;
    }
    std::set<unsigned int> subscribers;
    counter = 0;
    pastStreams.clear();
    while(getline(fin, line )){
        switch(counter){
            case 0:
                name = line;
                counter++;
                break;
            case 1:
                nick = line;
                counter++;
                break;
            case 2:
                date = line;
                counter++;
                break;
            case 3:
                id = stoi(line);
                counter++;
                break;
            default:
                if(line[0] == '*'){     //stream history member
                    line = line.substr(1); // slice the 1st char of the string
                    pastStreamId = stoi(line);
                    pastStreams.insert(pastStreamId);
                }
                else if(line[0] == '/'){    //subscriber (nick)
                    line = line.substr(1);
                    subscribers.insert(stoi(line));
                }
                else{                      // transition to new streamer
                    Date birthDate(date);   // create object of class Date with the string date
                    Streamer* streamer = new Streamer(name, nick, birthDate, id);
                    streamer->setStreamHistory(pastStreams);
                    streamer->setSubscribers(subscribers);
                    this->users.insert({id, streamer});
                    this->streamersNickID.insert({streamer->getNick(), streamer->getID()});

                    name = line;            //saves the name of the next user
                    counter = 1;
                    pastStreams.clear();
                }
                break;
        }
    }
    Date birthDate2(date);   // create object of class Date with the string date
    Streamer* streamer = new Streamer(name, nick, birthDate2, id);
    streamer->setStreamHistory(pastStreams);
    streamer->setSubscribers(subscribers);
    this->users.insert({id, streamer});
    this->streamersNickID.insert({streamer->getNick(), streamer->getID()});
    fin.close();
    pastStreams.clear();

    fin.open(pastStreamsFile);
    string line3, dateString;
    if(!fin.is_open()){
        cout << "Couldn't open " << pastStreamsFile << " file!" << endl;
        throw runtime_error("Couldn't open " + pastStreamsFile + " file!");
    }
    while(getline(fin, line )) {
        if (line == "\n") break;
        getline(fin, line2);    // id
        getline(fin, line3);    // no_viewers when stream ended
        getline(fin, dateString);   // date in the format of a string
        id = stoi(line2);
        struct PastStream* s = new PastStream;          // !! VERIFY WHEN YOU NEED TO FREE THIS MEMORY
        s->name = line, s->id = id, s->noViewers = stoi(line3), s->StartDate = Date(dateString); // NEEDS THE STARTDATE AS WELL
        this->pastStreams.insert({id, s});
    }
    fin.close();


    fin.open(adminFile);
    if(!fin.is_open()){
        cout << "Couldn't open " << adminFile << " file!" << endl;
        throw runtime_error("Couldn't open " + adminFile + " file!");
    }
    getline(fin, line);
    if(!line.empty()){
        this->admin = new Admin(line, this);
    }
    else
        this->admin = nullptr;
    fin.close();

}

/**
 * Writes data in files that contain the registered users, past streams,, etc.
 */
void StreamZ::storeDataInFile(){
    string streamersFile = "streamers.txt";
    string viewersFile = "viewers.txt";
    string pastStreamsFile = "pastStreams.txt";
    string adminFile = "admin.txt";
    fstream fout;
    unsigned int currUserId;

    fout.open(pastStreamsFile, ios::out | ios::trunc);      // need to call this first since users are changed here
    PastStream* pastStream;
    if(!fout.is_open()){
        cout << "Couldn't open " << pastStreamsFile << " file!" << endl;
        throw runtime_error("Couldn't open " + pastStreamsFile + " file!");
    }
    for(auto it = this->streamersNickID.begin(); it != this->streamersNickID.end(); it++){      //iterates streamers and if they have an active stream, ends it updating PastStream
        if (this->users[ it->second ]->inAStream()) {
            this->deleteStream((Streamer *) this->users[it->second]);
        }
    }
    for(auto it = this->pastStreams.begin(); it != this->pastStreams.end(); it++){
        pastStream = it->second;
        fout << pastStream->name << endl << pastStream->id << endl << pastStream->noViewers << endl << pastStream->StartDate.getDate() << endl;
    }
    fout.close();

    fout.open(viewersFile, ios::out | ios::trunc);  // Overwrite previous info
    Viewer* viewer;
    if(!fout.is_open()){
        cout << "Couldn't open " << viewersFile << " file!" << endl;
        throw runtime_error("Couldn't open " + viewersFile + " file!");
    }
    for(auto it = this->viewersNickID.begin(); it != this->viewersNickID.end(); it++){
        currUserId = it->second;
        viewer = (Viewer *) this->users.at(currUserId);
        fout << viewer->getName() << endl << viewer->getNick() << endl << viewer->getAgeString() << endl << viewer->getID() << endl;
        for(auto historyIt = viewer->getStreamHistory().begin(); historyIt != viewer->getStreamHistory().end(); historyIt++ ){
            fout << '*' << *historyIt << endl;
        }
    }
    fout.close();

    fout.open(streamersFile, ios::out | ios::trunc);
    Streamer* streamer;
    if(!fout.is_open()){
        cout << "Couldn't open " << streamersFile << " file!" << endl;
        throw runtime_error("Couldn't open " + streamersFile + " file!");
    }
    for(auto it = this->streamersNickID.begin(); it != this->streamersNickID.end(); it++){
        currUserId = it->second;
        streamer = (Streamer *) this->users.at(currUserId);
        fout << streamer->getName() << endl << streamer->getNick() << endl << streamer->getAgeString() << endl << streamer->getID() << endl;
        for(auto historyIt = streamer->getStreamHistory().begin(); historyIt != streamer->getStreamHistory().end(); historyIt++ ){  // writes past streams
            fout << '*' << *historyIt << endl;
        }
        for(auto subsIt = streamer->getSubscribers().begin(); subsIt != streamer->getSubscribers().end(); subsIt++ ){   //writes the subscribers
            fout << '/' << *subsIt << endl;
        }
    }
    fout.close();

    fout.open(adminFile, ios::out | ios::trunc);
    if(!fout.is_open()){
        cout << "Couldn't open " << adminFile << " file!" << endl;
        throw runtime_error("Couldn't open " + adminFile + " file!");
    }
    if(admin != nullptr)
        fout << this->admin->getName();
    fout.close();


}


void StreamZ::init(){
    while (true) {
        cout << "WELCOME TO STREAMZ" << endl << endl;
        cout << "1- Create Viewer" << endl << "2- Create Streamer" << endl;
        if (admin == nullptr) cout << "3- Create Admin";
        else cout << "3- Login as Admin";
        cout << endl << "4- Login as User" << endl << "5- Exit" << endl;
        int choice;
        cin >> choice;
        if (cin.fail() || cin.eof()){
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Please enter a number between 1 and 5" << endl << endl;
            continue;
        }
        cin.ignore(1000, '\n');
        switch (choice) {
            case 1:
                createViewer();
                break;
            case 2:
                createStreamer();
                break;
            case 3:
                if (admin == nullptr) createAdmin();
                else adminMenu();
                break;
            case 4:
                userMenu();
                break;
            case 5:
                this->storeDataInFile();
                return;
            default:
                cout << "That is not a valid choice. Please enter a valid number" << endl;
                continue;
        }
    }
}

void StreamZ::userMenu() {
    while (true) {
        cout << "Which type of user are you?" << endl << endl
             << "1- Viewer" << endl << "2- Streamer" << endl << "3- Go back" << endl;
        int choice;
        cin >> choice;
        if (cin.fail() || cin.eof()){
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Choose a number between 1 and 3" << endl << endl;
            continue;
        }
        cin.ignore(1000, '\n');
        switch (choice) {
            case 1:
                loginViewer();
                break;
            case 2:
                loginStreamer();
                break;
            case 3:
                return;
            default:
                cout << "Choose a number between 1 and 3" << endl;
                continue;
        }
    }
}

void StreamZ::loginViewer() {
    if (viewersNickID.empty()){
        cout << "Create an account before trying to login" << endl << endl;
        return;
    }
    cout << "Please type the nickname of your account: ";
    int id;
    while (true) {
        string nick;
        getline(cin, nick);
        if (nick.find_first_not_of (' ') == nick.npos || cin.fail() || cin.eof()){
            cin.clear();
            cout << "Please enter a valid nickname: ";
            continue;
        }
        try {
            id = viewersNickID.at(nick);
            break;
        }
        catch (out_of_range &e) {
            cout << "That nickname does not exist. Please verify it and type it again: ";
        }
    }
    if (users.at(id)->inAStream()) watchingOptions(id);
    viewerMenu(id);
}

void StreamZ::loginStreamer() {
    if (streamersNickID.empty()){
        cout << "Create an account before trying to login" << endl << endl;
        return;
    }
    cout << "Please type the nickname of your account: ";
    int id;
    while (true) {
        string nick;
        getline(cin, nick);
        if (nick.find_first_not_of (' ') == nick.npos || cin.fail() || cin.eof()){
            cin.clear();
            cout << "Please enter a valid nickname: ";
            continue;
        }
        try {
            id = streamersNickID.at(nick);
            break;
        }
        catch (out_of_range &e) {
            cout << "That nickname does not exist. Please verify it and type it again: ";
        }
    }
    streamerMenu(id);
}

void StreamZ::viewerMenu(int id) {
    Viewer* v = (Viewer*) users.at(id);
    while(true){
        if (v->inAStream()) return;
        cout << "What do you want to do?" << endl << endl
             << "1- Search streams" << endl << "2- Show top viewed streams" << endl << "3- Show top liked streams"
             << endl << "4- List all streams" << endl << "5- List all users" << endl << "6- Account settings" <<
             endl << "7- Go back" << endl;
        int choice;
        cin >> choice;
        if (cin.fail() || cin.eof()){
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Please enter a valid number" << endl << endl;
            continue;
        }
        cin.ignore(1000, '\n');
        switch(choice){
            case 1:
                joinStream(id, searchStreamsMenu());
                break;
            case 2:
                listStreams(topViews());
                joinStream(id,topViews());
                break;
            case 3:
                listStreams(topLikes());
                joinStream(id, topLikes());
                break;
            case 4:
                this->listStreams(this->streams);
                joinStream(id, this->streams);
                break;
            case 5:
                this->listUsers();
                break;
            case 6:
                if (viewerSettings(id)) return;
                break;
            case 7:
                return;
            default:
                cout << "Please enter a number between 1 and 6" << endl;
        }
        if (v->inAStream()) watchingOptions(id);
    }
}

void StreamZ::joinStream(int id, vector<Stream*> filteredStreams) {
    if (filteredStreams.empty()){
        cout << "No streams available to join" << endl;
        return;
    }
    cout << "Type the number of the stream you want to join (0 if you don't want any): ";
    int num;
    while (true) {
        cin >> num;
        if(cin.fail() || cin.eof()){
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Please enter a valid number" << endl;
            continue;
        }
        cin.ignore(1000, '\n');
        if (num > filteredStreams.size()) {
            cout << "That's not a valid number!" << endl;
            continue;
        }
        else if (num == 0) return;
        break;
    }
    Viewer* v = (Viewer*) users.at(id);
    try {
        filteredStreams[num-1]->addUser(v->getID());
        v->joinStream(filteredStreams[num-1]);
    }
    catch(NoCapacity& e){
        cout << e.what() << endl;
    }
    catch (NotSubscribed& e){
        cout << e.what() << endl;
    }
    catch (AlreadyInAStream& e){
        cout << e.what() << endl;
        filteredStreams[num-1]->removeUser(v->getID());
    }
    catch (NotOldEnough& e){
        cout << e.what() << endl;
        filteredStreams[num-1]->removeUser(v->getID());
    }
}

void StreamZ::watchingOptions(int id) {
    Viewer* v = (Viewer*) users.at(id);
    string streamerNick = v->getStream()->getStreamerNick();
    Streamer* s = (Streamer *) users.at(streamersNickID.at(streamerNick));
    while (true) {
        cout << "You are currently watching " << v->getStream()->getTitle() << ". Here, you can:" << endl << endl
             << "1- Give feedback" << endl << "2- Show stream details" << endl;
        if (s->isSubscriber(id)) cout << "3- Unsubscribe to the streamer";
        else cout << "3- Subscribe to the streamer";
        cout << endl << "4- Leave stream" << endl << "5- Account Settings" << endl<< "6- Go back" << endl;
        int choice;
        cin >> choice;
        if(cin.fail() || cin.eof()){
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Please enter a valid number" << endl << endl;
            continue;
        }
        cin.ignore(1000, '\n');
        switch (choice) {
            case 1: {
                cout << "Type 1 to like and 2 to dislike: ";
                int like, megaLikezao;
                cin >> like;
                cin.ignore(100, '\n');
                if (like == 1) megaLikezao = 1;
                else if (like == 2) megaLikezao = -1;
                else {
                    cout << "That's not a valid number!" << endl;
                    break;
                }
                v->feedback(megaLikezao);
                vector<PrivateStream *>::iterator it = find(privateStreams.begin(), privateStreams.end(),
                                                            v->getStream());
                if (it != privateStreams.end()) {
                    string mes;
                    cout << "Insert a message you'd like to send to your streamer (empty if you don't want to):" << endl;
                    getline(cin, mes);
                    v->message(mes);
                }
                break;
            }
            case 2:
                v->getStream()->showStream();
                break;
            case 3:
                if (s->isSubscriber(id))
                    s->removeSubscriber(id);
                else
                    s->addSubscriber(id);
                break;
            case 4:
                v->getStream()->removeUser(v->getID());
                v->leaveStream();
                return;
            case 5:
                viewerSettings(id);
                break;
            case 6:
                return;
            default:
                cout << "Enter a valid number" << endl << endl;
        }
    }
}

void StreamZ::streamerMenu(int id) {
    while(true) {
        cout << "What do you want to do?" << endl << endl << "1- Search streams" << endl
             << "2- List all streams" << endl << "3- List all users" << endl << "4- Show top viewed streams" << endl
             << "5- Show top liked streams " << endl << "6- Show number of subscribers" << endl << "7- List subscribers"
             << endl << "8- Streaming options" << endl << "9- Account settings" << endl << "10- Go back" << endl;
        int choice;
        cin >> choice;
        if (cin.fail() || cin.eof()){
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Please enter a valid number" << endl << endl;
            continue;
        }
        cin.ignore(1000, '\n');
        switch (choice) {
            case 1:
                searchStreamsMenu();
                break;
            case 2:
                listStreams(this->streams);
                break;
            case 3:
                listUsers();
                break;
            case 4:
                listStreams(topViews());
                break;
            case 5:
                listStreams(topLikes());
                break;
            case 6: {
                Streamer *s = (Streamer *) users[id];
                int num = s->getNumSubs();
                cout << "You currently have " << num << " subscriber";
                if (num != 1) cout << "s";
                cout << endl;
                break;
            }
            case 7: {
                Streamer *s = (Streamer *) users[id];
                set<unsigned int> subs = s->getSubscribers();
                if (subs.empty()) cout << "You don't have any subscribers yet :(" << endl;
                else listUsers(subs);
                break;
            }
            case 8:
                streamingOptions(id);
                break;
            case 9:
                if (streamerSettings(id)) return;
                break;
            case 10:
                return;
            default:
                cout << "Please enter a valid number" << endl;
        }
    }
}

void StreamZ::streamingOptions(int id) {
    Streamer* s = (Streamer*) users.at(id);
    while (true){
        if (!(s->inAStream())){
            cout << "Do you wish to start a new stream? (y/n)" << endl;
            char choice;
            cin >> choice;
            cin.ignore(100, '\n');
            if (choice == 'y' || choice == 'Y') createStream(s);
            else return;
        }
        cout << "What do you wish to do?" << endl << endl;
        cout << "1- See number of viewers" << endl << "2- See feedback" << endl << "3- End stream"
             << endl << "4- Go back" << endl;
        int c;
        cin >> c;
        if (cin.fail() || cin.eof()){
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Please enter a valid number" << endl << endl;
            continue;
        }
        cin.ignore(1000, '\n');
        switch (c) {
            case 1: {
                int num = s->getNumViewers();
                cout << "You currently have " << num << " viewer";
                if (num != 1) cout << "s";
                cout << endl;
                break;
            }
            case 2: {
                vector<PrivateStream *>::iterator it = find(privateStreams.begin(), privateStreams.end(),
                                                            s->getStream());
                if (it != privateStreams.end()) {
                    PrivateStream *p = (PrivateStream *) s->getStream();
                    p->showMessages();
                }
                int noLikes = s->getStream()->getNoLikes();
                cout << "You currently have " << noLikes << " like";
                if (noLikes != 1) cout << "s";
                cout << endl;
                break;
            }
            case 3:
                deleteStream(s);
            case 4:
                return;
            default:
                cout << "Please select a valid number" << endl;
        }
    }
}

void StreamZ::adminMenu() {
    cout << "Welcome " << admin->getName() << endl << endl;

    cout << "Total number of active Streams: " << admin->getNumStreams() << endl <<endl;

    cout << "Number of active Public Streams: " << admin->getNumPublicStreams() <<endl<<endl;

    cout << "Number of active Private Streams: " << admin->getNumPrivateStreams() <<endl<<endl;
    try {
        float views = admin->getAvgViews();
        cout << "Average stream views: " << views << endl << endl;

        cout << "Most common stream language is " << admin->getPreferredLanguage(streams) << endl << endl;

        cout  << admin->getPreferredStreamType() << endl << endl;

        cout << "Most viewed streamer: " << admin->getMostViewedStreamer()->getNick() << endl << endl;
    }
    catch(NoActiveStreams& e){
        cout << e.what() << endl;
    }
    while(true) {
        cout << "Stats about all streams?" << endl << endl
             << "1- Number of Streams created (interval)" << endl
             << "2- Number of Public active Streams (interval)" << endl
             << "3- Number of Private active Streams (interval)" << endl
             << "4- Average views for all streams (interval)" << endl
             << "5- Account Settings" << endl
             << "6- Go back" << endl;
        int choice;
        cin >> choice;
        if (cin.fail() || cin.eof()){
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Please enter a valid number" << endl << endl;
            continue;
        }
        cin.ignore(1000, '\n');
        switch (choice){
            case 5:
                if (adminSettings()) return;
                continue;
            case 6:
                return;
        }
        if (choice > 6){
            cout << "Insert a valid number" << endl;
            continue;
        }
        try{
            string from;
            string to;
            cout << "Start date (yyyy/mm/dd): " << endl;
            cin >> from;
            while (cin.fail() || cin.eof()) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Enter a date in the format 'yyyy/mm/dd': ";
                cin >> from;
            }
            cin.ignore(1000, '\n');
            Date f(from);
            cout << "End date (yyyy/mm/dd): " << endl;
            cin >> to;
            while (cin.fail() || cin.eof()) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Enter a date in the format 'yyyy/mm/dd': ";
                cin >> to;
            }
            cin.ignore(1000, '\n');
            Date t(to);
            switch (choice) {
                case 1: {
                    int numAll = admin->getNumCreatedStreams(f, t);
                    cout << "Streams created from " << f.getDate() << " to " << t.getDate() << " : "
                         << numAll << endl;
                    break;
                }
                case 2: {
                    int numPublic = admin->getNumPublicStreams(f, t);
                    cout << "Public Streams created from " << f.getDate() << " to " << t.getDate() << " : "
                         << numPublic << endl;
                    break;
                }
                case 3: {
                    int numPrivate = admin->getNumPrivateStreams(f, t);
                    cout << "Private Streams created from " << f.getDate() << " to " << t.getDate() << " : "
                         << numPrivate << endl;
                    break;
                }
                case 4: {
                    float avg = admin->getAvgViews(f, t);
                    cout << "Average stream views from " << f.getDate() << " to " << t.getDate() << " : "
                         << avg << endl;
                    break;
                }
            }
        }
        catch(badDateComp& e){
            cout << e.what() << endl;
        }
        catch(DateIsNotValid& e){
            cout << e.what() << endl;
        }
        catch(NoActiveStreams& e){
            cout << e.what() << endl;
        }
    }
}


void StreamZ::createViewer() {
    string name, nick, birthDateString;
    cout << "Lets begin the creation of a new Viewer! " << "Please insert the following data: " << endl;
    cout << "Name: ";
    getline(cin, name);
    while (name.find_first_not_of (' ') == name.npos || cin.fail() || cin.eof()){
        cin.clear();
        cout << "Enter a valid name: ";
        getline(cin, name);
    }
    cout << "Nickname: ";
    while (true) {
        getline(cin, nick);
        if(nick.find_first_not_of (' ') == nick.npos || cin.fail() || cin.eof()){
            cin.clear();
            cout << "Enter a valid nickname: ";
            continue;
        }
        if (viewersNickID.find(nick) != viewersNickID.end()){
            cout << "That nickname is already taken. Choose another one: ";
            continue;
        }
        break;
    }
    while(true){
        try{
            cout << "Birth Date(yyyy/mm/dd):";
            cin >> birthDateString;
            if (cin.fail() || cin.eof()){
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Enter a valid date: " << endl;
                continue;
            }
            cin.ignore(1000, '\n');
            Date birthDate(birthDateString);
            Date today;
            if (birthDate > today){
                cout << "Insert a valid date: " << endl;
                continue;
            }
            Viewer* newViewer = new Viewer(name, nick, birthDate);
            this->users[newViewer->getID()] = newViewer;
            viewersNickID[newViewer->getNick()] = newViewer->getID();
            cout << "A new Viewer was successfully created! " << endl;
            break;
        }
        catch(DateIsNotValid &d){
            cout << d.what() << endl;
        }
        catch(NotOldEnough &n){
            cout << n.what() << endl << endl;
            return;
        }
    }
}


void StreamZ::createStreamer() {
    string name, nick, birthDateString;
    cout << "Lets begin the creation of a new Streamer! " << "Please insert the following data: " << endl;
    cout << "Name: ";
    getline(cin, name);
    while (name.find_first_not_of (' ') == name.npos || cin.fail() || cin.eof()){
        cin.clear();
        cout << "Enter a valid name: ";
        getline(cin, name);
    }
    cout << "Nickname: ";
    while (true) {
        getline(cin, nick);
        if(nick.find_first_not_of (' ') == nick.npos || cin.fail() || cin.eof()){
            cin.clear();
            cout << "Enter a valid nickname: ";
            continue;
        }
        if (streamersNickID.find(nick) != streamersNickID.end()){
            cout << "That nickname is already taken. Choose another one: ";
            continue;
        }
        break;
    }
    while(true){
        try{
            cout << "Birth Date(yyyy/mm/dd): ";
            cin >> birthDateString;
            if (cin.fail() || cin.eof()){
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Enter a valid date" << endl;
                continue;
            }
            Date birthDate(birthDateString);
            Date today;
            if (birthDate > today){
                cout << "Insert a valid date" << endl;
                continue;
            }
            Streamer* newStreamer = new Streamer(name, nick, birthDate);
            this->users[newStreamer->getID()] = newStreamer;
            streamersNickID[newStreamer->getNick()] = newStreamer->getID();
            cout << "A new Streamer was successfully created! " << endl;
            break;
        }
        catch(DateIsNotValid &d){
            cout << d.what() << endl;
        }
        catch(NotOldEnough &n){
            cout << n.what() << endl << endl;
            return;
        }
    }
}

void StreamZ::createAdmin() {
    string name;
    cout << "Lets begin the creation of a new Admin! " << "Please insert the following data: " << endl;
    cout << "Name: ";
    getline(cin, name);
    while (name.find_first_not_of (' ') == name.npos || cin.fail() || cin.eof()){
        cin.clear();
        cout << "Enter a valid name: ";
        getline(cin, name);
    }
    admin = new Admin(name, this);
    cout << "A new Admin was successfully created! " << endl;
}

void StreamZ::createStream(Streamer *streamer) {
    string title, language;
    Date startDate = Date();        //curr date
    unsigned int minAge, typeOfStream;
    bool error = true;
    while (error) {
        cout << "What is the title of the stream?" << endl;
        getline(cin, title);
        while (title.find_first_not_of (' ') == title.npos || cin.fail() || cin.eof()){
            cin.clear();
            cout << "Enter a valid title " << endl;
            getline(cin, title);
        }
        cout << "What language is the stream on?" << endl;
        cin >> language;
        while (language.find_first_not_of (' ') == language.npos || cin.fail() || cin.eof()){
            cin.clear();
            cout << "Enter a valid language: " << endl;
            getline(cin, language);
        }
        cout << "What is the minimum age?" << endl;
        cin >> minAge;
        while (cin.fail() || cin.eof()){
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Insert a valid number" << endl;
        }
        cout << "Will it be a public(1) or private(2) stream?" << endl;
        cin >> typeOfStream;
        while(true){
            if (cin.fail() || cin.eof()){
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Enter a valid number" << endl;
                cin >> typeOfStream;
                continue;
            }
            if (typeOfStream != 1 && typeOfStream != 2){
                cout << "Enter a number between 1 and 2" << endl;
                cin >> typeOfStream;
            }
            break;
        }
        cin.ignore(1000, '\n');
        switch (typeOfStream) {
            case 1: {
                try {
                    PublicStream *newStream = new PublicStream(title, startDate, language, minAge, streamer->getNick());
                    streamer->startStream(newStream);
                    streams.push_back(newStream);
                    publicStreams.push_back(newStream);

                    struct PastStream* pastStream = new PastStream(newStream);      //add a past stream to the global map
                    this->pastStreams.insert({newStream->getId(), pastStream});     //no_viewers has a default value of -1

                    error = false;
                    break;
                }
                catch (AlreadyInAStream &e) {
                    cout << e.what() << endl;
                    error = true;
                    break;
                }
            }
            case 2:{
                try{
                    int capacity;
                    cout << "What will be its capacity?" << endl;
                    cin >> capacity;
                    cin.ignore(100, '\n');
                    PrivateStream *newStream = new PrivateStream(title, startDate, language, minAge, streamer->getNick(), streamer->getSubscribers(), capacity);
                    streamer->startStream(newStream);
                    streams.push_back(newStream);
                    privateStreams.push_back(newStream);

                    struct PastStream* pastStream = new PastStream(newStream);      //add a past stream to the global map
                    this->pastStreams.insert({newStream->getId(), pastStream});     //no_viewers has a default value of -1

                    error = false;
                    break;
                }
                catch (AlreadyInAStream& e){
                    cout << e.what() << endl;
                    error = true;
                    break;
                }
            }
        }
    }
}

void StreamZ::deleteStream(Streamer *streamer) {    // this has to change the history of the streamer and viewers
    while(1) {
        try {
            Stream* stream = streamer->getStream();
            if(stream != nullptr){
                this->pastStreams.at(stream->getId())->noViewers = stream->getNumViewers();     //update no_viewers on the PastStream
                streamer->endStream();
                set<unsigned int> viewers = stream->getViewers();
                for (set<unsigned int>::iterator it = viewers.begin(); it != viewers.end(); ++it){
                    Viewer* v = (Viewer*) users[(*it)];
                    v->leaveStream();
                }
                streams.erase(find(streams.begin(), streams.end(), stream));
                vector<PublicStream*>::iterator it = find(publicStreams.begin(), publicStreams.end(), stream);
                if (it != publicStreams.end()) publicStreams.erase(it);
                else privateStreams.erase(find(privateStreams.begin(), privateStreams.end(), stream));
                delete stream;
                break;
            }
        }
        catch (NotInAStream &e) {
            cout << e.what() << endl;
            break;
        }
    }
}

bool StreamZ::viewerSettings(int id) {
    while (true) {
        cout << "What do you wish to do?" << endl;
        cout << "1- Change name" << endl << "2- Change nickname" << endl << "3- Delete account"
        << endl << "4- Show stream history" << endl << "5- Go back" << endl;
        int choice;
        cin >> choice;
        if (cin.fail() || cin.eof()){
            cout << "Select a valid number" << endl << endl;
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }
        cin.ignore(1000, '\n');
        switch (choice){
            case 1: {
                std::string name;
                cout << "Insert your new name: " << endl;
                getline(cin, name);
                while (name.find_first_not_of(' ') == name.npos || cin.fail() || cin.eof()) {
                    cin.clear();
                    cout << "Enter a valid name: ";
                    getline(cin, name);
                }
                users.at(id)->setName(name);
                break;
            }
            case 2: {
                viewersNickID.erase(users.at(id)->getNick());
                std::string nick;
                cout << "Insert your new nickname: " << endl;
                while (true) {
                    getline(cin, nick);
                    if(nick.find_first_not_of (' ') == nick.npos || cin.fail() || cin.eof()){
                        cin.clear();
                        cout << "Enter a valid nickname: ";
                        continue;
                    }
                    if (viewersNickID.find(nick) != viewersNickID.end()){
                        cout << "That nickname is already taken. Choose another one: ";
                        continue;
                    }
                    break;
                }
                users.at(id)->setNick(nick);
                viewersNickID[nick] = id;
                break;
            }
            case 3: {
                Viewer *v = (Viewer *) users.at(id);
                viewersNickID.erase(v->getNick());
                if (v->inAStream()) v->leaveStream();
                delete v;
                users.erase(id);
                std::map<std::string, unsigned int>::iterator it;
                for (it = streamersNickID.begin(); it != streamersNickID.end(); ++it){
                    Streamer* s = (Streamer*) users.at(it->second);
                    set<unsigned int> subs = s->getSubscribers();
                    set<unsigned int>::iterator search = subs.find(id);
                    if (search != subs.end()) s->removeSubscriber(id);
                }
                cout << "Account successfully deleted!" << endl;
                return true;
            }
            case 4:
                showStreamHistory(id);
                break;
            case 5:
                return false;
            default:
                cout << "Chose a valid number" << endl << endl;
        }
    }
}

bool StreamZ::streamerSettings(int id) {
    while (true) {
        cout << "What do you wish to do?" << endl;
        cout << "1- Change name" << endl << "2- Change nickname" << endl << "3- Delete account"
        << endl << "4- Show stream history" << endl << "5- Go back" << endl;
        int choice;
        cin >> choice;
        if (cin.fail() || cin.eof()) {
            cout << "Select a valid number" << endl << endl;
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }
        cin.ignore(1000, '\n');
        switch (choice){
            case 1:{
                std::string name;
                cout << "Insert your new name: " << endl;
                getline(cin, name);
                while (name.find_first_not_of(' ') == name.npos || cin.fail() || cin.eof()) {
                    cin.clear();
                    cout << "Enter a valid name: ";
                    getline(cin, name);
                }
                users.at(id)->setName(name);
                break;
            }
            case 2: {
                streamersNickID.erase(users.at(id)->getNick());
                std::string nick;
                cout << "Insert your new nickname: " << endl;
                while (true) {
                    getline(cin, nick);
                    if (nick.find_first_not_of(' ') == nick.npos || cin.fail() || cin.eof()) {
                        cin.clear();
                        cout << "Enter a valid nickname: ";
                        continue;
                    }
                    if (viewersNickID.find(nick) != viewersNickID.end()) {
                        cout << "That nickname is already taken. Choose another one: ";
                        continue;
                    }
                    if (users.at(id)->inAStream()) users.at(id)->getStream()->setStreamerNick(nick);
                    break;
                }
                users.at(id)->setNick(nick);
                streamersNickID[nick] = id;
                break;
            }
            case 3:{
                Streamer* s = (Streamer*) users.at(id);
                streamersNickID.erase(s->getNick());
                if (s->inAStream()) s->endStream();
                delete s;
                users.erase(id);
                cout << "Account successfully deleted!" << endl;
                return true;
            }
            case 4:
                showStreamHistory(id);
                break;
            case 5:
                return false;
            default:
                cout << "Insert a valid number" << endl << endl;
        }
    }
}

bool StreamZ::adminSettings() {
    while (true){
        cout << "What do you wish to do?" << endl;
        cout << "1- Change name" << endl << "2- Delete account" << endl << "3- Go back" << endl;
        int choice;
        cin >> choice;
        if (cin.fail() || cin.eof()) {
            cout << "Select a valid number" << endl << endl;
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }
        cin.ignore(1000, '\n');
        switch (choice){
            case 1: {
                std::string name;
                cout << "Insert your new name: " << endl;
                getline(cin, name);
                while (name.find_first_not_of(' ') == name.npos || cin.fail() || cin.eof()) {
                    cin.clear();
                    cout << "Enter a valid name: ";
                    getline(cin, name);
                }
                admin->setName(name);
                break;
            }
            case 2:{
                delete admin;
                admin = nullptr;
                return true;
            }
            case 3:
                return false;
            default:
                cout << "Please insert a valid number" << endl << endl;
        }

    }
}

std::vector<Stream *> StreamZ::topViews() {
    vector<Stream*> top10;
    sort(streams.begin(), streams.end(), [] (Stream* s1, Stream* s2) {return s1->getNumViewers() > s2->getNumViewers();});
    for (int i = 0; i < streams.size(); ++i){
        if (i >= 10) break;
        top10.push_back(streams.at(i));
    }
    return top10;
}

std::vector<Stream *> StreamZ::topLikes() {
    vector<Stream*> top10;
    sort(streams.begin(), streams.end(), [] (Stream* s1, Stream* s2) {return s1->getNoLikes() > s2->getNoLikes();});
    for (int i = 0; i < streams.size(); ++i){
        if (i >= 10) break;
        top10.push_back(streams.at(i));
    }
    return top10;
}

vector<Stream*> StreamZ::searchStreamsMenu() const {
    int choice1;
    std::string choice2;
    unsigned int ageChoice;
    std::vector<Stream*> filteredStreams;
    while(1){
        cout << "Search streams by: " << endl << "1- Title\n2- Language\n3- Minimum Age\n4- Exit\n";  //Possibly add a category to streams
        cin >> choice1;
        while (cin.fail() || cin.eof()){
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Insert a valid number" << endl;
            cin >> choice1;
        }
        cin.ignore(1000, '\n');
        switch(choice1){
            case 1:
                cout << "Insert the Title" << endl;
                getline(cin, choice2);
                while (choice2.find_first_not_of (' ') == choice2.npos || cin.fail() || cin.eof()){
                    cin.clear();
                    cout << "Insert a valid title" << endl;
                    getline(cin, choice2);
                }
                filteredStreams = this->searchStreamsByTitle(choice2);
                for(int i = 0; i < filteredStreams.size(); i++)
                    cout << i+1 << "- " << *(filteredStreams[i])<< endl;
                break;
            case 2:
                cout << "What language are you looking for?" << endl;
                cin >> choice2;
                cin.ignore(100, '\n');
                while (choice2.find_first_not_of (' ') == choice2.npos || cin.fail() || cin.eof()){
                    cin.clear();
                    cout << "Insert a valid language" << endl;
                    getline(cin, choice2);
                }
                filteredStreams = this->searchStreams(choice2);
                for(int i = 0; i < filteredStreams.size(); i++)
                    cout << i+1 << "- " << *(filteredStreams[i]) << endl;
                break;
            case 3:
                cout << "What is the minimum age?" << endl;
                cin >> ageChoice;
                while (cin.fail() || cin.eof()){
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "Insert a valid number" << endl;
                    cin >> ageChoice;
                }
                cin.ignore(1000, '\n');
                filteredStreams = this->searchStreams(ageChoice);
                for(int i = 0; i < filteredStreams.size(); i++)
                    cout << i+1 << "- " << *(filteredStreams[i]) << endl;
                break;
            case 4:
                return filteredStreams;
        }
    }
}

std::vector<Stream*> StreamZ::searchStreamsByTitle(std::string title) const {
    std::vector<Stream *> ans;
    transform(title.begin(), title.end(), title.begin(), ::toupper);
    for(int i = 0; i < this->streams.size(); i++){
        string streamTitle = this->streams[i]->getTitle();
        transform(streamTitle.begin(), streamTitle.end(), streamTitle.begin(), ::toupper);
        if(streamTitle.find(title) != string::npos){   // check string::npos on hover
            ans.push_back(this->streams[i]);
        }
    }
    return ans;
}

std::vector<Stream *> StreamZ::searchStreams(std::string language) const {
    std::vector<Stream *> ans;
    transform(language.begin(), language.end(), language.begin(), ::toupper);
    for(int i = 0; i < this->streams.size(); i++){
        string streamLanguage = this->streams[i]->getLanguage();
        transform(streamLanguage.begin(), streamLanguage.end(), streamLanguage.begin(), ::toupper);
        if( streamLanguage == language )
            ans.push_back(this->streams[i]);
    }
    return ans;
}

std::vector<Stream*> StreamZ::searchStreams(int viewerAge) const {
    std::vector<Stream *> ans;
    for(int i = 0; i < this->streams.size(); i++){
        if( viewerAge >= this->streams[i]->getMinAge() )
            ans.push_back(this->streams[i]);
    }
    return ans;
}


void StreamZ::listStreams(std::vector<Stream *> streams) const {
    for (int i = 0; i < streams.size(); ++i){
        cout << i + 1 << "- ";
        streams.at(i)->showStream();
        cout << endl;
    }
}

void StreamZ::listUsers() const {
    map<unsigned int, User*>::const_iterator it;
    for (it = users.begin(); it != users.end(); ++it){
        it->second->showUser();
        cout << endl;
    }
}

void StreamZ::listUsers(const std::set<unsigned int>& users) const {
    for (set<unsigned int>::iterator it = users.begin(); it != users.end(); ++it){
        this->users.at((*it))->showUser();
        cout << endl;
    }
}

void StreamZ::showStreamHistory(int id) const {
    set<unsigned int> history = users.at(id)->getStreamHistory();
    if (history.empty()){
        cout << "No streams in " << users.at(id)->getNick() << "'s history" << endl;
        return;
    }
    set<unsigned int>::iterator it;
    for (it = history.begin(); it != history.end(); ++it){
        cout << endl << pastStreams.at(*it)->name << endl;
        int noViewers = pastStreams.at(*it)->noViewers;
        if (noViewers == - 1)
            cout << "Stream is still active" << endl;
        else
            cout << "Ended with " << noViewers << " viewers" << endl;
    }
    cout << endl;
}