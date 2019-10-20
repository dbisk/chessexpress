/**
 * interface.c - implements the functions declared in interface.h
 * 
 * @author Dean Biskup and Mitalee Bharadwaj
 * University of Illinois, ADSL (ECE 395) Fall 2019
 */

#include <stdio.h>
#include "string.h"
#include "../chess/boardConstants.h"
#include "interface.h"

/* a static array we'll use to hold the command */
static char command[5]; // max length is 4 chars + 1 null character

char* getNextMove(int player) {
  char playerStr[6];
  if (player == BLACK) {
    strcpy(playerStr, "BLACK");
  } else {
    strcpy(playerStr, "WHITE");
  }
  printf("Please input %s's next move:\r\n", playerStr);
  scanf("%4s", command);
  command[0]++; // unsure why this is necessary
  return command;
}
