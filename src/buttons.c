#include "buttons.h"

#include <stdint.h>

#include "lm3s1968.h"
#include "startup_definitions.h"

#define PB100 5
#define PB101 6
#define PB100_MASK (1 << PB100)
#define PB101_MASK (1 << PB101)

void initButtons(bool pb100Int, bool pb101Int, uint8_t priority)
{
	volatile uint32_t delay;
	if (pb100Int || pb101Int)
		DisableInterrupts();
	// Enable Port C for the 3 push buttons
	SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOC;
	delay = SYSCTL_RCGC2_R;

	// Disable Alternate Function
	GPIO_PORTC_AFSEL_R &= ~(PB100_MASK);

	// Enable the GPIO pins as inputs
	GPIO_PORTC_DEN_R |= PB100_MASK;
	GPIO_PORTC_DIR_R &= ~(PB100_MASK);
	GPIO_PORTC_DEN_R |= PB101_MASK;
	GPIO_PORTC_DIR_R &= ~(PB101_MASK);

	// Set interrupts to occur on both presses and relases of PB 100
	if (pb100Int) {
		GPIO_PORTC_IBE_R |= PB100_MASK;
		GPIO_PORTC_IM_R |= PB100_MASK;
	}

	// Set interrupts to occur on both presses and relases of PB 100
	if (pb101Int) {
		GPIO_PORTC_IBE_R |= PB101_MASK;
		GPIO_PORTC_IM_R |= PB101_MASK;
	}

	// See page 81 of the manual for interrupt numbers. Port C is 2
	NVIC_PRI0_R &= ~NVIC_PRI0_INT2_M; // Clear current priority
	NVIC_PRI0_R |= (priority << NVIC_PRI0_INT2_S) & NVIC_PRI0_INT2_M; // Priority 2
	NVIC_EN0_R |= NVIC_EN0_INT2; // Enable interrupt;

	if (pb100Int || pb101Int) {
		clearPB100Int();
		clearPB101Int();
		EnableInterrupts();
	}
}

void clearPB100Int(void)
{
	GPIO_PORTC_ICR_R |= PB100_MASK; // Clear the interrupt
}

void clearPB101Int(void)
{
	GPIO_PORTC_ICR_R |= PB101_MASK; // Clear the interrupt
}

bool pb100Pressed(void)
{
	return (GPIO_PORTC_DATA_R & PB100_MASK) == 0;
}

bool pb101Pressed(void)
{
	return (GPIO_PORTC_DATA_R & PB101_MASK) == 0;
}
