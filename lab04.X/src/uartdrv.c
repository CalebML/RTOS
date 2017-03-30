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
#include "uartdrv.h"

/****************************
 * sets up the UART
 ***************************/
void initUART(UART_MODULE umPortNum, uint32_t ui32WantedBaud, QueueHandle_t *xQueue)
{
    
    //create a queue
    *xQueue = xQueueCreate( 5, sizeof(char[50]) );

     xTaskParameter_t xuartTaskParameters = {0 /* NO LED */,
                                             *xQueue /* Queue */,
                                             NULL /* NO next task */};

    UARTSetDataRate(umPortNum, (uint32_t)configPERIPHERAL_CLOCK_HZ, ui32WantedBaud);

    UARTEnable(umPortNum, UART_ENABLE_FLAGS(UART_PERIPHERAL | UART_TX));

    //create UART task and set up queue
    xTaskCreate(uartTask,
            "UART task",
            configMINIMAL_STACK_SIZE,
            (void *) &xuartTaskParameters,
            1,
            NULL);
}


/****************************
 * Sends 1 byte (char on the UART)
 ***************************/
void vUartPutC(UART_MODULE umPortNum, char cByte)
{
    const TickType_t xDelay = 2;

    while( UARTTransmitterIsReady(umPortNum) == 0 )
    {
        vTaskDelay( xDelay );
    }
    UARTSendDataByte(umPortNum, cByte);
}


/****************************
 * Sends a string on the UART
 ***************************/
void vUartPutStr(UART_MODULE umPortNum, char *pString, int iStrLen)
{
    int count = 0;

    while(count < iStrLen)
    {
        vUartPutC(umPortNum, pString[count]);

        count = count + 1;
    }
}


/****************************
 * handles the UART queue
 ***************************/
void uartTask(void *pvParameters)
{
    QueueHandle_t xQueue = ( (xTaskParameter_t *) pvParameters )->xQueue;
    const TickType_t xDelay = 100;
    char message[50];

    while(1)
    {
        //check the queue for messages
        while( uxQueueMessagesWaiting( xQueue ) )
        {
            //get the message from the queue
            xQueueReceive(xQueue, &message, 0);

            //send the message
            vUartPutStr( UART1, message, strlen(message) );
        }

        //Delay xDelay miliseconds
        vTaskDelay( xDelay );
    }
}