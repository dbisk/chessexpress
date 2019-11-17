#include "LPC11xx.h"
#include <stdio.h>
#include <string.h>
#include <rt_misc.h>

/* include user defined files */
#include "mcu/mcu.h"
#include "lpc_utils.h"
#include "serial/interface.h"
#include "game/game.h"

/* Import external functions from Serial.c file                               */
extern void SER_init (void);

/* initialization sequence */
void initialize() {
	SER_init();
	lpcWait(0xFFFF);
	printf("Starting Initialization Sequence...\r\n");
	printf("Configuring X axis GPIO...");
	configureGPIO(X_AXIS);
	printf(" OK\r\n");
	printf("Configuring Y axis GPIO...");
	configureGPIO(Y_AXIS);
	printf(" OK\r\n");
	printf("Setting defaults...");
	resetEDPins(X_AXIS);
	resetEDPins(Y_AXIS);
	printf(" OK\r\n");
}

int main() {
	initialize();
  
  // testing sequence
  // serial testing
  printf("Testing serial command input... \r\n");
  getNextMove(WHITE);
  printf("Next player... \r\n");
  getNextMove(BLACK);
  printf("Interface testing complete... OK\r\n\n");
  
  // electromagnet testing
  printf("Activating electromagnet... OK\r\n");
  setPinGPIO0(MAGNET_PIN, PIN_HIGH);

  // motor testing
  printf("Starting motor testing... \r\n");
  printf("Moving X Axis motor forward 2 squares... ");
  moveMotor(X_AXIS, 4, FORWARD); // move 4 half squares forward
  printf(" OK\r\n");
  lpcWait(0x7FFFF);
  printf("Moving Y Axis motor forward 2 squares... ");
  moveMotor(Y_AXIS, 4, FORWARD); // move 4 half squares forward
  printf(" OK\r\n");
  lpcWait(0x7FFFF);
  /*printf("Moving X Axis motor backward 4 squares... ");
  moveMotor(X_AXIS, 8, BACKWARD); // move 8 half squares backward
  printf(" OK\r\n");
  lpcWait(0x7FFFF);
  printf("Moving X Axis motor forward 1 square..."); 
  moveMotor(X_AXIS, 2, FORWARD); // move 2 half squares forward
  printf(" OK\r\n");*/
  
  // deactivate electromagnet
  printf("Deactivating electromagnet... OK\r\n");
  setPinGPIO0(MAGNET_PIN, PIN_LOW);
  
  // program
  while(1) {
    printf("Starting new game...\r\n");
    gameLoop(SCRIPTED);
  }
	// return 0;
}
