#ifndef __TIMER_H__
#define __TIMER_H__

#include <stdint.h>

/*!
 * \brief Initializes timer 0 (subtimer A) to fire interrupts at a given period
 * \param period The number of clock cycles between timer ticks
 * \param priority Interrupt priority. Only the bottom three bits are used.
 */
void initTimer0(uint32_t period, uint8_t priority);

//! Changes the number of clock cycles between timer 0 ticks
void changeTimer0Rate(uint32_t period);

//! Clears the interrupt for timer 0
void clearTimer0Int(void);

/*!
 * \brief Initializes the system tick timer to fire interrupts at a given period
 * \param period The number of clock cycles between timer ticks
 * \param priority Interrupt priority. Only the bottom three bits are used.
 */
void initSysTick(uint32_t period, uint8_t priority);

#endif
