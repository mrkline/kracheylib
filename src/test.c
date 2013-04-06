//*****************************************************************************
//
//*****************************************************************************
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>

#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "lm3s1968.h"
#include "buttons.h"
#include "led.h"
#include "timer.h"

void timer0Handler(void)
{
	static int8_t currentLED = -1;
	currentLED = (currentLED + 1) % 8;
	setLEDs(1 << currentLED);
	clearTimer0Int();
}

void buttonHandler(void)
{
	if (pb100Pressed()) {
		setLEDColor(BLUE);
	}
	else if (pb101Pressed()) {
		setLEDColor(RED);
	}
	clearPB101Int();
	clearPB100Int();
}

int
main(void)
{
    // Set the clocking to run at 50MHz from the PLL.
    //
	SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN |
	               SYSCTL_XTAL_8MHZ);
	initButtons(true, true, 2);
	initLEDs();
	setLEDColor(GREEN);
	initTimer0(50000000 / 3, 1);
	while(1) { };
}
