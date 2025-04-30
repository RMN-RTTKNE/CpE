#include "tm4c123gh6pm.h"
#include <stdint.h>
#include "wait.h"

#ifndef PWM_H_
#define PWM_H_

void initPWM();
void zero();
void one();
void preamble();
void tail();
void send(uint8_t transmit);
void TVsend(uint32_t transmit);
#endif
