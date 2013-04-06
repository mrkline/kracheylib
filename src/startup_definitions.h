#ifndef __STARTUP_DEFINITIONS_H__
#define __STARTUP_DEFINITIONS_H__

// Defined in assembly file startup_rvmdk.S

void DisableInterrupts(void); //!< Disable all interrupts
void EnableInterrupts(void);  //!< Enable interrupts (after calling DisableInterrupts)
long StartCritical (void);    //!< previous I bit, disable interrupts
void EndCritical(long sr);    //!< restore I bit to previous value
void WaitForInterrupt(void);  //!< low power mode

#endif
