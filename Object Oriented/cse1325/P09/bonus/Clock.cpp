#include <iostream>
#include <iomanip>
#include "Clock.h"

Clock::Clock(int hours, int minutes, int seconds) : _hours{hours}, _minutes{minutes}, _seconds{seconds} {
    if(_hours < 0 || _hours > 23 ){
            throw std::out_of_range("Hour value of out range: " + std::to_string(_hours));
    }
    if(_minutes < 0 || _minutes > 59 ) {
        throw std::out_of_range("Minute value of out range: " +  std::to_string(_minutes));
    }
    if(_seconds < 0 || _seconds > 59) {
            throw std::out_of_range("Seconds value of out range: " +  std::to_string(_seconds));
    }
};
Clock::~Clock(){};
void Clock::tic() {
    _seconds++;
    if(_seconds == 60) {
        _seconds = 0;
        _minutes++;
    }
    if(_minutes == 60) {
        _minutes = 0;
        _hours++;
    }
    if(_hours == 24) {
        _hours = 0;
    }
}
void Clock::print(){
    std::cout << std::setw(2) << std::setfill('0') << _hours << ":" << std::setw(2) <<  std::setfill('0') << _minutes << ":" << std::setw(2) << std::setfill('0') << _seconds << std::endl;
}