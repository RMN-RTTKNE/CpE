#include "led.h"
#include "cti.h"
#include "systick.h"
#include "clock.h"
#include <stdint.h>
#include <stdbool.h>
#include "tm4c123gh6pm.h"
#include "pwm.h"
#include "wait.h"
#include "receive.h"
#include "toAsciiHex.h"

int main()
{
    initSystemClockTo40Mhz();
    initUart0();
    initPWM();
    init_led();
    init_SysTick();
    init_receive();
    USER_DATA data;
    char buffer[9] = { 0 };

    while (1)
    {
        getsUart0(&data);
        parseFields(&data);

        bool valid = false;
        if (isCommand(&data, "READ", 1))
        {
            int32_t display = getFieldInteger(&data, 1);
            valid = true;
            if (display)
            {
                toAsciiHex(buffer, bits);
                putsUart0("0x");
                putsUart0(buffer);
                putcUart0('\n');
            }
            else if (display == 0)
            {
                putsUart0("Saved\n");
                save(bits);
            }
            else
            {
                valid = false;
            }
        }
        if (isCommand(&data, "LAST", 1))
        {
            int n = 0;
            n = getFieldInteger(&data, 1);
            if (n > 0 && n < 10)
            {
                valid = true;
                int i;
                for (i = num_val - 1; i >= num_val - n; i--)
                {
                    toAsciiHex(buffer, last[i]);
                    putsUart0("0x");
                    putsUart0(buffer);
                    putcUart0('\n');
                }
            }
            else
            {
                valid = false;
            }
        }
        if (isCommand(&data, "SEND", 1))
        {
            int num = getFieldInteger(&data, 1);
            if (num == 1)
            {
                int8_t transmit = getFieldInteger(&data, 2);
                valid = true;
                preamble();
                send(transmit);
                tail();
            }
            else if (num == 2)
            {
                int32_t transmit = getFieldInteger(&data, 2);
                int32_t transmit2 = getFieldInteger(&data, 3);
                valid = true;
                preamble();
                send(transmit);
                send(transmit2);
                tail();
            }
            else if (num == 3)
            {
                int32_t transmit = getFieldInteger(&data, 2);
                int32_t transmit2 = getFieldInteger(&data, 3);
                int32_t transmit3 = getFieldInteger(&data, 4);
                valid = true;
                preamble();
                send(transmit);
                send(transmit2);
                send(transmit3);
                tail();
            }
            else if (num == 4)
            {
                int32_t transmit = getFieldInteger(&data, 2);
                int32_t transmit2 = getFieldInteger(&data, 3);
                int32_t transmit3 = getFieldInteger(&data, 4);
                int32_t transmit4 = getFieldInteger(&data, 5);
                valid = true;
                preamble();
                send(transmit);
                send(transmit2);
                send(transmit3);
                send(transmit4);
                tail();
            }
            else
            {
                valid = false;
            }

        }
        // Look for error
        if (!valid)
        {
            putsUart0(": Invalid command\n");
        }
    }
    return 0;
}
