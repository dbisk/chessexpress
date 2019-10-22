/**
 * board.h
 * 
 * Holds declarations for all functions in board.c. Also holds the declaration
 * for the struct that represents the board state.
 */
#ifndef CHESS_BOARD_H_
#define CHESS_BOARD_H_

#include "boardConstants.h"

/**
 * pos_t - a struct that holds an x-y position on the chessboard
 * 
 * Fields:
 *    col - the column (A-H in chess notation)
 *    row - the row (1-8 in chess notation, but stored 0-7 here)
 */
typedef struct {
  int col;
  int row;
} pos_t;

/**
 * vec_t - a struct that holds two pos_ts, representing a vector on the
 * chessboard.
 * 
 * Fields:
 *    fromLoc - the position we are going from
 *    toLoc - the position we are going to
 */
typedef struct {
  pos_t fromLoc;
  pos_t toLoc;
} vec_t;

/**
 * board_t - a struct to hold the state of a chessboard.
 * 
 * Fields:
 *    squares - a 2-D array holding the state of each square on the board. The 
 *              data is arranged such that the bottom byte holds the type of 
 *              piece, and the second byte holds the color. Any more 
 *              significant bytes are disregarded.
 * 
 *    graveyard - a 2-D array holding the graveyard pieces. Columns 3 & 4 will
 *                be for white pieces, and columns 1 & 2 for black pieces.
 */
typedef struct {
  int squares[BOARD_SIZE][BOARD_SIZE];
  int graveyard[4][BOARD_SIZE];
  pos_t nextGraveWhite, nextGraveBlack;
} board_t;

/**
 * newBoard()
 * 
 * returns a fresh board that is the starting state of a chess game.
 */
board_t newBoard(void);

/**
 * makeMove(board, player, fromPos, toPos)
 * 
 * Checks if a given move is valid and performs the move on the given board if
 * it is.
 * 
 * @param
 *    board - pointer to the board to make the modifications to
 *    player - the color of the player requesting the move
 *    fromPos - the location the piece is requesting to move from
 *    toPos - the location the piece is requesting to move to
 * 
 * @return
 *    int - 1 if successful move, 0 if the move was illegal
 */
int makeMove(board_t* board, int player, pos_t fromPos, pos_t toPos);

/**
 * makeMoveNoCheck(board, fromPos, toPos)
 * 
 * Performs the requested move without making chess logic checks. See the docs
 * for makeMove for parameter specifications.
 * 
 * This function mostly used if we have a queue of moves that have been
 * previously vetted for legality.
 */
int makeMoveNoCheck(board_t* board, pos_t fromPos, pos_t toPos);

/**
 * isSquareClear(board, position)
 * 
 * Checks if the given position is clear.
 * 
 * @param board pointer to the board we're checking on
 * @param position pos_t of the position to check
 * @return 1 if position is clear, 0 otherwise
 */
int isSquareClear(board_t* board, pos_t position);

/**
 * getNextGraveSpot(board, player)
 * 
 * Gets the next grave position for the provided color.
 * 
 * @param board pointer to the board we're checking on
 * @param color the color of the grave position we are checking for
 */
pos_t getNextGraveSpot(board_t* board, int color);

#endif // CHESS_BOARD_H_
