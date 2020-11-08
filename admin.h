//
// Created by joaog on 10/23/2020.
//

#ifndef PROJETO1_ADMIN_H
#define PROJETO1_ADMIN_H

#include <string>
#include "user.h"
#include "streamZ.h"

/**
 * @brief Class which has access to private methods of StreamZ, used to get statistics
 */
class Admin{
private:
    std::string name;
    StreamZ* site;   // pointer so we can delete admin
public:
    /**
     * @brief Creates and admin with given name and site
     * @param name Name of the admin
     * @param site Site in which the admin operates
     */
    Admin(const std::string& name, StreamZ* site);

    /**
     * @brief Gets the number of active streams at the moment
     * @return  Integer containing the number of streams
     */
    int getNumStreams() const;

    /**
     * @brief Gets the number of streams created in a given interval of time: [from, to]
     * @param from Start date
     * @param to End date
     * @return Integer containing the number of created streams in the interval
     */
    int getNumCreatedStreams(Date& from, const Date& to) const;

    /**
     * @brief Gets the average views for all the active streams
     * @return Float containing the average views
     */
    float getAvgViews() const;

    /**
     * @brief Gets the average views of the streams created in a given interval: [from, to]
     * @param from Start date
     * @param to End date
     * @return Float containing the average views
     */
    float getAvgViews(Date& from, const Date& to) const;

    /**
     * @brief Gets the number of active public streams at the moment
     * @return  Integer containing the number of public streams
     */
    int getNumPublicStreams() const;

    /**
     * @brief Gets the number of public streams created in a given interval of time: [from, to]
     * @param from Start date
     * @param to End date
     * @return Integer containing the number of created public streams in the interval
     */
    int getNumPublicStreams(Date& from, const Date& to) const;

    /**
     * @brief Gets the number of active private streams at the moment
     * @return  Integer containing the number of private streams
     */
    int getNumPrivateStreams() const;

    /**
     * @brief Gets the number of private streams created in a given interval of time: [from, to]
     * @param from Start date
     * @param to End date
     * @return Integer containing the number of created private streams in the interval
     */
    int getNumPrivateStreams(Date& from, const Date& to) const;

    /**
     * @brief Gets the name of the admin
     * @return String containing the name of the admin
     */
    string getName() const;

    /**
     * @brief Updates the name of the admin
     * @param name Name of the admin
     */
    void setName(const std::string& name);

    /**
     * @brief Gets the preferred language in a given vector of streams
     * @param streams Vector of Stream* with the streams which will be analyzed
     * @return String containing the preferred language
     */
    std::string getPreferredLanguage(std::vector<Stream*>& streams) const;

    /**
     * @brief Gets the preferred stream type of the active streams
     * @return String containing the preferred stream type
     */
    std::string getPreferredStreamType() const;

    /**
     * @brief Gets the pointer to the most viewed streamer at the moment
     * @return Streamer* to the most viewed streamer
     */
    Streamer* getMostViewedStreamer() const;
};

/**
 *  @brief Exception class which should be thrown when an interval of dates is faulty
 */
class badDateComp{
private:
    string reason;
public:

    /**
     * @brief Creates a badDateComp exception with a given reason
     * @param reason Reason of the exception
     */
    badDateComp(const string& reason);

    /**
     * @brief Gets the reason of the exception
     * @return String containing the reason
     */
    string what() const;
};

/**
 * @brief Exception class which should be thrown when there are unexpectedly no active streams
 */
class noActiveStreams{
private:
    string reason;
public:

    /**
     * @brief Creates a noActiveStreams exception with a given reason
     * @param reason Reason of the exception
     */
    noActiveStreams(const string& reason);

    /**
     * @brief Gets the reason of the exception
     * @return String containing the reason
     */
    string what() const;
};

#endif //PROJETO1_ADMIN_H
