#include <stdint.h>
#include "receive.h"
#include "tm4c123gh6pm.h"
#include "led.h"
#include "systick.h"

#define PIN_MASK 0x00000020


uint32_t edge = 0;
uint32_t prev_edge = 0;
uint32_t num_edge = 0;
volatile uint32_t dt[33] = {0};
volatile uint32_t bits = 0;
volatile uint32_t last[9] = {0};
volatile int num_val = 0;

void save(uint32_t val)
{
    if(num_val < 9)
    {
        last[num_val] = val;
        num_val++;
    }
    else
    {
        int i;
        for(i = 0; i < 8; i++)
        {
            last[i] = last[i+1];
        }
        last[8] = val;
    }
}

uint32_t decode(uint32_t *dt)
{
    uint32_t result = 0;
    int i;
    for(i = 1; i <= 32; i++)
    {
        result <<= 1;
        if(dt[i] > 150)
        {
            result |= 1;
        }
        else
        {
            result |= 0;
        }
    }
    return result;
}

void receive_handler()
{
    blue_tog();
    GPIO_PORTA_ICR_R = PIN_MASK;
    edge = currentTime();
    if(num_edge > 0 && num_edge < 34)
    {
        dt[num_edge - 1] = edge - prev_edge;
    }
    prev_edge = edge;
    num_edge++;
    if(num_edge == 34)
    {
        bits = decode(dt);
        num_edge = 0;
    }
}

void init_receive()
{
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R0;
    _delay_cycles(3);

    GPIO_PORTA_DIR_R &= ~(PIN_MASK);
    GPIO_PORTA_DEN_R |= PIN_MASK;

    GPIO_PORTA_IS_R &= ~PIN_MASK;    // edge triggered
    GPIO_PORTA_IBE_R &= ~PIN_MASK;  // not both edges
    GPIO_PORTA_IEV_R &= ~PIN_MASK;    // falling edge
    GPIO_PORTA_ICR_R |= PIN_MASK;   // clear it
    GPIO_PORTA_IM_R |= PIN_MASK;    // arm interrupt

    NVIC_EN0_R |= 0x00000001;
}

