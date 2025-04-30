#ifndef RECEIVE_H_
#define RECEIVE_H_
#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "led.h"

extern volatile uint32_t bits;
extern volatile uint32_t last[9];
extern volatile int num_val;

void init_receive();
void receive_handler();
uint32_t decode();
void save(uint32_t val);

#endif
