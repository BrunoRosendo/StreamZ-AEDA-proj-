#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <map>
#include <algorithm>

#include "streamZ.h"
#include "pastStream.h"
#include "date.h"
#include "user.h"
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
    admin = NULL;
}


/**
 * Reads data from files that contains the registered users, created streams, etc.
 */
/*void StreamZ::fetchDataFromFile() {
    string streamersFile = "streamers.txt";
    string viewersFile = "viewers.txt";
    string streamsFile = "streams.txt";
    string adminFile = "admin.txt";
    fstream fin;
    //IMPLEMENT VIEWERS FILE FIRST

    fin.open(viewersFile);
    if(!fin.is_open()){
        //cout << "Couldn't open " << viewersFile << " file!" << endl;
        throw runtime_error("Couldn't open" + viewersFile + " file!");
    }

    // implement

    fin.close();

    fin.open(streamersFile);
    if(!fin.is_open()){
        cout << "Couldn't open " << streamersFile << " file!" << endl;
    }
    string line, line2, name, nick, date;
    vector<string> subscribers;
    vector<struct PastStream> pastStreams;
    int counter = 0;
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
            default:
                if(line[0] == '*'){     //stream history member
                    getline(fin, line2);
                    struct PastStream s;
                    s.name = line, s.noViewers = stoi(line2);
                    pastStreams.push_back(s);
                }
                else if(line[0] == '/'){    //subscriber (nick)
                    subscribers.push_back(line);
                }
                else{                      // transition to new streamer
                    // create object of class Date with the string date
                    Date birthDate;
                    Streamer streamer(name, nick, birthDate);
                    streamer.setStreamHistory(pastStreams);
                    streamer.setSubscribers(subscribers);

                }
        }
    }
    fin.close();
}
*/

void StreamZ::init(){ //prototipo, so para mostrar a ideia
    while (1) {
        cout << "WELCOME TO STREAMZ" << endl << endl;
        cout << "1- Create Viewer" << endl << "2- Create Streamer" << endl << "3- Create Admin" << endl
             << "4- Login as User" << endl << "5- Login as Admin" << endl << "6- Exit" << endl;
        int choice;
        cin >> choice;
        switch (choice) {
            case 1:
                createViewer();
                break;
            case 2:
                createStreamer();
                break;
            case 3:
                createAdmin();
                break;
            case 4:
                userMenu();
                break;
            case 5:
                adminMenu();
                break;
            case 6:
                return;
            default:
                cout << "That is not a valid choice. Please enter a number from 1-6" << endl;
                continue;
        }
    }
}

void StreamZ::userMenu() {  // Depois vai ter de escolher o user que é
    while (1) {
        cout << "Which type of user are you?" << endl << endl   // "Select type of user:" *FICA MELHOR TALVEZ*
             << "1- Viewer" << endl << "2- Streamer" << endl << "3- Go back" << endl;
        int choice;
        cin >> choice;
        switch (choice) {
            case 1:
                //viewerMenu();   // IT NEEDS TO CHOOSE THE USER
                break;
            case 2:
                //streamerMenu();
                break;
            case 3:
                return;
        }
    }
}

void StreamZ::viewerMenu() {
    while(1){
        cout << "What do you want to do?" << endl << endl
             << "1- Search streams" << endl << "2- Show top Streams" << endl
             << "3- Show all streams" << endl << "4- Show all users" << endl << "5- Go back" << endl;
        int choice;
        cin >> choice;
        switch(choice){
            case 1:
                searchStreamsMenu();
            case 2:
                showTopStreams();
            case 3:
                //this->listStreams(this->streams);
            case 4:
                //this->listUsers();  // NOT SURE IF THIS ONE IS SUPPOSED TO EXIST
            case 5:
                return;

        }
    }
}

void StreamZ::streamerMenu(int id) {
    while(1){
        cout << "What do you want to do?" << endl << endl
             << "1- Start Stream" << endl << "2- Go back" << endl;
        int choice;
        cin >> choice;
        switch(choice){
            case 1: {
                createStream( (Streamer*) users[id]);
            }
            case 2:
                return;
        }
    }
}

void StreamZ::adminMenu() {
    cout << "Welcome admin" << endl << endl;

    cout << "Total number of Streams created: " << admin->getNumStreams() << endl <<endl;

    cout << "Number of Public Streams created: " << admin->getNumPublicStreams() <<endl<<endl;

    cout << "Number of Private Streams created: " << admin->getNumPrivateStreams() <<endl<<endl;

    cout << "Average stream views: " << admin->getAvgViews() <<endl<<endl;

    cout << "Most common stream language is " << admin->getPreferredLanguage(streams) <<endl<<endl;

    cout << "Most common stream type is " << admin->getPreferredStreamType() <<endl<<endl;

    cout << "Most viewed streamer: " << admin->getMostViewedStreamer() <<endl<<endl;

    cout << "More stats?" << endl << endl
         << "1- Number of Streams created (interval)" << endl
         << "2- Number of Public Streams created (interval)" << endl
         << "3- Number of Private Streams created (interval)" << endl
         << "4- Average stream views (interval)" << endl
         << "5- Go back" << endl;
    int choice;
    cin >>choice;
    string from;
    string to;
    cout << "Start date: " << endl;
    cin >> from;
    Date f(from);
    cout << "End date: " << endl;
    cin >> to;
    Date t (to);
    switch (choice) {
        case 1: //passar isto pro menu seguinte adminMenu2()
            cout << "Streams created from " << f.getDate() << " to " << t.getDate() << " : "
                << admin->getNumCreatedStreams(f, t) << endl;
            break;
        case 2:
            cout << "Public Streams created from " << f.getDate() << " to " << t.getDate() << " : "
                << admin->getNumPublicStreams(f, t) <<endl;
            break;
        case 3:
            cout << "Private Streams created from " << f.getDate() << " to " << t.getDate() << " : "
                << admin->getNumPrivateStreams(f, t) << endl;
            break;
        case 4:
            cout << "Average stream views from " << f.getDate() << " to " << t.getDate() << " : "
                << admin->getAvgViews(f, t) << endl;
            break;
        case 5:
            return;
    }
}


void StreamZ::createViewer() {
    string name, nick, birthDateString;
    cout << "Lets begin the creation of a new Viewer! " << "Please insert the following data: " << endl;
    cout << "Name:";
    cin >> name;
    cout << "Nickname:";
    cin >> nick;
    while(1){
        try{
            cout << "Birth Date(yyyy/mm/dd):";
            cin >> birthDateString;                // NEED TO DO INPUT VERIFICATION
            Date birthDate(birthDateString);
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
            cout << n.what() << endl;
        }
    }
}


void StreamZ::createStreamer() {
    string name, nick, birthDateString;
    cout << "Lets begin the creation of a new Streamer! " << "Please insert the following data: " << endl;
    cout << "Name:";
    cin >> name;
    cout << "Nickname:";
    cin >> nick;
    while(1){
        try{
            cout << "Birth Date(yyyy/mm/dd):";
            cin >> birthDateString;                // NEED TO DO INPUT VERIFICATION
            Date birthDate(birthDateString);
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
            cout << n.what() << endl;
        }
    }
}

void StreamZ::createAdmin() {
    string name;
    cout << "Lets begin the creation of a new Admin! " << "Please insert the following data: " << endl;
    cout << "Name:";
    cin >> name;
    admin = new Admin(name, streams, publicStreams, privateStreams);
    cout << "A new Admin was successfully created! " << endl;
}

void StreamZ::createStream(Streamer *streamer) {
    string title, language;
    Date startDate = Date();        //curr date
    int minAge, typeOfStream, capacity;
    bool error = true;
    while (error) {
        cout << "What is the title of the stream?" << endl;
        cin >> title;
        cout << "What language is the stream on?" << endl;
        cin >> language;
        cout << "What is the minimum age?" << endl;
        cin >> minAge;
        cout << "Will it be a public(1) or private(2) stream?" << endl;
        cin >> typeOfStream;
        switch (typeOfStream) {
            case 1: {
                try {
                    PublicStream *newStream = new PublicStream(title, startDate, language, minAge);
                    streamer->startStream(newStream);
                    streams.push_back(newStream);
                    publicStreams.push_back(newStream);
                    error = false;
                    break;
                }
                catch (AlreadyStreaming &e) {
                    cout << e.what() << endl;
                    error = true;   // desnecessario?
                    break;
                }
            }
            case 2:{
                try{
                    int capacity;
                    cout << "What will be its capacity?" << endl;
                    cin >> capacity;
                    PrivateStream *newStream = new PrivateStream(title, startDate, language, minAge, streamer->getSubscribers(), capacity);
                    streamer->startStream(newStream);
                    streams.push_back(newStream);
                    privateStreams.push_back(newStream);
                    error = false;
                    break;
                }
                catch (AlreadyStreaming& e){
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
            PastStream* p = new PastStream;
            p->name = stream->getTitle();
            p->noViewers = stream->getNumViewers();
            streamer->endStream();
            streamer->addPastStream(p);
            set<unsigned int> viewers = stream->getViewers();
            for (set<unsigned int>::iterator it = viewers.begin(); it != viewers.end(); ++it){
                users[(*it)]->addPastStream(p);
            }
            streams.erase(find(streams.begin(), streams.end(), stream));
            vector<PublicStream*>::iterator it = find(publicStreams.begin(), publicStreams.end(), stream);
            if (it != publicStreams.end()) publicStreams.erase(it);
            else privateStreams.erase(find(privateStreams.begin(), privateStreams.end(), stream));
            break;
        }
        catch (NotInAStream &e) {
            cout << e.what() << endl;
        }
    }
}


void StreamZ::searchStreamsMenu() {
    int choice1;
    std::string choice2;
    int ageChoice;
    std::vector<Stream*> filteredStreams;
    while(1){
        cout << "Search streams by: " << endl << "1- Title\n2- Language\n3- Minimum Age\n4- Exit\n";  //Possibly add a category to streams
        cin >> choice1;
        switch(choice1){
            case 1:
                cout << "Insert the Title:" << endl;
                cin >> choice2;
                filteredStreams = this->searchStreamsByTitle(choice2);
                for(int i = 0; i < filteredStreams.size(); i++)
                    cout << *(filteredStreams[i])<< endl;
                // joining a stream needs to be done
            case 2:
                cout << "What language are you looking for?" << endl;
                cin >> choice2;
                filteredStreams = this->searchStreams(choice2);
                for(int i = 0; i < filteredStreams.size(); i++)
                    cout << *(filteredStreams[i]) << endl;
                //joining a stream needs to be done. Maybe could merge this and the one on top
            case 3:
                cout << "What is the minimum age?" << endl;
                cin >> ageChoice;
                filteredStreams = this->searchStreams(ageChoice);
                for(int i = 0; i < filteredStreams.size(); i++)
                    cout << *(filteredStreams[i]) << endl;
                //joining a stream needs to be done. Maybe could merge this and the one on top
            case 4:
                return;
        }
    }
}

std::vector<Stream*> StreamZ::searchStreamsByTitle(std::string title) { // USE A BETTER ALGORITHM?
    std::vector<Stream *> ans;
    for(int i = 0; i < this->streams.size(); i++){
        if(this->streams[i]->getTitle().find(title) != string::npos){   // check string::npos on hover
            ans.push_back(this->streams[i]);
        }
    }
    return ans;
}

std::vector<Stream *> StreamZ::searchStreams(std::string language) const {
    std::vector<Stream *> ans;
    for(int i = 0; i < this->streams.size(); i++){
        if( this->streams[i]->getLanguage() == language )
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

void StreamZ::showTopStreams() {    // add sort functions
    for(int i = 0; i < 10; i++){        //ASSUMES THAT THE STREAMS VECTOR IS ORDERED BY NUM OF VIEWERS
        cout << i+1 << "º ";
        this->streams[i]->showStream();
        cout << endl;
    }
}
