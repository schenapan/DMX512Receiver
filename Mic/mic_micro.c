/*******************************************************************************
*                                                                              *
*                         File to be included                                  *
*                                                                              *
*******************************************************************************/

// Include micro abstraction layer
#include "mic_micro.h"


/*******************************************************************************
*                                                                              *
*                         private type declaration                             *
*                                                                              *
*******************************************************************************/


/*******************************************************************************
*                                                                              *
*                         constantes declaration                               *
*                                                                              *
*******************************************************************************/


/*******************************************************************************
*                                                                              *
*                             Private  data                                    *
*                                                                              *
*******************************************************************************/


/*******************************************************************************
*                                                                              *
*                            Generic definition                                *
*                                                                              *
*******************************************************************************/


/*******************************************************************************
*                                                                              *
*                         Private Macros of the module                         *
*                                                                              *
*******************************************************************************/


/*******************************************************************************
*                                                                              *
*                  Private Functions of the Module                             *
*                                                                              *
*******************************************************************************/


/*******************************************************************************
*                                                                              *
*                  Public Functions of the Module                              *
*                                                                              *
*******************************************************************************/


/*******************************************************************************
*                                                                              *
*  Name: memcopy                                                               *
*                                                                              *
*  Subject: make a copy byte after byte from one location to another           *
*                                                                              *
*  Input(s): None                                                              *
*                                                                              *
*  Output(s): None                                                             *
*                                                                              *
*******************************************************************************/

void memCpy (Int8U dest_ptr[],
             Int8U src_ptr[],
             Int8U len )
{
  while ( len )
  {
    len--;
    dest_ptr[len] = src_ptr[len];
  }

  return;
}


/*******************************************************************************
*                                                                              *
*  Name: memMove                                                               *
*                                                                              *
*  Subject: make a move byte after byte from one location to another           *
*                                                                              *
*  Input(s): dest_ptr : addresse de destination                                *
*            src_ptr : addresse source                                         *
*            len : taille a déplacer en octet                                  *
*                                                                              *
*  Output(s): None                                                             *
*                                                                              *
*******************************************************************************/

void memMove (Int8U dest_ptr[],
              Int8U src_ptr[],
              Int8U len )
{
  if ( dest_ptr > src_ptr )
  {
    while ( len )
    {
      len--;
      dest_ptr[len] = src_ptr[len];
    }
  }
  else
  {
    Int8U i;

    for ( i = 0U; i < len; i++ )
    {
      dest_ptr[i] = src_ptr[i];
    }
  }

  return;
}


/*******************************************************************************
*                                                                              *
*  Name: memCmp                                                                *
*                                                                              *
*  Subject: compare byte after byte 2 data locations                           *
*                                                                              *
*  Input(s): None                                                              *
*                                                                              *
*  Output(s): result of the comparaison,                                       *
*             0, if all data byte are the same                                 *
*             1, if at least one data byte is different                        *
*                                                                              *
*******************************************************************************/

Int8U memCmp(Int8U dest_ptr[],
             Int8U src_ptr[],
             Int8U len )
{
  Int8U rvalue = 0U;

  while ( len )
  {
    len--;
    if ( dest_ptr[len] != src_ptr[len] )
    {
      rvalue = 1U;
    }
  }

  return rvalue;
}


/*******************************************************************************
*                                                                              *
*  Name: memSet                                                                *
*                                                                              *
*  Subject: remplit un buffer avec une valeur constante                        *
*                                                                              *
*  Input(s): dest_ptr : buffer a remplir                                       *
*            value_to_fill : valeur utilisée pour remplir le buffer            *
*            len : longueur du buffer                                          *
*                                                                              *
*  Output(s): None                                                             *
*                                                                              *
*******************************************************************************/

void memSet( Int8U dest_ptr[], Int8U value_to_fill, Int8U len )
{
  while ( len )
  {
    len--;
    dest_ptr[len] = value_to_fill;
  }

  return;
}


/*******************************************************************************
*                                                                              *
*  Name: delayMicroSecond                                                      *
*                                                                              *
*  Subject: create an active wait in the software                              *
*                                                                              *
*  Input(s): time to wait, in µs                                               *
*                                                                              *
*  Output(s): None                                                             *
*                                                                              *
*******************************************************************************/

void delayMicroSecond(Int32U us)
{
/*
  if ( us != 0U )
  {
    #if (FOSC_HZ <= 4000000UL)
      //Due to a crystal of 3.6864MHz, this function wont be precise
      //Actual delays will be about 9% longer than desired delays
      while ( (us-=2U) > 2U )
    #elif (FOSC_HZ >= 8000000UL)
      while ( (us-=1U) > 1U )
    #endif
    {
      micNop();
    }
    // return is 4 cycles (but not accounted for)
  }
*/
  return;
}


/*******************************************************************************
*                                                                              *
*  Name: soft_reset                                                            *
*                                                                              *
*  Subject: call to reset the product, in case of wanted reset                 *
*                                                                              *
*  Input(s): None                                                              *
*                                                                              *
*  Output(s): None                                                             *
*                                                                              *
*******************************************************************************/

void softReset( Int8U error_index )
{
  if ( error_index != 0xFFU )
  {
    // change watchdog timer to speed the reset
    ATOMIC( micSetWatchdogPrescaler( WDTPR_256K ); )
  }
  else
  {
    // on souhaite un reset rapide (pour le dimmer)
    ATOMIC( micSetWatchdogPrescaler( WDTPR_2K ); )
  }
  #ifdef E_UNIT_LEGRAND
    // pour identifier les probleme de reset on n'accelere pas le watchdog mais
    // on passe en clignotement rapide sur les deux led
    srvLedExecute( E_UNIT_LEGRAND, E_TYPE_LED_NWK, E_EVENT_SRV_LED_NWK_FLASHING, 0xFFU );
    srvLedExecute( E_UNIT_LEGRAND, E_TYPE_LED_BND, E_EVENT_SRV_LED_BND_FLASHING_5S, 0xFFU );
  #endif
  while (1)
  {
    micNop(); // boucle vide en attente de watchdog
  }
}


/*******************************************************************************
*                                                                              *
*                  Private Functions of the Module                             *
*                                                                              *
*******************************************************************************/


/*******************************************************************************
*                                                                              *
*                  ISR Function of the Module                                  *
*                                                                              *
*******************************************************************************/


//------------------------------------------------------------------------------



/******************************************************************************/
/******************************************************************************/
