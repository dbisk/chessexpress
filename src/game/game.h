/**
 * game.h
 * 
 * Declares functions for the "game" layer, which interfaces between the chess
 * constructs and the actual hardware control in order to induce movement on the
 * actual board.
 * 
 * @author Dean Biskup and Mitalee Bharadwaj
 * University of Illinois, ADSL (ECE 395), Fall 2019.
 */
#ifndef _GAME_GAME_H_
#define _GAME_GAME_H_

/* defines for game modes */
#define SCRIPTED        0
#define INTERACTIVE     1

/**
 * gameLoop()
 * 
 * The entry point to the game. Runs the mode of the game specified.
 * 
 * @param mode the mode of the game specified - either SCRIPTED or INTERACTIVE
 */
void gameLoop(int mode);



#endif // _GAME_GAME_H_
