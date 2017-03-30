/* Standard includes. */
#include <stdlib.h>
#include <plib.h>
#include <stdint.h>

//include hardware stuff
#include <xc.h>

#include <FreeRTOS.h>
#include "task.h"
#include "queue.h"

#include "toggleTask.h"
#include "leddrv.h"
#include "MyTasks.h"



/****************************
 * LED toggle task
 ***************************/
void taskToggleLEDs(void *pvParameters)
{
    //xTaskParameter_t *pxTaskParameter;
    const TickType_t xDelay = 500;
    //int LEDNum;

    //LEDNum = ( (xTaskParameter_t *) pvParameters )->usLEDNumber;
    //LEDNum = pxTaskParameter->usLEDNumber;

    while(1)
    {
        toggleLED( ( (xTaskParameter_t *) pvParameters )->usLEDNumber );
        vTaskDelay( xDelay );
    }
}