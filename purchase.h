//
// Created by joaog on 12/21/2020.
//

#ifndef PROJETO1_PURCHASE_H
#define PROJETO1_PURCHASE_H

#include <string>

using namespace std;

class Purchase {
    string name;
    int numOfProducts;
    int availability;
public:
    Purchase(string name, int numOfProducts, int availability);
    string getName() const;
    int getNumOfProducts() const;
    int getAvailability() const;
    bool operator<(const Purchase& p2) const;       // operators need this exact format
    bool operator==(const Purchase& p2) const;
};

ostream& operator<<(ostream& out, Purchase p);

#endif //PROJETO1_PURCHASE_H
