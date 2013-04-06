#include "timer.h"

#include "lm3s1968.h"
#include "startup_definitions.h"

void initTimer0(uint32_t period, uint8_t priority)
{
	volatile uint32_t wait;
	DisableInterrupts();
	SYSCTL_RCGC1_R |= SYSCTL_RCGC1_TIMER0;
	wait = SYSCTL_RCGC1_R;
	TIMER0_CTL_R &= ~TIMER_CTL_TAEN; // Disable timer during setup
	TIMER0_CFG_R = TIMER_CFG_32_BIT_TIMER; // 32-bit mode
	TIMER0_TAMR_R = TIMER_TAMR_TAMR_PERIOD; // Timer A periodic mode
	TIMER0_TAILR_R = period;
	TIMER0_ICR_R = TIMER_ICR_TATOCINT; // Clear interrupt timeout flag
	TIMER0_IMR_R = TIMER_IMR_TATOIM; // Arm the interrupt
	// See page 81 of the manual for interrupt numbers. Timer 0A is 19
	NVIC_PRI4_R = NVIC_PRI4_R & ~NVIC_PRI4_INT19_M; // Clear current priority
	NVIC_PRI4_R |= (priority << NVIC_PRI4_INT19_S) & NVIC_PRI4_INT19_M; // Priority 2
	NVIC_EN0_R |= NVIC_EN0_INT19; // Enable interrupt;
	TIMER0_CTL_R |= TIMER_CTL_TAEN; // Re-enable timer
	EnableInterrupts();
}

void changeTimer0Rate(uint32_t period)
{
	DisableInterrupts();
	TIMER0_TAILR_R = period;
	EnableInterrupts();
}

void clearTimer0Int(void)
{
	TIMER0_ICR_R = TIMER_ICR_TATOCINT; // Clear interrupt timeout flag
}

void initSysTick(uint32_t period, uint8_t priority)
{
	DisableInterrupts();
	NVIC_ST_CTRL_R &= ~NVIC_ST_CTRL_ENABLE; // disable SysTick timer

	// Set reload register to count
	NVIC_ST_RELOAD_R &= ~NVIC_ST_RELOAD_M; // Upper byte is reserved
	NVIC_ST_RELOAD_R |=  period & NVIC_ST_RELOAD_M;

	// clear the current count
	NVIC_ST_CURRENT_R &= ~NVIC_ST_CURRENT_M; // Upper byte is reserved

	// Set the priority
	// See pg 81 and 118 to get the information on the SysTick Interrupt Number
	// and how to set its priority
	NVIC_SYS_PRI3_R &= ~NVIC_PRI3_INT15_M;
	NVIC_SYS_PRI3_R |= (priority << NVIC_PRI3_INT15_S) & NVIC_PRI3_INT15_M;

	// Enable SysTick, SysTick Interrupts,Core Clock
	NVIC_ST_CTRL_R |= NVIC_ST_CTRL_ENABLE | NVIC_ST_CTRL_INTEN | NVIC_ST_CTRL_CLK_SRC;
	EnableInterrupts();
}
