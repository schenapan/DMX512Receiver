#ifndef _COMPILATOR_H_
#define _COMPILATOR_H_
/******************************************************************************/




		// on suppose qu'il s'agit avr gcc
		#include <avr/io.h>
		#include <avr/interrupt.h>
		#include <avr/sleep.h>
		#include <avr/wdt.h>
		#include <avr/pgmspace.h>
	
		// Redefinition des carateristique intrinsec au micro :
		// Internal code memory
		#define __CODE_MEMORY                   

		// No default initialisation of memory variables
		#define __NO_INIT                       

		// Internal EEPROM memory
		#define __EEPROM_MEMORY                 

		// Interrupt functions
		#define __ISR_FUNCTION                  


		// Monitor function
		#define __MONITOR_FUNCTION            
	
		#define __enable_interrupt() sei()  
		#define __disable_interrupt() cli()  
		#define __watchdog_reset() wdt_reset()
		#define __no_operation()
		#define __sleep()
		#define __io

		// code en flash	
		#define FLASH_DECLARE(x) x __attribute__((__progmem__))

		/**
		 * @description A block of code may be made atomic by wrapping it with this
		 * macro.  Something which is atomic cannot be interrupted by interrupts.
		 */
		#ifndef ATOMIC
		  #define ATOMIC(code)          \
			{                           \
			  Int8U em_isr_state;       \
			  em_isr_state = SREG;		\
			  __disable_interrupt();	\
			  do{ code }while(0);       \
		      SREG = em_isr_state;		\
			}
		#endif  



/******************************************************************************/
#endif // _COMPILATOR_H_

