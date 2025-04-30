#include <stdint.h>
#include "systick.h"
#include "tm4c123gh6pm.h" 
#include "led.h"

extern volatile uint32_t us = 0;

void SysTick_Handler() 
{
    us++;
    if(us % 10000 == 0)
    {
        green_tog();
    }
}

void init_SysTick() 
{
    NVIC_ST_CTRL_R = 0;
    NVIC_ST_RELOAD_R = 399;
    NVIC_ST_CURRENT_R = 0;
    NVIC_ST_CTRL_R |= NVIC_ST_CTRL_ENABLE | NVIC_ST_CTRL_INTEN | NVIC_ST_CTRL_CLK_SRC;
}

uint32_t currentTime() 
{
    return us;
}

uint32_t deltaTime(uint32_t start, uint32_t stop) 
{
    return start - stop;
}
