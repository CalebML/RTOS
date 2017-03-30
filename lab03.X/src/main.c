/*
    FreeRTOS V7.1.1 - Copyright (C) 2012 Real Time Engineers Ltd.


 ***************************************************************************
 *                                                                       *
 *    FreeRTOS tutorial books are available in pdf and paperback.        *
 *    Complete, revised, and edited pdf reference manuals are also       *
 *    available.                                                         *
 *                                                                       *
 *    Purchasing FreeRTOS documentation will not only help you, by       *
 *    ensuring you get running as quickly as possible and with an        *
 *    in-depth knowledge of how to use FreeRTOS, it will also help       *
 *    the FreeRTOS project to continue with its mission of providing     *
 *    professional grade, cross platform, de facto standard solutions    *
 *    for microcontrollers - completely free of charge!                  *
 *                                                                       *
 *    >>> See http://www.FreeRTOS.org/Documentation for details. <<<     *
 *                                                                       *
 *    Thank you for using FreeRTOS, and thank you for your support!      *
 *                                                                       *
 ***************************************************************************


    This file is part of the FreeRTOS distribution.

    FreeRTOS is free software; you can redistribute it and/or modify it under
    the terms of the GNU General Public License (version 2) as published by the
    Free Software Foundation AND MODIFIED BY the FreeRTOS exception.
    >>>NOTE<<< The modification to the GPL is included to allow you to
    distribute a combined work that includes FreeRTOS without being obliged to
    provide the source code for proprietary components outside of the FreeRTOS
    kernel.  FreeRTOS is distributed in the hope that it will be useful, but
    WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
    or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
    more details. You should have received a copy of the GNU General Public
    License and the FreeRTOS license exception along with FreeRTOS; if not it
    can be viewed here: http://www.freertos.org/a00114.html and also obtained
    by writing to Richard Barry, contact details for whom are available on the
    FreeRTOS WEB site.

    1 tab == 4 spaces!

 ***************************************************************************
 *                                                                       *
 *    Having a problem?  Start by reading the FAQ "My application does   *
 *    not run, what could be wrong?                                      *
 *                                                                       *
 *    http://www.FreeRTOS.org/FAQHelp.html                               *
 *                                                                       *
 ***************************************************************************


    http://www.FreeRTOS.org - Documentation, training, latest information,
    license and contact details.

    http://www.FreeRTOS.org/plus - A selection of FreeRTOS ecosystem products,
    including FreeRTOS+Trace - an indispensable productivity tool.

    Real Time Engineers ltd license FreeRTOS to High Integrity Systems, who sell
    the code with commercial support, indemnification, and middleware, under
    the OpenRTOS brand: http://www.OpenRTOS.com.  High Integrity Systems also
    provide a safety engineered and independently SIL3 certified version under
    the SafeRTOS brand: http://www.SafeRTOS.com.
 */



/* Hardware include. */
#include <xc.h>

/* Standard includes. */
#include <stdint.h>
#include <plib.h>

/* FreeRTOS includes. */
#include <FreeRTOS.h>
#include "task.h"
#include "queue.h"

/*Lab2 Files*/
#include "leddrv.h"
#include "btndrv.h"
#include "MyTasks.h"


/* Hardware configuration. */
#pragma config FPLLMUL = MUL_20, FPLLIDIV = DIV_2, FPLLODIV = DIV_1, FWDTEN = OFF
#pragma config POSCMOD = HS, FNOSC = PRIPLL, FPBDIV = DIV_2, CP = OFF, BWP = OFF
#pragma config PWP = OFF /*, UPLLEN = OFF, FSRSSEL = PRIORITY_7 */

/* Time is measured in "ticks".  The tick rate is set by the configTICK_RATE_HZ
configuration parameter (defined in FreeRTOSConfig.h).  If configTICK_RATE_HZ
is equal to or less than 1000 (1KHz) then portTICK_RATE_MS can be used to
convert a time in milliseconds into a time in ticks. */
#define mainTOGGLE_PERIOD ( 200UL / portTICK_RATE_MS )


/* Performs the hardware initialisation to ready the hardware to run this example */
static void prvSetupHardware(void);



/*-----------------------------------------------------------*/
int main(void)
{
    //static TaskHandle_t controlTaskHandle[3];
    static TaskHandle_t controlTask0Handle;
    static TaskHandle_t controlTask1Handle;
    static TaskHandle_t controlTask2Handle;

    static const xTaskParameter_t xTask0Parameters = {0 /* LED1 */, 
                                                    NULL /* No Queue */,
                                                    &controlTask1Handle /*next task*/};
    static const xTaskParameter_t xTask1Parameters = {1 /* LED2 */, 
                                                    NULL /* No Queue */,
                                                    &controlTask2Handle /*next task*/};
    static const xTaskParameter_t xTask2Parameters = {2 /* LED3 */, 
                                                    NULL /* No Queue */,
                                                    &controlTask0Handle /*next task*/};

    /* Perform any hardware initialisation that may be necessary. */
    prvSetupHardware();


    xTaskCreate(taskControlLEDs,
            "Control Task 0",
            configMINIMAL_STACK_SIZE,
            (void *) &xTask0Parameters,
            1,
            &controlTask0Handle);

    xTaskCreate(taskControlLEDs,
            "Control Task 1",
            configMINIMAL_STACK_SIZE,
            (void *) &xTask1Parameters,
            1,
            &controlTask1Handle);

    xTaskCreate(taskControlLEDs,
            "Control Task 2",
            configMINIMAL_STACK_SIZE,
            (void *) &xTask2Parameters,
            1,
            &controlTask2Handle);


    /* Start the scheduler so the tasks start executing.  This function should not return. */
    vTaskStartScheduler();
}


static void prvSetupHardware(void)
{
    /* Setup the CPU clocks, and configure the interrupt controller. */
    SYSTEMConfigPerformance(configCPU_CLOCK_HZ);
    mOSCSetPBDIV(OSC_PB_DIV_2);
    INTEnableSystemMultiVectoredInt();

    /*Set up LEDs*/
    initializeLedDriver();

    /*Set up UART1*/
    initUART(UART1, 9600);

    /*enable pullups on the switches*/
    ConfigCNPullups(CN15_PULLUP_ENABLE | CN16_PULLUP_ENABLE | CN19_PULLUP_ENABLE);
}

