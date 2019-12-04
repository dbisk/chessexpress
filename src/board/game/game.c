/**
 * game.c
 * 
 * Implements the functions declared in game.h
 * 
 * @author Dean Biskup and Mitalee Bharadwaj
 * University of Illinois, ADSL (ECE 395), Fall 2019.
 */
#include "../serial/interface.h"
#include "../mcu/mcu.h"
#include "../lpc_utils.h"
#include "game.h"
#include <stdio.h>

void gameLoop() {
  int gameOver = 0;
  while (!gameOver) {
    int* move = requestMove();
    if (move[0] == 9) {
      gameOver = 1; // gameover signal
      break;
    }
    int fromX = move[0];
    int fromY = move[1];
    int toX = move[2];
    int toY = move[3];

    // move the magnet to the first piece
    moveMotor(fromX, fromY);
    // energize the magnet
    setPinGPIO0(MAGNET_PIN, PIN_HIGH);
    // move the motor to the to position
    moveMotor(toX, toY);
    // de-energize the magnet
    setPinGPIO0(MAGNET_PIN, PIN_LOW);
    // wait a bit to make sure the magnet has entirely de-energized
    lpcWait(0xFFFFF);
    // send finished signal
    serialAck();
  }
}
