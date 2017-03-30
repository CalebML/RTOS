#ifndef LEDDRV_H
#define LEDDRV_H

/****************************
 * uint8_t initializeLedDriver(void)
 *
 * This function will setup the ports for the LEDs and set them to the OFF state.
 * Returns a 0 for success, any other value for failure.
 *
 *  (desc from lab)
 ***************************/
uint8_t initializeLedDriver(void);


/****************************
 * uint8_t readLed(uint8_t ledNum)
 *
1. This function will return the current state of the given LED Number. 0 for off, 1 for
        on, any other number is an error condition
2. ledNum is defined as:
    1. 0 = LED1 (RD0)
    2. 1 = LED2 (RD1)
    3. 2 = LED3 (RD2)
 *
 *  (desc from lab)
 ***************************/
uint8_t readLED(uint8_t ledNum);


/****************************
 * uint8_t setLED(uint8_t ledNum, uint8_t value)
 *
Sets ledNum to a state of OFF or ON depending on value. If value is 0 turn OFF
LED, any other value will turn ON LED. Returns a 0 for success or any other
number for failure
 *
 *  (desc from lab)
 ***************************/
uint8_t setLED(uint8_t ledNum, uint8_t value);


/****************************
 * uint8_t toggleLED(uint8_t ledNum)
 *
This function will toggle the current state of the LED. If the LED is OFF it will turn
it ON, if LED is ON it will turn it OFF. Returns 0 for success, any other value for
error.
 *
 *  (desc from lab)
 ***************************/
uint8_t toggleLED(uint8_t ledNum);

#endif