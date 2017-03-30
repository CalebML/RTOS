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


/****************************
 * control task
 ***************************/
void taskControlLEDs(void)
{
    uint8_t button = 0;
    uint8_t runningTasks = 0;
    uint8_t LEDsSuspended = 0;
    TaskHandle_t LEDTaskHandle[3];
    const TickType_t xDelay = 100;

    while(1)
    {
        button = pollAllButtons();

        if( (button == 1) & (runningTasks < 3) )
        {
            LEDTaskHandle[runningTasks] = startToggle(runningTasks);
            runningTasks = runningTasks + 1;
        }
        else if( (button == 2) & (runningTasks > 0) )
        {
            deleteToggle(LEDTaskHandle[runningTasks-1]);

            if(LEDsSuspended >= runningTasks)
            {
                LEDsSuspended = LEDsSuspended-1;
            }
            
            runningTasks = runningTasks - 1;
        }
        else if( button == 3 )
            LEDsSuspended = suspendToggle(LEDTaskHandle, runningTasks, LEDsSuspended);

        
        vTaskDelay( xDelay );
    }
}

TaskHandle_t startToggle(uint8_t runningTasks)
{
    TaskHandle_t handle;
    static xTaskParameter_t xTaskParameterarray[3];

    xTaskParameter_t tempTask0Patameter = {0};
    xTaskParameterarray[0] = tempTask0Patameter;

    xTaskParameter_t tempTask1Patameter = {1};
    xTaskParameterarray[1] = tempTask1Patameter;

    xTaskParameter_t tempTask2Patameter = {2};
    xTaskParameterarray[2] = tempTask2Patameter;


    xTaskCreate(taskToggleLEDs,
            "LED Task" + (char)(((int)'0')+ runningTasks),
            configMINIMAL_STACK_SIZE,
            (void *) &xTaskParameterarray[runningTasks],
            1,
            &handle);
    

    return handle;
}

/****************************
 * deletes a toggle LED task
 ***************************/
void deleteToggle(TaskHandle_t handle)
{
    vTaskDelete(handle);
}

/****************************
 * suspend a toggle LED task
 ***************************/
uint8_t suspendToggle(TaskHandle_t *handles, uint8_t runningTasks, uint8_t LEDsSuspended)
{
    int i;

    if( runningTasks > LEDsSuspended )
    {
        for(i = LEDsSuspended; i < runningTasks; i = i+1)
        {
            vTaskSuspend(handles[i]);
            LEDsSuspended = LEDsSuspended + 1;
        }
    }
    else
    {
        for(i = 0; i < LEDsSuspended; i = i+1)
        {
            vTaskResume(handles[i]);
        }
        LEDsSuspended = 0;
    }

    return LEDsSuspended;
}

///****************************
// * resumes a toggle LED task
// ***************************/
//void resumeToggle(uint8_t runningTasks)
//{
//
//}