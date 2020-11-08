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
    /**
     * @brief Name of the User
     */
    std::string name;

    /**
     * @brief Nickname of the User
     */
    std::string nick;

    /**
     * @brief Birthdate of the User
     */
    Date birthDate;

    /**
     * @brief Pointer to the Stream the User is watching; nullptr if he's not watching a Stream
     */
    Stream* stream;

    /**
     * @brief Stream history of the User. Only the IDs are stored on the set
     */
    std::set<unsigned int> streamHistory;

    /**
     * @brief ID of the User
     */
    unsigned int ID;

    /**
     * @brief ID of the next User created
     */
    static unsigned int nextID;
public:

    /**
     * @brief Creates a User with given name, nick and birthdate; stream is initialized with nullptr
     * @param name Name of the User
     * @param nick Nickname of the User
     * @param birthDate Birthdate of the User
     */
    User(const std::string& name, const std::string& nick, const Date& birthDate);

    /**
     * @brief Creates a User with given name, nick, birthdate and ID. Useful when reading from files;
     * stream is initialized with nullptr
     * @param name Name of the User
     * @param nick Nickname of the User
     * @param birthDate Birthdate of the User
     * @param id ID of the User
     */
    User(const std::string& name, const std::string& nick, const Date& birthDate, unsigned int id);

    /**
     * @brief Default destructor of the base class User
     */
    virtual ~User();

    /**
     * @brief Sets the streamHistory of the User (either streamed or watched)
     * @param pastStreams Set including the IDs of the past Streams
     */
    void setStreamHistory(std::set<unsigned int>& pastStreams);

    /**
     * @brief Updates the name of the Sser
     * @param name Name of the Sser
     */
    void setName(const std::string& name);

    /**
     * @brief Updates the nickname of the User
     * @param nick Nickname of the User
     */
    void setNick(const std::string& nick);

    /**
     * @brief Gets the name of the User
     * @return String containing the name of the User
     */
    std::string getName() const;

    /**
     * @brief Gets the nickname of the User
     * @return String containing the nickname of the User
     */
    std::string getNick() const;

    /**
     * @brief Gets the age of the User
     * @return Integer containing the age of the User
     */
    int getAge() const;

    /**
     * @brief Gets the age of the User as a string
     * @return String containing the age of the User
     */
    string getAgeString() const;

    /**
     * @brief Gets the ID of the User
     * @return Unsigned int containing the ID of the User
     */
    unsigned int getID() const;

    /**
     * @brief Gets the pointer to the Stream of the User (either streaming or watching). Throws NotInAStream exception
     * if the User isn't in one
     * @return Stream* of the User's Stream
     */
    Stream* getStream() const;

    /**
     * @brief Checks if the User is currently in a Stream (either streaming or watching)
     * @return Returns true if the User is in a Stream and false otherwise
     */
    bool inAStream() const;

    /**
     * @brief Gets the Stream history of the User (either streamed or watched)
     * @return Set containing the IDs of the past Streams
     */
    std::set<unsigned int>& getStreamHistory();

    /**
     * @brief Prints the User's information to the standard output. Only defined in the derived classes
     */
    virtual void showUser() const = 0;
};

/**
 * @brief Derived class of the class User, representing a streamer of the website
 */
class Streamer : public User{
private:
    /**
     * @brief Set of Viewers subscribed to the Streamer
     */
    std::set<unsigned int> subscribers;
public:

    /**
     * @brief Creates a Streamer with given name, nick and birthdate. The ID is set to nextID and increments it.
     * Throws NotOldEnough exception if the User is younger than 15. Also see User()
     * @param name Name of the Streamer
     * @param nick Nickname of the Streamer
     * @param birthDate Birthdate of the Streamer
     */
    Streamer(const std::string& name, const std::string& nick, const Date& birthDate);

    /**
     * @brief Creates a Streamer with given name, nick, birthdate and ID. Doesn't increment nextID.
     * Throws NotOldEnough exception if the User is younger than 15. Also see User()
     * @param name Name of the Streamer
     * @param nick Nickname of the Streamer
     * @param birthDate Birthdate of the Streamer
     * @param id ID of the Streamer
     */
    Streamer(const std::string& name, const std::string& nick, const Date& birthDate, unsigned int id);

    /**
     * @brief Default destructor of the derived class Streamer
     */
    virtual ~Streamer();

    /**
     * @brief Gets the number of Viewers currently on the Streamer's Stream. Throws NotInAStream exception
     * if he isn't streaming
     * @return Integer containing the number of Viewers
     */
    int getNumViewers() const;

    /**
     * @brief Gets the number of Viewers subscribed to the Streamer
     * @return Integer containing the number of subscribers
     */
    int getNumSubs() const;

    /**
     * @brief Gets the set of Viewers subscribed to the Streamer
     * @return Set containing the IDs of the subscribers
     */
    std::set<unsigned int>& getSubscribers();

    /**
     * @brief Ends the Stream. Throws NotInAStream exception if the Streamer is not streaming
     */
    void endStream();

    /**
     * @brief Starts a new Stream. Throws AlreadyStreaming exception if the Streamer is already streaming
     * @param stream Pointer to the Stream starting
     */
    void startStream(Stream* stream);

    /**
     * @brief Sets the subscribers of the Streamer
     * @param subscribers Set with the IDs of the Viewers subscribed to the Streamer
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
     * @brief Checks if a Viewer is subscribed to the Streamer
     * @param id ID of the Viewer intended to check
     * @return Returns true if the Viewer is subscribed and false otherwise
     */
    bool isSubscriber(unsigned int id) const;

    /**
     * @brief Prints the Streamer's information to the standard output. Also see User::showUser()
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
     * @param name Name of the Viewer
     * @param nick Nickname of the Viewer
     * @param birthDate Birthdate of the Viewer
     */
    Viewer(const std::string& name, const std::string& nick, const Date& birthDate);

    /**
     * @brief Creates a Viewer with given name, nick, birthdate and ID. Doesn't increment nextID.
     * Throws NotOldEnough exception if the user is younger than 12. Also see User()
     * @param name Name of the Viewer
     * @param nick Nickname of the Viewer
     * @param birthDate Birthdate of the Viewer
     * @param id ID of the Viewer
     */
    Viewer(const std::string& name, const std::string& nick, const Date& birthDate, unsigned int id);

    /**
     * @brief Default destructor of the derived class Viewer
     */
    virtual ~Viewer();

    /**
     * @brief The viewer joins a stream. Throws AlreadyStreaming exception if the viewer is already watching a stream.
     * Throws NotOldEnough exception if the viewer is not old enough to join the stream
     * @param stream Pointer to the Stream intended to join
     */
    void joinStream(Stream* stream);

    /**
     * @brief The viewer leaves the Stream he is currently watching. Throws NotInAStream exception if the Viewer
     * is not watching a Stream
     */
    void leaveStream();

    /**
     * @brief The Viewer sends a message to the Streamer he's currently watching. Can only be used while in a PrivateStream
     * Throw NotInAStream exception if the Viewer is not watching a PrivateStream
     * @param text Message the Viewer wants to send to the Streamer
     */
    void message(std::string text) const;

    /**
     * @brief TheViewer sends feedback to the Stream he's currently watching, in the form of a like or a dislike
     * @param like Value of the feedback the Viewer sent. Either 1 or -1 (like or dislike)
     */
    void feedback(int like);

    /**
     * @brief Prints the Viewer's information to the standard output. Also see User::showUser()
     */
    virtual void showUser() const;
    friend ostream& operator<<(ostream& out, const Viewer& viewer);
};

/**
 * @brief Prints the given Streamer's information to the given output stream
 * @param out Output Stream to write to
 * @param streamer Streamer whose information is going to be printed
 * @return Given output stream (out)
 */
ostream& operator<<(ostream& out, const Streamer& streamer);

/**
 * @brief Prints the given Viewer's information to the given output Stream
 * @param out Output stream to write to
 * @param viewer Viewer whose information is going to be printed
 * @return Given output stream (out)
 */
ostream& operator<<(ostream& out, const Viewer& viewer);


// Exceptions related to the user

/**
 * @brief Exception class which should be thrown when a User is not old enough for a certain task
 */
class NotOldEnough{
private:
    /**
     * @brief Reason the exception was thrown
     */
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
 * @brief Exception class which should be thrown when a User is unexpectedly not in a Stream
 */
class NotInAStream{
private:
    /**
     * @brief Reason the exception was thrown
     */
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
 * @brief Exception class which should be thrown when a User is unexpectedly in a Stream
 */
class AlreadyInAStream{
private:
    /**
     * @brief Reason the exception was thrown
     */
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
