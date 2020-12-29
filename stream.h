//
// Created by joaog on 10/23/2020.
//

#ifndef PROJETO1_STREAM_H
#define PROJETO1_STREAM_H

#include <map>
#include <fstream>
#include <set>
#include <vector>
#include "date.h"

/**
 * @brief Abstract class representing a stream
 */
class Stream{
protected:
    /**
     * @brief Title of the Stream
     */
    std::string title;

    /**
     * @brief Start date of the Stream
     */
    Date startDate;

    /**
     * @brief Language of the Stream
     */
    std::string language;

    /**
     * @brief Minimum age of the Stream
     */
    int minAge;

    /**
     * @brief The Stream's Viewers are stored in this set
     */
    std::set<unsigned int> viewers;

    /**
     * @brief Number of likes of the Stream
     */
    int noLikes;

    /**
     * Number of Viewers of the Stream
     */
    int numViewers;

    /**
     * @brief Nickname of the Streamer controlling the Stream
     */
    string streamerNick;

    /**
     * @brief ID of the Stream
     */
    unsigned int id;

public:
    /**
     * @brief ID of the next Stream created
     */
    static unsigned int nextID;

    /**
     * @brief Constructs a Stream with given title, start date, language, minimum age and the nick of the Streamer
     * @param title Title of the Stream
     * @param startDate Start date of the Stream
     * @param language Language of the Stream
     * @param minAge Minimum age of the Stream
     * @param streamerNick Nickname of the Streamer controlling the Stream
     */
    Stream(const string& title, const Date& startDate, const string& language, int minAge, const string& streamerNick);

    /**
     * @brief Default constructor of the base class Stream
     */
    virtual ~Stream();

    /**
     * @brief Adds a User to the viewers set. Only defined in the derived classes
     * @param user User joining the stream
     */
    virtual void addUser(unsigned int user) = 0;

    /**
     * @brief Removes a User from the viewers set
     * @param user ID of the user intended to remove
     */
    void removeUser(unsigned int user);

    /**
     * @brief Gets number of current Viewers in the stream
     * @return Integer containing the number of Viewers
     */
    int getNumViewers() const;

    /**
     * @brief Gets the tile of the Stream
     * @return String containing the title of the Stream
     */
    std::string getTitle() const;

    /**
     * @brief Gets the Stream's start date
     * @return Date with the start date
     */
    Date getStartDate() const;

    /**
     * @brief Gets the language of the Stream
     * @return String containing the language of the Stream
     */
    std::string getLanguage() const;

    /**
     * @brief Gets the minimum age of the Stream
     * @return Integer containing the minimum age of the Stream
     */
    int getMinAge() const;

    /**
     * @brief Gets the number of likes of the Stream
     * @return Integer containing the number of likes
     */
    int getNoLikes() const;

    /**
     * @brief Gets the nickname of the Streamer controlling the Stream
     * @return String containing the nickname of the Streamer
     */
    std::string getStreamerNick() const;

    /**
     * @brief Gets the set of Viewers in the Stream (by reference)
     * @return Set of Viewers in the Stream
     */
    std::set<unsigned int>& getViewers();

    /**
     * @brief Receives feedback from a Viewer in the form of a like (1) or a dislike (-1)
     * @param megaLikezao Value added to the overall feedback (1 or -1)
     */
    void feedback(int megaLikezao);

    /**
     * @brief Prints the Stream's information to the standard output
     */
    virtual void showStream() const;

    /**
     * @brief Gets the ID of the Stream
     * @return Unsigned int containing the ID of the Stream
     */
    unsigned int getId() const;

    /**
     * @brief Sets the nickname of the Streamer
     * @param nick Nickname of the Streamer
     */
    void setStreamerNick(const string& nick);
    void add50likes();
};

/**
 * @brief Stream restricted to certain Viewers (subscribers) with a maximum number of Viewers at a time.
 * Derived from Stream class
 */
class PrivateStream : public Stream{
    /**
     * @brief Maximum number of viewers watching at a time
     */
    int capacity;

    /**
     * @brief Set of Viewers subscribed to the Streamer controlling the Stream
     */
    std::set<unsigned int> subscribers;

    /**
     * @brief Vector storing the messages that the Viewers send
     */
    std::vector<std::string> messages;
public:
    /**
     * @brief Creates a private stream with given subscribers, capacity and Stream() parameters. Also see Stream()
     * @param title Title of the stream
     * @param startDate Start date of the stream
     * @param language Language of the stream
     * @param minAge Minimum age of the stream
     * @param streamerNick Nickname of the Streamer controlling the stream
     * @param subscribers Set of Viewers (IDs) subscribed to the Streamer
     * @param capacity Capacity of the stream
     * @throw NoCapacity If the number of Viewers in the PrivateStream exceeds the capacity
     * @throw NotSubscribed If the Viewer trying to join isn't subscribed to the Streamer
     */
    PrivateStream(const string& title, const Date& startDate, const string& language, int minAge, const string& streamerNick,
                  std::set<unsigned int> &subscribers, int capacity);

    /**
     * @brief Default destructor of the derived PrivateStream class
     */
    virtual ~PrivateStream();

    /**
     * @brief Adds a User to the viewers set. Throws the exceptions noCapacity if the stream is full
     * and NotSubscribed if the given User is not subscribed
     * @param user ID of the user trying to join the stream
     */
    virtual void addUser(unsigned int user);

    /**
     * @brief Prints the private stream's information to the standard output
     */
    virtual void showStream() const;

    /**
     * @brief Prints all the Viewer's messages to the standard output
     */
    void showMessages() const;

    /**
     * @brief Adds a message from a Viewer to the messages vector
     * @param message Message written by a Viewer
     */
    void addMessage(const std::string& message); // the message includes the name of the user
};

/**
 * @brief Stream which can be accessed by any Viewer. Derived from Stream class
 */
class PublicStream : public Stream{
public:
    /**
     * @brief Creates a public stream with Stream() parameters. Also see Stream()
     * @param title Title of the stream
     * @param startDate Start date of the stream
     * @param language Language of the stream
     * @param minAge Minimum age of the stream
     * @param streamerNick Nickname of the Streamer controlling the stream
     */
    PublicStream(const string& title, const Date& startDate, const string& language, int minAge, const string& streamerNick);

    /**
     * @brief Default destructor of the derived class PublicStream
     */
    virtual ~PublicStream();

    /**
     * @brief Adds a User to the viewers set
     * @param user ID of the User joining the stream
     */
    virtual void addUser(unsigned int user);

    /**
     * @brief Prints the public stream's information to the standard output
     */
    virtual void showStream() const;
};

/**
 * @brief Prints the given Stream's information to the standard output
 * @param out Output stream which is going to be written to
 * @param stream Stream whose information is going to be printed
 * @return Returns the given ostream out
 */
ostream& operator<<(ostream& out, Stream& stream );

/**
 * @brief Struct used to store a Stream which has already ended
 */
struct PastStream{
    /**
     * @brief Creates an empty PastStream struct. Its members should be updated before using it
     */
    PastStream(){Stream::nextID++;};

    /**
     * @brief Creates a struct storing a past Stream, containing the Stream title, its ID and its start date;
     * noViewers is set to -1 and updated when the Stream ends.
     * @param stream Pointer to the stream intended to store
     */
    PastStream(Stream* stream){this->name = stream->getTitle(), this->noViewers = -1, this->id = stream->getId(),
                               this->StartDate = stream->getStartDate();};

    /**
     * @brief Name of the Stream
     */
    std::string name;

    /**
     * @brief Number of Viewers the moment the Stream ended
     */
    int noViewers;

    /**
     * @brief ID of the Stream
     */
    unsigned int id;

    /**
     * @brief Start Date of the Stream
     */
    Date StartDate;
};


// Exceptions

/**
 * @brief Exception class which should be thrown when a PrivateStream's capacity is full and a Viewer tries to join
 */
class NoCapacity{
private:
    /**
     * @brief Reason the exception was thrown
     */
    string reason;
public:
    /**
     * @brief Creates a noCapacity exception with a given reason
     * @param reason Reason for the exception to be thrown
     */
    NoCapacity(const string& reason);
    /**
     * Gets the reason for which the exception was thrown
     * @return String containing the reason
     */
    string what();
};

/**
 * @brief Exception class which should be thrown when a Viewer tries to join a PrivateStream
 * he is not subscribed to
 */
class NotSubscribed{
private:
    /**
     * @brief Reason the exception was thrown
     */
    string reason;
public:
    /**
     * @brief Creates a NotSubscribed exception with a given reason
     * @param reason Reason for the exception to be thrown
     */
    NotSubscribed(const string& reason);
    /**
     * Gets the reason for which the exception was thrown
     * @return String containing the reason
     */
    string what() const;
};

#endif //PROJETO1_STREAM_H
