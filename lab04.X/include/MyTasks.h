#ifndef MYTASK_H
#define MYTASK_H

typedef struct xTASK_PARAMETER {
    uint8_t usLEDNumber;                   /* The number of the LED to toggle. */
    QueueHandle_t xQueue;
    TaskHandle_t nextHandle;
} xTaskParameter_t;

typedef enum {SPEEDUP, SLOWDOWN} tCOMMAND;

/****************************
 * control task
 ***************************/
void taskControlLEDs(void *pvParameters);

/****************************
 * Speed up the LED
 ***************************/
void increaseSpeed(QueueHandle_t xQueue);

/****************************
 * Slow down the LED
 ***************************/
void decreaseSpeed(QueueHandle_t xQueue);

/****************************
 * Switch task to next LED
 ***************************/
void nextLED(TaskHandle_t *handle, uint8_t LEDNum, QueueHandle_t *xQueue);


#endif