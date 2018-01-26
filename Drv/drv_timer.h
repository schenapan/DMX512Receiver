#ifndef _DRV_TIMER_H_
#define _DRV_TIMER_H_
/*******************************************************************************
*                                                                              *
*                         File to be included                                  *
*                                                                              *
*******************************************************************************/

// Include application header


/*******************************************************************************
*                                                                              *
*                         Constants declaration                                *
*                                                                              *
*******************************************************************************/

//------------------------------------------------------------------------------

// To specify whether timer user function calling is periodic or One shot when
// adding a new user
#define TIMER_PERIODIC_CALL             1U    // Periodic call
#define TIMER_ONE_SHOT_CALL             0U    // One shot
typedef Boolean TimerMode;

//------------------------------------------------------------------------------

// To specificy whether timer is trigger at once or later when adding a new
// One Shot Mode user
#define TIMER_ONE_SHOT_TRIGGER_LATER   0U


/*******************************************************************************
*                                                                              *
*                             Public data types                                *
*                                                                              *
*******************************************************************************/

// User function pointer Timer
typedef void (*TimerFctnPtr)( void );

// Time unit in system timer is system timer base time
typedef Int16U TimerUnit;


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

//------------------------------------------------------------------------------
/*
 * => Timer based on system timer base time
 */

/**
* \brief fonction d'initialisation du module, utilise le timer 0 de l'avr en roll
*        over avec une periode superieur a 1ms et interruption sur output compare A
*/
void drvTimerInit( void );

/**
* \brief permet d'ajouter un timer utilisateur indexer sur le timer system
*        dont le tick est a 1ms
*
* \param[IN] in_fctn_ptr: fonction callback a appeler
* \param[IN] delay_ms: periode en ms du timer
* \param[IN] is_periodic: TRUE, la periode est automatique rechargee a la fin 
*                         du timer
*
* \return TRUE si le timer a pu etre ajoute, FALSE si il n'y a plus de place
*/
Boolean drvTimerAdd(TimerFctnPtr in_fctn_ptr, 
                    TimerUnit delay_ms, TimerMode is_periodic);

/**
* \brief fonction de suppresion d'un timer, on passe le pointeur de fonction
*        de la callback associe a ce timer
*/
void drvTimerRemove(TimerFctnPtr in_fctn_ptr);

//------------------------------------------------------------------------------
/*
 * => Particular service function based on system timer
 */

/**
* \brief realise un wait bloquant a la ms
*
* \param[IN] duration: temps d'attente en ms
*/
void drvTimerWait(TimerUnit duration);


/******************************************************************************/
#endif /* _DRV_TIMER_H_ */
