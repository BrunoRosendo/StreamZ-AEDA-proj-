#include <iostream>
#include <fstream>
#include <vector>

#include "streamZ.h"
#include "streamHistory.h"
#include "date.h"
#include "user.h"

using namespace std;

/**
 * StreamZ class constructor
 */
StreamZ::StreamZ() {
    if( fetchDataFromFile() != 0 ) {
        cout << "Error fetching data from file!" << endl;
    }
}

/**
 * Reads data from files that contains the registered users, created streams, etc.
 * @return returns 0 on success, 1 otherwise
 */
int StreamZ::fetchDataFromFile() {
    string streamersFile = "streamers.txt";
    string viewersFile = "viewers.txt";
    string streamsFile = "streams.txt";
    string adminFile = "admin.txt";
    fstream fin;
    //IMPLEMENT VIEWERS FILE FIRST

    fin.open(viewersFile);
    if(!fin.is_open()){
        cout << "Couldn't open " << viewersFile << " file!" << endl;
        return 1;
    }

    // implement

    fin.close()

    fin.open(streamersFile);
    if(!fin.is_open()){
        cout << "Couldn't open " << streamersFile << " file!" << endl;
        return 1;
    }
    string line, line2, name, nick, date;
    vector<string> subscribers;
    vector<struct streamHistory> pastStreams;
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
                    struct streamHistory s;
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
                    streamer.setStreamerhistory(pastStreams);
                    streamer.setSubscribers(subscribers);

                }
        }
    }
    fin.close();


    return 0;
}