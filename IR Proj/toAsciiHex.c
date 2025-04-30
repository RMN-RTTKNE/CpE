#include "toAsciiHex.h"
#include <stdint.h>
void toAsciiHex(char *buffer, uint32_t Val)
{
    int i;
    int temp;
    for (i = 7; i >= 0; i--)
    {
        temp = Val % 16;
        if (temp < 10)
        {
            buffer[i] = (char) (temp + 48);
        }
        else if (temp == 10)
        {
            buffer[i] = 'A';
        }
        else if (temp == 11)
        {
            buffer[i] = 'B';
        }
        else if (temp == 12)
        {
            buffer[i] = 'C';
        }
        else if (temp == 13)
        {
            buffer[i] = 'D';
        }
        else if (temp == 14)
        {
            buffer[i] = 'E';
        }
        else if (temp == 15)
        {
            buffer[i] = 'F';
        }
        Val /= 16;
    }
    buffer[8] = '\0';
}

