//
// Created by joaog on 10/23/2020.
//

#ifndef PROJETO1_USER_H
#define PROJETO1_USER_H

#include <string>
#include <vector>
#include <set>
#include "date.h"
#include "stream.h"
#include "pastStream.h"

using namespace std;

/**
 * @brief Abstract class for a user of the website
 */
class User{
protected:
    std::string name;
    std::string nick;
    Date birthDate;
    Stream* stream;
    std::set<unsigned int> streamHistory;
    unsigned int ID;
    static unsigned int nextID;
public:

    /**
     * @brief Creates a User with given name, nick and birthdate; stream is initialized with nullptr
     * @param name Name of the user
     * @param nick Nickname of the user
     * @param birthDate Birthdate of the user
     */
    User(const std::string& name, const std::string& nick, const Date& birthDate);

    /**
     * @brief Creates a User with given name, nick, birthdate and ID. Useful when reading from files;
     * stream is initialized with nullptr
     * @param name Name of the user
     * @param nick Nickname of the user
     * @param birthDate Birthdate of the user
     * @param id ID of the user
     */
    User(const std::string& name, const std::string& nick, const Date& birthDate, unsigned int id);

    /**
     * @brief Default destructor of the base class User
     */
    virtual ~User();

    /**
     * @brief Sets the stream history of the user (either streamed or watched)
     * @param pastStreams Set including the IDs of the past streams
     */
    void setStreamHistory(std::set<unsigned int>& pastStreams);

    /**
     * @brief Updates the name of the user
     * @param name Name of the user
     */
    void setName(const std::string& name);

    /**
     * @brief Updates the nickname of the user
     * @param nick Nickname of the user
     */
    void setNick(const std::string& nick);

    /**
     * @brief Gets the name of the user
     * @return String containing the name of the user
     */
    std::string getName() const;

    /**
     * @brief Gets the nickname of the user
     * @return String containing the nickname of the user
     */
    std::string getNick() const;

    /**
     * @brief Gets the age of the user
     * @return Integer containing the age of the user
     */
    int getAge() const;

    /**
     * @brief Gets the age of the user as a string
     * @return String containing the age of the user
     */
    string getAgeString() const;

    /**
     * @brief Gets the ID of user
     * @return Unsigned int containing the ID of the user
     */
    unsigned int getID() const;

    /**
     * @brief Gets the pointer to the stream of the user (either streaming or watching). Throws NotInAStream exception
     * if the user isn't in one
     * @return Stream* of the user's stream
     */
    Stream* getStream() const;

    /**
     * @brief Checks if the user is currently in a stream (either streaming or watching)
     * @return Returns true if the user is in a stream and false otherwise
     */
    bool inAStream() const;

    /**
     * @brief Gets the stream history of the user (either streamed or watched)
     * @return Set containing the IDs of the past streams
     */
    std::set<unsigned int>& getStreamHistory();

    /**
     * @brief Prints the user's information to the standard output
     */
    virtual void showUser() const = 0;
};

/**
 * @brief Derived class of the class User, representing a streamer of the website
 */
class Streamer : public User{
private:
    std::set<unsigned int> subscribers;
public:

    /**
     * @brief Creates a Streamer with given name, nick and birthdate. The ID is set to nextID and increments it.
     * Throws NotOldEnough exception if the user is younger than 15. Also see User()
     * @param name Name of the streamer
     * @param nick Nickname of the streamer
     * @param birthDate Birthdate of the streamer
     */
    Streamer(const std::string& name, const std::string& nick, const Date& birthDate);

    /**
     * @brief Creates a Streamer with given name, nick, birthdate and ID. Doesn't increment nextID.
     * Throws NotOldEnough exception if the user is younger than 15. Also see User()
     * @param name Name of the streamer
     * @param nick Nickname of the streamer
     * @param birthDate Birthdate of the streamer
     * @param id ID of the streamer
     */
    Streamer(const std::string& name, const std::string& nick, const Date& birthDate, unsigned int id);

    /**
     * @brief Default destructor of the derived class Streamer
     */
    virtual ~Streamer();

    /**
     * @brief Gets the number of viewers currently on the streamer's stream. Throws NotInAStream exception
     * if he isn't streaming
     * @return Integer containing the number of viewers
     */
    int getNumViewers() const;

    /**
     * @brief Gets the number of viewers subscribed to the streamer
     * @return Integer containing the number of subscribers
     */
    int getNumSubs() const;

    /**
     * @brief Gets the set of viewers subscribed to the streamer
     * @return Set containing the IDs of the subscribers
     */
    std::set<unsigned int>& getSubscribers();

    /**
     * @brief Ends the stream. Throws NotInAStream exception if the streamer is not streaming
     */
    void endStream();

    /**
     * @brief Starts a new stream. Throws AlreadyStreaming exception
     * @param stream Pointer to the stream starting
     */
    void startStream(Stream* stream);

    /**
     * @brief Sets the subscribers of the streamer
     * @param subscribers Set with the IDs of the viewers subscribed to the streamer
     */
    void setSubscribers(set<unsigned int>& subscribers);

    /**
     * @brief Adds a subscriber to the set
     * @param id ID of the new subscriber (Viewer)
     */
    void addSubscriber(unsigned int id);

    /**
     * @brief Removes a subscriber from the set
     * @param id ID of the subscriber intended to remove
     */
    void removeSubscriber(unsigned int id);

    /**
     * @brief Checks if a viewer is subscribed to the streamer
     * @param id ID of the viewer intended to check
     * @return Returns true if the viewer is subscribed and false otherwise
     */
    bool isSubscriber(unsigned int id) const;

    /**
     * @brief Prints the streamer's information to the standard output. Also see User::showUser()
     */
    virtual void showUser() const;
    friend ostream& operator<<(ostream& out, const Streamer& streamer);
};

/**
 * @brief Derived class of the class User, representing a viewer of the website
 */
class Viewer : public User{

public:
    /**
     * @brief Creates a Viewer with given name, nick and birthdate. The ID is set to nextID and increments it.
     * Throws NotOldEnough exception if the user is younger than 12. Also see User()
     * @param name Name of the viewer
     * @param nick Nickname of the viewer
     * @param birthDate Birthdate of the viewer
     */
    Viewer(const std::string& name, const std::string& nick, const Date& birthDate);

    /**
     * @brief Creates a Viewer with given name, nick, birthdate and ID. Doesn't increment nextID.
     * Throws NotOldEnough exception if the user is younger than 12. Also see User()
     * @param name Name of the viewer
     * @param nick Nickname of the viewer
     * @param birthDate Birthdate of the viewer
     * @param id ID of the viewer
     */
    Viewer(const std::string& name, const std::string& nick, const Date& birthDate, unsigned int id);

    /**
     * @brief Default destructor of the derived class Viewer
     */
    virtual ~Viewer();

    /**
     * @brief The viewer joins a stream. Throws AlreadyStreaming exception if the viewer is already watching a stream.
     * Throws NotOldEnough exception if the viewer is not old enough to join the stream
     * @param stream Pointer to the stream intended to join
     */
    void joinStream(Stream* stream);

    /**
     * @brief The viewer leaves the stream he is currently watching. Throws NotInAStream exception if the viewer
     * is not watching a stream
     */
    void leaveStream();

    /**
     * @brief The viewer sends a message to the streamer he's currently watching. Can only be used while in a private stream
     * Throw NotInAStream exception if the viewer is not watching a private stream
     * @param text Message the viewer wants to send to the streamer
     */
    void message(std::string text) const;

    /**
     * @brief The viewer sends feedback to the stream he's currently watching, in the form of a like or a dislike
     * @param like Value of the feedback the viewer sent. Either 1 or -1 (like or dislike)
     */
    void feedback(int like);

    /**
     * @brief Prints the viewer's information to the standard output. Also see User::showUser()
     */
    virtual void showUser() const;
    friend ostream& operator<<(ostream& out, const Viewer& viewer);
};

/**
 * @brief Prints the given streamer's information to the given output stream
 * @param out Output stream to write to
 * @param streamer Streamer whose information is going to be printed
 * @return Given output stream (out)
 */
ostream& operator<<(ostream& out, const Streamer& streamer);

/**
 * @brief Prints the given viewer's information to the given output stream
 * @param out Output stream to write to
 * @param streamer Viewer whose information is going to be printed
 * @return Given output stream (out)
 */
ostream& operator<<(ostream& out, const Viewer& viewer);


// Exceptions related to the user

/**
 * @brief Exception class which should be thrown when a user is not old enough for a certain task
 */
class NotOldEnough{
private:
    string reason;
public:

    /**
     * @brief Creates a NotOldEnough exception with a given reason
     * @param reason Reason the exception was thrown
     */
    NotOldEnough(const string& reason);

    /**
     * @brief Gets the reason of the exception
     * @return String containing the reason
     */
    string what() const;
};

/**
 * @brief Exception class which should be thrown when a user is unexpectedly not in a stream
 */
class NotInAStream{
private:
    string reason;
public:

    /**
     * @brief Creates a NotInAStream exception with a given reason
     * @param reason Reason the exception was thrown
     */
    NotInAStream(const string& reason);

    /**
     * @brief Gets the reason of the exception
     * @return String containing the reason
     */
    string what() const;
};


/**
 * @brief Exception class which should be thrown when a user is unexpectedly in a stream
 */
class AlreadyInAStream{
private:
    string reason;
public:

    /**
     * @brief Creates a AlreadyInAStream exception with a given reason
     * @param reason Reason the exception was thrown
     */
    AlreadyInAStream(const string& reason);

    /**
     * @brief Gets the reason of the exception
     * @return String containing the reason
     */
    string what() const;
};

#endif //PROJETO1_USER_H
