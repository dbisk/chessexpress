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
/* on GPIO0, avoid pins 0, 1, 4, 5, and 10 */
#define GPIO0_STEP_STP  2
#define GPIO0_STEP_DIR  3
#define GPIO0_STEP_MS1  6
#define GPIO0_STEP_MS2  8
#define GPIO0_STEP_EN   9

/* on GPIO1, avoid pins 3, 4, 5, 6, and 7 */
#define GPIO1_STEP_STP  0
#define GPIO1_STEP_DIR  1
#define GPIO1_STEP_MS1  2
#define GPIO1_STEP_MS2  8
#define GPIO1_STEP_EN   9

/* define other useful things for motor control */
#define X_AXIS          0
#define Y_AXIS          1
#define FORWARD         0
#define BACKWARD        1

/* define stepper motor distances */
#define HALF_SQUARE     323
#define FULL_SQUARE     (HALF_SQUARE * 2 + 1)

/**
 * configureGPIO(int axis)
 * 
 * This function configures the GPIO pins for the given axis of motion. 
 * 
 * @param axis - the axis whose motor controls should be configured
 * @returns 1 if valid axis, 0 otherwise
 */
int configureGPIO(int axis);

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
 * moveMotor(axis, distance, direction)
 * 
 * Moves the motors along the given axis a certain distance, in half-squares, in
 * the given direction.
 * 
 * @param axis - the axis whose motors will move
 * @param distance - the distance to move, in half-squares. If negative, will
 *                   move indefinitely.
 * @param direction - the direction to move
 */
int moveMotor(int axis, int distance, int direction);

#endif // _MOTOR_MCU_H_
