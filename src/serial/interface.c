/**
 * interface.c - implements the functions declared in interface.h
 * 
 * @author Dean Biskup and Mitalee Bharadwaj
 * University of Illinois, ADSL (ECE 395) Fall 2019
 */

#include <stdio.h>
#include "string.h"
#include "../chess/board.h"
#include "interface.h"

/* a static array we'll use to hold the command */
static char command[5]; // max length is 4 chars + 1 null character

char* getNextMove(int player) {
  for (int i = 0; i < 5; i++) {
    command[i] = 0;
  }
  char playerStr[6];
  if (player == BLACK) {
    strcpy(playerStr, "BLACK");
  } else {
    strcpy(playerStr, "WHITE");
  }
  printf("Please input %s's next move:\r\n", playerStr);
  scanf("%4s", command);
  // command[0]++; // unsure why this is necessary @TODO WTF IS THIS
  
  // convert to uppercase
  for (int i = 0; i < 5; i++) {
    if (command[i] > 96 && command[i] < 123)
      command[i] ^= 0x20;
  }
  printf("You inputted: %s\r\n", command);
  return command;
}

void printBoard(board_t* board) {
  for (int j = 0; j < BOARD_SIZE; j++) {
    for (int i = -2; i < BOARD_SIZE + 2; i++) {
      if (i == 0 || i == BOARD_SIZE) {
        printf("|");
      }
      int c = CLEAR;
      if (i < 0) {
        c = board->graveyard[-1*i][j];
      } else if (i >= BOARD_SIZE) {
        c = board->graveyard[i-6][j];
      } else {
        c = board->squares[i][j];
      }
      if (c == CLEAR) {
        c = '_';
      }
      printf("%c", (char)c);
    }
    printf("\r\n");
  }
}
