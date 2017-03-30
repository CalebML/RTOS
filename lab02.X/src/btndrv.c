/* Standard includes. */
#include <stdlib.h>
#include <plib.h>
#include <stdint.h>

//include hardware stuff
#include <xc.h>

#include "btndrv.h"

uint8_t pollAllButtons(void)
{
    uint8_t retVal = 0;

    /*check each button*/
    if( pollButton(1) )
        retVal = 1;
    else if( pollButton(2) )
        retVal = 2;
    else if( pollButton(3) )
        retVal = 3;

    return retVal;
}


uint8_t pollButton(uint8_t btnNum)
{
    uint16_t portValue;
    uint8_t retVal = 0;
    uint8_t release = 0;

    /*change 1, 2, and 3 into 0x40, 0x80, and 0x2000*/
    if(btnNum == 1)
        portValue = 0x40;
    else if(btnNum == 2)
        portValue = 0x80;
    else
        portValue = 0x2000;

    /*check button*/
    if( !(PORTD & portValue) )       //if the Button is pressed
        retVal = debounce(btnNum, 1);

    if(retVal)
    {
        while(!release)
        {
            if( PORTD & portValue )       //if the Button is not pressed
                release = debounce(btnNum, 0);
        }
    }

    return retVal;
}

static uint8_t debounce(uint8_t btnNum, uint8_t initValue)
{
    //const TickType_t xDelay = 10;   //delay period - mS;
    uint16_t portValue;
    uint8_t retVal = 0;
    uint16_t delay = 0xFF;

    /*change 1, 2, and 3 into 0x40, 0x80, and 0x2000*/
    if(btnNum == 1)
        portValue = 0x40;
    else if(btnNum == 2)
        portValue = 0x80;
    else
        portValue = 0x2000;

    /*delay*/
   // vTaskDelay(10);
    while(delay)
        --delay;

    /*check for change*/
    if( (PORTD & portValue) != initValue)
        retVal = 1;

    return retVal;
}