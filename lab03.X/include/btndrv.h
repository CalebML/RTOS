#ifndef BTNDRV_H
#define BTNDRV_H

/****************************
 * uint8_t pollAllButtons(void)
 *
 * This function will check all buttons once for a press
 *
 * returns 0 for no press, 1-3 for button press
 *
 ***************************/
uint8_t pollAllButtons(void);

/****************************
 * uint8_t pollAllButtons(void)
 *
 * This function will check the button whos number is passed in once for a press
 *
 * returns 1 for a press, 0 for no press
 *
 ***************************/
uint8_t pollButton(uint8_t btnNum);

/****************************
 * uint8_t pollAllButtons(void)
 *
 * This function will check for debounce on the button number passed to it
 *
 * The second value passed to it is as follows:
 *      0 = 0-1 debounce
 *      1 = 1-0 debounce
 *
 * returns 1 for a change, 0 for no change
 *
 ***************************/
static uint8_t debounce(uint8_t btnNum, uint8_t initValue);

#endif