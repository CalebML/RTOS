/* Standard includes. */
#include <stdlib.h>
#include <plib.h>
#include <stdint.h>

//include hardware stuff
#include <xc.h>

#include <FreeRTOS.h>
#include "task.h"

/****************************
 * sets up the UART
 ***************************/
void initUART(UART_MODULE umPortNum, uint32_t ui32WantedBaud)
{
    UARTSetDataRate(umPortNum, (uint32_t)configPERIPHERAL_CLOCK_HZ, ui32WantedBaud);

    UARTEnable(umPortNum, UART_ENABLE_FLAGS(UART_PERIPHERAL | UART_TX));

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