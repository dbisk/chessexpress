/**
 * lpc_utils.h
 * 
 * Declares some functions that are useful utilities for the LPC1114.
 * 
 * @author Dean Biskup and Mitalee Bharadwaj
 * University of Illinois, ADSL (ECE 395) Fall 2019
 */
#ifndef _LPCUTILS_H_
#define _LPCUTILS_H_

#define PIN_HIGH  1
#define PIN_LOW   0

/**
 * setPinGPIO0(pin, level)
 * 
 * Sets the corresponding GPIO0 pin.
 * 
 * @param pin the pin number to set low
 * @param level the level to set the pin at (high or low)
 */
void setPinGPIO0(int pin, int level);

/**
 * setPinGPIO1(pin, level)
 * 
 * Sets the corresponding GPIO1 pin.
 * 
 * @param pin the pin number to set low
 * @param level the level to set the pin at (high or low)
 */
void setPinGPIO1(int pin, int level);

/**
 * lpcWait(time)
 * 
 * The processor spins not doing anything for given amount of time.
 * 
 * @param time the amount of time to wait
 */
void lpcWait(int time);

#endif // _LPCUTILS_H_
