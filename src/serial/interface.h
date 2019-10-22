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

/**
 * getNextMove(player)
 * 
 * Prompts the next move from the serial port, expects algebraic notation. 
 * 
 * @param player the color of the player whose turn is next. Only changes text.
 * @returns char* a pointer to an array that holds the next move in algebraic
 * notation, all lower case
 */
char* getNextMove(int player);

/**
 * printBoard(board)
 * 
 * Prints the current state of the board to the serial port.
 * 
 * @param board the board to print
 */
void printBoard(board_t board);

#endif // _SERIAL_INTERFACE_H_
