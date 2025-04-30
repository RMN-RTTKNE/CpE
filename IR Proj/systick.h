#ifndef SYSTICK__H
#define SYSTICK__H
#include <stdint.h>

extern volatile uint32_t ms;
void init_SysTick();
uint32_t currentTime();
uint32_t deltaTime(uint32_t start, uint32_t stop);

#endif
