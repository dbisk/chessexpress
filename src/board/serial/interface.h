/**
 * interface.h
 * 
 * Header file for functions that handle the interface between the LPC1114 and the users or a computer through serial connection.
 * 
 * @author Dean Biskup and Mitalee Bharadwaj
 * University of Illinois, ADSL (ECE 395) Fall 2019
 */

#ifndef _SERIAL_INTERFACE_H_
#define _SERIAL_INTERFACE_H_

#include "../chess/board.h"

/**
 * requestMove()
 * 
 * Requests the next motor movement from the serial port. The movement is stored
 * in an integer array formatted such that [fromX, fromY, toX, toY].
 * 
 * @returns int* a string that holds the move, as integers
 */
int* requestMove(void);

/**
 * serialAck()
 * 
 * Sends an acknowledge signal through serial.
 */
void serialAck(void);

#endif // _SERIAL_INTERFACE_H_
