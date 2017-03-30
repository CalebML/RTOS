/* Standard includes. */
#include <stdlib.h>
#include <plib.h>
#include <stdint.h>

//include hardware stuff
#include <xc.h>

#include "leddrv.h"

uint8_t initializeLedDriver(void)
{
    /* LEDs off. */
    mPORTDClearBits(BIT_0 | BIT_1 | BIT_2);

    /* LEDs are outputs. */
    mPORTDSetPinsDigitalOut(BIT_0 | BIT_1 | BIT_2);

    /*return*/
     return 0;
}


uint8_t readLED(uint8_t ledNum)
{
    /*change 0, 1, and 2 into 1, 2, and 4*/
    ledNum++;
    if(ledNum == 3)
        ledNum = 4;

    /*return value of requested LED*/
    return LATD & ledNum;
}


uint8_t setLED(uint8_t ledNum, uint8_t value)
{
    /*change 0, 1, and 2 into 1, 2, and 4*/
    ledNum++;
    if(ledNum == 3)
        ledNum = 4;

    /*Set LED to requested value value*/
    if(value)
        LATDSET = ledNum;
    else
        LATDCLR = ledNum;

    return 0;
}


uint8_t toggleLED(uint8_t ledNum)
{
    /*change 0, 1, and 2 into 1, 2, and 4*/
    ledNum++;
    if(ledNum == 3)
        ledNum = 4;

    /*Set LED to requested value value*/
    LATDINV = ledNum;

    return 0;
}