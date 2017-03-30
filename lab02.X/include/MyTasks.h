#ifndef MYTASK_H
#define MYTASK_H

typedef struct xTASK_PARAMETER {
    uint8_t usLEDNumber;                   /* The number of the LED to toggle. */
} xTaskParameter_t;

/****************************
 * control task
 ***************************/
void taskControlLEDs(void);

/****************************
 * starts a toggle LED task
 ***************************/
TaskHandle_t startToggle(uint8_t runningTasks);

/****************************
 * deletes a toggle LED task
 ***************************/
void deleteToggle(TaskHandle_t handle);

/****************************
 * suspend a toggle LED task
 ***************************/
uint8_t suspendToggle(TaskHandle_t *handles, uint8_t runningTasks, uint8_t LEDsSuspended);

///****************************
// * resumes a toggle LED task
// ***************************/
//void resumeToggle(uint8_t runningTasks);


#endif