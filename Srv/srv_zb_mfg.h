#ifndef _SRV_ZB_MFG_H_
#define _SRV_ZB_MFG_H_

/**
* \file srv_zb_mfg
* \brief module d'abstraction pour les commande lie a la mfg library ember
* \author SM
* \version 0.1
* \date 23 fevrier 2011
*
* ce module a pour but de fournir une API d'acces a la librairie manufacturing 
* d'ember quel que soit le chip utilisé (em260 / em357 : inclure le bon .c)
*
*/

/*******************************************************************************
*                                                                              *
*                         File to be included                                  *
*                                                                              *
*******************************************************************************/
// Include micro abstraction layer
#include "Mic/mic_micro.h"

// include event management */
#include "Drv/drv_event.h"


#ifndef CORTEXM3


/**
 * @name txPowerModes for emberSetTxPowerMode and mfglibSetPower 
 */
//@{

/** @brief The application should call ::emberSetTxPowerMode() with the
  * txPowerMode parameter set to this value to disable all power mode options,
  * resulting in normal power mode and bi-directional RF transmitter output.
  */
#define EMBER_TX_POWER_MODE_DEFAULT             0x0000
/** @brief The application should call ::emberSetTxPowerMode() with the
  * txPowerMode parameter set to this value to enable boost power mode.
  */
#define EMBER_TX_POWER_MODE_BOOST               0x0001
/** @brief The application should call ::emberSetTxPowerMode() with the
  * txPowerMode parameter set to this value to enable the alternate transmitter
  * output.
  */
#define EMBER_TX_POWER_MODE_ALTERNATE           0x0002
/** @brief The application should call ::emberSetTxPowerMode() with the
  * txPowerMode parameter set to this value to enable both boost mode and the
  * alternate transmitter output.
  */
#define EMBER_TX_POWER_MODE_BOOST_AND_ALTERNATE (EMBER_TX_POWER_MODE_BOOST     \
                                                |EMBER_TX_POWER_MODE_ALTERNATE)

#define EMBER_BAD_ARGUMENT EMBER_INVALID_CALL
#endif

/*******************************************************************************
*                                                                              *
*                         Constants declaration                                *
*                                                                              *
*******************************************************************************/

/// liste des tokens de la mfg library
/// Custom version (2 bytes).
#define ID_TOKEN_MFG_CUSTOM_VERSION    0x00U 
/// Manufacturing string (16 bytes).
#define ID_TOKEN_MFG_STRING            0x01U 
/// Board name (16 bytes).
#define ID_TOKEN_MFG_BOARD_NAME        0x02U 
/// Manufacturing ID (2 bytes).
#define ID_TOKEN_MFG_MANUF_ID          0x03U 
/// Radio configuration (2 bytes).
#define ID_TOKEN_MFG_PHY_CONFIG        0x04U 
/// Bootload AES key (16 bytes).
#define ID_TOKEN_MFG_BOOTLOAD_AES_KEY  0x05U 
/// ASH configuration (40 bytes).
#define ID_TOKEN_MFG_ASH_CONFIG        0x06U 
/// EZSP storage (8 bytes).
#define ID_TOKEN_MFG_EZSP_STORAGE      0x07U 
/// Radio calibration data (64 bytes). 4 bytes per channel
#define ID_TOKEN_STACK_CAL_DATA        0x08U 
/// Certificate Based Key Exchange (CBKE) data (92 bytes).
#define ID_TOKEN_MFG_CBKE_DATA         0x09U 
/// Installation code (20 bytes).
#define ID_TOKEN_MFG_INSTALLATION_CODE 0x0AU 
/// EUI64 actuellement utilise (8 bytes).
#define ID_TOKEN_MFG_EUI_64            0x0BU
/// definition d'un type
typedef Int8U TokenMfgId;

typedef enum
{
  EMBER_SUCCESS = 0x00U,

  // The generic "fatal error" message.
  EMBER_ERR_FATAL = 0x01U,

  // There are no more buffers.
  EMBER_NO_BUFFERS = 0x18U,

  // the poll is success but there is no pending data exists for device doing
  // a data poll.
  EMBER_MAC_NO_DATA = 0x31U,

  // emberStartScan was called with an invalid channel mask.
  EMBER_MAC_INVALID_CHANNEL_MASK  = 0x35U,

  // The MAC can't complete this task because it is scanning
  EMBER_MAC_SCANNING = 0x3DU,

  // Poll_complete_handler status, when the parent of a zed doesn't answer
  EMBER_MAC_NO_ACK_RECEIVED = 0x40U,

  // he APS layer attempted to send or deliver a message, but it failed
  EMBER_DELIVERY_FAILED = 0x66U,
  // The API call is not allowed given the current state of the stack
  EMBER_INVALID_CALL = 0x70U,

  EMBER_ADDRESS_TABLE_ENTRY_IS_ACTIVE = 0x76U,

  // The stack software has completed initialization and is ready
  // to send and receive packets over the air
  EMBER_NETWORK_UP = 0x90U,
  // The network is not operating
  EMBER_NETWORK_DOWN = 0x91U,
  // The node has not joined a network.
  EMBER_NOT_JOINED = 0x93U,
  // An attempt to join a network failed
  EMBER_JOIN_FAILED = 0x94U,
  // After moving, a mobile node's attempt to re-establish contact with the
  // network failed
  EMBER_MOVE_FAILED = 0x96U,
  // A message cannot be sent because the network is currently overloaded
  EMBER_NETWORK_BUSY = 0xA1U,


  // An attempt to join or rejoin the network failed because
  // no router beacons could be heard by the joining node.
  EMBER_NO_BEACONS = 0xABU,
  // An attempt was made to join a Secured Network using a pre-configured
  // key, but the Trust Center sent back a Network Key in-the-clear when
  // an encrypted Network Key was required. (::EMBER_REQUIRE_ENCRYPTED_KEY).
  EMBER_RECEIVED_KEY_IN_THE_CLEAR =  0xACU,
  // An attempt was made to join a Secured Network, but the device did
  // not receive a Network Key.
  EMBER_NO_NETWORK_KEY_RECEIVED = 0xADU

}EEmberStatus;
#define EmberStatus EEmberStatus

/** definition de la taille d'une addr ieee en octet */
#define SIZE_OF_MISC_IEEE 8U

/** definit la taille maximale d'un message zigbee */
#define ZB_MAX_MSG_SIZE       130U

/*******************************************************************************
*                                                                              *
*                             Public data types                                *
*                                                                              *
*******************************************************************************/

/*******************************************************************************
*                                                                              *
*                             Public data types                                *
*                                                                              *
*******************************************************************************/

/*******************************************************************************
*                                                                              *
*                        Public data types for the module                      *
*                                                                              *
*******************************************************************************/


/*******************************************************************************
*                                                                              *
*                         Public Macros of the module                          *
*                                                                              *
*******************************************************************************/


/*******************************************************************************
*                                                                              *
*                       Public Functions of the Module                         *
*                                                                              *
*******************************************************************************/

/**
* \brief fonction d'initialisation
*
* \return FALSE si le traitement a genere une erreur
*/
Boolean srvZbMfgInit( void );

/**
*
* \brief fonction de traitement des events genere par d'autre module (driver, dervice, ...)
*
* \param[in] i_event : event a prendre en compte ... ou pas
*
* \return i_event, si on ne souhaite pas que l'event continue son chemin mettre
*         le champ type a E_EVENT_NONE
*/
SEvent srvZbMfgDispatcher( SEvent i_event );

void srvZbMfgCheckMessage( void );

/**
*
* \brief demarre la mfglib
*
* \param[in] i_rx_callback : poiteur vers la fonction de reception,
*                            NUL si non utilisée
*
* \return EMBER_SUCCESS si aucune erreur
*/
EmberStatus srvZbMfgStart( void (*i_rx_callback)( Int8U *packet, 
                                                         Int8U linkQuality, 
                                                         Int8S rssi) );

/**
*
* \brief arrete la mfglib
*
* \param[in] None
*
* \return EMBER_SUCCESS si aucune erreur
*/
EmberStatus srvZbMfgStop( void );

/**
*
* \brief transmit an unmodulated tone on the currently set channel and power level
*
* \param[in] None
*
* \return EMBER_SUCCESS si aucune erreur
*/
EmberStatus srvZbMfgStartTone( void );

/**
*
* \brief Stops transmitting a tone
*
* \param[in] None
*
* \return EMBER_SUCCESS si aucune erreur
*/
EmberStatus srvZbMfgStopTone( void );

/**
*
* \brief Starts transmitting a random stream of characters
*
* \param[in] None
*
* \return EMBER_SUCCESS si aucune erreur
*/
EmberStatus srvZbMfgStartStream( void );

/**
*
* \brief Stops transmitting a random stream of characters
*
* \param[in] None
*
* \return EMBER_SUCCESS si aucune erreur
*/
EmberStatus srvZbMfgStopStream( void );

/**
*
* \brief Sends a single packet
*
* \param[in] i_packet_size : taille du packet en octets
* \param[in] i_packet : donnée a envoyer sans l'octet de taille. 
*                       La taille doit etre comprise entre 3 et 123 bytes
* \param[in] i_repeat : nombre de repetition a effectuer, 
*                       0 correspond a un envoi simple
*
* \return EMBER_SUCCESS si aucune erreur
*/
EmberStatus srvZbMfgSendPacket( Int8U i_packet_size, Int8U *i_packet, 
                                Int16U i_repeat );

/**
*
* \brief Selects the radio channel
*
* \param[in] i_channel : numero du canal a utiliser entre 11 et 26
*
* \return EMBER_SUCCESS si aucune erreur
*/
EmberStatus srvZbMfgSetChannel( Int8U i_channel );

/**
*
* \brief Returns the current radio channel
*
* \param[in] None
*
* \return numero du canal radio entre 11 et 26
*/
Int8U srvZbMfgGetChannel( void );

/**
*
* \brief adjust the transmit power
*
* \param[in] i_power_mode : mode a utiliser : 
*                           EMBER_TX_POWER_MODE_DEFAULT
*                           EMBER_TX_POWER_MODE_BOOST
*                           EMBER_TX_POWER_MODE_ALTERNATE
*                           EMBER_TX_POWER_MODE_BOOST_AND_ALTERNATE
* \param[in] i_power_dbm : discrete valeur definie dans la datasheet du composant
*
* \return EMBER_SUCCESS si aucune erreur
*/
EmberStatus srvZbMfgSetPower( Int16U i_power_mode, Int8S i_power_dbm );

/**
*
* \brief returns the current radio power
*
* \return puissance actuellement utilisee
*/
Int8S srvZbMfgGetPower( void );


/**
*
* \brief lit un token de type mfg 
*
* \param[in] i_mfg_token_id : token id :
* \param[in] i_data : buffer dans lequel sera copiee les valeurs 
* \param[in|out] io_data_size : en entree la taille de i_data, 
*                               en sortie la taille du token lu en octet
*
* \return EMBER_SUCCESS si aucune erreur
*/
EmberStatus srvZbMfgGetToken( TokenMfgId i_mfg_token_id, Int8U *i_data, 
                                                  Int8U *io_data_size );

/**
* \brief ZigBee Networking frame lit l'adresse IEEE du noeud
*
* \return pointeur sur l'ieee, NUL en cas d'erreur
*/
Int8U *srvZbMfgGetEUI64( void );

/**
* \brief test si l'ieee entrante correspond a notre noeud 
* 
* \param[IN] ip_ieee : ieee a tester
*
* \return TRUE si l'ieee correspond
*/
Boolean srvZbMfgCheckIeee( Int8U *ip_ieee );

/******************************************************************************/
/******************************************************************************/
#endif /* _SRV_ZB_MFG_H_ */
