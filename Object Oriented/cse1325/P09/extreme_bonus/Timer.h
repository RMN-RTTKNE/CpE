#ifndef __TIMER_H
#define __TIMER_H

#include "Clock.h"

class Timer : public Clock {
    public: 
    Timer(int hours, int minutes, int seconds);
    virtual ~Timer();
    void tic();
};

#endif