/*******************************************************************************
***                                                                          ***
**                                                                            **
**                              JTAG MANAGEMENT                               **
**                                                                            **
***                                                                          ***
*******************************************************************************/

// Note AT 16 and AT 164 and other:
// In order to avoid unintentional disabling or enabling of
// the JTAG interface, a timed sequence must be followed when changing this bit:
// The application software must write this bit to the desired value twice
// within 4 cycles to change its value.

// Include header for this micrcontroller
#include "Mic/mic_micro.h"


/*******************************************************************************
*                                                                              *
*  Name: micJTagTurnOn                                                         *
*                                                                              *
*  Subject: Turns on the JTAG.                                                 *
*                                                                              *
*                                                                              *
*  Input(s):  None                                                             *
*                                                                              *
*  Output(s): None                                                             *
*                                                                              *
*  Modified Global variables: None                                             *
*                                                                              *
*  Necessary Interrupts: None                                                  *
*                                                                              *
*******************************************************************************/

void micJTagTurnOn(void)
{
  mcucr &= ~(1U << JTD);
  mcucr &= ~(1U << JTD);
  return;
}


/*******************************************************************************
*                                                                              *
*  Name: micJTagTurnOff                                                        *
*                                                                              *
*  Subject: Turns off the JTAG.                                                *
*                                                                              *
*                                                                              *
*  Input(s):  None                                                             *
*                                                                              *
*  Output(s): None                                                             *
*                                                                              *
*  Modified Global variables: None                                             *
*                                                                              *
*  Necessary Interrupts: None                                                  *
*                                                                              *
*******************************************************************************/

void micJTagTurnOff(void)
{
  mcucr |= (1U << JTD);
  mcucr |= (1U << JTD);
  return;
}


/*****************************************************************************/

