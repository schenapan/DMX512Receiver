/*******************************************************************************
*                                                                              *
*                         File to be included                                  *
*                                                                              *
*******************************************************************************/

/*******************************************************************************
*
* define a utiliser pour activer la remontee de l'état de la machine d'envoi
* sur la liason ember :
*
* EM260_DEBUG_EVENT_FIFO : remotee d'information sur la fifo
*
*******************************************************************************/

// include micro abstraction layer
#include "mic/mic_micro.h"

// include driver
#include "drv_event.h"
#include "drv_timer.h"

// service to include

// include application

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

#define EVENT_FIFO_MAX  10U // warning limited to 254 due to variable in Int8U

/*******************************************************************************
*                                                                              *
*                             Private  data                                    *
*                                                                              *
*******************************************************************************/
static struct Sevent_state
{
  SEvent  fifo[EVENT_FIFO_MAX];
  Int8U   current_pos;                // = (fifo read pointor + 1)
  Int8U   head_pos;                   // = (fifo write pointor )
  Int8U   count_ms;                   // index compteur pour la generation evenement a la seconde
#ifdef DEBUG
  Int8U max_event;
#endif
} event_state;

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

// callback timer pour la generation du tick 100ms
static void drvEventTick100msISR(void);

// callback timer pour la generation du tick 1s
static void drvEventTick1sISR(void);

/*******************************************************************************
*                                                                              *
*                  Public Functions of the Module                              *
*                                                                              *
*******************************************************************************/

/**
* \brief fonction d'initialisation du module
*/
void drvEventInit( void )
{
  event_state.current_pos = 0U;
  event_state.head_pos = EVENT_FIFO_MAX;
}


/*******************************************************************************
*                                                                              *
*  Name: drvEventAdd                                                           *
*                                                                              *
*  Subject: Add an Event in the fifo                                           *
*                                                                              *
*                                                                              *
*  Input(s): Event to add                                                      *
*                                                                              *
*  Output(s): None                                                             *
*                                                                              *
*                                                                              *
*******************************************************************************/
void drvEventAdd( SEvent event_to_add )
{
// SEB mettre un atomic dans la fonction appelante si ce n'est pas une interruption
    if( event_state.head_pos == EVENT_FIFO_MAX )
    {
      // no event in fifo
      event_state.fifo[event_state.current_pos] = event_to_add;
      event_state.head_pos = event_state.current_pos;
      event_state.current_pos++;
    }
    else
    {
      if( event_state.current_pos == event_state.head_pos )
      {
        // error fifo is full !!!      
        while(1)
          ;
      }
      else
      {
        Int8U continue_flag = 1U;
        Int8U add_flag = 1U;
        Int8U search_pos = event_state.current_pos;
        // intelligent filter
        // search if same type is already in the fifo

        do
        {
          if( search_pos == 0U )
          {
            search_pos = EVENT_FIFO_MAX - 1U;
          }
          else
          {
            search_pos -= 1U;
          }
          if( search_pos == event_state.head_pos )
          {
            continue_flag = 0U;
          }

          if( event_state.fifo[search_pos].type == event_to_add.type )
          {
            if( event_state.fifo[search_pos].name == event_to_add.name )
            {
              continue_flag = 0U;
              if( (event_state.fifo[search_pos].value == event_to_add.value) &&
                  (event_state.fifo[search_pos].ext_value == event_to_add.ext_value)
                )
              {
                add_flag = 0U;
                if ( event_state.fifo[search_pos].nb < (0xFFU - event_to_add.nb) )
                {
                  event_state.fifo[search_pos].nb += event_to_add.nb;
                }
              }
            }
          }
        }while( continue_flag );


        if( add_flag == 1U )
        {
          event_state.fifo[event_state.current_pos] = event_to_add;
          event_state.current_pos++;
        }
      }
    }

    if( event_state.current_pos == EVENT_FIFO_MAX )
    {
      event_state.current_pos = 0U;
    }
}

/*******************************************************************************
*                                                                              *
*  Name: drvEventGet                                                           *
*                                                                              *
*  Subject: return the first event in the fifo                                 *
*                                                                              *
*                                                                              *
*  Input(s): None                                                              *
*                                                                              *
*  Output(s): Event present in the fifo or NO_EVENT                            *
*                                                                              *
*******************************************************************************/
SEvent drvEventGet( void )
{
  SEvent event_to_return;

  event_to_return.type = E_EVENT_NONE;

  ATOMIC(
    if( event_state.head_pos != EVENT_FIFO_MAX )
    {
      // copie l'event
      event_to_return = event_state.fifo[event_state.head_pos];
      // efface l'event par precaution
      event_state.fifo[event_state.head_pos].type = E_EVENT_NONE;
      event_state.fifo[event_state.head_pos].name = 0U;
      event_state.fifo[event_state.head_pos].value = 0U;
      event_state.fifo[event_state.head_pos].ext_value = 0U;
      event_state.fifo[event_state.head_pos].nb = 0U;
      
      // incremente la tete
      event_state.head_pos++;

      if( event_state.head_pos == EVENT_FIFO_MAX )
      {
        event_state.head_pos = 0U;
      }

      if( event_state.head_pos == event_state.current_pos )
      {
        event_state.head_pos = EVENT_FIFO_MAX;
      }
    }
  ) // end ATOMIC

  return event_to_return;
}

/*******************************************************************************
*                                                                              *
*  Name: drvEventIsPresent                                                     *
*                                                                              *
*  Subject:                                                                    *
*                                                                              *
*                                                                              *
*  Input(s): None                                                              *
*                                                                              *
*  Output(s):                                                                  *
*                                                                              *
*******************************************************************************/
Int8U drvEventIsPresent( EEventType in_type, Int8U in_name )
{
  Int8U loop;
  Int8U out_value = 0U;

  ATOMIC(
    if( event_state.head_pos != EVENT_FIFO_MAX )
    {
      if( event_state.head_pos < event_state.current_pos )
      {
        Int8U end_loop = event_state.current_pos;

        for ( loop = event_state.head_pos ;
             loop < end_loop ;
             loop++ )
        {
          if( event_state.fifo[loop].type == in_type )
          {
            if( (event_state.fifo[loop].name == in_name) || (in_name == 0xFFU) )
            {
              out_value = 1U;
              loop = event_state.current_pos;
            }
          }
        }
      }
      else
      {
        for( loop = event_state.head_pos; loop < EVENT_FIFO_MAX; loop++ )
        {
          if( event_state.fifo[loop].type == in_type )
          {
            if( (event_state.fifo[loop].name == in_name) || (in_name == 0xFFU) )
            {
              out_value = 1U;
              loop = event_state.current_pos;
            }
          }
        }
        if( out_value == 0U )
        {
          Int8U end_loop = event_state.current_pos;

          for( loop = 0U; loop < end_loop; loop++ )
          {
            if( event_state.fifo[loop].type == in_type )
            {
              if( (event_state.fifo[loop].name == in_name)
                  || (in_name == 0xFFU) )
              {
                out_value = 1U;
                loop = event_state.current_pos;
              }
            }
          }
        }
      }
    }
  ) // end atomic

  return out_value;
}

/*******************************************************************************
*                                                                              *
*  Name: drvEventRemove                                                        *
*                                                                              *
*  Subject:                                                                    *
*                                                                              *
*                                                                              *
*  Input(s): None                                                              *
*                                                                              *
*  Output(s):                                                                  *
*                                                                              *
*******************************************************************************/
void drvEventRemove( EEventType in_type, Int8U in_name )
{
  Int8U loop;

  ATOMIC(
    if( event_state.head_pos != EVENT_FIFO_MAX )
    {
      if( event_state.head_pos < event_state.current_pos )
      {
        Int8U end_loop = event_state.current_pos;

        for( loop = event_state.head_pos; loop < end_loop; loop++ )
        {
          if( event_state.fifo[loop].type == in_type )
          {
            if( (event_state.fifo[loop].name == in_name) || (in_name == 0xFFU) )
            {
              event_state.fifo[loop].type = E_EVENT_NONE;
            }
          }
        }
      }
      else
      {
        Int8U end_loop = event_state.current_pos;

        for( loop = event_state.head_pos; loop < EVENT_FIFO_MAX; loop++ )
        {
          if( event_state.fifo[loop].type == in_type )
          {
            if( (event_state.fifo[loop].name == in_name) || (in_name == 0xFFU) )
            {
              event_state.fifo[loop].type = E_EVENT_NONE;
            }
          }
        }
        for( loop = 0U; loop < end_loop; loop++ )
        {
          if( event_state.fifo[loop].type == in_type )
          {
            if( (event_state.fifo[loop].name == in_name) || (in_name == 0xFFU) )
            {
              event_state.fifo[loop].type = E_EVENT_NONE;
            }
          }
        }
      }
    }
  ) // end atomic
}

/**
* \brief fonction de gestion de la generation d'un event tout les 100ms
*
* \param[IN] i_enable : TRUE pour l'active, FALSE pour l'arreter
*
* \return TRUE si l'action a pu avoir lieu
*/
Boolean drvEventTick100ms( Boolean i_enable )
{
  Boolean lo_success = TRUE;
  
  if( TRUE == i_enable )
  {
    lo_success = drvTimerAdd( drvEventTick100msISR, 100U, TIMER_PERIODIC_CALL );
  }
  else
  {
    drvTimerRemove( drvEventTick100msISR );
  }
  
  return lo_success;
}

/**
* \brief fonction de gestion de la generation d'un event tout les 1s
*
* \param[IN] i_enable : TRUE pour l'active, FALSE pour l'arreter
*
* \return TRUE si l'action a pu avoir lieu
*/
Boolean drvEventTick1s( Boolean i_enable )
{
  Boolean lo_success = TRUE;
  
  if( TRUE == i_enable )
  {
    lo_success = drvTimerAdd( drvEventTick1sISR, 1000U, TIMER_PERIODIC_CALL );
  }
  else
  {
    drvTimerRemove( drvEventTick1sISR );
  }
  
  return lo_success;
}

/*******************************************************************************
*                                                                              *
*                  Private Functions of the Module                             *
*                                                                              *
*******************************************************************************/


/*******************************************************************************
*                                                                              *
*                  ISR Function of the Module                                  *
*                                                                              *
*******************************************************************************/



/*******************************************************************************
*                                                                              *
*  Name: drvEventISR                                                           *
*                                                                              *
*  Subject: Generate the second Tick event every second                        *
*                                                                              *
*  Input(s): None                                                              *
*                                                                              *
*  Output(s):                                                                  *
*                                                                              *
*******************************************************************************/

// callback timer pour la generation du tick 100ms
static void drvEventTick100msISR(void)
{
  SEvent new_event_ms;

  new_event_ms.type = E_EVENT_GENERAL;
  new_event_ms.name = E_GENERAL_TICK_100MS_EVENT;
  new_event_ms.value = 0xFFU;
  new_event_ms.nb = 0x01U;
  drvEventAdd( new_event_ms );
}

// callback timer pour la generation du tick 1s
static void drvEventTick1sISR(void)
{
  SEvent new_event_s;

  new_event_s.type = E_EVENT_GENERAL;
  new_event_s.name = E_GENERAL_TICK_1S_EVENT;
  new_event_s.value = 0xFFU;
  new_event_s.nb = 0x01U;
  drvEventAdd( new_event_s );
}

//------------------------------------------------------------------------------
