/**
 * mcu.c
 * 
 * This file holds the implementation for functions defined in mcu.h
 * 
 * @author Dean Biskup and Mitalee Bharadwaj
 * University of Illinois, ADSL (ECE 395) Fall 2019
 */
#include "LPC11xx.h"
#include "mcu.h"

int configureGPIO(int axis) {
  if (axis == X_AXIS) {
    LPC_GPIO0->DIR |= (1<<GPIO0_STEP_STP);
    LPC_GPIO0->DIR |= (1<<GPIO0_STEP_DIR);
    LPC_GPIO0->DIR |= (1<<GPIO0_STEP_MS1);
    LPC_GPIO0->DIR |= (1<<GPIO0_STEP_MS2);
    LPC_GPIO0->DIR |= (1<<GPIO0_STEP_EN);
  } else if (axis == Y_AXIS) {
    LPC_GPIO1->DIR |= (1<<GPIO1_STEP_STP);
    LPC_GPIO1->DIR |= (1<<GPIO1_STEP_DIR);
    LPC_GPIO1->DIR |= (1<<GPIO1_STEP_MS1);
    LPC_GPIO1->DIR |= (1<<GPIO1_STEP_MS2);
    LPC_GPIO1->DIR |= (1<<GPIO1_STEP_EN);
  } else {
    return 0; // invalid axis
  }
  return 1; // success
}

int resetEDPins(int axis) {
  if (axis == X_AXIS) {
    LPC_GPIO0->DATA &= ~(1 << GPIO0_STEP_STP);
    LPC_GPIO0->DATA &= ~(1 << GPIO0_STEP_DIR);
    LPC_GPIO0->DATA &= ~(1 << GPIO0_STEP_MS1);
    LPC_GPIO0->DATA &= ~(1 << GPIO0_STEP_MS2);
    LPC_GPIO0->DATA |= (1 <<  GPIO0_STEP_EN);
  } else if (axis == Y_AXIS) {
    LPC_GPIO1->DATA &= ~(1 << GPIO1_STEP_STP);
    LPC_GPIO1->DATA &= ~(1 << GPIO1_STEP_DIR);
    LPC_GPIO1->DATA &= ~(1 << GPIO1_STEP_MS1);
    LPC_GPIO1->DATA &= ~(1 << GPIO1_STEP_MS2);
    LPC_GPIO1->DATA |= (1 <<  GPIO1_STEP_EN);
  } else {
    return 0; // invalid axis
  }
  return 1; // success
}

int moveMotor(int axis, int distance, int direction) {
  return 1;
}
