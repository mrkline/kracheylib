#ifndef __LED_H__
#define __LED_H__

#include <stdint.h>

#define RED (1 << 0) //!< Red bit for LED color functions
#define GREEN (1 << 1) //!< Green bit for LED color functions
#define BLUE (1 << 2) //!< Blue bit for LED color functions
#define NO_COLOR 0 //!< For LED color functions

//! Initializes GPIO registers needed to control LEDs
void initLEDs(void);

//! Sets a value on the LEDs
//! \param count The count to display on the LEDs. Will be inverted automatically since LEDs are active-low.
void setLEDs(uint8_t count);

//! Returns the current LED color
uint8_t getLEDColor(void);

//! Sets the color for all LEDs
//! \param color The color to use (see definitions in led.h). Only the bottom three bits are used.
void setLEDColor(uint8_t color);

#endif
