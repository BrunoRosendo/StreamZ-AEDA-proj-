#include <iostream>
#include "donation.h"

using namespace std;

Donation::Donation(string streamer, float amount, int rating) {
    this->streamer = streamer;
    this->amount = amount;
    this->rating = rating;
}

string Donation::getStreamer() const {
    return streamer;
}

float Donation::getAmount() const {
    return amount;
}

int Donation::getRating() const {
    return rating;
}

void Donation::showDonation() const {
    cout << amount << " euros were donated to " << streamer << " with a rating of " << rating << "/5" << endl;
}

bool Donation::operator<(const Donation &d2) const {  // we want to access donations in decreasing order
    if (amount == d2.getAmount()){
        return rating > d2.getRating();
    }
    return amount > d2.getAmount();
}