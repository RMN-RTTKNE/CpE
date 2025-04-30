#ifndef __PURSE_H
#define __PURSE_H

#include <iostream>

class Purse {

    private:
    int _pounds;
    int _shillings;
    int _pence;

    public: 
    Purse(int pounds = 0, int shillings = 0, int pence = 0); 
    friend std::ostream& operator<<(std::ostream& ost, const Purse& purse);
    auto operator<=>(const Purse& purse) const = default;
    Purse& operator ++();
    Purse operator ++(int);
    Purse operator +(const Purse& purse);
    Purse operator -(const Purse& purse);
    Purse& operator +=(const Purse& purse);
    Purse& operator -=(const Purse& purse);

    private:
    void rationalize();
};

#endif