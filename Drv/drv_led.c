/*******************************************************************************
*                                                                              *
*                         File to be included                                  *
*                                                                              *
*******************************************************************************/

// Include micro abstraction layer
#include "Mic/mic_micro.h"

// Include driver
#include "drv_led.h"
#include "drv_timer.h"

// Include application
#include "app_product_hardware.h"


/*******************************************************************************
*                                                                              *
*                         constantes declaration                               *
*                                                                              *
*******************************************************************************/



/*******************************************************************************
*                                                                              *
*                         Private type declaration                             *
*                                                                              *
*******************************************************************************/

struct  
{
	SIo led; 
	Int8U on_time;
	Int8U on_counter;
}dim_led_tbl[NB_DIMMABLE_LED];

/*******************************************************************************
*                                                                              *
*                  Private Functions of the Module                             *
*                                                                              *
*******************************************************************************/

static void drvLedTimer( void );

/*******************************************************************************
*                                                                              *
*                  Public Functions of the Module                              *
*                                                                              *
*******************************************************************************/

/**
* \brief fonction d'initialisation du module
*/
void drvLedInit( void )
{
	for( int loop=0; loop<NB_DIMMABLE_LED; loop++ )
	{
		dim_led_tbl[loop].led = INVALID_IO;
	}
	drvTimerAdd( drvLedTimer, 1U, TIMER_PERIODIC_CALL );
}

/**
*
* \brief permet d'allumer une led
*
* \param[in] i_led : definition de la led
*
*/
void drvLedSetLedOn( SIo i_led )
{
	if((APP_LED_1.pin == i_led.pin)&&(APP_LED_1.port == i_led.port))
	{
	  micIoConfigOutput( i_led );
	  micIoSet( i_led, IO_LVL_VCC );
	}
	else
	{
	  micIoConfigOutput( i_led );
	  micIoSet( i_led, IO_LVL_GND );
	}
}

/**
*
* \brief permet d'eteindre une led
*
* \param[in] i_led : definition de la led
*
*/
void drvLedSetLedOff( SIo i_led )
{
	if((APP_LED_1.pin == i_led.pin)&&(APP_LED_1.port == i_led.port))
	{
	  micIoConfigOutput( i_led );
	  micIoSet( i_led, IO_LVL_GND );	
	}
	else
	{
		micIoConfigInput( i_led, IO_NO_PULL_UP );
	}
}

/**
* \brief permet d'allumer une led pendant un temps definit sur une periode de 0x0F pas de 2ms
*
* \ temps on pour une led : 0->eteint, 0x0F->allumé
*/
void drvLedSetOnTime( SIo i_led, Int8U on_time_value )
{
	// remove existing led
	for( int loop=0; loop<NB_DIMMABLE_LED; loop++ )
	{
		if( IO_EQUAL(dim_led_tbl[loop].led, i_led) )
		{
			dim_led_tbl[loop].led = INVALID_IO;
			loop=NB_DIMMABLE_LED;
		}
	}

	if( 0 == on_time_value )
	{
		// off
		drvLedSetLedOff(i_led);
	}
	else if( on_time_value >= 0x0F )
	{
		// on
		drvLedSetLedOn(i_led);
	}
	else
	{
		for( int loop=0; loop<NB_DIMMABLE_LED; loop++ )
		{
			if( IO_EQUAL(dim_led_tbl[loop].led,INVALID_IO) )
			{
				dim_led_tbl[loop].led = i_led;
				dim_led_tbl[loop].on_time = on_time_value;
				dim_led_tbl[loop].on_counter = 0;
				loop=NB_DIMMABLE_LED;
			}
		}
	}
}


/*******************************************************************************
*                                                                              *
*                  Private Functions of the Module                             *
*                                                                              *
*******************************************************************************/


static void drvLedTimer( void )
{
	static Int8U roll_over_counter = 0x0F;

	for( int loop=0; loop<NB_DIMMABLE_LED; loop++ )
	{
		if( !IO_EQUAL(dim_led_tbl[loop].led,INVALID_IO) )
		{
			dim_led_tbl[loop].on_counter -= 1;
			if( 0 == dim_led_tbl[loop].on_counter )
			{
				drvLedSetLedOff(dim_led_tbl[loop].led);
			}
		}
	}

	roll_over_counter -= 1;
	if( 0 == roll_over_counter )
	{
		roll_over_counter = 0x0F;

		for( int loop=0; loop<NB_DIMMABLE_LED; loop++ )
		{
			if( !IO_EQUAL(dim_led_tbl[loop].led,INVALID_IO) )
			{
				dim_led_tbl[loop].on_counter = dim_led_tbl[loop].on_time;
				drvLedSetLedOn(dim_led_tbl[loop].led);
			}
		}
	}
}

/******************************************************************************/
/******************************************************************************/
