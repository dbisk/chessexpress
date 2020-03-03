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

#define CORNER_DIST 30

// static int magnetX, magnetY;
int moveMotorHelper(int axis, int distance, int direction);
int magnetX, magnetY;

void configureGPIO() {
  // configure IOCONFIG block with pin functions
  LPC_IOCON->R_PIO0_11 = (1UL << 0);

  // initialize GPIO directions
  LPC_GPIO0->DIR |= (1 << X_AXIS_STP);
  LPC_GPIO0->DIR |= (1 << X_AXIS_DIR);
  LPC_GPIO0->DIR |= (1 << X_AXIS_EN);
  LPC_GPIO0->DIR &= ~(1 << X_AXIS_BUT);
  LPC_GPIO0->DIR |= (1 << Y_AXIS_STP);
  LPC_GPIO0->DIR |= (1 << Y_AXIS_DIR);
  LPC_GPIO0->DIR |= (1 << Y_AXIS_EN);
  LPC_GPIO0->DIR &= ~(1 << Y_AXIS_BUT);
  LPC_GPIO0->DIR |= (1 << MAGNET_PIN);
  magnetX = 0;
  magnetY = 0;
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

int moveMotor(int xPos, int yPos) {
  if (xPos > 8 || xPos < 0 || yPos > 7 || yPos < 0) {
    return 0; // failure
  }
  if (xPos == magnetX && yPos == magnetY) {
    return 1;
  }

  int xDist = 2 * (xPos - magnetX);
  int yDist = 2 * (yPos - magnetY);
  int xDir = FORWARD;
  int yDir = FORWARD;
  
  if (xDist < 0) {
    xDir = BACKWARD;
    xDist = -xDist;
  }

  if (yDist < 0) {
    yDir = BACKWARD;
    yDist = -yDist;
  }

  // first move the motor to the corner of the square
  moveMotorHelper(X_AXIS, 1, BACKWARD);
  moveMotorHelper(Y_AXIS, 1, BACKWARD);

  moveMotorHelper(X_AXIS, xDist, xDir);
  moveMotorHelper(Y_AXIS, yDist, yDir);
  
  // move the motor back to the center
  moveMotorHelper(X_AXIS, 1, FORWARD);
  moveMotorHelper(Y_AXIS, 1, FORWARD);
  magnetX = xPos;
  magnetY = yPos;
  return 1;
}

int moveMotorHelper(int axis, int distance, int direction) {
  // assume GPIOs have been configured
  int numSteps = distance * HALF_SQUARE;
  int totalSteps = numSteps;
  unsigned int waitTime = WAIT_TIME;
  if (axis == X_AXIS) {
    setPinGPIO0(X_AXIS_EN, PIN_LOW); // enable the motor control (active low)
    setPinGPIO0(X_AXIS_DIR, direction); // set the direction
    while (numSteps > 0) {
      if (numSteps > totalSteps - CORNER_DIST || numSteps < CORNER_DIST) {
        waitTime = WAIT_TIME * 4;
      } else {
        waitTime = WAIT_TIME;
      }
      setPinGPIO0(X_AXIS_STP, PIN_HIGH);
      lpcWait(waitTime);
      setPinGPIO0(X_AXIS_STP, PIN_LOW);
      lpcWait(waitTime);
      numSteps--;
    }
  } else if (axis == Y_AXIS) {
    setPinGPIO0(Y_AXIS_EN, PIN_LOW); // enable the motor control (active low)
    setPinGPIO0(Y_AXIS_DIR, direction); // set the direction
    while (numSteps > 0) {
      if (numSteps > totalSteps - CORNER_DIST || numSteps < CORNER_DIST) {
        waitTime = WAIT_TIME * 4;
      } else {
        waitTime = WAIT_TIME;
      }
      setPinGPIO0(Y_AXIS_STP, PIN_HIGH);
      lpcWait(waitTime);
      setPinGPIO0(Y_AXIS_STP, PIN_LOW);
      lpcWait(waitTime);
      numSteps--;
    }
  } else {
    return 0; // invalid axis
  }

  // reset the ED pins to their default state
  resetEDPins(axis);
  return 1; // success
}

void resetMotor(void) {
  moveMotor(0, 0);
  return;
}
