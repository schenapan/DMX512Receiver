#ifndef _ATMEGA164_ACOMP_H_
#define _ATMEGA164_ACOMP_H_
/******************************************************************************/
/*                                                                            */
/* => Analog Comparator management                                            */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*
 * => Types:
 */



//------------------------------------------------------------------------------
/*
 * => Functions:
 */

// Turn on Analog comparator

void micComparatorTurnOn(void);

// Turn off Analog comparator

void micComparatorTurnOff(void);


void micCompSrcTrigForInCaptureOn(void);


void micCompSrcTrigForInCaptureOff(void);




/******************************************************************************/
#endif  //_ATMEGA164_ACOMP_H_
