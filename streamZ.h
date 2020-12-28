//
// Created by joaog on 10/23/2020.
//

#ifndef PROJETO1_STREAMZ_H
#define PROJETO1_STREAMZ_H

#include "user.h"
#include "date.h"
#include "stream.h"
#include "bst.h"
#include "donation.h"
#include <unordered_map>

class Admin;    // forward declaration, in order to separate the files

/**
 * @brief Main class of the application. Manages all of the other ones, shows the menus and manipulates inputs
 */
class StreamZ{

    /**
     * @brief Class with access to the site's containers, used for statistics
     */
    friend class Admin;
private:

    /**
     * @brief Users (pointers) are stored in this map and accessed by their unique IDs
     */
    std::unordered_map<unsigned int, User*> users;  // access to users by the ID

    /**
     * @brief All the active streams (pointers) are stored in this vector
     */
    std::vector<Stream *> streams;

    /**
     * Note that a Viewer and a Streamer can have the same nickname but two Streamers/Viewers can't
     * @brief This map is used to login the Viewers, getting their ID with a nickname.
     */
    std::map<std::string, unsigned int> viewersNickID;  // use this to login

    /**
     * Note that a Viewer and a Streamer can have the same nickname but two Streamers/Viewers can't
     * @brief This map is used to login the Streamers, getting their ID with a nickname.
     */
    std::map<std::string, unsigned int> streamersNickID;

    /**
     * @brief The active public streams (pointers) are stored in this vector
     */
    std::vector<PublicStream*> publicStreams;

    /**
     * @brief The active private streams (pointers) are stored in this vector
     */
    std::vector<PrivateStream*> privateStreams;

    /**
     * @brief The pastStreams (pointers) are all stored in this map and can be accessed by their IDs
     */
    std::map<unsigned int, PastStream*> pastStreams;

    /**
     * @brief Viewer's donations to their streamers, ordered by amount and then rating
     */
    BST<Donation> donations;

    /**
     * @brief Pointer to the only Admin that can exist in the site; nullptr if the Admin doesn't exist
     */
    Admin* admin;

public:

    /**
     * @brief Reads the information from files and creates the site accordingly
     */
    StreamZ();

    /**
     * @brief Deletes the Streams, pastStreams, Users and Admin created by dynamic memory allocation
     */
    ~StreamZ();  // we need this because of dynamic memory allocation

    /**
     * @brief Creates a Streamer using user inputs
     */
    void createStreamer();

    /**
     * @brief Creates a Viewer using user input
     */
    void createViewer();

    /**
     * @brief Creates an Admin using user input
     */
    void createAdmin();

    /**
     * @brief Creates a Stream using user input and a given Streamer
     * @param streamer Streamer who will control the Stream
     */
    void createStream(Streamer* streamer);

    /**
     * @brief Creates a Donation by asking the user the amount and the rating
     * @param streamerNick Name of streamer receiving the donation
     */
    void createDonation(const string& streamerNick);

    /**
     * @brief Ends and deletes a Stream by a given Streamer. Also creates a pastStream and stores it in the User's
     * history accordingly
     * @param streamer Streamer who will end the Stream
     */
    void deleteStream(Streamer* streamer);

    /**
     * @brief Fetches data from the files and restores a previously saved state of the site
     * @throw runtime_error If the program fails to open a file
     */
    void fetchDataFromFile();

    /**
     * @brief Stores data in the files, saving the state of the site
     * @throw runtime_error If the program fails to open a file
     */
    void storeDataInFile();

    /**
     * @brief Sorts the streams vector by number of views and saves the top 10
     * @return Vector of the top 10 streams (pointers), sorted by number of views
     */
    std::vector<Stream*> topViews();

    /**
     * @brief Sorts the streams vector by number of likes and saves the top 10
     * @return Vector of the top 10 streams (pointers), sorted by number o likes
     */
    std::vector<Stream*> topLikes();

    /**
     * @brief Searches all Streams with a given language and saves them in a vector
     * @param language Language to search for
     * @return Vector of all the Streams (pointers) with the given language
     */
    std::vector<Stream*> searchStreams(std::string language) const;

    /**
     * @brief Searches all Streams with the same or less minimum age and saves them in a vector
     * @param minAge Upper bound which the Streams' minimum age can't surpass
     * @return Vector of all the Streams (pointers) with less or equal minimum age
     */
    std::vector<Stream*> searchStreams(int minAge) const;

    /**
     * @brief Prints the Streams' information in the given vector to the standard output
     * @param streams Streams to be printed
     */
    void listStreams(std::vector<Stream *> streams) const;

    /**
     * @brief Prints all the Users' information to the standard output
     */
    void listUsers() const;

    /**
     * @brief Prints all the active Users' information to the standard output
     */
    void listActiveUsers() const;

    /**
     * @brief Prints the Users' information in the set to the standard output
     * @param users Set of Users (IDs) to print
     */
    void listUsers(const std::set<unsigned int>& users) const;

    /**
     * @brief Lists the donations given to a certain Streamer
     * @param streamerName Nickname of Streamer
     */
    void listDonations(const string& streamerName) const;

    /**
     * @brief Prints the stream history of a given User
     * @param id ID of a User whose history is going to be printed
     */
    void showStreamHistory(int id) const;

    /**
     * @brief Searches all Streams with a given string included in its title and saves them in a vector
     * @param title String which should be included in the Streams' title (can either be the title itself or not)
     * @return Vector of Streams (pointers) that include the given string in the title
     */
    std::vector<Stream* > searchStreamsByTitle(std::string title) const;

    // Menus

    /**
     * The user can go to createViewer(), createStreamer(), createAdmmin(), userMenu(), adminMenu() or exit the program
     * @brief Menu in which the site starts at.
     */
    void init();

    /**
     * The user can go to userMenu(), streamerMenu() or go back to init()
     * @brief Menu in which the user can choose whether he wants to login as a viewer or as a streamer
     */
    void userMenu();

    /**
     * The viewer can give feedback (like, dislike and message, in case of a private stream), see the Stream details,
     * subscribe/unsubscribe to/from a Streamer, leave the Stream, go to viewerSettings() or go back to userMenu()
     * @brief Menu with the options while a Viewer is watching a Stream
     * @param id Viewer's ID
     */
    void watchingOptions(int id);

    /**
     * @brief Prints the Streams in the given vector and asks for the Viewer to chose one of them to join
     * @param id User's ID
     * @param streams Vector of streams to be printed (they are also the Viewer's options)
     */
    void joinStream(int id, vector<Stream*> streams);

    /**
     * The menu shows the number of Streams (public, private or either), average Stream views, the most common
     * language, the preferred stream type and the most viewed Streamer.
     * The Admin can also choose to see the number of Streams created (public, private or either) and the average views
     * for a given interval of time, as well as go to adminSettings()
     * @brief Menu which shows basic information of the site and shows all the other options for the Admin to choose from
     */
    void adminMenu();

    /**
     * The menu can return to userMenu() if the nickname doesn't exist or go to viewerMenu(), otherwise
     * @brief Asks the viewer for his nickname and logs him in the site
     */
    void loginViewer();

    /**
     * The menu can return to userMenu() if the nickname doesn't exist or go to streamerMenu(), otherwise
     * @brief Asks the streamer for his nickname and logs him in the site
     */
    void loginStreamer();

    /**
     * The viewer can list all streams, list the top viewed/liked Streams, search for Streams (searchStreamsMenu()),
     * list all Users, go to viewerSettings() or go back to userMenu().
     * If he chooses so, the viewer can go to watchingOptions() with a new Stream.
     * @brief Menu with the viewer's options, when he's not watching a Stream
     * @param id Viewer's ID
     */
    void viewerMenu(int id);

    /**
     * The streamer can list all the Streams, list the top viewed/liked Streams, search for Streams(searchStreamsMenu()),
     * list all Users, show number of subscribers, list his subscribers, go to streamingOptions(), go to
     * streamerSettings() or go back to userMenu()
     * @brief Menu with all the streamer's options
     * @param id Streamer's ID
     */
    void streamerMenu(int id);

    /**
     * If the streamer starts a new Stream, he goes to createStream(). Otherwise, he can see the number of
     * current Viewers, see the feedback or go back to streamerMenu()
     * @brief Menu in which the streamer can either start a new Stream or manage the current one
     * @param id
     */
    void streamingOptions(int id);

    /**
     * The viewer can change his name, change his nickname, delete his account,
     * see his Stream history (showStreamHistory()) or go back to viewerMenu()/watchingOptions()
     * @brief Account settings of a viewer
     * @param id Viewer's ID
     * @return Returns true if the user deleted his account and false otherwise
     */
    bool viewerSettings(int id);

    /**
     * The streamer can change his name, change his nickname, delete his account,
     * see his Stream history (showStreamHistory()) or go back to streamerMenu()
     * @brief Account settings of a streamer
     * @param id Streamer's ID
     * @return Returns true if the streamer deleted his account and false otherwise
     */
    bool streamerSettings(int id);

    /**
     * The admin can change his name, delete his account or go back to adminMenu()
     * @brief Account settings of the admin
     * @return Returns true if the admin deleted his account and false otherwise
     */
    bool adminSettings();

    /**
     * @brief The user can search Streams by title, minimum age or language
     * @return Vector of Streams (pointers) found by the user
     */
    vector<Stream*> searchStreamsMenu() const;
};

#endif //PROJETO1_STREAMZ_H
