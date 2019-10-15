#include "LPC11xx.h"
#include <stdio.h>
#include <rt_misc.h>

/* include user defined files */
#include "mcu/mcu.h"

/* Import external functions from Serial.c file                               */
extern void SER_init (void);

/* initialization sequence */
void initialize() {
	SER_init();
	configureGPIO(X_AXIS);
	configureGPIO(Y_AXIS);
	resetEDPins(X_AXIS);
	resetEDPins(Y_AXIS);
}

int main() {
	initialize();
  // TESTING
  moveMotor(X_AXIS, 8, BACKWARD); // move 4 half squares forward
  // moveMotor(X_AXIS, 8, BACKWARD); // move 8 half squares backward
  int i = 0;
  for (i = 0; i < 0xFFFFFF; i++) ;
  moveMotor(X_AXIS, -1, FORWARD); // move indefinitely
	/*int i, j = 0;
	SER_init();
	configureGPIO();
	while (1)
	{
		ledOn();
		printf("Led On, Iteration %d\n\r", j);
		for (i = 0; i < 0xFFF; i++)
		{
		}
		ledOff();
		printf("Led Off, Iteration %d\n\r", j);
		for (i = 0; i < 0xFFF; i++)
		{
		}
		j++;
	} */
}
