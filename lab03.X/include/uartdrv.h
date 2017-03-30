#ifndef UARTDRV
#define UARTDRV


/****************************
 * sets up the UART
 ***************************/
void initUART(UART_MODULE umPortNum, uint32_t ui32WantedBaud);


/****************************
 * Sends 1 byte (char on the UART)
 ***************************/
void vUartPutC(UART_MODULE umPortNum, char cByte);


/****************************
 * Sends a string on the UART
 ***************************/
void vUartPutStr(UART_MODULE umPortNum, char *pString, int iStrLen);


#endif