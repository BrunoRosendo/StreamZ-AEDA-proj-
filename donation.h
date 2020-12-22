#ifndef DONATION_H
#define DONATION_H

#include <iostream>
#include <string>

using namespace std;

/**
 * @brief A donation is defined by the streamer who received it, its amount and the rating of the streamer (1 to 5)
 */
class Donation{
private:

    /**
     * @brief Name of the Streamer who received the donation
     */
    string streamer;

    /**
     * @brief Amount of the donation (in euros)
     */
    float amount;

    /**
     * @brief Rating of the Streamer (1 to 5)
     */
    int rating;
public:

    /**
     * @brief Constructs a Donations with a given streamer, amount and rating
     * @param streamer Name of the Streamer who received the donation
     * @param amount Amount of the donation
     * @param rating Rating of the Streamer
     */
    Donation(string streamer, float amount, int rating);

    /**
     * @brief Gets the name of the Streamer who received the donations
     * @return String containing the name of the Streamer
     */
    string getStreamer() const;

    /**
     * @brief Gets the amount of the donation (in euros)
     * @return Float containing the amount
     */
    float getAmount() const;

    /**
     * @brief Gets the rating of the Streamer who received the donation
     * @return Char containing a number of 1 to 5
     */
    int getRating() const;

    /**
     * @brief Prints the Donation to the screen
     */
    void showDonation() const;

    /**
     * @brief A Donation is less than another if it has a smaller amount or, in case of a draw, a worse rating
     * @param d2 Donations for comparison
     * @return True if this is smaller than d2 and false otherwise
     */
    bool operator< (const Donation& d2) const;
};



#endif
