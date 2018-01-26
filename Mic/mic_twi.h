#ifndef _ATMEGA164_TWI_H_
#define _ATMEGA164_TWI_H_
/******************************************************************************/
/*                                                                            */
/* => TWI (I2C) management                                                    */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*
 * => Types:
 */


//------------------------------------------------------------------------------
/*
 * => Functions:
 */
// Turns on the TWI peripheral.

void micTwiTurnOn(void);

// Turns off the TWI peripheral.
void micTwiTurnOff(void);


/******************************************************************************/
#endif  // _ATMEGA164_TWI_H_
