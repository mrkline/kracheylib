#ifndef __BUTTONS_H__
#define __BUTTONS_H__

#include <stdbool.h>
#include <stdint.h>

/*!
 * \brief Initializes GPIO register C for use with push buttons 100 and 101
 * \param pb100Int Enable interrupts for push button 100
 * \param pb101Int Enable interrupts for push button 101
 * \param priority Interrupt priority. Only the bottom three bits are used.
 *                 Ignored if pb100Init and pb101Init are false.
 *
 * Interrupts, if enabled, will be generated on both rising and falling edges.
 * \todo Add parameter(s) to select which edge(s) should trigger interrupts
 */
void initButtons(bool pb100Int, bool pb101Int, uint8_t priority);

//! Clears the interrupt for push button 100
void clearPB100Int(void);

//! Clears the interrupt for push button 101
void clearPB101Int(void);

//! Returns true if push button 100 is currently pressed
bool pb100Pressed(void);

//! Returns true if push button 101 is currently pressed
bool pb101Pressed(void);

#endif
