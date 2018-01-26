#ifndef _ATMEGA164_JTAG_H_
#define _ATMEGA164_JTAG_H_
/******************************************************************************/
/*                                                                            */
/* => JTAG management                                                         */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*
 * => Types:
 */



//------------------------------------------------------------------------------
/*
 * => Functions:
 */

// Turn on JTAG

void micJTagTurnOn(void);

// Turn off JTAG (power comsumption reduction)

void micJTagTurnOff(void);


/******************************************************************************/
#endif   // _ATMEGA164_JTAG_H_
