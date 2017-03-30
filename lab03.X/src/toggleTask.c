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
    QueueHandle_t xQueue;
    tCOMMAND command;

    //xTaskParameter_t *pxTaskParameter;
    TickType_t xDelay = 500;
    //int LEDNum;

    //LEDNum = ( (xTaskParameter_t *) pvParameters )->usLEDNumber;
    //LEDNum = pxTaskParameter->usLEDNumber;

    xQueue = ( (xTaskParameter_t *) pvParameters )->xQueue;

    while(1)
    {
        //Toggle LED
        toggleLED( ( (xTaskParameter_t *) pvParameters )->usLEDNumber );
        //Delay xDelay miliseconds
        vTaskDelay( xDelay );

        //check the queue for messages
        while( uxQueueMessagesWaiting( xQueue ) )
        {
            //get the message from the queue
            xQueueReceive(xQueue, &command, 0);

            //handle command
            if( command == SLOWDOWN )
            {
                if( xDelay < 1000 )
                    xDelay = xDelay + 50;
            }
            else
            {
                if( xDelay > 200 )
                    xDelay = xDelay - 50;
            }
        }
    }
}