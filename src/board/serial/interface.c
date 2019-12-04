/**
 * interface.c - implements the functions declared in interface.h
 * 
 * @author Dean Biskup and Mitalee Bharadwaj
 * University of Illinois, ADSL (ECE 395) Fall 2019
 */

#include <stdio.h>
#include "../chess/board.h"
#include "interface.h"

extern int getkey(void);

int* requestMove() {
  
  static int command[5];

  printf("INPUT: ");
  command[0] = getkey() - 48;
  command[1] = getkey() - 48;
  command[2] = getkey() - 48;
  command[3] = getkey() - 48;
  command[4] = 0;
  serialAck();
  return command;
}

void serialAck() {
  printf("ACK");
}
