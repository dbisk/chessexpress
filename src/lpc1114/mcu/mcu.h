/**
 * mcu.h 
 * 
 * A header file for functions that involve motor control.
 * 
 * @author Dean Biskup and Mitalee Bharadwaj
 * 
 * University of Illinois, ADSL (ECE 395), Fall 2019.
 */
#ifndef _MOTOR_MCU_H_
#define _MOTOR_MCU_H_

/* define pins for the motor control signals */
/* on GPIO0 (12 bits), avoid pins 0, 1, 4, 5, and 10 */
#define X_AXIS_STP  2
#define X_AXIS_DIR  3
#define X_AXIS_EN   7
#define Y_AXIS_STP  6
#define Y_AXIS_DIR  11
#define Y_AXIS_EN   9
#define MAGNET_PIN  8

/* define pins for button motor control */
#define X_AXIS_BUT  4
#define Y_AXIS_BUT  5

/* on GPIO1 (10 bits), avoid pins 3, 4, 5, 6, and 7 */

/* define other useful things for motor control */
#define X_AXIS          0
#define Y_AXIS          1
#define FORWARD         0
#define BACKWARD        1

/* define stepper motor distances */
#define HALF_SQUARE     105
#define FULL_SQUARE     (HALF_SQUARE * 2 + 1)

// For 1/8 step, 0x7FF. For full step, 0x5FFF
#define WAIT_TIME 0xDFFF

extern int magnetX;
extern int magnetY;

/**
 * configureGPIO()
 * 
 * This function configures the GPIO pins for the given axis of motion. 
 */
void configureGPIO(void);

/**
 * resetEDPins(int axis)
 * 
 * This function configures the ED pins to their defaults for the given axis.
 * 
 * @param axis - the axis whose motor controls should be configured
 * @returns 1 if valid axis, 0 otherwise
 */
int resetEDPins(int axis);

/**
 * moveMotor(xPos, yPos)
 * 
 * Moves the motors along the given axis to the specified square.
 * 
 * @param xPos - the x position of the square to move the motor to
 * @param yPos - the y position of the square to move the motor to
 */
int moveMotor(int xPos, int yPos);

/**
 * resetMotor()
 * 
 * resets the motor's position to the origin (top left corner of chessboard)
 */
void resetMotor(void);

#endif // _MOTOR_MCU_H_
