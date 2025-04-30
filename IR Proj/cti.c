#include <stdbool.h>
#include <stdint.h>
#include"tm4c123gh6pm.h"
#include "cti.h"
#define MAX_CHARS 80
#define MAX_FIELDS 5
#define UART_TX_MASK 2
#define UART_RX_MASK 1

char getcUart0()
{
    char error[8];
    while (UART0_FR_R & UART_FR_RXFE)
        ;               // wait if uart0 rx fifo empty
    return UART0_DR_R & 0xFF;                        // get character from fifo
}

void getsUart0(USER_DATA *data)
{
    int count = 0;
    while (1)
    {
        char c = getcUart0();
        if (((int) c == 8 || (int) c == 127))
        {
            if (count > 0)
            {
                count--;
            }
        }
        if ((int) c == 13)
        {
            data->buffer[count] = '\0';
            return;
        }
        if ((int) c >= 32)
        {
            data->buffer[count] = c;
            count++;
            if (count == MAX_CHARS)
            {
                data->buffer[count] = '\0';
                return;
            }
        }
    }
}

void initUart0()
{
    // Enable clocks
    SYSCTL_RCGCUART_R |= SYSCTL_RCGCUART_R0;
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R0;
    _delay_cycles(3);

    // Configure UART0 pins
    GPIO_PORTA_DR2R_R |= UART_TX_MASK; // set drive strength to 2mA (not needed since default configuration -- for clarity)
    GPIO_PORTA_DEN_R |= UART_TX_MASK | UART_RX_MASK; // enable digital on UART0 pins
    GPIO_PORTA_AFSEL_R |= UART_TX_MASK | UART_RX_MASK; // use peripheral to drive PA0, PA1
    GPIO_PORTA_PCTL_R &= ~(GPIO_PCTL_PA1_M | GPIO_PCTL_PA0_M); // clear bits 0-7
    GPIO_PORTA_PCTL_R |= GPIO_PCTL_PA1_U0TX | GPIO_PCTL_PA0_U0RX;
    // select UART0 to drive pins PA0 and PA1: default, added for clarity

    // Configure UART0 to 115200 baud, 8N1 format
    UART0_CTL_R = 0;                 // turn-off UART0 to allow safe programming
    UART0_CC_R = UART_CC_CS_SYSCLK;                 // use system clock (40 MHz)
    UART0_IBRD_R = 21; // r = 40 MHz / (Nx115.2kHz), set floor(r)=21, where N=16
    UART0_FBRD_R = 45;                                  // round(fract(r)*64)=45
    UART0_LCRH_R = UART_LCRH_WLEN_8 | UART_LCRH_FEN; // configure for 8N1 w/ 16-level FIFO
    UART0_CTL_R = UART_CTL_TXE | UART_CTL_RXE | UART_CTL_UARTEN;
    // enable TX, RX, and module
}

void putcUart0(char c)
{
    while (UART0_FR_R & UART_FR_TXFF)
        ;               // wait if uart0 tx fifo full
    UART0_DR_R = c;                                  // write character to fifo
}
void putsUart0(char *str)
{
    uint8_t i = 0;
    while (str[i] != '\0')
        putcUart0(str[i++]);
}

void parseFields(USER_DATA *data)
{
    data->fieldCount = 0;
    int i = 0;
    int j = 0;
    char prev = 'd';
    while (data->buffer[i] != '\0')
    {
        char c = data->buffer[i];
        char current;
        if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
        {
            current = 'a';
        }
        else if (c >= '0' && c <= '9')
        {
            current = 'n';
        }
        else
        {
            current = 'd';
            data->buffer[i] = '\0';
        }
        if ((prev == 'd' && current == 'a') || (prev == 'd' && current == 'n'))
        {
            data->fieldType[j] = current;
            data->fieldPosition[j] = i;
            data->fieldCount += 1;
            j++;
        }
        prev = current;
        if (data->fieldCount == MAX_FIELDS)
        {
            return;
        }
        i++;
    }
}

char* getFieldString(USER_DATA *data, uint8_t fieldNumber)
{
    if (fieldNumber >= 0 || fieldNumber <= 5)
    {
        int k = data->fieldPosition[fieldNumber];
        return &data->buffer[k];
    }
    else
        return '\0';
}

int32_t getFieldInteger(USER_DATA *data, uint8_t fieldNumber)
{
    if ((fieldNumber >= 0 || fieldNumber <= 5)
            && data->fieldType[fieldNumber] == 'n')
    {
        return strToInt(data, fieldNumber);
    }
    else
        return 0;

}

int strToInt(USER_DATA *data, uint8_t fieldNumber)
{
    int i = data->fieldPosition[fieldNumber];
    int cint = 0;
    while (data->buffer[i] != '\0')
    {
        cint *= 10;
        cint += data->buffer[i] - '0';
        i++;
    }

    return cint;
}

bool isCommand(USER_DATA *data, const char strCommand[], uint8_t minArguments)
{
    return strcomp(&data->buffer[data->fieldPosition[0]], (char*) strCommand)
            && (minArguments <= data->fieldCount - 1);
}

bool strcomp(char *arg1, char *arg2)
{
    int i = 0;
    while ((arg1[i] != '\0') && (arg2[i] != '\0'))
    {
        if (arg1[i] - arg2[i] != 0)
        {
            return 0;
        }
        i++;
    }
    return (arg1[i] == '\0' && arg2[i] == '\0');
}
