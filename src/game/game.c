/**
 * game.c
 * 
 * Implements the functions declared in game.h
 * 
 * @author Dean Biskup and Mitalee Bharadwaj
 * University of Illinois, ADSL (ECE 395), Fall 2019.
 */
#include <stdlib.h>
#include <string.h>
#include "../chess/board.h"
#include "../serial/interface.h"
#include "../mcu/mcu.h"
#include "../lpc_utils.h"
#include "game.h"

/* declare static data that needs to be stored */
static board_t chessboard;
static int captureFlag;

/* declare static helper functions */
static int getRowFromChar(char c);
static int getColFromChar(char c);
static vec_t parseMove(int mode, char* command);
static int executeMove(board_t* board, vec_t move);

void gameLoop(int mode) {
  // regardless of the mode, create a fresh chessboard
  chessboard = newBoard();

  // set up some data regarding the new chessboard
  int currentPlayer = WHITE;
  int totalTurns = 0;

  // flags
  int gameOver = 0;

  // main game loop
  while(!gameOver) {
    // get the next move from the user
    char* nextMoveRaw = getNextMove(currentPlayer);
    if (nextMoveRaw[0] == '#') {
      gameOver = 1;
      break; // checkmate
    }
    vec_t nextMovePar = parseMove(mode, nextMoveRaw);

    if (mode == SCRIPTED) {
      // just move the motors and update the board state
      if (!isSquareClear(&chessboard, nextMovePar.toLoc)) {
        // need to move the captured piece to the graveyard first. we can think
        // of the graveyard as columns -1, -2 for black and 8, 9 for white
        pos_t graveSpot = getNextGraveSpot(&chessboard, PLAYER(chessboard.squares[nextMovePar.toLoc.col][nextMovePar.toLoc.col]));
        if (graveSpot.col < 2) {
          // black side
          graveSpot.col = -1 * graveSpot.col;
        } else {
          // white side
          graveSpot.col = 5 + graveSpot.col;
        }
        vec_t graveMove = {nextMovePar.toLoc, graveSpot};
        executeMove(&chessboard, graveMove);
      }
      executeMove(&chessboard, nextMovePar);

      // update the board representation
      makeMoveNoCheck(&chessboard, nextMovePar.fromLoc, nextMovePar.toLoc);
    }

    // update variables
    if (currentPlayer == BLACK) {
      // completed one full turn
      totalTurns++;
    }
    currentPlayer = (currentPlayer == WHITE) ? BLACK : WHITE;
  }
}

/**
 * executeMove(nextMovePar)
 * 
 * Executes the given move physically on the board. First moves the captured
 * piece into the graveyard (if applicable), then moves the acting piece to the
 * empty space. Does not perform any other checks.
 * 
 * @param nextMovePar vec_t that holds the target movement vector
 */
int executeMove(board_t* board, vec_t move) {
  pos_t fromPos = move.fromLoc;
  pos_t toPos = move.toLoc;
  
  // move the acting piece in the following steps
  // move the motor under the piece
  moveMotor(X_AXIS, fromPos.col + 1, FORWARD);
  moveMotor(Y_AXIS, fromPos.row + 1, FORWARD);
  // attach to the piece
  setPinGPIO0(MAGNET_PIN, PIN_HIGH);
  // move the piece to the corner of its square
  moveMotor(X_AXIS, 1, BACKWARD);
  moveMotor(Y_AXIS, 1, BACKWARD);
  // move the piece the correct distance in the x axis
  int dir = FORWARD;
  int dist = abs(toPos.col - fromPos.col);
  if (toPos.col < fromPos.col) {
    dir = BACKWARD;
  }
  moveMotor(X_AXIS, dist, dir);
  // move the piece the correct distance in the y axis
  dir = FORWARD;
  dist = abs(toPos.row - fromPos.row);
  if (toPos.row < fromPos.row) {
    dir = BACKWARD;
  }
  moveMotor(Y_AXIS, dist, dir);
  // move the piece back to the center of the square
  moveMotor(X_AXIS, 1, FORWARD);
  moveMotor(Y_AXIS, 1, FORWARD);
  // release the piece
  setPinGPIO0(MAGNET_PIN, PIN_LOW);
  // reset the motor
  resetMotor();
  return 0;
}

/**
 * parseMove(command)
 * 
 * Parses the text string command into a vector on the chessboard. See the
 * wikipedia page for algebraic notation
 * (https://en.wikipedia.org/wiki/Algebraic_notation_(chess)) for the exact
 * details of how moves are represented in text.
 * 
 * If mode is scripted, the command should just be two squares instead of
 * algebraic notation, e.g. b2b4 or a3xa7 
 * 
 * @param command pointer to the string command to parse (all uppercase)
 * @returns vec_t the vector the move represents
 */
vec_t parseMove(int mode, char* command) {
  pos_t fromPos = {0, 0};
  pos_t toPos = {0, 0};

  if (mode == SCRIPTED) {
    fromPos.col = getColFromChar(command[0]);
    fromPos.row = getRowFromChar(command[1]);
    if (strlen(command) == 5) {
      // a capture happened
      toPos.col = getColFromChar(command[3]);
      toPos.row = getRowFromChar(command[4]);
      captureFlag = 1;
    } else {
      toPos.col = getColFromChar(command[2]);
      toPos.row = getRowFromChar(command[3]);
    }
  }

  vec_t retVal = {fromPos, toPos};
  return retVal;
}

int getColFromChar(char c) {
  switch (c) {
    case 'A':
      return COL_A;
    case 'B':
      return COL_B;
    case 'C':
      return COL_C;
    case 'D':
      return COL_D;
    case 'E':
      return COL_E;
    case 'F':
      return COL_F;
    case 'G':
      return COL_G;
    case 'H':
      return COL_H;
    default:
      return -1;
  }
}

int getRowFromChar(char c) {
  switch (c) {
    case '1':
      return ROW_1;
    case '2':
      return ROW_2;
    case '3':
      return ROW_3;
    case '4':
      return ROW_4;
    case '5':
      return ROW_5;
    case '6':
      return ROW_6;
    case '7':
      return ROW_7;
    case '8':
      return ROW_8;
    default:
      return -1;
  }
}
