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

StreamZ::~StreamZ() {
    //storeDataInFile();    // uncomment when function is done
    delete admin;
    for (int i = 0; i < streams.size(); ++i)
        delete streams.at(i);
    map<unsigned int, User*>::iterator it;
    for (it = users.begin(); it != users.end(); ++it)
        delete it->second;
}

/**
 * Reads data from files that contains the registered users, created streams, etc.
 */

void StreamZ::fetchDataFromFile() {
    string streamersFile = "streamers.txt";
    string viewersFile = "viewers.txt";
    string streamsFile = "streams.txt";
    string pastStreamsFile = "pastStreams.txt";
    string adminFile = "admin.txt";
    fstream fin;
    string line, line2, name, nick, date;
    unsigned int id, pastStreamId;
    //vector<struct PastStream> pastStreams;
    std::set<unsigned int> pastStreams;
    int counter = 0;
    //IMPLEMENT VIEWERS FILE FIRST

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
                    /*
                    getline(fin, line2);
                    struct PastStream s;
                    s.name = line, s.noViewers = stoi(line2);
                     */
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
    string line3;
    if(!fin.is_open()){
        cout << "Couldn't open " << streamsFile << " file!" << endl;
        throw runtime_error("Couldn't open " + streamsFile + " file!");
    }
    while(getline(fin, line )) {
        getline(fin, line2);    // id
        getline(fin, line3);    // no_viewers when stream ended
        id = stoi(line2);
        struct PastStream* s = new PastStream;          // !! VERIFY WHEN YOU NEED TO FREE THIS MEMORY
        s->name = line, s->id = id, s->noViewers = stoi(line3);
        this->pastStreams.insert({id, s});
    }
    fin.close();

}


void StreamZ::init(){ //prototipo, so para mostrar a ideia
    while (1) {
        cout << "WELCOME TO STREAMZ" << endl << endl;
        cout << "1- Create Viewer" << endl << "2- Create Streamer" << endl;
        if (admin == NULL) cout << "3- Create Admin";
        else cout << "3- Login as Admin";
        cout << endl << "4- Login as User" << endl << "5- Exit" << endl;
        int choice;
        cin >> choice;
        cin.ignore(100, '\n');
        switch (choice) {
            case 1:
                createViewer();
                break;
            case 2:
                createStreamer();
                break;
            case 3:
                if (admin == NULL) createAdmin();
                else adminMenu();
                break;
            case 4:
                userMenu();
                break;
            case 5:
                return;
            default:
                cout << "That is not a valid choice. Please enter a valid number" << endl;
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
        cin.ignore(100, '\n');
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
                cout << "Choose a value between 1 and 3" << endl;
                continue;
        }
    }
}

void StreamZ::loginViewer() {
    if (viewersNickID.size() == 0){
        cout << "Create an account before trying to login" << endl;
        system("pause");
        return;
    }
    cout << "Please type the nickname of your account: ";
    int id;
    while (1) {
        string nick;
        getline(cin, nick);
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
    if (streamersNickID.size() == 0){
        cout << "Create an account before trying to login" << endl;
        system("pause");
        return;
    }
    cout << "Please type the nickname of your account: ";
    int id;
    while (1) {
        string nick;
        getline(cin, nick);
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
    while(1){
        if (v->inAStream()) return;
        cout << "What do you want to do?" << endl << endl
             << "1- Search streams" << endl << "2- Show top viewed streams" << endl << "3- Show top liked streams"
             << endl << "4- List all streams" << endl << "5- List all users" << endl << "6- Go back" << endl;
        int choice;
        cin >> choice;
        cin.ignore(100, '\n');
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
            case 4:
                this->listStreams(this->streams);
                joinStream(id, this->streams);
                break;
            case 5:
                this->listUsers();
                break;
            case 6:
                return;
            default:
                cout << "Enter a valid number" << endl;
        }
        if (v->inAStream()) watchingOptions(id);
    }
}

void StreamZ::joinStream(int id, vector<Stream*> filteredStreams) {
    if (filteredStreams.size() == 0){
        cout << "No streams to join" << endl;
        return;
    }
    cout << "Type the number of the stream you want to join (0 if you don't want any): ";
    int num;
    while (1) {
        cin >> num;
        cin.ignore(100, '\n');
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
    catch(noCapacity& e){
        cout << e.what() << endl;
    }
    catch (NotSubscribed& e){
        cout << e.what() << endl;
    }
    catch (AlreadyStreaming& e){
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
        cout << endl << "4- Leave stream" << endl<< "5- Go back" << endl;
        int choice;
        cin >> choice;
        cin.ignore(100, '\n');
        switch (choice) {
            case 1:
                cout << "Type 1 to like and 2 to dislike: ";
                int like, megaLikezao;
                cin >> like;
                cin.ignore(100, '\n');
                if (like == 1) megaLikezao = 1;
                else megaLikezao = -1;
                v->feedback(megaLikezao);
                break;
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
            case 5:
                return;
        }
    }
}

void StreamZ::streamerMenu(int id) {
    while(1) {
        cout << "What do you want to do?" << endl << endl << "1- Search streams" << endl
             << "2- List all streams" << endl << "3- List all users" << endl << "4- Show top viewed streams" << endl
             << "5- Show top liked streams " << endl << "6- Show number of subscribers" << endl << "7- List subscribers"
             << endl << "8- Streaming options" << endl << "9- Go back" << endl;
        int choice;
        cin >> choice;
        cin.ignore(100, '\n');
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
                cout << "You currently have " << s->getNumSubs() << " subscribers" << endl;
                break;
            }
            case 7: {
                Streamer *s = (Streamer *) users[id];
                set<unsigned int> subs = s->getSubscribers();
                listUsers(subs);
                break;
            }
            case 8:
                streamingOptions(id);
                break;
            case 9:
                return;
            default:
                cout << "Please enter a valid number" << endl;
        }
    }
}

void StreamZ::streamingOptions(int id) {
    Streamer* s = (Streamer*) users.at(id);
    while (1){
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
        cin.ignore(100, '\n');
        switch (c) {
            case 1:
                cout << "You currently have " << s->getNumViewers() << " viewers" << endl;
                system("pause");
                break;
            case 2:
                cout << "You currently have " << s->getStream()->getNoLikes() << " likes" << endl;
                system("pause");
                break;
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
    cout << "Welcome admin" << endl << endl;

    cout << "Total number of Streams created: " << admin->getNumStreams() << endl <<endl;

    cout << "Number of Public Streams created: " << admin->getNumPublicStreams() <<endl<<endl;

    cout << "Number of Private Streams created: " << admin->getNumPrivateStreams() <<endl<<endl;
    try {
        float views = admin->getAvgViews();
        cout << "Average stream views: " << views << endl << endl;

        cout << "Most common stream language is " << admin->getPreferredLanguage(streams) << endl << endl;

        cout  << admin->getPreferredStreamType() << endl << endl;

        cout << "Most viewed streamer: " << admin->getMostViewedStreamer()->getNick() << endl << endl;
    }
    catch(noActiveStreams& e){
        cout << e.what() << endl;
    }
    while(1) {
        cout << "More stats?" << endl << endl
             << "1- Number of Streams created (interval)" << endl
             << "2- Number of Public Streams created (interval)" << endl
             << "3- Number of Private Streams created (interval)" << endl
             << "4- Average stream views (interval)" << endl
             << "5- Go back" << endl;
        int choice;
        cin >> choice;
        cin.ignore(100, '\n');
        if (choice == 5) return;
        string from;
        string to;
        cout << "Start date: " << endl;
        cin >> from;
        Date f(from);
        cout << "End date: " << endl;
        cin >> to;
        Date t(to);
        try {
            switch (choice) {
                case 1: { //passar isto pro menu seguinte adminMenu2()
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
                case 5:
                    return;
            }
        }
        catch(badDateComp& e){
            cout << e.what() << endl;
        }
        catch(noActiveStreams& e){
            cout << e.what() << endl;
        }
    }
}


void StreamZ::createViewer() {
    string name, nick, birthDateString;
    cout << "Lets begin the creation of a new Viewer! " << "Please insert the following data: " << endl;
    cout << "Name: ";
    getline(cin, name);
    cout << "Nickname: ";
    while (1) {
        getline(cin, nick);
        if (viewersNickID.find(nick) != viewersNickID.end()){
            cout << "That nickname is already taken. Choose another one: ";
            continue;
        }
        break;
    }
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
    cout << "Name: ";
    getline(cin, name);
    cout << "Nickname: ";
    while (1) {
        getline(cin, nick);
        if (streamersNickID.find(nick) != streamersNickID.end()){
            cout << "That nickname is already taken. Choose another one: ";
            continue;
        }
        break;
    }
    while(1){
        try{
            cout << "Birth Date(yyyy/mm/dd): ";
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
    cout << "Name: ";
    getline(cin, name);
    admin = new Admin(name, *this);
    cout << "A new Admin was successfully created! " << endl;
}

void StreamZ::createStream(Streamer *streamer) {
    string title, language;
    Date startDate = Date();        //curr date
    int minAge, typeOfStream;
    bool error = true;
    while (error) {
        cout << "What is the title of the stream?" << endl;
        getline(cin, title);
        cout << "What language is the stream on?" << endl;
        cin >> language;
        cout << "What is the minimum age?" << endl;
        cin >> minAge;
        cout << "Will it be a public(1) or private(2) stream?" << endl;
        cin >> typeOfStream;
        cin.ignore(100, '\n');
        switch (typeOfStream) {
            case 1: {
                try {
                    PublicStream *newStream = new PublicStream(title, startDate, language, minAge, streamer->getNick());
                    streamer->startStream(newStream);
                    streams.push_back(newStream);
                    publicStreams.push_back(newStream);

                    struct PastStream* pastStream = new PastStream(newStream);      //add a past stream to the global map
                    this->pastStreams.insert({newStream->getId(), pastStream});     //no_viewers has a default value of 0

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
                    cin.ignore(100, '\n');
                    PrivateStream *newStream = new PrivateStream(title, startDate, language, minAge, streamer->getNick(), streamer->getSubscribers(), capacity);
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
            /*
            PastStream* p = new PastStream;
            p->name = stream->getTitle();
            p->noViewers = stream->getNumViewers();
            streamer->addPastStream(p);
             */
            this->pastStreams.at(stream->getId())->noViewers = stream->getNumViewers();
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
            break;
        }
        catch (NotInAStream &e) {
            cout << e.what() << endl;
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


vector<Stream*> StreamZ::searchStreamsMenu() {
    int choice1;
    std::string choice2;
    int ageChoice;
    std::vector<Stream*> filteredStreams;
    while(1){
        cout << "Search streams by: " << endl << "1- Title\n2- Language\n3- Minimum Age\n4- Exit\n";  //Possibly add a category to streams
        cin >> choice1;
        cin.ignore(100, '\n');
        switch(choice1){
            case 1:
                cout << "Insert the Title: " << endl;
                getline(cin, choice2);
                filteredStreams = this->searchStreamsByTitle(choice2);
                for(int i = 0; i < filteredStreams.size(); i++)
                    cout << i+1 << "- " << *(filteredStreams[i])<< endl;
                break;
            case 2:
                cout << "What language are you looking for?" << endl;
                cin >> choice2;
                cin.ignore(100, '\n');
                filteredStreams = this->searchStreams(choice2);
                for(int i = 0; i < filteredStreams.size(); i++)
                    cout << i+1 << "- " << *(filteredStreams[i]) << endl;
                break;
            case 3:
                cout << "What is the minimum age?" << endl;
                cin >> ageChoice;
                cin.ignore(100, '\n');
                filteredStreams = this->searchStreams(ageChoice);
                for(int i = 0; i < filteredStreams.size(); i++)
                    cout << i+1 << "- " << *(filteredStreams[i]) << endl;
                break;
            case 4:
                return filteredStreams;
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

void StreamZ::listUsers(std::set<unsigned int> users) const {
    for (set<unsigned int>::iterator it = users.begin(); it != users.end(); ++it){
        this->users.at((*it))->showUser();
        cout << endl;
    }
}