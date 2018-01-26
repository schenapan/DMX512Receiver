#ifndef _MIC_IO_H_
#define _MIC_IO_H_

/******************************************************************************/
/*                                                                            */
/* => IO management                                                           */
/*                                                                            */
/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*                                                                            */
/*  Constant and type                                                         */
/*                                                                            */
/******************************************************************************/

/** \brief define possible io port */
#define IO_PORT_A 0U
#define IO_PORT_B 1U
#define IO_PORT_C 2U
#define IO_PORT_D 3U
typedef Int8U IoPort;

/** \brief une pin precise sur un port est donnee de facon numerique a partir de 0 */
typedef Int8U IoPin;

/** \brief define direction of the PIN */
#define IO_DIR_INPUT  0U
#define IO_DIR_OUTPUT 1U
typedef Boolean IoDir;

/** \brief Define physical level of an io */
#define IO_LVL_GND              0U
#define IO_LVL_VCC              1U
typedef Boolean IoLevel;

/** \brief define pull up state */
#define IO_NO_PULL_UP	0U
#define IO_PULL_UP		1U
typedef Int8U IoPullUp;

/** \brief definit une io unique port + pin */
typedef struct  
{
  IoPort port;
  IoPin  pin;
}SIo;
#define IO_A_0 ((SIo){IO_PORT_A,0})
#define IO_A_1 {IO_PORT_A,1}
#define IO_A_2 {IO_PORT_A,2}
#define IO_A_3 {IO_PORT_A,3}
#define IO_A_4 {IO_PORT_A,4}
#define IO_A_5 {IO_PORT_A,5}
#define IO_A_6 {IO_PORT_A,6}
#define IO_A_7 {IO_PORT_A,7}
#define IO_B_0 {IO_PORT_B,0}
#define IO_B_1 {IO_PORT_B,1}
#define IO_B_2 {IO_PORT_B,2}
#define IO_B_3 {IO_PORT_B,3}
#define IO_B_4 {IO_PORT_B,4}
#define IO_B_5 {IO_PORT_B,5}
#define IO_B_6 {IO_PORT_B,6}
#define IO_B_7 {IO_PORT_B,7}
#define IO_C_0 {IO_PORT_C,0}
#define IO_C_1 {IO_PORT_C,1}
#define IO_C_2 {IO_PORT_C,2}
#define IO_C_3 {IO_PORT_C,3}
#define IO_C_4 {IO_PORT_C,4}
#define IO_C_5 {IO_PORT_C,5}
#define IO_C_6 {IO_PORT_C,6}
#define IO_C_7 {IO_PORT_C,7}
#define IO_D_0 {IO_PORT_D,0}
#define IO_D_1 {IO_PORT_D,1}
#define IO_D_2 {IO_PORT_D,2}
#define IO_D_3 {IO_PORT_D,3}
#define IO_D_4 {IO_PORT_D,4}
#define IO_D_5 {IO_PORT_D,5}
#define IO_D_6 {IO_PORT_D,6}
#define IO_D_7 {IO_PORT_D,7}

#define INVALID_IO ((SIo){0xFF,0xFF})

#define IO_EQUAL(IO_1, IO_2) ((IO_1.port==IO_2.port)&&(IO_1.pin==IO_2.pin))

/******************************************************************************/
/*  Public function                                                           */
/******************************************************************************/

/**
* \brief fonction d'initialisation du module
*/
void micIoInit( void );

/**
* \brief configure une io en sortie
*
* \param[IN] i_io : io complete
*/
void micIoConfigOutput( SIo i_io );

/**
* \brief configure une io en entree
*
* \param[IN] i_io : io complete
* \param[IN] i_pull_up_mode : activation de la pull-up interne
*/
void micIoConfigInput( SIo i_io, IoPullUp i_pull_up_mode );

/**
* \brief affecte un etat a une io
*
* \param[IN] i_io : io complete
* \param[IN] i_level : niveau de sortie souhaite
*/
void micIoSet( SIo i_io, IoLevel i_level );

/**
* \brief Toggle l'etat d'une io
*
* \param[IN] i_io : io complete
*/
void micIoToggle( SIo i_io );

/**
* \brief lit la valeur d'un io
*
* \param[IN] i_io : io complete
*
* \return level of the io, (IO_LVL_GND by default )
*/
IoLevel micIoGet( SIo i_io );

/**
* \brief ecrit sur un port
*
* \param[IN] i_port : port concerne
* \param[IN i_value : valeur a ecrire
*/
void micIoWrite( IoPort i_port, Int8U i_value );

/**
* \brief lit sur un port
*
* \param[IN] i_port : port concerne
*
* \return valeur lue sur le port
*/
Int8U micioRead( IoPort i_port );


/**
* \brief Inclusion des fichier .h specifique a chaque micro
*/
#if defined(AVR_ATMEGA_324)
  #include "mic_io_avr.h"
#endif


/******************************************************************************/
#endif  // _MIC_IO_H_
