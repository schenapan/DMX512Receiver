#ifndef _DRV_LED_H_
#define _DRV_LED_H_
/*******************************************************************************
*                                                                              *
*                         File to be included                                  *
*                                                                              *
*******************************************************************************/

// include micro abstraction layer
#include "Mic/mic_micro.h"

/*******************************************************************************
*                                                                              *
*                  	     Public Functions of the Module                        *
*                                                                              *
*******************************************************************************/

/**
* \brief fonction d'initialisation du module
*/
void drvLedInit( void );

/**
*
* \brief permet d'allumer une led
*
* \param[in] i_led : definition de la led
*
*/
void drvLedSetLedOn( SIo i_led );

/**
*
* \brief permet d'eteindre une led
*
* \param[in] i_led : definition de la led
*
*/
void drvLedSetLedOff( SIo i_led );

void drvLedSetOnTime( SIo i_led, Int8U on_time_value );

/******************************************************************************/
#endif  /* _DRV_LED_H_ */
