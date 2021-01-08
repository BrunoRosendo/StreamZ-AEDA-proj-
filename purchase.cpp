//
// Created by joaog on 12/21/2020.
//

#include <iostream>
#include <string>
#include <iomanip>
#include "purchase.h"


Purchase::Purchase(string name, int numOfProducts, int availability){
    this->name = name;
    this->numOfProducts = numOfProducts;
    this->availability = availability;
}

string Purchase::getName() const{
    return this->name;
}

int Purchase::getNumOfProducts() const{
    return this->numOfProducts;
}

int Purchase::getAvailability() const{
    return this->availability;
}

bool Purchase::operator<(const Purchase& p2) const {
    if( this->numOfProducts < p2.getNumOfProducts() )
        return false;               
    else if(this->numOfProducts > p2.getNumOfProducts())
        return true;
    else{
        return this->availability < p2.getAvailability();
    }
}

bool Purchase::operator==(const Purchase &p2) const {
    return this->name == p2.getName();
}

ostream& operator<<(ostream& out, Purchase p){
    out << setfill(' ') << setw(15) << p.getName()  <<  " |" << setw(10)   <<  p.getNumOfProducts() <<  " |" << setw(10) <<  p.getAvailability() << endl;
    return out;
}

