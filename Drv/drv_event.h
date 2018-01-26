#ifndef _DRV_EVENT_H_
#define _DRV_EVENT_H_
/*******************************************************************************
*                                                                              *
*                         File to be included                                  *
*                                                                              *
*******************************************************************************/

/*******************************************************************************
*                                                                              *
*                          constantes declaration                              *
*                                                                              *
*******************************************************************************/

/// liste des evenements pouvant être present dans le produit, on assume le 
/// fait qu'il y aura moins de 255 type d'event different
enum
{
  E_EVENT_GENERAL,      // evenement generique manage par le kernel
  E_EVENT_BUTTON,       // evenement de type bouton
  E_EVENT_UART_FAMILY,  // evenement generer par le drivers uart family
  E_EVENT_EM260,        // evenement du driver em260      

  //--------------- Always at end ----------------------------------------------
  E_EVENT_NB_TYPE,      // must be < 0xFF
  E_EVENT_NONE,         // absence d'evenement
};
typedef Int8U EEventType;

// evenement de type general
enum
{
  // definit un tick a 100 milliseconde
  E_GENERAL_TICK_100MS_EVENT,
  // definit un tick a 1 seconde
  E_GENERAL_TICK_1S_EVENT,

  //----------------------------------------------------------------------------
  E_GENERAL_NB_EVENT
};
typedef Int8U EGeneralEvent;


/*******************************************************************************
*                                                                              *
*                             Public  data types                               *
*                                                                              *
*******************************************************************************/

/**
* \struct SEvent
* \brief structure d'un evenement
*
* permet de definir les differents attribut d'un evenement kernel
*/
typedef struct SSEvent
{
  EEventType  type; /*!< famille d'evenement, voir definition plus haut */
  Int16U      name; /*!< nom de l'evenement dans sa famille, definit dans le module proprietaire de la famille */
  Int16U      value; /*!< valeur sur 16 bits donne a l'evenement */
  Int8U       ext_value; /*!< valeur etendue, en complement de la valeur principale */
  Int8U       nb; /*!< nombre de fois que l'evenement est genere */
}SEvent;


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
* \brief fonction d'initialisation du module
*/
void drvEventInit( void );

void drvEventAdd( SEvent event_to_add );

SEvent drvEventGet( void );

Int8U drvEventIsPresent( EEventType in_type, Int8U in_name );

void drvEventRemove( EEventType in_type, Int8U in_name );

/**
* \brief fonction de gestion de la generation d'un event tout les 100ms
*
* \param[IN] i_enable : TRUE pour l'active, FALSE pour l'arreter
*
* \return TRUE si l'action a pu avoir lieu
*/
Boolean drvEventTick100ms( Boolean i_enable );

/**
* \brief fonction de gestion de la generation d'un event tout les 1s
*
* \param[IN] i_enable : TRUE pour l'active, FALSE pour l'arreter
*
* \return TRUE si l'action a pu avoir lieu
*/
Boolean drvEventTick1s( Boolean i_enable );

/******************************************************************************/
/******************************************************************************/
#endif /* _DRV_EVENT_H_ */
