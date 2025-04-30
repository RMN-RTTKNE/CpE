#include "tm4c123gh6pm.h"
#include "pwm.h"
#include <stdint.h>
#include "wait.h"

#define PIN *(volatile uint32_t*)(0x42000000 + (0x400053FC - 0x40000000)*32 + (6*4)) //PB6
#define MASK    0x00000040 //6th bit

void initPWM()
{
    SYSCTL_RCGC0_R |= SYSCTL_SCGC0_PWM0;
    _delay_cycles(3);

    SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOB;
    _delay_cycles(3);

    GPIO_PORTB_AFSEL_R |= MASK;

    GPIO_PORTB_DEN_R |= MASK;

    GPIO_PORTB_PCTL_R &= ~(GPIO_PCTL_PB6_M);
    GPIO_PORTB_PCTL_R |= GPIO_PCTL_PB6_M0PWM0;

    SYSCTL_RCC_R &= ~SYSCTL_RCC_PWMDIV_M;

    SYSCTL_RCC_R |= SYSCTL_RCC_USEPWMDIV | SYSCTL_RCC_PWMDIV_4; //40Mhz / 4 = 10Mhz

    PWM0_CTL_R = 0x0; //Off

    PWM0_0_GENA_R = PWM_0_GENA_ACTLOAD_M | PWM_0_GENA_ACTCMPAD_ZERO;

    PWM0_0_LOAD_R = 262; // 263-1

    PWM0_0_CMPA_R = 130; // 263/2 - 1

    PWM0_CTL_R |= PWM_CTL_GLOBALSYNC0;
    PWM0_0_CTL_R |= PWM_0_CTL_ENABLE;
    PWM0_ENABLE_R &= ~PWM_ENABLE_PWM0EN;
}

void zero()
{
    PWM0_ENABLE_R |= PWM_ENABLE_PWM0EN;
    waitMicrosecond(560);
    PWM0_ENABLE_R &= ~PWM_ENABLE_PWM0EN;
    waitMicrosecond(560);
}

void one()
{
    PWM0_ENABLE_R |= PWM_ENABLE_PWM0EN;
    waitMicrosecond(560);
    PWM0_ENABLE_R &= ~PWM_ENABLE_PWM0EN;
    waitMicrosecond(1660);
}
void preamble()
{
    PWM0_ENABLE_R |= PWM_ENABLE_PWM0EN;
    waitMicrosecond(9100);
    PWM0_ENABLE_R &= ~PWM_ENABLE_PWM0EN;
    waitMicrosecond(4500);
}
void tail()
{
    PWM0_ENABLE_R |= PWM_ENABLE_PWM0EN;
    waitMicrosecond(560);
    PWM0_ENABLE_R &= ~PWM_ENABLE_PWM0EN;
}

void send(uint8_t transmit)
{
    int i;
    for(i = 7; i >= 0; i--)
    {
        int bit = (transmit >> i) & 1;
        if(bit == 1)
        {
            one();
        }
        else
        {
            zero();
        }
    }
}
void TVsend(uint32_t transmit)
{
    preamble();
    int i;
    for(i = 31; i >= 0; i--)
    {
        int bit = (transmit >> i) & 1;
        if(bit == 1)
        {
            one();
        }
        else
        {
            zero();
        }
    }
    tail();
}
