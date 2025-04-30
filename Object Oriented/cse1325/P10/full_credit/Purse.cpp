#include <iostream>
#include "Purse.h"

Purse::Purse(int pounds, int shillings, int pence) : _pounds{pounds}, _shillings{shillings}, _pence{pence} {
    rationalize();
}

std::ostream& operator<<(std::ostream& ost, const Purse& purse) {
    ost << "£" << purse._pounds << " " << purse._shillings << "s" << purse._pence << "d";
    return ost;
}
Purse& Purse::operator++() {
    ++_pence;
    rationalize();
    return *this;
}
Purse Purse::operator++(int) {
    Purse purse{*this};
    ++*this;
    return purse;
}
Purse Purse::operator +(const Purse& purse) {
    Purse sum(_pounds + purse._pounds, _shillings + purse._shillings, _pence + purse._pence);
    sum.rationalize();
    return sum;
}
Purse Purse::operator -(const Purse& purse) {
    Purse diff(_pounds - purse._pounds, _shillings - purse._shillings, _pence - purse._pence);
    diff.rationalize();
    return diff;
}
Purse& Purse::operator +=(const Purse& purse) {
    _pounds += purse._pounds;
    _shillings += purse._shillings;
    _pence += purse._pence;
    rationalize();
    return *this;
}
Purse& Purse::operator -=(const Purse& purse) {
    _pounds -= purse._pounds;
    _shillings -= purse._shillings;
    _pence -= purse._pence;
    rationalize();
    return *this;
}
void Purse::rationalize() {
    if (_pence > 11) {
        _shillings += _pence/12;
        _pence = _pence % 12;
    }
    if(_pence < 0) {
        _shillings--;
        _pence = _pence + 12;
    }
    if(_shillings > 19) {
        _pounds += _shillings/20;
        _shillings = _shillings % 20;
    }
    if(_shillings < 0) {
        _pounds--;
        _shillings = _shillings + 20;

    }
}