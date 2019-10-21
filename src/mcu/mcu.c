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

// For 1/8 step, 0x7FF. For full step, 0x3FFF
#define WAIT_TIME 0x3FFF

int configureGPIO(int axis) {
  if (axis == X_AXIS) {
    LPC_GPIO0->DIR |= (1<<X_AXIS_STP);
    LPC_GPIO0->DIR |= (1<<X_AXIS_DIR);
    LPC_GPIO0->DIR |= (1<<X_AXIS_EN);
  } else if (axis == Y_AXIS) {
    LPC_GPIO0->DIR |= (1<<Y_AXIS_STP);
    LPC_GPIO0->DIR |= (1<<Y_AXIS_DIR);
    LPC_GPIO0->DIR |= (1<<Y_AXIS_EN);
  } else {
    return 0; // invalid axis
  }
  LPC_GPIO0->DIR |= (1 << MAGNET_PIN);
  return 1; // success
}

int resetEDPins(int axis) {
  if (axis == X_AXIS) {
    setPinGPIO0(X_AXIS_STP, PIN_LOW);
    setPinGPIO0(X_AXIS_DIR, PIN_LOW);
    setPinGPIO0(X_AXIS_EN, PIN_HIGH);
  } else if (axis == Y_AXIS) {
    setPinGPIO0(Y_AXIS_STP, PIN_LOW);
    setPinGPIO0(Y_AXIS_DIR, PIN_LOW);
    setPinGPIO0(Y_AXIS_EN, PIN_HIGH);
  } else {
    return 0; // invalid axis
  }
  return 1; // success
}

int moveMotor(int axis, int distance, int direction) {
  // assume GPIOs have been configured
  int numSteps = distance * HALF_SQUARE;
  if (axis == X_AXIS) {
    setPinGPIO0(X_AXIS_EN, PIN_LOW); // enable the motor control (active low)
    setPinGPIO0(X_AXIS_DIR, direction); // set the direction
    while (numSteps != 0) {
      setPinGPIO0(X_AXIS_STP, PIN_HIGH);
      lpcWait(WAIT_TIME);
      setPinGPIO0(X_AXIS_STP, PIN_LOW);
      lpcWait(WAIT_TIME);
      numSteps--;
    }
  } else if (axis == Y_AXIS) {
    setPinGPIO0(Y_AXIS_EN, PIN_LOW); // enable the motor control (active low)
    setPinGPIO0(Y_AXIS_DIR, direction); // set the direction
    while (numSteps != 0) {
      setPinGPIO0(Y_AXIS_STP, PIN_HIGH);
      lpcWait(WAIT_TIME);
      setPinGPIO0(Y_AXIS_STP, PIN_LOW);
      lpcWait(WAIT_TIME);
      numSteps--;
    }
  } else {
    return 0; // invalid axis
  }

  // reset the ED pins to their default state
  resetEDPins(axis);
  return 1; // success
}
