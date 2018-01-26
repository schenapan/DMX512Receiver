/*******************************************************************************
***                                                                          ***
**                                                                            **
**                        System timer: based on timer 0                      **
**                                                                            **
***                                                                          ***
*******************************************************************************/

/*******************************************************************************
*                                                                              *
*                         File to be included                                  *
*                                                                              *
*******************************************************************************/

// Include micro abstraction layer
#include "Mic/mic_micro.h"

// Include driver layer header files
#include "drv_timer.h"

//Include applicative product file
#include "app_product_hardware.h"


/*******************************************************************************
*                                                                              *
*                         Private type declaration                             *
*                                                                              *
*******************************************************************************/


/*******************************************************************************
*                                                                              *
*                         Constants declaration                                *
*                                                                              *
*******************************************************************************/

/** definit le diseur utiliser pour une clock a 8MHz sur le timer 0 */
#define DRV_TIMER_DIVISOR TIMER0_CLK_DIV_64

/** definit la valeur de rechargement pour un tick system a la ms */
#define DRV_1MS_SYSTEM_TICK 125U

/** 
* definit le nombre de timer disponible pour le produit, a placer dans 
* app_product_hardware.h
*/
#ifndef E_NB_USER_TIMER
  #define E_NB_TIMER 1U
#else
  #define E_NB_TIMER (E_NB_USER_TIMER + 1U)
#endif

/*******************************************************************************
*                                                                              *
*                             Private data types                               *
*                                                                              *
*******************************************************************************/

/** structure de defintion d'un timer utilisateur */
typedef struct SSTimerUser
{
  TimerFctnPtr fctn_ptr;
  TimerUnit reset_counter;
  volatile TimerUnit counter;
} STimerUser;

/*******************************************************************************
*                                                                              *
*                         Private Macros of the module                         *
*                                                                              *
*******************************************************************************/

// variable privee du module
static struct
{
  STimerUser timer[E_NB_TIMER]; // table des timer, ATTENTION L'index 0 est 
                                // reserve pour la fonctionnalite WAIT
  volatile Boolean waiting;
} drv_timer_status;

/*******************************************************************************
*                                                                              *
*                   Private Functions of the Module                            *
*                                                                              *
*******************************************************************************/

// fonction de callback pour la fonctionnalite d'attente bloquante
static void drvTimerWaitISR(void);

// ISR
//------------------------------------------------------------------------------
static void drvTimerSystemISR(void);

/*******************************************************************************
***                                                                          ***
**                                                                            **
*                  Public Functions of the Module                              *
**                                                                            **
***                                                                          ***
*******************************************************************************/

/**
* \brief fonction d'initialisation du module, utilise le timer 0 de l'avr en roll
*        over avec une periode superieur a 1ms et interruption sur output compare A
*/
void drvTimerInit( void )
{
  Int8U loop;
  
  // Initialize private variable
  for ( loop = 0U; loop < E_NB_TIMER ; loop++ )
  {
   drv_timer_status.timer[loop].fctn_ptr = NUL;
   drv_timer_status.timer[loop].counter = 0U;
   drv_timer_status.timer[loop].reset_counter = 0U;
  }
  
  drv_timer_status.waiting = 0U;
  
  // initialisation du timer micro
  // enable timer
  micPeripheralsTurnOn( PERIPHERAL_TIMER0 );

  // configure timer
  micTimer0SetClockDivision( DRV_TIMER_DIVISOR );

  micTimer0SetValue(0U);
  micTimer0SetGeneratorMode( TIMER0_NORMAL_COMPARE );
  micTimer0SetCompareValueA( DRV_1MS_SYSTEM_TICK );

  micTimer0SetCompACallback( drvTimerSystemISR );

   // start interrupts
  micTimer0ClearInterruptFlags(TIMER0_COMPARE_A_FLAG);
  micTimer0UnmaskInterrupts(TIMER0_COMPARE_A_INTERRUPT);
}

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
                    TimerUnit delay_ms, TimerMode is_periodic)
{
  Boolean lo_success = FALSE;
  Int8U l_timer_idx = 0xFF;
  Int8U loop;
  
  if ( (TimerFctnPtr)NUL != in_fctn_ptr )
  {
    ATOMIC
    (
      // regarde si il y a une place de libre
      for( loop=1U; loop<E_NB_TIMER; loop++ )
      {
        if( 0U == drv_timer_status.timer[loop].counter )
        {
          l_timer_idx = loop;
          loop = E_NB_TIMER;
        }
      }
      if( 0xFFU != l_timer_idx )
      {
        // add value
        drv_timer_status.timer[l_timer_idx].fctn_ptr = in_fctn_ptr;
        drv_timer_status.timer[l_timer_idx].counter = delay_ms; 
  
        if ( is_periodic )
        {
          // Periodic mode: Start timer at once
          drv_timer_status.timer[l_timer_idx].reset_counter =
                                    drv_timer_status.timer[l_timer_idx].counter;
        }
        else
        {
          // One shot mode start immediatly
          drv_timer_status.timer[l_timer_idx].reset_counter = 0U;
        }
        
        lo_success = TRUE;
      }
    ) // end ATOMIC
  }
  else
  {
    // signal an error !!!
  }

  return lo_success;
}

/**
* \brief fonction de suppresion d'un timer, on passe le pointeur de fonction
*        de la callback associe a ce timer
*/
void drvTimerRemove(TimerFctnPtr in_fctn_ptr)
{
  Int8U loop;
  
  ATOMIC
  (
    for( loop=1U; loop<E_NB_TIMER; loop++ )
    {
      if( in_fctn_ptr == drv_timer_status.timer[loop].fctn_ptr )
      {
        // Reset parameter
        drv_timer_status.timer[loop].fctn_ptr = NUL;
        drv_timer_status.timer[loop].counter = 0U;
        drv_timer_status.timer[loop].reset_counter = 0U;
      }
    }
  ) // end ATOMIC

  return;
}

/**
* \brief realise un wait bloquant a la ms
*
* \param[IN] duration: temps d'attente en ms
*/
void drvTimerWait(TimerUnit duration)
{
  ATOMIC
  (
    drv_timer_status.timer[0U].fctn_ptr = drvTimerWaitISR;
    drv_timer_status.timer[0U].counter = duration; 
    drv_timer_status.timer[0U].reset_counter = 0U;
    
    drv_timer_status.waiting = TRUE;
  ) // end ATOMIC
  
  while( TRUE == drv_timer_status.waiting )
  {
    micResetWatchdog();
  }
}

/*******************************************************************************
*                                                                              *
*                   Private Functions of the Module                            *
*                                                                              *
*******************************************************************************/



/*******************************************************************************
*                                                                              *
*  Name: drvTimerWaitISR                                                       *
*                                                                              *
*  Subject:                                                                    *
*                                                                              *
*  Input(s): None                                                              *
*                                                                              *
*  Output(s): None                                                             *
*                                                                              *
*******************************************************************************/
static void drvTimerWaitISR(void)
{
  drv_timer_status.waiting = FALSE;
}

/*******************************************************************************
***                                                                          ***
**                                                                            **
*                      ISR Function of the Module                              *
**                                                                            **
***                                                                          ***
*******************************************************************************/
/*******************************************************************************
*                                                                              *
*  Name: drvTimerWaitISR                                                       *
*                                                                              *
*  Subject:                                                                    *
*                                                                              *
*  Input(s): None                                                              *
*                                                                              *
*  Output(s): None                                                             *
*                                                                              *
*  Necessary Interrupts: COMPA of timer 0                                      *
*                                                                              *
*******************************************************************************/
static void drvTimerSystemISR(void)
{
  Int8U loop;

  // recharge le timer pour la prochaine fois
  Timer0Value timer0_value_start;
  timer0_value_start = micTimer0GetValue();
  micTimer0SetCompareValueA( timer0_value_start +  DRV_1MS_SYSTEM_TICK  );

  // Call associated functions
  for ( loop = 0U; loop < E_NB_TIMER; loop++ )
  {
    if ( drv_timer_status.timer[loop].counter != 0U  )
    {
      drv_timer_status.timer[loop].counter -= 1U;
      if ( drv_timer_status.timer[loop].counter == 0U )
      {
        drv_timer_status.timer[loop].fctn_ptr();

        drv_timer_status.timer[loop].counter =
                                   drv_timer_status.timer[loop].reset_counter;
      }
    }
  }

  return;
}


/******************************************************************************/
