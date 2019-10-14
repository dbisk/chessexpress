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
}

int main() {
	initialize();
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
