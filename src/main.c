#include "LPC11xx.h"
#include <stdio.h>
#include <rt_misc.h>

/* include user defined files */
#include "mcu/mcu.h"
#include "lpc_utils.h"

/* Import external functions from Serial.c file                               */
extern void SER_init (void);

/* initialization sequence */
void initialize() {
	SER_init();
	lpcWait(0xFFFF);
	printf("Starting Initialization Sequence...\n");
	printf("Configuring X axis GPIO...");
	configureGPIO(X_AXIS);
	printf(" OK\n");
	printf("Configuring Y axis GPIO...");
	configureGPIO(Y_AXIS);
	printf(" OK\n");
	printf("Setting defaults...");
	resetEDPins(X_AXIS);
	resetEDPins(Y_AXIS);
	printf(" OK\n");
}

int main() {
	initialize();
  
	// testing sequence
	printf("Moving X Axis motor forward 2 squares... ");
  moveMotor(X_AXIS, 4, FORWARD); // move 4 half squares forward
	printf(" OK\n");
	lpcWait(0x7FFFF);
	printf("Moving X Axis motor backward 4 squares... ");
  moveMotor(X_AXIS, 8, BACKWARD); // move 8 half squares backward
	printf(" OK\n");
	lpcWait(0x7FFFF);
	printf("Moving X Axis motor forward indefinitely..."); 
  moveMotor(X_AXIS, -1, FORWARD); // move indefinitely

	while(1) ;
	// return 0;
}
