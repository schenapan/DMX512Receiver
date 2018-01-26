#ifndef _ATMEGA164_INT_H_
#define _ATMEGA164_INT_H_
/******************************************************************************/
/*                                                                            */
/* => Interrupts management                                                   */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/******************************************************************************/
/*                                                                            */
/*  Constant and type                                                         */
/*                                                                            */
/******************************************************************************/

 /** \brief define available mode of trigger */
#define EXT_INT_TRIGGER_LOW_LVL	      0U
#define EXT_INT_TRIGGER_ANY_EDGE	    1U
#define EXT_INT_TRIGGER_FALLING_EDGE  2U
#define EXT_INT_TRIGGER_RISING_EDGE	  3U
typedef Int8U ExtIntTrMode;


/******************************************************************************/
/*  Public function                                                           */
/******************************************************************************/

/**
* \brief rend actif une interruption externe
*
* \param[IN] i_io : io concernee par l'interruption
*/
void micExtIntEnable( SIo i_io );

/**
* \brief rend inactif une interruption externe
*
* \param[IN] i_io : io concernee par l'interruption
*/
void micExtIntDisable( SIo i_io );

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
                       );



#if 0

// Available external interrupt 0 trigger (INT0)
enum
{
  INT0_TRIGGER_LOW_LEVEL = ((0U << ISC01) | (0U << ISC00)),
  INT0_TRIGGER_ANY_EDGE = ((0U << ISC01) | (1U << ISC00)),
  INT0_TRIGGER_FALLING_EDGE = ((1U << ISC01) | (0U << ISC00)),
  INT0_TRIGGER_RISING_EDGE = ((1U << ISC01) | (1U << ISC00))
};
typedef Int8U Int0Trigger;


// Available external interrupt 1  trigger (INT1)
enum
{
  INT1_TRIGGER_LOW_LEVEL = ((0U << ISC11) | (0U << ISC10)),
  INT1_TRIGGER_ANY_EDGE = ((0U << ISC11) | (1U << ISC10)),
  INT1_TRIGGER_FALLING_EDGE = ((1U << ISC11) | (0U << ISC10)),
  INT1_TRIGGER_RISING_EDGE = ((1U << ISC11) | (1U << ISC10))
};
typedef Int8U Int1Trigger;


// Available external interrupt 2 trigger (INT2)
enum
{
  INT2_TRIGGER_LOW_LEVEL = ((0U << ISC21) | (0U << ISC20)),
  INT2_TRIGGER_ANY_EDGE = ((0U << ISC21) | (1U << ISC20)),
  INT2_TRIGGER_FALLING_EDGE = ((1U << ISC21) | (0U << ISC20)),
  INT2_TRIGGER_RISING_EDGE = ((1U << ISC21) | (1U << ISC20))
};
typedef Int8U Int2Trigger;


// Available port change interrupt flags
enum
{
  PORTA_CHANGE_FLAG = (1U << PCIF0),
  PORTB_CHANGE_FLAG = (1U << PCIF1),
  PORTC_CHANGE_FLAG = (1U << PCIF2),
  PORTD_CHANGE_FLAG = (1U << PCIF3)
};
typedef Int8U PortChangeInterruptFlag;
#define ALL_PORT_CHANGE_FLAGS ((1U << PCIF0) | (1U << PCIF1) | \
                               (1U << PCIF2) | (1U << PCIF3))

// Available port change selection mask
enum
{
  PORTA_CHANGE_INTERRUPT_MASK = (1U << PCIE0),
  PORTB_CHANGE_INTERRUPT_MASK = (1U << PCIE1),
  PORTC_CHANGE_INTERRUPT_MASK = (1U << PCIE2),
  PORTD_CHANGE_INTERRUPT_MASK = (1U << PCIE3)
};
typedef Int8U PortChangeInterruptMask;


// Type for mask of selection  of pins that take part in port change
typedef Int8U PortChangePinMask;



/*
 *  External interrupt INT0
 */
// Clear External interrupt 0 flag.

void micClearInterrupt0Flag(void);


Boolean micInterrupt0FlagRead(void);

// Unmask external interrupt 0.

void micUnmaskInterrupt0(void);

// Mask external interrupt 0.

void micMaskInterrupt0(void);

// Set external Interrupt 0 trigger event.

void micSetTriggerInterrupt0(Int0Trigger trigger_event);

// Get external Interrupt 0 trigger event.
Int0Trigger micGetTriggerInterrupt0( void );


/*
 *  External interrupt INT1
 */
// Clear External interrupt 1 flag.

void micClearInterrupt1Flag(void);

// Unmask external interrupt 1.

void micUnmaskInterrupt1(void);

// Mask external interrupt 1.

void micMaskInterrupt1(void);

// Set external Interrupt 1 trigger event.

void micSetTriggerInterrupt1(Int1Trigger trigger_event);

// Get external Interrupt 1 trigger event.
Int1Trigger micGetTriggerInterrupt1( void );


/*
 *  External interrupt INT1
 */
// Clear External interrupt 2 flag.

void micClearInterrupt2Flag(void);

// Unmask external interrupt 2.

void micUnmaskInterrupt2(void);

// Mask external interrupt 2.

void micMaskInterrupt2(void);

// Set external Interrupt 2 trigger event.

void micSetTriggerInterrupt2(Int2Trigger trigger_event);

// Get external Interrupt 2 trigger event.
Int2Trigger micGetTriggerInterrupt2( void );

/*
 *  Port change interrupts
 */


void micPortChangeClearInterruptFlag(PortChangeInterruptFlag flags_mask);

// Unmask "port change" interrupts.
void micPortChangeUnmaskInterrupts( PortChangeInterruptMask mask );

// Mask "port change" interrupts.

void micPortChangeMaskInterrupts(PortChangeInterruptMask mask);

// Select pins of port A that takes part in Port change interrupt.

void micPortChangeSelectPinsPortA(PortChangePinMask pins_mask);

// Select pins of port B that takes part in Port change interrupt.

void micPortChangeSelectPinsPortB(PortChangePinMask pins_mask);

// Select pins of port C that takes part in Port change interrupt.

void micPortChangeSelectPinsPortC(PortChangePinMask pins_mask);

// Select pins of port D that takes part in Port change interrupt.

void micPortChangeSelectPinsPortD(PortChangePinMask pins_mask);

#endif


/******************************************************************************/
#endif  // _ATMEGA164_INT_H_
