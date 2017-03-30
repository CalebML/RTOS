/* Standard includes. */
#include <stdlib.h>
#include <plib.h>
#include <stdint.h>

//include hardware stuff
#include <xc.h>

#include <FreeRTOS.h>
#include "task.h"
#include "queue.h"

#include "MyTasks.h"
#include "leddrv.h"
#include "btndrv.h"
#include "toggleTask.h"
#include "uartdrv.h"


/****************************
 * control task
 ***************************/
void taskControlLEDs(void *pvParameters)
{
    uint8_t button = 0;
    TaskHandle_t *handle = ( (xTaskParameter_t *) pvParameters )->nextHandle;
    QueueHandle_t xQueue;
    const TickType_t xDelay = 100;
    uint8_t LEDNum = ( (xTaskParameter_t *) pvParameters )->usLEDNumber;

    //create a queue
    xQueue = xQueueCreate( 5, sizeof(tCOMMAND) );
    xTaskParameter_t TaskParameter = {LEDNum, xQueue, NULL};


//    //set up TaskParameter
//    TaskParameter->usLEDNumber = LEDNum;
//    TaskParameter->xQueue = xQueue;

    //create LED toggle task
    xTaskCreate(taskToggleLEDs,
            "LED Task " + (char)( ((int)'0')+ LEDNum ),
            configMINIMAL_STACK_SIZE,
            (void *) &TaskParameter,
            1,
            NULL);

    //suspend all but task 0
    if(LEDNum > 0)
    {
        vTaskSuspend( NULL );
    }

    //task is now running
    while(1)
    {
        button = pollAllButtons();

        if( button == 1 )
        {
            increaseSpeed(xQueue);
        }
        else if( button == 2 )
        {
            decreaseSpeed(xQueue);
        }
        else if( button == 3 )
        {
            nextLED(*handle, LEDNum);
        }
        
        vTaskDelay( xDelay );
    }
}

/****************************
 * Speed up the LED
 ***************************/
void increaseSpeed(QueueHandle_t xQueue)
{
    tCOMMAND command = SPEEDUP;
    xQueueSendToBack(xQueue, &command, 0);
}

/****************************
 * Slow down the LED
 ***************************/
void decreaseSpeed(QueueHandle_t xQueue)
{
    tCOMMAND command = SLOWDOWN;
    xQueueSendToBack(xQueue, &command, 0);
}

/****************************
 * Switch task to next LED
 ***************************/
void nextLED(TaskHandle_t *handle, uint8_t LEDNum)
{
    //set up the message
    LEDNum = LEDNum + 1;
    if( LEDNum > 2 )
        LEDNum = 0;

    char message[21] = "LED * IS NOW ACTIVE\r\n";
    //insert LED number
    message[4] = (char)( ((int)'0')+ LEDNum );

    //send the message
    vUartPutStr(UART1, message, 21);

    //switch tasks
    vTaskResume( handle );
    vTaskSuspend( NULL );
}

