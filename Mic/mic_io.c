/*******************************************************************************
***                                                                          ***
**                                                                            **
**                           IO MANAGEMENT                                    **
**                                                                            **
***                                                                          ***
*******************************************************************************/

// Include header for this micrcontroller
#include "Mic/mic_micro.h"


/******************************************************************************/
/*                                                                            */
/*                         Constant and type                                  */
/*                                                                            */
/******************************************************************************/



/*
typedef struct
{
  Int8U volatile __io *port;
  Int8U volatile __io *ddr;
  Int8U volatile __io *pin;
  Int8U bit;
} SIoPin;

// WARNING the table is in the same ordre than then EIOPIN enum
static __CODE_MEMORY const SIoPin io_table[EIO_NB_PIN] =
{
  { &PORTA, &DDRA, &PINA, 0U},
  { &PORTA, &DDRA, &PINA, 1U},
  { &PORTA, &DDRA, &PINA, 2U},
  { &PORTA, &DDRA, &PINA, 3U},
  { &PORTA, &DDRA, &PINA, 4U},
  { &PORTA, &DDRA, &PINA, 5U},
  { &PORTA, &DDRA, &PINA, 6U},
  { &PORTA, &DDRA, &PINA, 7U},

  { &PORTB, &DDRB, &PINB, 0U},
  { &PORTB, &DDRB, &PINB, 1U},
  { &PORTB, &DDRB, &PINB, 2U},
  { &PORTB, &DDRB, &PINB, 3U},
  { &PORTB, &DDRB, &PINB, 4U},
  { &PORTB, &DDRB, &PINB, 5U},
  { &PORTB, &DDRB, &PINB, 6U},
  { &PORTB, &DDRB, &PINB, 7U},

  { &PORTC, &DDRC, &PINC, 0U},
  { &PORTC, &DDRC, &PINC, 1U},
  { &PORTC, &DDRC, &PINC, 2U},
  { &PORTC, &DDRC, &PINC, 3U},
  { &PORTC, &DDRC, &PINC, 4U},
  { &PORTC, &DDRC, &PINC, 5U},
  { &PORTC, &DDRC, &PINC, 6U},
  { &PORTC, &DDRC, &PINC, 7U},

  { &PORTD, &DDRD, &PIND, 0U},
  { &PORTD, &DDRD, &PIND, 1U},
  { &PORTD, &DDRD, &PIND, 2U},
  { &PORTD, &DDRD, &PIND, 3U},
  { &PORTD, &DDRD, &PIND, 4U},
  { &PORTD, &DDRD, &PIND, 5U},
  { &PORTD, &DDRD, &PIND, 6U},
  { &PORTD, &DDRD, &PIND, 7U}
};
*/

/**
* \brief fonction d'initialisation du module
*
* \return TRUE si success
*/
#ifndef micIoInit
  Boolean micIoInit( void )
  {
  /*  
    Int8U loop;
  
    for( loop=0U ; loop<EIO_NB_PIN ; loop++)
    {
      micIoConfigInput( (EIOPIN)loop, PORT_NO_PULL_UP );
    }
  */  
    return TRUE;
  }
#endif // micIoInit

/**
* \brief configure une io en sortie
*
* \param[IN] i_port : port sur lequel ce trouve l'io
* \param[IN] i_io : numero de l'io
*
* \return TRUE si success
*/
#ifndef micIoConfigOutput
  Boolean micIoConfigOutput( IoPort i_port, IoPin i_io ){return FALSE;};
#endif // micIoConfigOutput

/**
* \brief configure une io en entree
*
* \param[IN] i_port : port sur lequel ce trouve l'io
* \param[IN] i_io : numero de l'io
* \param[IN] i_pull_up_mode : activation de la pull-up interne
*
* \return TRUE si success
*/
#ifndef micIoConfigInput
  void micIoConfigInput( SIo i_io, IoPullUp i_pull_up_mode ){};
#endif // micIoConfigInput

/**
* \brief affecte un etat a une io
*
* \param[IN] i_port : port sur lequel ce trouve l'io
* \param[IN] i_io : numero de l'io
* \param[IN] i_level : niveau de sortie souhaite
*
* \return TRUE si success
*/
#ifndef micIoSet
  Boolean micIoSet( IoPort i_port, IoPin i_io, IoLevel i_level ){return FALSE;};
#endif // micIoSet

/**
* \brief Toggle l'etat d'une io
*
* \param[IN] i_port : port sur lequel ce trouve l'io
* \param[IN] i_io : numero de l'io
*
* \return TRUE si success
*/
#ifndef micIoToggle
  Boolean micIoToggle( IoPort i_port, IoPin i_io ){return FALSE;};
#endif // micIoToggle

/**
* \brief lit la valeur d'un io
*
* \param[IN] i_port : port sur lequel ce trouve l'io
* \param[IN] i_io : numero de l'io
*
* \return level of the io, (IO_LVL_GND by default )
*/
#ifndef micIoGet
  IoLevel micIoGet( IoPort i_port, IoPin i_io ){return FALSE;};
#endif // micIoGet

/**
* \brief ecrit sur un port
*
* \param[IN] i_port : port concerne
* \param[IN i_value : valeur a ecrire
*
* \return TRUE if success
*/
#ifndef micIoWrite
  Boolean micIoWrite( IoPort i_port, Int8U i_value ){return FALSE;};
#endif // micIoWrite


/**
* \brief lit sur un port
*
* \param[IN] i_port : port concerne
*
* \return valeur lue sur le port
*/
#ifndef micioRead
  Int8U micioRead( IoPort i_port ){return 0U;};
#endif // micioRead


#if 0

/*******************************************************************************
*                                                                              *
*  Name: micIoConfigOutput                                                     *
*                                                                              *
*  Subject: Set IO as output                                                   *
*                                                                              *
*                                                                              *
*  Input(s): io to configure (see enum of io)                                  *
*                                                                              *
*  Output(s): None                                                             *
*                                                                              *
*  Modified Global variables: None                                             *
*                                                                              *
*  Necessary Interrupts: None                                                  *
*                                                                              *
*******************************************************************************/

void micIoConfigOutput( EIOPIN io )
{
  *(io_table[io].ddr) |= (1U << io_table[io].bit);
  return;
}


/*******************************************************************************
*                                                                              *
*  Name: micIoConfigInput                                                      *
*                                                                              *
*  Subject: Set IO as input and add pull up if necessary                       *
*                                                                              *
*                                                                              *
*  Input(s): io to configure (see enum of io), pull-up enable                  *
*                                                                              *
*  Output(s): None                                                             *
*                                                                              *
*  Modified Global variables: None                                             *
*                                                                              *
*  Necessary Interrupts: None                                                  *
*                                                                              *
*******************************************************************************/

void micIoConfigInput( EIOPIN io, EInputPullUp pull_up_enable )
{
  *(io_table[io].ddr) &= ~(1U << io_table[io].bit);
  *(io_table[io].port) &= ~(1U << io_table[io].bit);
  *(io_table[io].port) |= (Int8U)((pull_up_enable) << io_table[io].bit);
}


/*******************************************************************************
*                                                                              *
*  Name: micIoSet                                                              *
*                                                                              *
*  Subject: Set IO at specified level                                          *
*                                                                              *
*                                                                              *
*  Input(s): io to set (see enum of io)                                        *
*            level : level to set (IO_LEVEL_GND or IO_LEVEL_VCC)               *
*                                                                              *
*  Output(s): None                                                             *
*                                                                              *
*******************************************************************************/

void micIoSet( EIOPIN io, IoLevel level )
{
  IoLevel not_level = ((IoLevel)(~level)) & 0x01U ;

  *(io_table[io].port) &= (Int8U)(~(Int8U)(not_level << (Int8U)io_table[io].bit));
  *(io_table[io].port) |= (Int8U)( level << (Int8U)io_table[io].bit );
}


/*******************************************************************************
*                                                                              *
*  Name: micIoToggle                                                           *
*                                                                              *
*  Subject: Toggle IO                                                          *
*                                                                              *
*                                                                              *
*  Input(s): io to toggle (see enum of io)                                     *
*                                                                              *
*  Output(s): None                                                             *
*                                                                              *
*******************************************************************************/
void micIoToggle( EIOPIN io )
{
  //ATOMIC(
  *(io_table[io].port) ^= (1U << io_table[io].bit);
  //)

}

/*******************************************************************************
*                                                                              *
*  Name: micIoRead                                                             *
*                                                                              *
*  Subject: Read IO level                                                      *
*                                                                              *
*                                                                              *
*  Input(s): io to read (see enum of io)                                       *
*                                                                              *
*  Output(s): value read (0 / 1)                                               *
*                                                                              *
*  Modified Global variables: None                                             *
*                                                                              *
*  Necessary Interrupts: None                                                  *
*                                                                              *
*******************************************************************************/

Int8U micIoRead( EIOPIN io )
{
  Int8U pin_value;

  pin_value = *(io_table[io].pin);
  pin_value = pin_value >> io_table[io].bit;
  pin_value &= 0x01U;

  return( pin_value );
}

/*******************************************************************************
*                                                                              *
*  Subject: Read the ddr register for a io                                     *
*           usefull to make some backup of the register                        *
*  Input(s): io of the ddr to read (see enum of io)                            *
*                                                                              *
*  Output(s): value read (0 / 1)                                               *
*                                                                              *
*  Modified Global variables: None                                             *
*                                                                              *
*  Necessary Interrupts: None                                                  *
*                                                                              *
*******************************************************************************/

Int8U micIoReadDdr( EIOPIN io )
{
  Int8U ddr_value;
  ddr_value = *(io_table[io].ddr);
  ddr_value = ddr_value >> io_table[io].bit;
  ddr_value &= 0x01U;

  return ddr_value;
}

/*******************************************************************************
*                                                                              *
*  Input(s): io of the port to read (see enum of io)                           *
*            usefull to make some backup of the register                       *
*  Output(s): value read (0 / 1)                                               *
*                                                                              *
*  Modified Global variables: None                                             *
*                                                                              *
*  Necessary Interrupts: None                                                  *
*                                                                              *
*******************************************************************************/
Int8U micIoReadPort( EIOPIN io )
{
  Int8U port_value ;
  port_value = *(io_table[io].port);
  port_value = port_value >> io_table[io].bit;
  port_value &= 0x01U;

  return port_value;
}

/*******************************************************************************
*                                                                              *
*  Name:                                                                       *
*                                                                              *
*  Subject:                                                                    *
*                                                                              *
*                                                                              *
*  Input(s):                                                                   *
*                                                                              *
*  Output(s):                                                                  *
*                                                                              *
*******************************************************************************/

void micIoEnableMask( EIOPIN io )
{
  if( io < EIO_PORT_A )
  {
    pcmsk0 |= (1U << io_table[io].bit);
  }
  else if( io < EIO_PORT_B )
  {
    pcmsk1 |= (1U << io_table[io].bit);
  }
  else if( io < EIO_PORT_C )
  {
    pcmsk2 |= (1U << io_table[io].bit);
  }
  else
  {
    pcmsk3 |= (1U << io_table[io].bit);
  }
}


/*******************************************************************************
*                                                                              *
*  Name:                                                                       *
*                                                                              *
*  Subject:                                                                    *
*                                                                              *
*                                                                              *
*  Input(s):                                                                   *
*                                                                              *
*  Output(s):                                                                  *
*                                                                              *
*******************************************************************************/

void micIoDisableMask( EIOPIN io )
{
  if( io < EIO_PORT_A )
  {
    pcmsk0 &= ~(1U << io_table[io].bit);
  }
  else if( io < EIO_PORT_B )
  {
    pcmsk1 &= ~(1U << io_table[io].bit);
  }
  else if( io < EIO_PORT_C )
  {
    pcmsk2 &= ~(1U << io_table[io].bit);
  }
  else
  {
    pcmsk3 &= ~(1U << io_table[io].bit);
  }
}


/*******************************************************************************
*                                                                              *
*  Name:                                                                       *
*                                                                              *
*  Subject:                                                                    *
*                                                                              *
*                                                                              *
*  Input(s):                                                                   *
*                                                                              *
*  Output(s):                                                                  *
*                                                                              *
*******************************************************************************/

void micIoEnableISR( EIOPIN io )
{
  if( io < EIO_PORT_A )
  {
    pcicr |= (1U << PCIE0);
  }
  else if( io < EIO_PORT_B )
  {
    pcicr |= (1U << PCIE1);
  }
  else if( io < EIO_PORT_C )
  {
    pcicr |= (1U << PCIE2);
  }
  else
  {
    pcicr |= (1U << PCIE3);
  }
}


/*******************************************************************************
*                                                                              *
*  Name:                                                                       *
*                                                                              *
*  Subject:                                                                    *
*                                                                              *
*                                                                              *
*  Input(s):                                                                   *
*                                                                              *
*  Output(s):                                                                  *
*                                                                              *
*******************************************************************************/

void micIoDisableISR( EIOPIN io )
{
  if( io < EIO_PORT_A )
  {
    pcicr &= ~(1U << PCIE0);
  }
  else if( io < EIO_PORT_B )
  {
    pcicr &= ~(1U << PCIE1);
  }
  else if( io < EIO_PORT_C )
  {
    pcicr &= ~(1U << PCIE2);
  }
  else
  {
    pcicr &= ~(1U << PCIE3);
  }
}

#endif // #if 0

/******************************************************************************/
/******************************************************************************/
