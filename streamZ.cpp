#include <iostream>
#include <fstream>
#include <vector>

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
    cout << "What do you want to do?" << endl << endl
        << "1- Search streams" << endl << "2- Show top Streams" << endl
        << "3- Show all streams" << endl << "4- Show all users" << endl << "5- Go back" << endl;
    int choice;
    cin >> choice;
    switch (choice) {
        case 1:

            break;
        case 2:

            break;
        case 3:

            break;
        case 4:

            break;
        case 5:
            return;
    }
}

void StreamZ::streamerMenu() {
    cout << "What do you want to do?" << endl << endl
        << "1- Start Stream" << endl << "2- Go back" << endl;
    int choice;
    cin >> choice;
    switch (choice) {
        case 1:
            Stream s(title, startDate, language, minAge);
            break;
        case 2:
            return;
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

void StreamZ::adminMenu2() {


}


void StreamZ::createViewer() {
    cout<< "Creating Viewer ..." <<endl<<endl;
    cout << "Insert your name: " <<endl;
    string name;
    cin >> name;
    cout << "Insert your nickname: " << endl;
    string nickname;
    cin >> nickname;
    cout << "Insert your birthdate: " << endl;
    string birthdate;
    cin >> birthdate;
    Date d(birthdate); //construtor com string
    Viewer(name, nickname, d);
}

void StreamZ::createStreamer() {
    cout<< "Creating Streamer ..." <<endl<<endl;
    cout << "Insert your name: " <<endl;
    string name;
    cin >> name;
    cout << "Insert your nickname: " << endl;
    string nickname;
    cin >> nickname;
    cout << "Insert your birthdate: " << endl;
    string birthdate;
    cin >> birthdate;
    Date d(birthdate); //construtor com string
    Viewer(name, nickname, d);
}

void StreamZ::createAdmin() {
    cout<< "Creating Admin ..." <<endl<<endl;
    cout << "Insert admin's name: " <<endl;
    string name;
    cin >> name;
    Admin A(name, users, streams);
}