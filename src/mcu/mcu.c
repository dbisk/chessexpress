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
#include "../lpc_utils.h"

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
    setPinGPIO0(GPIO0_STEP_STP, PIN_LOW);
    setPinGPIO0(GPIO0_STEP_DIR, PIN_LOW);
    setPinGPIO0(GPIO0_STEP_MS1, PIN_HIGH);
    setPinGPIO0(GPIO0_STEP_MS2, PIN_HIGH);
    setPinGPIO0(GPIO0_STEP_EN, PIN_HIGH);
  } else if (axis == Y_AXIS) {
    setPinGPIO1(GPIO1_STEP_STP, PIN_LOW);
    setPinGPIO1(GPIO1_STEP_DIR, PIN_LOW);
    setPinGPIO1(GPIO1_STEP_MS1, PIN_HIGH);
    setPinGPIO1(GPIO1_STEP_MS2, PIN_HIGH);
    setPinGPIO1(GPIO1_STEP_EN, PIN_HIGH);
  } else {
    return 0; // invalid axis
  }
  return 1; // success
}

int moveMotor(int axis, int distance, int direction) {
  // assume GPIOs have been configured
  int numSteps = distance * HALF_SQUARE;
  if (axis == X_AXIS) {
    setPinGPIO0(GPIO0_STEP_EN, PIN_LOW); // enable the motor control
    setPinGPIO0(GPIO0_STEP_DIR, direction); // set the direction
    while (numSteps != 0) { // @TODO: change this to include distance
      setPinGPIO0(GPIO0_STEP_STP, PIN_HIGH);
      lpcWait(0x7FFF); // @TODO: test this time // 0x07FF
      setPinGPIO0(GPIO0_STEP_STP, PIN_LOW);
      lpcWait(0x7FFF);
      numSteps--;
    }
  } else if (axis == Y_AXIS) {
    // @TODO: Should be the same as X_AXIS but with GPIO1
  } else {
    return 0; // invalid axis
  }

  // reset the ED pins to their default state
  resetEDPins(axis);
  return 1; // success
}
