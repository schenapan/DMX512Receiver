#ifndef _MIC_UART_H_
#define _MIC_UART_H_
/******************************************************************************/
/*                                                                            */
/* => UART 1 management                                                       */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "mic_usart1.h"

/******************************************************************************/
/*                                                                            */
/* => UARTS management                                                        */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*
 * => Types:
 */

// enumeration des uarts hardware present
// dans le cas de l'em357 seul le controller serie 1 (SC1) peut être configurer
// en mode uart
enum
{
  E_UART_1,

  //-----------------------------------------------
  E_NB_UART_ID
};
// definition d'un type pour l'identifier uart
typedef Int8U UartId;

// enumeration des baud rate possible
#define E_UART_300_BAUDS      0U
#define E_UART_2400_BAUDS     1U
#define E_UART_4800_BAUDS     2U
#define E_UART_9600_BAUDS     3U
#define E_UART_19200_BAUDS    4U
#define E_UART_38400_BAUDS    5U
#define E_UART_57600_BAUDS    6U
#define E_UART_115200_BAUDS   7U
#define E_UART_230400_BAUDS   8U
#define E_UART_460800_BAUDS   9U
#define E_UART_921600_BAUDS   10U
//-----------------------------------------------
#define E_NB_UART_BAUDS       11U
// definition d'un type
typedef Int8U UartBaudRate;


// enumeration du nombre de data bits
// dans le registre
#define E_UART_DATA_7_BITS    0U
#define E_UART_DATA_8_BITS    1U
//-----------------------------------------------
#define E_NB_UART_DATA_BITS   2U
// definition d'un type
typedef Int8U UartDataBits;

// enumeration du type de parite
// dans le registre
#define E_UART_NO_PARITY      0U
#define E_UART_EVEN_PARITY    1U
#define E_UART_ODD_PARITY     2U
//-----------------------------------------------
#define E_NB_UART_PARITY      3U
// definition d'un type
typedef Int8U UartParityMode;

// enumeration du nombre de stop bits
// dans le registre
#define E_UART_STOP_1_BITS    0U
#define E_UART_STOP_2_BITS    1U
//-----------------------------------------------
#define E_NB_UART_STOP_BITS   2U
// definition d'un type
typedef Int8U UartStopBits;


// definit un type de pointeur de fonction pour les interruption micro
typedef void (*p_isr_uart_callback)( UartId i_mic_uart_id );

//------------------------------------------------------------------------------
/*
 * => Functions:
 */


/**
*
* \brief desactive un controleur UART
*
* \param[in] i_uart_id : controleur concerne
*
* \return FALSE si le traitement a genere une erreur
*/
Boolean MicUartDisable( UartId i_uart_id );

/**
*
* \brief fonction de configuration d'un controleur UART sans control de flux
*
* \param[in] i_uart_id : controleur concerne
* \param[in] i_baud_rate : baud rate souhaite
* \param[in] i_data_bits : nombre de bit data
* \param[in] i_parity_mode : parite utilisee
* \param[in] i_stop_bits : nombre de bit de stop
*
* \return FALSE si le traitement a genere une erreur
*/
Boolean MicUartConfigure( UartId i_uart_id, UartBaudRate i_baud_rate, 
                                            UartDataBits i_data_bits,
                                            UartParityMode i_parity_mode,
                                            UartStopBits i_stop_bits );

/**
*
* \brief configure une interruption sur la reception
*
* \param[in] i_uart_id : controleur concerne
* \param[in] i_p_callback : pointeur vers la fonction d'interruption, 
*                           NUL pour desactive l'interruption
*
* \return FALSE si le traitement a genere une erreur
*/
Boolean MicUartSetRxISR( UartId i_uart_id, p_isr_uart_callback i_p_callback );

/**
*
* \brief active un controleur UART
*
* \param[in] i_uart_id : controleur concerne
*
* \return FALSE si le traitement a genere une erreur
*/
Boolean MicUartEnable( UartId i_uart_id );

/**
*
* \brief ecrit un octet dans la fifo d'envoi
*
* \param[in] i_uart_id : controleur concerne
* \param[in] i_data : octet a ecrire
*
* \return FALSE si la fifo est pleine
*/
Boolean MicUartWriteByte( UartId i_uart_id, Int8U i_data );

/**
*
* \brief lit un octet dans la fifo de reception
*
* \param[in] i_uart_id : controleur concerne
* \param[out] o_data : variable contenant la valeur lue
*
* \return FALSE si il n'y a pas d'octet a lire
*/
Boolean MicUartReadByte( UartId i_uart_id, Int8U *o_data );


//------------------------------------------------------------------------------
// ISR
//------------------------------------------------------------------------------

/**
*
* \brief callback d'interrutpion du controleur serie si il est en mode UART
*
* \param[in] i_uart_id : controleur concerne
*
*/
void micUartIsr( UartId i_uart_id );

/******************************************************************************/
#endif  // _MIC_UART_H_
