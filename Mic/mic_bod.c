/*******************************************************************************
***                                                                          ***
**                                                                            **
**                  BROW OUT DETECTION MANAGEMENT                             **
**                                                                            **
***                                                                          ***
*******************************************************************************/
#include "mic/mic_micro.h"
#include "mic_bod.h"

// Note AT 16 and AT 164 and other:
// In order to avoid unintentional disabling or enabling of
// The BODS bit must be written to logic one in order to turn off BOD during sleep, see Table 9-1
// on page 42. Writing to the BODS bit is controlled by a timed sequence and an enable bit,
// BODSE in MCUCR. To disable BOD in relevant sleep modes, both BODS and BODSE must first
// be set to one. Then, to set the BODS bit, BODS must be set to one and BODSE must be set to
// zero within four clock cycles.
// The BODS bit is active three clock cycles after it is set. A sleep instruction must be executed
// while BODS is active in order to turn off the BOD for the actual sleep mode. The BODS bit is
// automatically cleared after three clock cycles.

// on avr644p this consum when it is working 20µA (measure at 18µA)

// on avr644p :
// When the Brown-out Detector (BOD) is enabled by BODLEVEL fuses, Table 26-3 on page 296,
// the BOD is actively monitoring the power supply voltage during a sleep period. To save power, it
// is possible to disable the BOD by software for some of the sleep modes, see Table 9-1 on page
// 43. The sleep mode power consumption will then be at the same level as when BOD is globally
// disabled by fuses. If BOD is disabled in software, the BOD function is turned off immediately
// after entering the sleep mode. Upon wake-up from sleep, BOD is automatically enabled again


/*******************************************************************************
*                                                                              *
*  Name: micBodTurnOff                                                         *
*                                                                              *
*  Subject: Turns off the BOD.                                                 *
*                                                                              *
*                                                                              *
*  Input(s):  None                                                             *
*                                                                              *
*  Output(s): None                                                             *
*                                                                              *
*  Modified Global variables: None                                             *
*                                                                              *
*  Necessary Interrupts: None                                                  *
*                                                                              *
*******************************************************************************/
// Force speed optimization, must be done 3 cycle before sleep instruction
// impossible!, donc ne pas appeller cette function mais coller ces intructions
// dans la fonction qui met en veille le micro

//#pragma optimize = speed none
//void micBodTurnOff(void)
//{
//  mcucr |= ((1U << BODS) | (1U << BODSE));
//  mcucr |= (1U << BODS);
//  mcucr &= ~(1U << BODSE);
//  return;
//}

// turning it on is automatic

/*****************************************************************************/

