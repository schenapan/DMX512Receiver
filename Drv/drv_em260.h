#ifndef drv_em260_H
#define drv_em260_H
/*******************************************************************************
*                                                                              *
*                         File to be included                                  *
*                                                                              *
*******************************************************************************/

// Include application

/******************************************************************************
*                                                                             *
*                         constantes declaration                              *
*                                                                             *
******************************************************************************/
// The EM260 enters the sleep mode specified by the command frame control once
// it has sent its response.
#define EMBER_FRAME_CONTROL_SLEEP_MODE_MASK                 0x03
typedef enum
{
  EMBER_FRAME_CONTROL_IDLE = 0U,        // Processor idle.
  EMBER_FRAME_CONTROL_DEEP_SLEEP = 1U,  // Wake on interrupt or timer.
  EMBER_FRAME_CONTROL_POWER_DOWN = 2U   // Wake on interrupt only.
// Sleep mode 0x03 is reserved.
}EEm260PowerMode;



typedef enum
{
  E_EM260_IO_nHOST_INT,
  E_EM260_IO_nRESET,
  E_EM260_IO_nWAKE,
  E_EM260_IO_nSSEL,
  E_EM260_IO_MISO,
  E_EM260_IO_MOSI,
  E_EM260_IO_SCK,
  //--------------- Always at end ----------------------------------------------
  E_EM260_NB_IO
} Em260IoName;

typedef enum
{
  E_EM260_DRV_CALLBACK_EVENT,    // generer par le driver lors de l'arrivée
                                 // d'une callback
  E_EM260_DRV_ERROR_EVENT,       // generer par le driver lors d'une erreur de
                                 // communication (un reset est fortement suggerer)

  //----------------------------------------------------------------------------
  E_EM260_NB_EVENT
} EZigBeeEvent;

#define EM260_MAX_IN_BUFFER       130U

/*******************************************************************************
*                                                                              *
*                             Public  data types                               *
*                                                                              *
*******************************************************************************/

typedef struct
{
  Int8U frame_is_ezsp;
  Int8U len;
  Int8U msg[EM260_MAX_IN_BUFFER];
} SEzspAnswer;

/*******************************************************************************
*                                                                              *
*                         Public Macros of the module                          *
*                                                                              *
*******************************************************************************/


/*******************************************************************************
*                                                                              *
*                  	     Public Functions of the Module                        *
*                                                                              *
*******************************************************************************/

/**
* \brief fonction d'initialisation du driver de communication avec l'em260
*         les constantes liee au io sont definie dans le fichier app_product_hardware.h
*
* \return TRUE en cas de succes
*/
Boolean drvEm260Init( void );

// change la valeur de l'interspacing dans le cas du manufacturing test
void drvEm260SetInterspacingMFT( void );

#ifdef SLEEPY_ZED_PRODUCT
// demande de reveil de l'em260
Boolean drvEm260WakeUp( void );

// change le mode de fonctionement de l'em260 : idle,
void drvEm260SetPowerMode( EEm260PowerMode power_mode );

// retourne l'etat courant de l'EM260: IDLE, DEEP SLEEP, POWER DOWN
EEm260PowerMode drvEm260GetPowerMode( void );
#endif

// retourne la version du protocole EZSP utilise
Int8U drvEm260ProtocolVersion( void );

// effectue un tranfsert de type EZSP avec l'em260
Int8U *drvEm260DataTranfert( Int8U Id, Int8U phead[], Int8U head_len,
                                 Int8U paf[], Int8U paf_len,
                                 Int8U pmsg[], Int8U msg_len );

// retourne la callback en attente
Int8U *drvEm260GetCallback( void );


/******************************************************************************/
#endif /* drv_em260_H */

