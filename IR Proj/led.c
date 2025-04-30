#include <stdint.h>
#include "clock.h"
#include "tm4c123gh6pm.h" 
#include "led.h"

#define RED  *(volatile uint32_t*)(0x42000000 + (0x400253FC - 0x40000000)*32 + (1*4))
#define BLUE *(volatile uint32_t*)(0x42000000 + (0x400253FC - 0x40000000)*32 + (2*4))
#define GREEN *(volatile uint32_t*)(0x42000000 + (0x400253FC - 0x40000000)*32 + (3*4))

#define RED_M 0x2 //0010 first bit
#define BLUE_M 0x4 //0100 second bit
#define GREEN_M 0x8 //1000 third bit

void init_led()
{
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R5;
    _delay_cycles(3);
    GPIO_PORTF_DIR_R |= RED_M | BLUE_M | GREEN_M; // set bits 1, 2, 3 as output
    GPIO_PORTF_DEN_R |= RED_M | BLUE_M | GREEN_M; // digitally enable LEDs

    red_off();
    blue_off();
    green_off();
}

void red_off()
{
    RED = 0;
}

void blue_off()
{
    BLUE = 0;
}

void green_off()
{
    GREEN = 0;
}

void red_on()
{
    RED = 1;
}

void blue_on()
{
    BLUE = 1;
}

void green_on()
{
    GREEN = 1;
}

void red_tog()
{
    RED = !RED;
}

void blue_tog()
{
    BLUE = !BLUE;
}

void green_tog()
{
    GREEN = !GREEN;
}
