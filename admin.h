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
    /**
     * @brief Name of the Admin
     */
    std::string name;

    /**
     * @brief Pointer to the StreamZ website the Admin is operating in
     */
    StreamZ* site;   // pointer so we can delete admin
public:
    /**
     * @brief Creates an Admin with given name and site
     * @param name Name of the Admin
     * @param site Site in which the Admin operates
     */
    Admin(const std::string& name, StreamZ* site);

    /**
     * @brief Gets the number of active Streams at the moment
     * @return  Integer containing the number of Streams
     */
    int getNumStreams() const;

    /**
     * @brief Gets the number of Streams created in a given interval of time: [from, to]
     * @param from Start Date
     * @param to End Date
     * @throw badDateComp If start date is after end date
     * @return Integer containing the number of created Streams in the interval
     */
    int getNumCreatedStreams(Date& from, const Date& to) const;

    /**
     * @brief Gets the average views for all the active Streams
     * @throw NoActiveStreams If there are no active Streams
     * @return Float containing the average views
     */
    float getAvgViews() const;

    /**
     * @brief Gets the average views of the Streams created in a given interval: [from, to]
     * @param from Start Date
     * @param to End Date
     * @throw badDateComp If start date is after end date
     * @return Float containing the average views
     */
    float getAvgViews(Date& from, const Date& to) const;

    /**
     * @brief Gets the number of active PublicStreams at the moment
     * @return  Integer containing the number of PublicStreams
     */
    int getNumPublicStreams() const;

    /**
     * @brief Gets the number of PublicStreams created in a given interval of time: [from, to]
     * @param from Start Date
     * @param to End Date
     * @throw badDateComp If start date is after end date
     * @return Integer containing the number of created PublicStreams in the interval
     */
    int getNumPublicStreams(Date& from, const Date& to) const;

    /**
     * @brief Gets the number of active PrivateStreams at the moment
     * @return  Integer containing the number of PrivateStreams
     */
    int getNumPrivateStreams() const;

    /**
     * @brief Gets the number of PrivateStreams created in a given interval of time: [from, to]
     * @param from Start Date
     * @param to End Date
     * @throw badDateComp If start date is after end date
     * @return Integer containing the number of created PrivateStreams in the interval
     */
    int getNumPrivateStreams(Date& from, const Date& to) const;

    /**
     * @brief Gets the name of the Admin
     * @return String containing the name of the Admin
     */
    string getName() const;

    /**
     * @brief Updates the name of the Admin
     * @param name Name of the Admin
     */
    void setName(const std::string& name);

    /**
     * @brief Gets the preferred language in a given vector of Streams
     * @param streams Vector of Stream* with the Streams which will be analyzed
     * @throw NoActiveStreams If there are no active Streams
     * @return String containing the preferred language
     */
    std::string getPreferredLanguage(std::vector<Stream*>& streams) const;

    /**
     * @brief Gets the preferred stream type of the active Streams
     * @throw NoActiveStreams If there are no active Streams
     * @return String containing the preferred Stream type
     */
    std::string getPreferredStreamType() const;

    /**
     * @brief Gets the pointer to the most viewed Streamer at the moment
     * @throw NoActiveStreams If there are no active Streams
     * @return Streamer* to the most viewed Streamer
     */
    Streamer* getMostViewedStreamer() const;

    /**
     * @brief Lists all the donations in the site, by decreasing order
     */
    void listDonations() const;

    /**
     * @brief Lists the donations in a given interval of ratings, by decreasing order
     * @param aval1 Lower bound of the interval
     * @param aval2 Upper bound of the interval
     * @throw badDateComp if the lower bound is higher than the upper bound
     */
    void listDonations(int rate1, int rate2) const;

    void listTopDonations() const;
};

/**
 *  @brief Exception class which should be thrown when an interval of Dates is faulty
 */
class badDateComp{
private:
    /**
     * @brief Reason the exception was thrown
     */
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
 * @brief Exception class which should be thrown when there are unexpectedly no active Streams
 */
class NoActiveStreams{
private:
    /**
     * @brief Reason the exception was thrown
     */
    string reason;
public:

    /**
     * @brief Creates a noActiveStreams exception with a given reason
     * @param reason Reason of the exception
     */
    NoActiveStreams(const string& reason);

    /**
     * @brief Gets the reason of the exception
     * @return String containing the reason
     */
    string what() const;
};

#endif //PROJETO1_ADMIN_H
