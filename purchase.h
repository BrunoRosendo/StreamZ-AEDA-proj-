//
// Created by joaog on 12/21/2020.
//

#ifndef PROJETO1_PURCHASE_H
#define PROJETO1_PURCHASE_H

#include <string>

using namespace std;

/**
 * @brief A Purchase is defined by the Viewer's name, the number of products in the purchase and the availability of the Viewer
 */
class Purchase {

    /**
     * @brief Name of the viewers who wants to purchase merch
     */
    string name;

    /**
     * @brief Number of products in the purchase
     */
    int numOfProducts;

    /**
     * @brief Availability of the Viewer
     */
    int availability;
public:

    /**
     * @brief Constructs a new Purchase with given name, number of products and user's availability
     * @param name Name of the Viewers
     * @param numOfProducts Number of products ordered
     * @param availability Availability of the Viewer
     */
    Purchase(string name, int numOfProducts, int availability);

    /**
     * @brief Gets the name of the Viewer buying merch
     * @return String containing the name of the Viewer
     */
    string getName() const;

    /**
     * @brief Gets the number of products in the purchase
     * @return Number of products
     */
    int getNumOfProducts() const;

    /**
     * @brief Gets the availability of the Viewer
     * @return Availability of the Viewer
     */
    int getAvailability() const;

    /**
     * @brief Compares two purchases and checks which has less products and more availability
     * @param p2 Second purchase to be compared
     * @return True if this is has more products than p2 or less availability in case of a draw. False otherwise
     */
    bool operator<(const Purchase& p2) const;       // operators need this exact format

    /**
     * @brief Checks if the name of this is the same as p2's
     * @param p2 Second purchase to be compared
     * @return True if the name is the same and false otherwise
     */
    bool operator==(const Purchase& p2) const;
};

/**
 * @brief Prints the information of a purchase to a given stream
 * @param out Stream to printed to
 * @param p Purchase to be printed
 * @return Out stream given
 */
ostream& operator<<(ostream& out, Purchase p);

#endif //PROJETO1_PURCHASE_H
