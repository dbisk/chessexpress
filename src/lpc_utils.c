/**
 * lpc_utils.c
 * 
 * Implementations of functions declared in lpc_utils.h.
 * 
 * @author Dean Biskup and Mitalee Bharadwaj
 * University of Illinois, ADSL (ECE 395) Fall 2019
 */
#include "LPC11xx.h"
#include "lpc_utils.h"

void setPinGPIO0(int pin, int level) {
  if (level == PIN_LOW)
    LPC_GPIO0->DATA &= ~(1<<pin);
  else if (level == PIN_HIGH)
    LPC_GPIO0->DATA |= (1<<pin);
}

void setPinGPIO1(int pin, int level) {
  if (level == PIN_LOW)
    LPC_GPIO1->DATA &= ~(1<<pin);
  else if (level == PIN_HIGH)
    LPC_GPIO1->DATA |= (1<<pin);
}

void lpcWait(int time) {
  int i;
  for (i = 0; i < time; i++) ;
}
