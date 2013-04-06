#include "led.h"

#include "lm3s1968.h"

void initLEDs()
{
	volatile uint32_t delay;
	// Enable clocks for D and F
	SYSCTL_RCGC2_R |= (1 << 3) | (1 << 5);
	delay = SYSCTL_RCGC2_R;

	GPIO_PORTD_DIR_R = 0x07;
	GPIO_PORTD_AFSEL_R = 0;
	GPIO_PORTD_DEN_R = 0xff;

	GPIO_PORTF_DIR_R = 0xff;
	GPIO_PORTF_AFSEL_R = 0;
	GPIO_PORTF_DEN_R = 0xff;
}

void setLEDs(uint8_t count)
{
	GPIO_PORTF_DATA_R = ~count;
}

uint8_t getLEDColor(void)
{
	return (uint8_t)(GPIO_PORTD_DATA_R & 0x7);
}

void setLEDColor(uint8_t color)
{
	GPIO_PORTD_DATA_R = color & 0x7;
}
