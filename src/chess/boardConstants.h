/**
 * boardConstants.h
 * 
 * Includes several constants that are important to the implementation of the
 * chessboard logic. This file shouldn't contain any definitions that are not
 * related specifically to the chessboard itself.
 */
#ifndef _CHESS_BOARDCONSTANTS_H_
#define _CHESS_BOARDCONSTANTS_H_

/* the various pieces */
#define KING    'K'
#define QUEEN   'Q'
#define BISHOP  'B'
#define KNIGHT  'N'
#define ROOK    'R'
#define PAWN    'P'
#define CLEAR   0

/* the player */
#define WHITE   0
#define BLACK   1

/* turn the color and rank of a piece into it's struct data */
#define PIECE(color, rank) ((color << 8) + rank)

/* backwards of the above */
#define RANK(value) (value & 0x00FF)
#define PLAYER(value) (value >> 8)

/* size of the board (square) */
#define BOARD_SIZE    8

/* the columns in algebraic notation */
#define COL_A   0
#define COL_B   1
#define COL_C   2
#define COL_D   3
#define COL_E   4
#define COL_F   5
#define COL_G   6
#define COL_H   7

/* the rows in algebraic notation */
#define ROW_1   0
#define ROW_2   1
#define ROW_3   2
#define ROW_4   3
#define ROW_5   4
#define ROW_6   5
#define ROW_7   6
#define ROW_8   7

#endif // _CHESS_BOARDCONSTANTS_H_
