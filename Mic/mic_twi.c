/*******************************************************************************
***                                                                          ***
**                                                                            **
**                            TWI (I2C) MANAGEMENT                            **
**                                                                            **
***                                                                          ***
*******************************************************************************/


// Include header for this micrcontroller
#include "Mic/mic_micro.h"


/*******************************************************************************
*                                                                              *
*  Name: micTwiTurnOn                                                          *
*                                                                              *
*  Subject: Turns on the TWI serial bus.                                       *
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

void micTwiTurnOn(void)
{
  // Power up TWI (I2C) module
  prr &= ~(1U << PRTWI);

  // Enable TWI
  twcr |= (1U << TWEN);

  return;
}

/*******************************************************************************
*                                                                              *
*  Name: micTwiTurnOff                                                         *
*                                                                              *
*  Subject: turns off the TWI serial bus.                                      *
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

void micTwiTurnOff(void)
{
  // Turn off TWI peripherals
  twcr &= ~ (1U << TWEN);

  // Reduce power consumption
  prr |= (1U << PRTWI);
  return;
}




/*****************************************************************************/

