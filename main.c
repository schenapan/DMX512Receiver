/*
 * DMX512Receiver.c
 *
 * Created: 25/01/2018 14:59:55
 * Author : marionse
 */ 

#include <string.h>

// include micro abstraction layer
#include "Mic/mic_micro.h"
#include "Drv/drv_timer.h"
#include "Drv/drv_event.h"
#include "Drv/drv_led.h"
#include "Srv/srv_zb_mfg.h"
#include "Drv/drv_em260.h"

#include "app_product_hardware.h"

#define RADIO_DMX_DATA_SIZE	64


static void RxCallback( Int8U *packet, Int8U linkQuality, Int8S rssi);

static Int8U rsp_msg[EM260_MAX_IN_BUFFER];
static Boolean send_flag;


int main(void)
{
  SEvent l_event;
  EmberStatus status;
  
  send_flag = FALSE;

  // start cpu at high speed
  micSetCpuClockPrescaler( CLKPR_DIV_1 ); // start cpu
  
  micSetWatchdogPrescaler( PRODUCT_WDTPR );
  micResetWatchdog();
  
  micPeripheralsTurnOff( ALL_PERIPHERALS );
  
  micEnableInterrupts();   // enable global interrupt

  // turn all pin into input with no pull up
  // it is up to every module to configure its inputs
  micIoInit();

  /** initialise les differents composants */
  drvTimerInit();
  drvEventInit();

  /** init radio */
  drvLedInit();
  drvLedSetLedOn( RF_LED );
  drvLedSetLedOn( DBG_LED );
  drvLedSetLedOn( APP_LED_1 );
  
  if( TRUE == srvZbMfgInit() )
  {
	status = srvZbMfgStart( RxCallback );
	if (status == EMBER_SUCCESS) 
	{
		status = srvZbMfgSetChannel( 15 );
		if (status == EMBER_SUCCESS)
		{
		  if( TRUE == drvEventTick1s( TRUE ) )
		  {
			  // on est de fait en reception
			  drvLedSetLedOff( RF_LED );
			  drvLedSetLedOff( APP_LED_1 );
			  drvTimerAdd( srvZbMfgCheckMessage, 20U, TIMER_PERIODIC_CALL );
		  }
		}
	}
  }
  

  /* Main Loop */
  while (1) 
  {
    // mise a jour du watchdog
    micResetWatchdog();

    // appel la boucle de gestion des events
    l_event = drvEventGet();
    if( E_EVENT_NONE != l_event.type )
    {
		if( (E_EVENT_GENERAL==l_event.type) && (E_GENERAL_TICK_1S_EVENT==l_event.name) )
		{
			micIoToggle( DBG_LED );
		}
    }
	
	if( send_flag )
	{
		srvZbMfgSendPacket( rsp_msg[0]+2, &rsp_msg[1], 0 );
		send_flag = FALSE;
	}
  }
}

/*******************************************************************************
*                                                                              *
*          Fonction d'execution des commandes zigbee entrante                  *
*                                                                              *
*******************************************************************************/
// callback de reception des packets
static void RxCallback( Int8U *packet, Int8U linkQuality, Int8S rssi)
{
	static Int8U l_last_value = 0;
	static Int8U l_last_seq_nb = 0xFF;

    // mise a jour du watchdog
    micResetWatchdog();

	Int8U packet_size = packet[0];

	if( packet_size > 12 )
	{

		// frm control
		if( (0x01==packet[1]) && (0x08==packet[2]) )
		{
			
			Int8U seq_number = packet[3];
			if( l_last_seq_nb != seq_number )
			{
				// update sequence numebr
				l_last_seq_nb = seq_number;
				
				// dest panId
				if( (0xCD==packet[4]) && (0xAB==packet[5]) )
				{
				
					// dest addr
					if( (0xFF==packet[6]) && (0xFF==packet[7]) )
					{
					
						// TAG
						if( ('D'==packet[8]) && ('M'==packet[9]) && ('X'==packet[10]) )
						{
						
							// Option
							Int8U frm_option = packet[11] >> 4;
							// Offset - or number of repeat if Option 1
							Int8U frm_offset = packet[11] & 0x0F;

						
							if( 0 == frm_option )
							{
								// un octet par addresse, niveau lumineux

								if( (DMX_ADDRESS >= (RADIO_DMX_DATA_SIZE*frm_offset)) &&
									(DMX_ADDRESS < (RADIO_DMX_DATA_SIZE*(frm_offset+1)))
								 )
								 {
									Int8U value = packet[12+(DMX_ADDRESS-(RADIO_DMX_DATA_SIZE*frm_offset))]>>4;
									if( l_last_value != value )
									{
										// drvLedSetOnTime(RF_LED, value);
										drvLedSetOnTime(APP_LED_1, value);
										l_last_value = value;
									}
								 }
							} 
							else if( 1 == frm_option )
							{
								// un octet dans le message contient les addresse 0->16 codé sur 1 bit (on/off)
								if( DMX_ADDRESS < 16 )
								{
									Int8U value = 0xFF * ((((Int16U)(packet[12]+(packet[13]<<8)))>>DMX_ADDRESS)&0x01);
								
									if( l_last_value != value )
									{
										// drvLedSetOnTime(RF_LED, value);
										drvLedSetOnTime(APP_LED_1, value);
										l_last_value = value;
									}
								}
								
								// manage repeat
								if( (0 != frm_offset) && (!send_flag) )
								{
									frm_offset--;
									packet[11] = (frm_option<<4) | frm_offset;
									memcpy(rsp_msg, packet, packet_size);
									send_flag = TRUE;
								}
							}
						}
					}
				}
			}
		}
	}
}