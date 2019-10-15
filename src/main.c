#include "LPC11xx.h"
#include <stdio.h>
#include <rt_misc.h>

/* include user defined files */
#include "mcu/mcu.h"

/* Import external functions from Serial.c file                               */
extern void SER_init (void);

void setLow(int pin)
{
	LPC_GPIO0->DATA &= ~(1<<pin);
}

void setHigh(int pin)
{						 
	LPC_GPIO0->DATA |= (1<<pin);
}

int main()
{
	// configureGPIO();
	// resetEDPins();
	
	// enable the motor control
	// setLow(STEP_EN);
	
	// Move the stepper motor forward
	// setLow(STEP_DIR); // pull dir pin low
	while(1) {
		// setHigh(STEP_STP);
		int i;
		for (i = 0; i < 0xFFFFF; i++) {}
		// setLow(STEP_STP);
		for (i = 0; i < 0xFFFFF; i++) {}
	}
	
	
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
