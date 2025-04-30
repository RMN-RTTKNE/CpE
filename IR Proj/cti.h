#ifndef CTI__H
#define CTI__H
#include <stdbool.h>
#include <stdint.h>
#define MAX_CHARS 80
#define MAX_FIELDS 5
typedef struct _USER_DATA
{
    char buffer[MAX_CHARS + 1];
    uint8_t fieldCount;
    uint8_t fieldPosition[MAX_FIELDS];
    char fieldType[MAX_FIELDS];
} USER_DATA;

char getcUart0();
void getsUart0(USER_DATA *data);
void parseFields(USER_DATA *data);
char* getFieldString(USER_DATA *data, uint8_t fieldNumber);
int32_t getFieldInteger(USER_DATA *data, uint8_t fieldNumber);
int strToInt(USER_DATA *data, uint8_t fieldNumber);
bool isCommand(USER_DATA *data, const char strCommand[], uint8_t minArguments);
bool strcomp(char *arg1, char *arg2);
void initUart0();
void putcUart0(char c);
void putsUart0(char *str);

#endif
