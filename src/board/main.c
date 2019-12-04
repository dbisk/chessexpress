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
	printf("Configuring IOCONFIG block and GPIO...");
	configureGPIO();
	printf(" OK\r\n");
	printf("Setting defaults...");
	resetEDPins(X_AXIS);
	resetEDPins(Y_AXIS);
	printf(" OK\r\n");
}

int main() {
	initialize();
  
  // get mode
  int mode = 1;

  while (1) {
    printf("MODE: ");
    scanf("%d", &mode);

    if (mode == 0) {
      // normal game
      gameLoop();
    } else if (mode == 1) {
      // calibration mode
      setPinGPIO0(X_AXIS_DIR, FORWARD);
      setPinGPIO0(Y_AXIS_DIR, FORWARD);
      int xdir = FORWARD;
      int ydir = FORWARD;
      while (1) {
        int flag = 0;
        while (readPinGPIO0(X_AXIS_BUT)) {
          setPinGPIO0(MAGNET_PIN, PIN_HIGH);
          setPinGPIO0(X_AXIS_EN, PIN_LOW); // active low enable
          setPinGPIO0(X_AXIS_STP, PIN_HIGH);
          lpcWait(WAIT_TIME);
          setPinGPIO0(X_AXIS_STP, PIN_LOW);
          lpcWait(WAIT_TIME);
          flag = 1;
        }
        if (flag) {
          xdir = (xdir - 1) * -1;
          setPinGPIO0(X_AXIS_DIR, xdir);
        }
        flag = 0;
        while (readPinGPIO0(Y_AXIS_BUT)) {
          setPinGPIO0(MAGNET_PIN, PIN_HIGH);
          setPinGPIO0(Y_AXIS_EN, PIN_LOW); // active low enable
          setPinGPIO0(Y_AXIS_STP, PIN_HIGH);
          lpcWait(WAIT_TIME);
          setPinGPIO0(Y_AXIS_STP, PIN_LOW);
          lpcWait(WAIT_TIME);
          flag = 1;
        }
        if (flag) {
          ydir = (ydir - 1) * -1;
          setPinGPIO0(Y_AXIS_DIR, ydir);
        }
        setPinGPIO0(X_AXIS_EN, PIN_HIGH);
        setPinGPIO0(Y_AXIS_EN, PIN_HIGH);
        setPinGPIO0(MAGNET_PIN, PIN_LOW);
      }
    } else if (mode == 2) {
      // just a debug mode
      while(1) {
        lpcWait(0xAFFFF);
        printf("X BUTTON: %d | Y BUTTON: %d\r\n", readPinGPIO0(X_AXIS_BUT), readPinGPIO0(Y_AXIS_BUT));
      }
    }
    resetEDPins(X_AXIS);
    resetEDPins(Y_AXIS);
  }
}
