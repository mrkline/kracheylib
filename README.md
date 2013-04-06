# Kracheylib

## Motivation

This repo aims to share code from previous assignments to speed up future ones.
For those unfamiliar with Github, the code can be downloaded by clicking the "ZIP" button.
Feel free to submit pull requests with additional code. So far, it contains the following:

- `led.h` and `led.c`, which provide functions for initializing and using the board LEDs

- `buttons.h` and `buttons.c`, which provide functions for initializing and using the board buttons (PB100 and 101).
  Interrupt support is provided for both buttons.

- `timer.h` and `timer.c`, which provide setup functions for both the SysTick timer and Timer 0 (subtimer A)

To use the code, just copy the `.h` and `.c` files you want to use into the Kyle project directory and add the
`.c` files to the Kyle project.

## What about the provided ECE 353 libraries?

Though the library currently contains some functionality that duplicates the provided ones, it aims to

- have a few simplifications (for example, the `setLEDs` function flips the bits for you)
- have useful additions as time goes on
- Allow for more options than the provided code

## License and use

Public domain, yada yada.
