/**
* \brief module de gestion de la communication spi avec l'em260
*
* Utilise drvTimer a 1ms, le peripherique SPI et quelques IO defini dans le 
*  fichier app_product_hardware.h
*
*/


/*******************************************************************************
*                                                                              *
*                         File to be included                                  *
*                                                                              *
*******************************************************************************/

// include micro abstraction layer
#include "Mic/mic_micro.h"

// include driver
#include "drv_timer.h"
#include "drv_event.h"
#include "drv_em260.h"
#include "Drv/drv_led.h"

// include application
#include "app_product_hardware.h"

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

/** commandes possible pour l'em260 */
#define EM260_SPI_BYTE_PROTOCOL_VERSION   0x0AU
#define EM260_SPI_BYTE_STATUS             0x0BU
#define EM260_SPI_BYTE_BOOTLOADER         0xFDU
#define EM260_SPI_BYTE_EZSP               0xFEU

/** octet de terminaison de trame spi */
#define EM260_SPI_END_FRAME               0xA7U

/** 
* timming a respecter enprime en ms
*/
// > 2 ms
#define INTER_SPACING_VALUE_STD   3U

// 8us < timeout < 200ms
#define RESET_TIMEOUT_VALUE       201U

// 250ms < timeout < 1500ms
#define RESET_TIMEOUT_WAIT_VALUE  1501U

// for a command time out is < 200ms
#define STD_TIMEOUT_VALUE         201U

// max timeout 10ms
#define WAKEUP_TIMEOUT_VALUE     11U

// -----------------------------------------------------------------------------
typedef enum
{
   /** Cause for the reset is not known.*/
   EMBER_RESET_UNKNOWN,                                                               // 0x00
   /** A low level was present on the reset pin.*/
   EMBER_RESET_EXTERNAL,                                                              // 0x01
   /** The supply voltage was below the power-on threshold.*/
   EMBER_RESET_POWERON,                                                               // 0x02
   /** The Watchdog is enabled, and the Watchdog Timer period expired.*/
   EMBER_RESET_WATCHDOG,                                                              // 0x03
   /** The Brown-out Detector is enabled, and the supply voltage was
    * below the brown-out threshold.*/
   EMBER_RESET_BROWNOUT,                                                              // 0x04
   /** A logic one was present in the JTAG Reset Register. */
   EMBER_RESET_JTAG,                                                                  // 0x05
   /** A self-check within the code failed unexpectedly. */
   EMBER_RESET_ASSERT,                                                                // 0x06
   /** The return address stack (RSTACK) went out of bounds. */
   EMBER_RESET_RSTACK,                                                                // 0x07
   /** The data stack (CSTACK) went out of bounds. */
   EMBER_RESET_CSTACK,                                                                // 0x08
   /** The bootloader deliberately caused a reset. */
   EMBER_RESET_BOOTLOADER,                                                            // 0x09
   /** The PC wrapped (rolled over) - Currently XAP2B specific */
   EMBER_RESET_PC_ROLLOVER,                                                           // 0x0A
   /** The software deliberately caused a reset - Currently XAP2B specific */
   EMBER_RESET_SOFTWARE,                                                              // 0x0B
   /** Protection fault or privilege violation - Currently XAP2B specific */
   EMBER_RESET_PROTFAULT,                                                             // 0x0C
   /** Flash write failed verification - XAP2B specific */
   EMBER_RESET_FLASH_VERIFY_FAIL,                                                     // 0x0D
   /** Flash write was inihibited, address was already written - XAP2B specific */
   EMBER_RESET_FLASH_WRITE_INHIBIT,                                                   // 0x0E
   /** Application bootloader reports bad upgrade image in EEPROM */
   EMBER_RESET_BOOTLOADER_IMG_BAD                                                     // 0x0F
}EmberResetType;


/*******************************************************************************
*                                                                              *
*                             Private  data                                    *
*                                                                              *
*******************************************************************************/
/** structure des variable privee du module */
static struct Sem260_status
{
  volatile Int16U timeout;
  volatile Int8U inter_spacing;
  volatile Int8U wait_msg;

  Int8U       ezsp_sequence;
  SEzspAnswer in_msg;            // input message
  
} em260_status;

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

// retourne le status de l'em260
static Boolean drvEm260Status( void );

// change temporairement la valeur d'inter spacing
static void drvEm260SetInterspacing( Int8U time );

static void drvEm260SetWaitMsg( Int16U timeout_value );
static void drvEm260ClearWaitMsg( void );

static Int8U drvEm260WaitAnswer( void );
static Int8U drvEm260WaitAnswerNoISR( void );

static Boolean drvEm260Reset( void );

static Int8U drvEm260Read( void );


// em260 nHostIn interrupt
static void drvEm260ISR(void);

// Interruption Timer
static void drvEm260TimerISR(void);

/*******************************************************************************
*                                                                              *
*                  Public Functions of the Module                              *
*                                                                              *
*******************************************************************************/

/**
* \brief fonction d'initialisation du driver de communication avec l'em260
*         les constantes liee au io sont definie dans le fichier app_product_hardware.h
*
* \return TRUE en cas de succes
*/
Boolean drvEm260Init( void )
{
  Boolean out_value = FALSE;

  // private variable
  em260_status.timeout = 0U;
  em260_status.inter_spacing = 0U;
  drvEm260ClearWaitMsg();

  em260_status.ezsp_sequence = 0U;

  // Configure IO
  // HOST_IN
  micIoConfigInput( EM260_IO_nHOST_INT, IO_PULL_UP ); // pull-up enable
  micExtIntDisable( EM260_IO_nHOST_INT );
  micExtIntConfigure( EM260_IO_nHOST_INT,
                      EXT_INT_TRIGGER_FALLING_EDGE,
						          drvEm260ISR
                    );
  // RSTB
  micIoSet( EM260_IO_nRESET, IO_LVL_VCC );
  micIoConfigOutput( EM260_IO_nRESET );
  // WAKE
  micIoSet( EM260_IO_nWAKE, IO_LVL_VCC );
  micIoConfigOutput( EM260_IO_nWAKE );
  // SSEL
  micIoSet( EM260_IO_nSSEL, IO_LVL_VCC );
  micIoConfigOutput( EM260_IO_nSSEL );
  // SPI
  micIoConfigInput( EM260_IO_MISO, IO_NO_PULL_UP );
  micIoConfigOutput( EM260_IO_MOSI );
  micIoConfigOutput( EM260_IO_SCK );

  // Start SPI as a Master in Mode 0 running at Fosc/2 sending MSB first
  // Turns on SPI peripheral
  micSpiTurnOn();
  micSpiConfigure(SPI_MASTER, SPI_MODE0, SPI_CLK_DIV_2, SPI_MSB_FIRST);
  
  // Configure l'interruption timer
  if( TRUE == drvTimerAdd( drvEm260TimerISR, 1U, TIMER_PERIODIC_CALL ) )
  {
    // enable host in interrupt
    micExtIntEnable( EM260_IO_nHOST_INT );

    // Reset Em260
    if( drvEm260Reset() == TRUE )
    {
      out_value = drvEm260Status();
    }
    else
    {
      drvTimerRemove( drvEm260TimerISR );
      out_value = FALSE;
    }
  }

  return out_value;
}

/** 
* \brief effectue un reset du chip
*
* \return TRUE en cas de reussite
*/
static Boolean drvEm260Reset( void )
{
  Boolean return_value = FALSE;
  Int8U read_byte;
  Int8U ValidReset = 1U;

  // 1. Assert nRESET and release to reset the EM260 and guarantee it is in a known state.
  // nWake must be high
  micIoSet( EM260_IO_nWAKE, IO_LVL_VCC );
  // assert nReset
  micIoSet( EM260_IO_nRESET, IO_LVL_GND );
  // wait between 8us and 200ms
  drvEm260SetWaitMsg( RESET_TIMEOUT_VALUE );  // at min 8us, for us the min is 250us, warning must be lower than 240ms
  drvEm260WaitAnswerNoISR();
  //drvEm260WaitAnswer();
  // release nReset
  micIoSet( EM260_IO_nRESET, IO_LVL_VCC );

  // set wait message
  drvEm260SetWaitMsg( RESET_TIMEOUT_WAIT_VALUE ); // typical time is 250ms, max time is 1500ms
  if( drvEm260WaitAnswerNoISR() /*drvEm260WaitAnswer()*/ == 1U )
  {
    // reset is perform with success
    // make a ezsp callback request

    // Assert nSSEL to begin a transaction.
    micIoSet( EM260_IO_nSSEL, IO_LVL_GND );
    // Transmit 0xFE : EZSP frame
    micSpiWriteData( EM260_SPI_BYTE_EZSP );
    while( !micSpiTransferIsCompleted() )
    {
    }
    // Transmit 0x03 : lenght of payload
    micSpiWriteData( 0x03U );
    while( !micSpiTransferIsCompleted() )
    {
    }
    // Transmit Ezsp sequence byte
    micSpiWriteData( em260_status.ezsp_sequence );
    em260_status.ezsp_sequence += 1U;
    while( !micSpiTransferIsCompleted() )
    {
    }
    // Transmit Control byte
    micSpiWriteData( EMBER_FRAME_CONTROL_IDLE );
    while( !micSpiTransferIsCompleted() )
    {
    }
    // Transmit 0x06 : callback command
    // CALLBACK, je crois que l'ember ne tiens pas compte de la commande quoi qu'il arrive
    micSpiWriteData( 0X06U );
    while( !micSpiTransferIsCompleted() )
    {
    }
    // Transmit end of frame
    drvEm260SetWaitMsg( STD_TIMEOUT_VALUE );
    micSpiWriteData( EM260_SPI_END_FRAME );
    while( !micSpiTransferIsCompleted() )
    {
    }

    // wait answer
    if( drvEm260WaitAnswerNoISR() /*drvEm260WaitAnswer()*/ == 1U )
    {
      // Continually transmit 0xFF until the byte received is not 0xFF. The first byte received that is not 0xFF will be 0x00.
      do{
        micSpiWriteData( 0xFFU );
        while( !micSpiTransferIsCompleted() )
        {
        }
        read_byte = micSpiReadData();
      }while( read_byte == 0xFFU );
      if( read_byte != 0x00U )
      {
        // error
        ValidReset = 0U;
      }
      // Transmit 0xFF while receiving reset cause : 0x02 = EMBER_RESET_POWERON
      micSpiWriteData( 0xFFU );
      while( !micSpiTransferIsCompleted() )
      {
      }
      read_byte = micSpiReadData();
      if( read_byte != EMBER_RESET_POWERON )
      {
        // error
        ValidReset = 0U;
      }

      // Transmit 0xFF while receiving 0xA7 (EM260_SPI_END_FRAME).
      micSpiWriteData( 0xFFU );
      while( !micSpiTransferIsCompleted() )
      {
      }
      read_byte = micSpiReadData();
      if( read_byte != EM260_SPI_END_FRAME )
      {
        // error
        ValidReset = 0U;
      }
      // De-assert nSSEL to finish the transaction.
      micIoSet( EM260_IO_nSSEL, IO_LVL_VCC );

      if( ValidReset )
      {
        drvEm260SetInterspacing( INTER_SPACING_VALUE_STD );
        em260_status.ezsp_sequence = 0U;

        return_value = TRUE;
      }
      else
      {
        return_value = FALSE;
      }
    }
    else
    {
      // em260 don't respond
      return_value = FALSE;
    }
  }
  else
  {
    // time out as occur, reset as failed
    return_value = FALSE;
  }

  return return_value;
}

/*******************************************************************************
*                                                                              *
*  Name: drvEm260ProtocolVersion                                          *
*                                                                              *
*  Subject:                                                      *
*                                                                              *
*                                                                              *
*  Input(s): none                                                              *
*                                                                              *
*  Output(s):                        *
*                                                                              *
*******************************************************************************/
Int8U drvEm260ProtocolVersion( void )
{
  Int8U r_value = 0U;

  while( em260_status.inter_spacing != 0U )
  {
  }

  // Assert nSSEL to begin a transaction.
  micIoSet( EM260_IO_nSSEL, IO_LVL_GND );
  // Transmit SPI Byte
  micSpiWriteData( EM260_SPI_BYTE_PROTOCOL_VERSION );
  while( !micSpiTransferIsCompleted() )
  {
  }
  // Transmit End Frame
  drvEm260SetWaitMsg( STD_TIMEOUT_VALUE );
  micSpiWriteData( EM260_SPI_END_FRAME );
  while( !micSpiTransferIsCompleted() )
  {
  }

  // wait answer
//  if( drvEm260WaitAnswer() == 1U )
  if( drvEm260Read() == 1U )
  {
//    drvEm260Read();

    // The response will always have bit 7 set and bit 6 cleared.
    // In this current version, the response will be 0x82,
    // since the version number corresponding to this set of Command-Response
    // values is version number 2.
    // The version number can be a value from 1 to 63 (0x81–0xBF).
    if( (em260_status.in_msg.msg[0U] & 0xC0U) == 0x80U )
    {
      r_value = em260_status.in_msg.msg[0U] & 0x3FU;
    }
  }

  return r_value;
}

/*******************************************************************************
*                                                                              *
*  Name:                                                    *
*                                                                              *
*  Subject:                                                    *
*                                                                              *
*                                                                              *
*  Input(s): none                                                              *
*                                                                              *
*  Output(s):                        *
*                                                                              *
*******************************************************************************/
static Boolean drvEm260Status( void )
{
  Boolean out_value = FALSE;

  while( em260_status.inter_spacing != 0U )
  {
  }

  // Assert nSSEL to begin a transaction.
  micIoSet( EM260_IO_nSSEL, IO_LVL_GND );
  // Transmit SPI Byte
  micSpiWriteData( EM260_SPI_BYTE_STATUS );
  while( !micSpiTransferIsCompleted() )
  {
  }
  // Transmit End Frame
  drvEm260SetWaitMsg( STD_TIMEOUT_VALUE );
  micSpiWriteData( EM260_SPI_END_FRAME );
  while( !micSpiTransferIsCompleted() )
  {
  }

  // wait answer
//  if( drvEm260WaitAnswer() == 1U )
  if( drvEm260Read() == 1U )
  {
//    drvEm260Read();

    // The response status byte will always have the upper 2 bits set.
    // In this current version, the status byte only has one status bit [0],
    // which is set if the EM260 is alive and ready for commands
    if( (em260_status.in_msg.msg[0U] & 0xC0U) == 0xC0U )
    {
      out_value = em260_status.in_msg.msg[0U] & 0x01U;
    }

    // effectue une attente
    drvEm260SetInterspacing( INTER_SPACING_VALUE_STD );
  }

  return out_value;
}

/*******************************************************************************
*                                                                              *
*  Name: drvEm260WakeUp                                                        *
*                                                                              *
*  Subject: use by file : drv_em260.c                                          *
*           just init EM260 I/O direction when the AVR wakes_up and want to    *
*           wake up the em260                                                  *
*                                                                              *
*  Input(s): none                                                              *
*                                                                              *
*  Output(s): none                                                             *
*                                                                              *
*******************************************************************************/
#ifdef SLEEPY_ZED_PRODUCT
Boolean drvEm260WakeUp( void )
{
  Int8U rvalue = TRUE;

  while( em260_status.inter_spacing != 0U )
  {
  }

  // check host_int line
  if( micIoRead(EM260_IO_nHOST_INT) == IO_LVL_GND )
  {
    rvalue = FALSE;
  }
  else
  {
    // assert on wake
    micIoSet( EM260_PORT_nWAKE, EM260_PORT_nWAKE, EM260_IO_nWAKE, IO_LVL_GND );

    // wait hostin become low
    // maximum time is 10 ms
    drvEm260SetWaitMsg( WAKEUP_TIMEOUT_VALUE );
    if( drvEm260WaitAnswerNoISR() /*drvEm260WaitAnswer()*/ == 1U )
    {
      // le timeout n'est pas echu
      // deasserts nWAKE
      micIoSet( EM260_PORT_nWAKE, EM260_IO_nWAKE, IO_LVL_VCC );

      // effectue une attente /*--*/ // pas forcement necessaire, mis par precaution
      drvEm260SetInterspacing( INTER_SPACING_VALUE_STD );
    }
    else
    {
      rvalue = FALSE;
    }
  }

  return rvalue;
}

#endif



/*******************************************************************************
*                                                                              *
*  Name: drvEm260DataTranfert                                                  *
*                                                                              *
*  Subject:  transmet trame ou commande ezsp a l'em260                         *
*                                                                              *
*                                                                              *
*  Input(s): trame ou commande ezsp a transmettre a l'em260                    *
*                                                                              *
*  Output(s): status renvoyer par l'em260, en retour de cette commande         *
*                                                                              *
*******************************************************************************/
Int8U *drvEm260DataTranfert( Int8U Id, Int8U phead[], Int8U head_len,
                             Int8U paf[], Int8U paf_len,
                             Int8U pmsg[], Int8U msg_len )
{
  Int8U *ptr = NUL;
  Int8U loop;
  Int8U retry = 0U;

  // SEB : stop l'interruption em260
//  drvEm260MaskHostIntInterrupt();


#ifdef SLEEPY_ZED_PRODUCT
  //if ( EMBER_FRAME_CONTROL_IDLE != EMBER_FRAME_CONTROL_IDLE )
  {
    drvEm260WakeUp();
  }
#endif

  do
  {
    while( em260_status.inter_spacing != 0U )
    {
    }

    // Assert nSSEL to begin a transaction.
    micIoSet( EM260_IO_nSSEL, IO_LVL_GND );

    // Transmit SPI Byte
    micSpiWriteData( EM260_SPI_BYTE_EZSP );
    while( !micSpiTransferIsCompleted() )
    {
    }

    // transmit lenght
    micSpiWriteData( head_len + paf_len + msg_len + 3U );
    while( !micSpiTransferIsCompleted() )
    {
    }

    // transmit ezsp sequence
    micSpiWriteData( em260_status.ezsp_sequence );
    em260_status.ezsp_sequence += 1U;
    while( !micSpiTransferIsCompleted() )
    {
    }

    // transmit ezsp frame type
    micSpiWriteData( EMBER_FRAME_CONTROL_IDLE );
    while( !micSpiTransferIsCompleted() )
    {
    }

    // transmit eszp id
    micSpiWriteData( Id );
    while( !micSpiTransferIsCompleted() )
    {
    }

    // send head
    for( loop=0U; loop<head_len; loop++ )
    {
      micSpiWriteData( phead[loop] );
      while( !micSpiTransferIsCompleted() )
      {
      }
    }

    // send paf
    for( loop=0U; loop<paf_len; loop++ )
    {
      micSpiWriteData( paf[loop] );
      while( !micSpiTransferIsCompleted() )
      {
      }
    }

    // send msg
    for( loop=0U; loop<msg_len; loop++ )
    {
      micSpiWriteData( pmsg[loop] );
      while( !micSpiTransferIsCompleted() )
      {
      }
    }

    // Transmit End Frame
    drvEm260SetWaitMsg( STD_TIMEOUT_VALUE );
    micSpiWriteData( EM260_SPI_END_FRAME );
    while( !micSpiTransferIsCompleted() )
    {
    }

    // wait answer
//    if( drvEm260WaitAnswer() == 1U )
    if( drvEm260Read() == 1U )
    {
	
//      drvEm260Read();

      if( em260_status.in_msg.frame_is_ezsp == 1U )
      {
        ptr = em260_status.in_msg.msg;
        retry = 3U;

        // SEB : on traite le bit callback pending dans le frame control byte
        if( (em260_status.in_msg.msg[1U]&0x04U) != 0U )
        {
          // on ajoute l'event callback a la pile
          SEvent send_event;

          send_event.type = E_EVENT_EM260;
          send_event.name = E_EM260_DRV_CALLBACK_EVENT;
          send_event.value = 0x00U;
          send_event.ext_value = 0x0000U;
          send_event.nb = 0x01U;
          ATOMIC( drvEventAdd( send_event ); )
        }
      }
      else
      {
        switch( em260_status.in_msg.msg[0U] )
        {
          case 0x00: // em260 reset
          case 0x01: // oversized EZSP frame
          case 0x04: // unsupported SPI command
          {
            // what to do ???
            SEvent send_event;

            // genere un event d'erreur
            send_event.type = E_EVENT_EM260;
            send_event.name = E_EM260_DRV_ERROR_EVENT;
            send_event.value = 0x00U;
            send_event.ext_value = 0x0000U;
            send_event.nb = 0x01U;
            ATOMIC( drvEventAdd( send_event ); ) // SEB : pour test

            ptr = NUL;
            retry = 3U;
          }
          break;

          case 0x02: // Aborted transaction
          case 0x03: // Missing frame terminator
          {
            retry += 1U ;
          }
          break;

          default:
          {
          }
          break;
        }
      }
    }
    else
    {
      // timeout occurs
      SEvent send_event;

      // genere un event d'erreur
      send_event.type = E_EVENT_EM260;
      send_event.name = E_EM260_DRV_ERROR_EVENT;
      send_event.value = 0x00U;
      send_event.ext_value = 0x0000U;
      send_event.nb = 0x01U;
      ATOMIC( drvEventAdd( send_event ); ) // SEB : pour test

      // initialise les variables de sortie
      ptr = NUL;
      retry = 3U;

      // Deassert nSSEL to finish the transaction.
      micIoSet( EM260_IO_nSSEL, IO_LVL_VCC );
      drvEm260SetInterspacing( INTER_SPACING_VALUE_STD );

    }

    // SEB : enleve le flag qui deviens obsolete
    drvEm260ClearWaitMsg();

  }while(retry < 3U);

  // SEB : remise en route des interruptions em260
//  drvEm260UnmaskHostIntInterrupt();

  return ptr;
}

/*******************************************************************************
*                                                                              *
*  Name: drvEm260GetCallback                                                   *
*                                                                              *
*  Subject:  retourne la callback en attente                                   *
*                                                                              *
*                                                                              *
*  Input(s): None                                                              *
*                                                                              *
*  Output(s): NULL si pas de message en attente                                *
*                                                                              *
*******************************************************************************/
Int8U *drvEm260GetCallback( void )
{
  Int8U *prep = NUL;

  prep = drvEm260DataTranfert( 0x06U, NUL, 0U, NUL, 0U, NUL, 0U );

  return prep;
}

/*******************************************************************************
*                                                                              *
*                  Private Functions of the Module                             *
*                                                                              *
*******************************************************************************/

/*******************************************************************************
*                                                                              *
*  Name: drvEm260SetInterspacing                                               *
*                                                                              *
*  Subject: introduit un delay entre deux commandes                            *
*                                                                              *
*                                                                              *
*  Input(s): valeur en l'interspacing en pas timer                             *
*                                                                              *
*  Output(s): None                                                             *
*                                                                              *
*******************************************************************************/
static void drvEm260SetInterspacing( Int8U time )
{
  if( em260_status.inter_spacing < time )
  {
    em260_status.inter_spacing = time;
  }
}

/*******************************************************************************
*                                                                              *
*  Name: drvEm260SetWaitMsg                                                    *
*                                                                              *
*  Subject: leve le flag d'attente d'un interruption HOST_INT                  *
*                                                                              *
*                                                                              *
*  Input(s): timeout_value : temps maximum d'attente avant abandon             *
*                                                                              *
*  Output(s): None                                                             *
*                                                                              *
*******************************************************************************/
static void drvEm260SetWaitMsg( Int16U timeout_value )
{
  ATOMIC(
    em260_status.wait_msg = 1U;
    em260_status.timeout = timeout_value;
  )
}

/*******************************************************************************
*                                                                              *
*  Name: drvEm260ClearWaitMsg                                                  *
*                                                                              *
*  Subject: baisse le flag d'attente d'un interruption HOST_INT                *
*                                                                              *
*                                                                              *
*  Input(s): None                                                              *
*                                                                              *
*  Output(s): None                                                             *
*                                                                              *
*******************************************************************************/
static void drvEm260ClearWaitMsg( void )
{
  //ATOMIC(
    em260_status.wait_msg = 0U;
    // ne surtout pas remettre a 0 le timeout, sinon on ne connait pas
    // la cause de la sortie
 // )
}

/*******************************************************************************
*                                                                              *
*  Name: drvEm260WaitAnswer                                                    *
*                                                                              *
*  Subject: attend que le flag d'attente d'interruption soit baissé ou         *
*           que le timeout arrive                                              *
*                                                                              *
*  Input(s): None                                                              *
*                                                                              *
*  Output(s): returne 1 si l'interruption est arrivée, 2 si c'est le timeout   *
*                                                                              *
*******************************************************************************/
static Int8U drvEm260WaitAnswer( void )
{
  Int8U return_value;
  volatile Int16U l_timeout;
  volatile Int16S test_condition;

  l_timeout = em260_status.timeout;
  test_condition = (Int16S)(em260_status.wait_msg == 1U);
  test_condition = (Int16S)(l_timeout != 0U) && test_condition;
  while( test_condition )
  {
    micResetWatchdog();
    l_timeout = em260_status.timeout;
    test_condition = (Int16S)(em260_status.wait_msg == 1U);
    test_condition = (Int16S)(l_timeout != 0U) && test_condition;
  }

  if( l_timeout != 0U )
  {
    return_value = 1U;
  }
  else
  {
    return_value = 2U;
  }

  return return_value;
}

/*******************************************************************************
*                                                                              *
*  Name: drvEm260WaitAnswer                                                    *
*                                                                              *
*  Subject: attend que le flag d'attente d'interruption soit baissé ou         *
*           que le timeout arrive                                              *
*                                                                              *
*  Input(s): None                                                              *
*                                                                              *
*  Output(s): returne 1 si l'interruption est arrivée, 2 si c'est le timeout   *
*                                                                              *
*******************************************************************************/

static Int8U drvEm260WaitAnswerNoISR( void )
{
	Int8U lo_ret = 1U;
	volatile Int8U l_host_in_state;
	volatile Int16U l_timeout;
	
	l_timeout = em260_status.timeout;
	do
	{
		micResetWatchdog();
		l_timeout = em260_status.timeout;
		l_host_in_state = micIoGet( EM260_IO_nHOST_INT ); // (HOST_IN_PIN>>HOST_IN_BIT)&0x1;
	} while ( (0U != em260_status.timeout) && (1==l_host_in_state) );
	

  if( l_timeout != 0U )
  {
	  lo_ret = 1U;
  }
  else
  {
	  lo_ret = 2U;
  }

	return lo_ret;
}

/*******************************************************************************
*                                                                              *
*  Name: drvEm260Read                                                          *
*                                                                              *
*  Subject: read function                                                      *
*                                                                              *
*                                                                              *
*  Input(s): none                                                              *
*                                                                              *
*  Output(s): none                                                             *
*                                                                              *
*******************************************************************************/
static Int8U drvEm260Read( void )
{
  Int8U read_byte;
  Int8U error_code = 1U;
  volatile Int16U l_timeout;
  volatile Int16S test_condition;

  em260_status.in_msg.len = 0U;

  // Continually transmit 0xFF until the byte received is not 0xFF.
  do
  {
    micSpiWriteData( 0xFFU );
    while( !micSpiTransferIsCompleted() )
    {
    }
    read_byte = micSpiReadData();

    l_timeout = em260_status.timeout;
    test_condition = (Int16S)(read_byte == 0xFFU);
    test_condition = (Int16S)(l_timeout != 0U) && test_condition;
  }while( test_condition );
//  }while( read_byte == 0xFFU );


  if( read_byte == 0xFFU )
  {
    // on sort en timeout
    error_code = 2U;
  }
  else
  {
    // depend of SPI Byte
    if( read_byte == EM260_SPI_BYTE_EZSP )
    {
      Int8U spi_lenght;

      em260_status.in_msg.frame_is_ezsp = 1U;

      micSpiWriteData( 0xFFU );
      while( !micSpiTransferIsCompleted() )
      {
      }
      spi_lenght = micSpiReadData();

      while( spi_lenght )
      {
        spi_lenght -= 1U;
        micSpiWriteData( 0xFFU );
        while( !micSpiTransferIsCompleted() )
        {
        }
        read_byte = micSpiReadData();
        em260_status.in_msg.msg[ em260_status.in_msg.len ] = read_byte;
        em260_status.in_msg.len += 1U;
      }
    }
    else
    {
      em260_status.in_msg.frame_is_ezsp = 0U;
      em260_status.in_msg.msg[ em260_status.in_msg.len ] = read_byte;
      em260_status.in_msg.len += 1U;
    }

    // Continually transmit 0xFF until the byte received is not EM260_SPI_END_FRAME.
    while( read_byte != EM260_SPI_END_FRAME )
    {
      micSpiWriteData( 0xFFU );
      while( !micSpiTransferIsCompleted() )
      {
      }
      read_byte = micSpiReadData();
      em260_status.in_msg.msg[ em260_status.in_msg.len ] = read_byte;
      em260_status.in_msg.len += 1U;
    }
    // remove end of frame byte
    em260_status.in_msg.len--;

    // Deassert nSSEL to finish the transaction.
    micIoSet( EM260_IO_nSSEL, IO_LVL_VCC );
    drvEm260SetInterspacing( INTER_SPACING_VALUE_STD );
  }

  return error_code;
}

/*******************************************************************************
*                                                                              *
*                  ISR Function of the Module                                  *
*                                                                              *
*******************************************************************************/

//------------------------------------------------------------------------------
// em260 nHostIn interrupt
static void drvEm260ISR(void)
{
  if( em260_status.wait_msg != 0U )
  {
    drvEm260ClearWaitMsg();
  }
  else
  {
    SEvent send_event;
  
    send_event.type = E_EVENT_EM260;
    send_event.name = E_EM260_DRV_CALLBACK_EVENT;
    send_event.value = 0x00U;
    send_event.ext_value = 0x0000U;
    send_event.nb = 0x01U;
    drvEventAdd( send_event );
  }
}

//------------------------------------------------------------------------------
// Interruption Timer
static void drvEm260TimerISR(void)
{
  if( em260_status.inter_spacing != 0U )
  {
    em260_status.inter_spacing -= 1U;
  }

  if( em260_status.timeout != 0U )
  {
    em260_status.timeout -= 1U;
  }
}
