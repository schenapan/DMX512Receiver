#ifndef _ATMEGA164_BOD_H_
#define _ATMEGA164_BOD_H_
/******************************************************************************/
/*                                                                            */
/* => BOD management                                                          */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*
 * => Types:
 */



//------------------------------------------------------------------------------
/*
 * => Functions:
 */

// Turn on BOD
void micBodTurnOn(void);

// Turn off BOD (power comsumption reduction)
void micBodTurnOff(void);


/******************************************************************************/
#endif   // _ATMEGA164_BOD_H_