#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

#include "streamZ.h"
#include "pastStream.h"
#include "date.h"
#include "user.h"
#include "admin.h"

using namespace std;

/**
 * StreamZ class constructor
 */
/*StreamZ::StreamZ() {
    try{
        fetchDataFromFile();
    }
    catch(runtime_error& e){
        cerr << e.what() << endl;
    }
}
 */

/**
 * Reads data from files that contains the registered users, created streams, etc.
 * @return returns 0 on success, 1 otherwise
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
                viewerMenu();
                break;
            case 2:
                streamerMenu();
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

void StreamZ::streamerMenu() {
    while(1){
        cout << "What do you want to do?" << endl << endl
             << "1- Start Stream" << endl << "2- Go back" << endl;
        int choice;
        cin >> choice;
        Stream* newStream;
        switch(choice){
            case 1:
                string title, language;
                Date startDate = Date();        //curr date
                int minAge, typeOfStream, capacity;
                cout << "What is the title of the stream?" << endl;
                cin >> title;
                cout << "What language is the stream on?" << endl;
                cin >> language;
                cout << "What is the minimum age?" << endl;
                cin >> minAge;
                cout << "Will it be a public(1) or private(2) stream?" << endl;
                if(typeOfStream == 1)
                    newStream = new PublicStream(title, startDate, language, minAge);
                else{
                    cout << "What will be the maximum capacity for this stream?" << endl;
                    cin >> capacity;
                    //newStream = new PrivateStream(title, startDate, language, minAge, this->users[0]->, capacity) ;   // set of subscribers
                }
            case 2:
                return;
        }
    }
}

void StreamZ::adminMenu() {
    Admin A;
    cout << "Welcome admin" << endl << endl;

    cout << "Total number of Streams created: " << A.getNumStreams() << endl <<endl;

    cout << "Number of Public Streams created: " << A.getNumPublicStreams() <<endl<<endl;

    cout << "Number of Private Streams created: " << A.getNumPrivateStreams() <<endl<<endl;

    cout << "Average stream views: " << A.getAvgViews() <<endl<<endl;

    cout << "Most common stream language is " << A.getPreferredLanguage(streams) <<endl<<endl;

    cout << "Most common stream type is " << A.getPreferredStreamType() <<endl<<endl;

    cout << "Most viewed streamer: " << A.getMostViewedStreamer() <<endl<<endl;

    cout << "More stats?" << endl << endl
         << "1- Number of Streams created (interval)" << endl
         << "2- Number of Public Streams created (interval)" << endl
         << "3- Number of Private Streams created (interval)" << endl
         << "4- Average stream views (interval)" << endl
         << "5- Go back" << endl;
    int choice;
    cin >>choice;
    switch (choice) {
        case 1: //passar isto pro menu seguinte adminMenu2()
            cout << "Start date: " << endl;
            string from;
            cin >> from;
            Date f(from);
            cout << "End date: " << endl;
            string to;
            cin >> to;
            Date t (to);
            cout << "Streams created from " << f.getDate() << " to " << t.getDate() << " : " << A.getNumCreatedStreams(f, t) <<endl;
            break;
        case 2:
            cout << "Start date: " << endl;
            string from;
            cin >> from;
            Date f(from);
            cout << "End date: " << endl;
            string to;
            cin >> to;
            Date t (to);
            cout << "Public Streams created from " << f.getDate() << " to " << t.getDate() << " : " << A.getNumPublicStreams(f, t) <<endl;
            break;
        case 3:
            cout << "Start date: " << endl;
            string from;
            cin >> from;
            Date f(from);
            cout << "End date: " << endl;
            string to;
            cin >> to;
            Date t (to);
            cout << "Private Streams created from " << f.getDate() << " to " << t.getDate() << " : " << A.getNumPrivateStreams(f, t) <<endl;
            break;
        case 4:
            cout << "Start date: " << endl;
            string from;
            cin >> from;
            Date f(from);
            cout << "End date: " << endl;
            string to;
            cin >> to;
            Date t (to);
            cout << "Average stream views from " << f.getDate() << " to " << t.getDate() << " : " << A.getAvgViews(f, t) <<endl;
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
    Date birthDate;
    Viewer* newViewer;
    while(1){
        try{
            cout << "Birth Date(yyyy/mm/dd):";
            cin >> birthDateString;                // NEED TO DO INPUT VERIFICATION
            Date birthDate(birthDateString);
            newViewer = new Viewer(name, nick, birthDate);
            break;
        }
        catch(DateIsNotValid &d){
            cout << d.what() << endl;
        }
        catch(NotOldEnough &n){
            cout << n.what() << endl;
        }
    }
    this->users.push_back( newViewer );
    cout << "A new Viewer was successfully created! " << endl;
}


void StreamZ::createStreamer() {
    string name, nick, birthDateString;
    cout << "Lets begin the creation of a new Streamer! " << "Please insert the following data: " << endl;
    cout << "Name:";
    cin >> name;
    cout << "Nickname:";
    cin >> nick;
    Date birthDate;
    Streamer* newStreamer;
    while(1){
        try{
            cout << "Birth Date(yyyy/mm/dd):";
            cin >> birthDateString;                // NEED TO DO INPUT VERIFICATION
            Date birthDate(birthDateString);
            newStreamer = new Streamer(name, nick, birthDate);
            break;
        }
        catch(DateIsNotValid &d){
            cout << d.what() << endl;
        }
        catch(NotOldEnough &n){
            cout << n.what() << endl;
        }
    }

    this->users.push_back( newStreamer );
    cout << "A new Streamer was successfully created! " << endl;
}

void StreamZ::createAdmin() {
    string name;
    cout << "Lets begin the creation of a new Admin! " << "Please insert the following data: " << endl;
    cout << "Name:";
    cin >> name;

    this->admins.push_back( new Admin(name, this->users, this->streams) );
    cout << "A new Admin was successfully created! " << endl;
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

std::vector<Stream*> StreamZ::searchStreamsByTitle(std::string title) {
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

void StreamZ::showTopStreams() {
    for(int i = 0; i < 10; i++){        //ASSUMES THAT THE STREAMS VECTOR IS ORDERED BY NUM OF VIEWERS
        cout << i+1 << "º " << this->streams[i];
    }
}
