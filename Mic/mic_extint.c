/*******************************************************************************
***                                                                          ***
**                                                                            **
**                     EXTERNAL INTERRUPT MANAGEMENT                          **
**                                                                            **
***                                                                          ***
*******************************************************************************/

// Include header for this micrcontroller
#include "Mic/mic_micro.h"


/**
* \brief rend actif une interruption externe
*
* \param[IN] i_io : io concernee par l'interruption
*/
void micExtIntEnable( SIo i_io ){};

/**
* \brief rend inactif une interruption externe
*
* \param[IN] i_io : io concernee par l'interruption
*/
void micExtIntDisable( SIo i_io ){};

/**
* \brief configure une interruption externe
*
* \param[IN] i_io : io concernee par l'interruption
* \param[IN] i_trigger_mode : mode de declenchement
* \param[IN] ip_callback : fonction a appeler lors du declenchement
*/
void micExtIntConfigure( SIo i_io,
                         ExtIntTrMode i_trigger_mode,
						             void (*ip_callback)(void)
                       ){};



#if 0

/*******************************************************************************
*                                                                              *
*  Name: micClearInterrupt0Flag                                                *
*                                                                              *
*  Subject: Clear External interrupt 0 flag.                                   *
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


void micClearInterrupt0Flag(void)
{
  eifr = (1U << INTF0);
  return;
}


Boolean micInterrupt0FlagRead(void)
{
  return (Boolean)(eifr & (1U << INTF0));
}

/*******************************************************************************
*                                                                              *
*  Name: micUnmaskInterrupt0                                                   *
*                                                                              *
*  Subject: Unmask external interrupt 0.                                       *
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


void micUnmaskInterrupt0(void)
{
  eimsk |= (1U << INT0);
  return;
}


/*******************************************************************************
*                                                                              *
*  Name: micMaskInterrupt0                                                     *
*                                                                              *
*  Subject: Mask external interrupt 0.                                         *
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


void micMaskInterrupt0(void)
{
  eimsk &= ~(1U << INT0);
  return;
}


/*******************************************************************************
*                                                                              *
*  Name:micSetTriggerInterrupt0                                                *
*                                                                              *
*  Subject: Set Interrupt0 trigger event.                                      *
*                                                                              *
*                                                                              *
*  Input(s): trigger_event = External interrupt 0 trigger event.               *
*                                                                              *
*  Output(s): None                                                             *
*                                                                              *
*******************************************************************************/


void micSetTriggerInterrupt0(Int0Trigger trigger_event)
{
   eicra = (eicra & ~((1U << ISC01) | (1U << ISC00))) |
           (trigger_event & ((1U << ISC01) | (1U << ISC00)));
}

/*******************************************************************************
*                                                                              *
*  Name:micGetTriggerInterrupt0                                                *
*                                                                              *
*  Subject: Get Interrupt0 trigger event.                                      *
*                                                                              *
*                                                                              *
*  Input(s): None                                                              *
*                                                                              *
*  Output(s): trigger_event = External interrupt 0 trigger event.              *
*                                                                              *
*******************************************************************************/


Int0Trigger micGetTriggerInterrupt0( void )
{
   return ( eicra & ((1U << ISC01) | (1U << ISC00)) );
}

/*******************************************************************************
*                                                                              *
*  Name: micClearInterrupt1Flag                                                *
*                                                                              *
*  Subject: Clear External interrupt 1 flag (INTF1).                           *
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


void micClearInterrupt1Flag(void)
{
  eifr = (1U << INTF1);
  return;
}


/*******************************************************************************
*                                                                              *
*  Name: micUnmaskInterrupt1                                                   *
*                                                                              *
*  Subject: Unmask external interrupt 1.                                       *
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


void micUnmaskInterrupt1(void)
{
  eimsk |= (1U << INT1);
  return;
}


/*******************************************************************************
*                                                                              *
*  Name: micMaskInterrupt1                                                     *
*                                                                              *
*  Subject: Mask external interrupt 1.                                         *
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


void micMaskInterrupt1(void)
{
  eimsk &= ~(1U << INT1);
  return;
}


/*******************************************************************************
*                                                                              *
*  Name:micSetTriggerInterrupt1                                                *
*                                                                              *
*  Subject: Set external Interrupt 1 trigger event.                            *
*                                                                              *
*                                                                              *
*  Input(s): trigger_event = External interrupt 1 trigger event.               *
*                                                                              *
*  Output(s): None                                                             *
*                                                                              *
*  Modified Global variables: None                                             *
*                                                                              *
*  Necessary Interrupts: None                                                  *
*                                                                              *
*******************************************************************************/


void micSetTriggerInterrupt1(Int1Trigger trigger_event)
{
   eicra = (eicra & ~((1U << ISC11) | (1U << ISC10))) |
           (trigger_event & ((1U << ISC11) | (1U << ISC10)));
   return;
}

/*******************************************************************************
*                                                                              *
*  Name:micGetTriggerInterrupt1                                                *
*                                                                              *
*  Subject: Get Interrupt1 trigger event.                                      *
*                                                                              *
*                                                                              *
*  Input(s): None                                                              *
*                                                                              *
*  Output(s): trigger_event = External interrupt 1 trigger event.              *
*                                                                              *
*******************************************************************************/


Int1Trigger micGetTriggerInterrupt1( void )
{
   return ( eicra & ((1U << ISC11) | (1U << ISC10)) );
}

/*******************************************************************************
*                                                                              *
*  Name: micClearInterrupt2Flag                                                *
*                                                                              *
*  Subject: Clear External interrupt 2 flag (INTF2).                           *
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


void micClearInterrupt2Flag(void)
{
  eifr = (1U << INTF2);
  return;
}


/*******************************************************************************
*                                                                              *
*  Name: micUnmaskInterrupt2                                                   *
*                                                                              *
*  Subject: Unmask external interrupt 2.                                       *
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


void micUnmaskInterrupt2(void)
{
  eimsk |= (1U << INT2);
  return;
}


/*******************************************************************************
*                                                                              *
*  Name: micMaskInterrupt2                                                     *
*                                                                              *
*  Subject: Mask external interrupt 2.                                         *
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


void micMaskInterrupt2(void)
{
  eimsk &= ~(1U << INT2);
  return;
}


/*******************************************************************************
*                                                                              *
*  Name:micSetTriggerInterrupt2                                                *
*                                                                              *
*  Subject: Set external Interrupt 2 trigger event.                            *
*                                                                              *
*                                                                              *
*  Input(s): trigger_event = External interrupt 2 trigger event.               *
*                                                                              *
*  Output(s): None                                                             *
*                                                                              *
*  Modified Global variables: None                                             *
*                                                                              *
*  Necessary Interrupts: None                                                  *
*                                                                              *
*******************************************************************************/


void micSetTriggerInterrupt2(Int2Trigger trigger_event)
{
   eicra = (eicra & ~((1U << ISC21) | (1U << ISC20))) |
           (trigger_event & ((1U << ISC21) | (1U << ISC20)));
   return;
}

/*******************************************************************************
*                                                                              *
*  Name:micGetTriggerInterrupt2                                                *
*                                                                              *
*  Subject: Get Interrupt2 trigger event.                                      *
*                                                                              *
*                                                                              *
*  Input(s): None                                                              *
*                                                                              *
*  Output(s): trigger_event = External interrupt 2 trigger event.              *
*                                                                              *
*******************************************************************************/


Int2Trigger micGetTriggerInterrupt2( void )
{
   return ( eicra & ((1U << ISC21) | (1U << ISC20)) );
}


/*******************************************************************************
*                                                                              *
*  Name:micPortChangeClearInterruptFlag                                        *
*                                                                              *
*  Subject: Clear the specified port pins change interrupts flags              *
*                                                                              *
*                                                                              *
*  Input(s): flags_mask = Mask selecting Port change interupt flags we need to *
*                         clear (a bit 1 means flag is selected)               *
*                                                                              *
*  Output(s): None                                                             *
*                                                                              *
*  Modified Global variables: None                                             *
*                                                                              *
*  Necessary Interrupts: None                                                  *
*                                                                              *
*******************************************************************************/


void micPortChangeClearInterruptFlag(PortChangeInterruptFlag flags_mask)
{
  pcifr = flags_mask;
}


/*******************************************************************************
*                                                                              *
*  Name:micPortChangeUnmaskInterrupt                                           *
*                                                                              *
*  Subject: Unmask specified port pins change interrupts.                      *
*                                                                              *
*                                                                              *
*  Input(s): mask = Mask selecting Port change interuptwe need to unmask.      *
*                   (a bit 1 means selected)                                   *
*                                                                              *
*  Output(s): None                                                             *
*                                                                              *
*******************************************************************************/
void micPortChangeUnmaskInterrupts( PortChangeInterruptMask mask )
{
  pcicr |= mask;
}


/*******************************************************************************
*                                                                              *
*  Name:micPortChangeMaskInterrupt                                             *
*                                                                              *
*  Subject: Mask specified port pins change interrupts                         *
*                                                                              *
*                                                                              *
*  Input(s): mask = Mask selecting Port change interupt we need to mask.       *
*                   (a bit 1 means selected)                                   *
*                                                                              *
*  Output(s): None                                                             *
*                                                                              *
*  Modified Global variables: None                                             *
*                                                                              *
*  Necessary Interrupts: None                                                  *
*                                                                              *
*******************************************************************************/


void micPortChangeMaskInterrupts( PortChangeInterruptMask mask )
{
  pcicr &= (Int8U)(~mask);
}



/*******************************************************************************
*                                                                              *
*  Name:micPortChangeSelectPinsPortA                                           *
*                                                                              *
*  Subject: Select pins of port A that takes part in Port change inetrrupt.    *
*                                                                              *
*                                                                              *
*  Input(s): mask = Select pins that takes part in Port A change interrupts.   *
*                   (a bit 1 means selected)                                   *
*                                                                              *
*  Output(s): None                                                             *
*                                                                              *
*  Modified Global variables: None                                             *
*                                                                              *
*  Necessary Interrupts: None                                                  *
*                                                                              *
*******************************************************************************/


void micPortChangeSelectPinsPortA(PortChangePinMask pins_mask)
{
  pcmsk0 = pins_mask;
  return;
}


/*******************************************************************************
*                                                                              *
*  Name:micPortChangeSelectPinsPortB                                           *
*                                                                              *
*  Subject: Select pins of port B that takes part in Port change inetrrupt.    *
*                                                                              *
*                                                                              *
*  Input(s): mask = Select pins that takes part in Port B change interrupts.   *
*                   (a bit 1 means selected)                                   *
*                                                                              *
*  Output(s): None                                                             *
*                                                                              *
*  Modified Global variables: None                                             *
*                                                                              *
*  Necessary Interrupts: None                                                  *
*                                                                              *
*******************************************************************************/


void micPortChangeSelectPinsPortB(PortChangePinMask pins_mask)
{
  pcmsk1 = pins_mask;
  return;
}


/*******************************************************************************
*                                                                              *
*  Name:micPortChangeSelectPinsPortC                                           *
*                                                                              *
*  Subject: elect pins of port C that takes part in Port change inetrrupt.     *
*                                                                              *
*                                                                              *
*  Input(s): mask = select pins that takes part in Port C change interrupts    *
*                   (a bit 1 means selected)                                   *
*                                                                              *
*  Output(s): None                                                             *
*                                                                              *
*  Modified Global variables: None                                             *
*                                                                              *
*  Necessary Interrupts: None                                                  *
*                                                                              *
*******************************************************************************/


void micPortChangeSelectPinsPortC(PortChangePinMask pins_mask)
{
  pcmsk2 = pins_mask;
  return;
}



/*******************************************************************************
*                                                                              *
*  Name:micPortChangeSelectPinsPortD                                           *
*                                                                              *
*  Subject: Select pins of port D that takes part in Port change interrupt.    *
*                                                                              *
*                                                                              *
*  Input(s): mask = Select pins that takes part in Port D change interrupts    *
*                   (a bit 1 means selected)                                   *
*                                                                              *
*  Output(s): None                                                             *
*                                                                              *
*  Modified Global variables: None                                             *
*                                                                              *
*  Necessary Interrupts: None                                                  *
*                                                                              *
*******************************************************************************/


void micPortChangeSelectPinsPortD(PortChangePinMask pins_mask)
{
  pcmsk3 = pins_mask;
  return;
}

#endif


/******************************************************************************/

