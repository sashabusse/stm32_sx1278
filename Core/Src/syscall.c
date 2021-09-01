
#include "stm32f1xx.h"

int _write(int file, char *buf, int nbytes)
{
    for (int i = 0; i < nbytes; i++)
    {
        ITM_SendChar(buf[i]);
    }
    return nbytes;
}