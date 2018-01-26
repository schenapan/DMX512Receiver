/*******************************************************************************
***                                                                          ***
**                                                                            **
**                      ANALOG COMPARATOR MANAGEMENT                          **
**                                                                            **
***                                                                          ***
*******************************************************************************/

// Include header for this micrcontroller
#include "Mic/mic_micro.h"


/*******************************************************************************
*                                                                              *
*  Name: micComparatorTurnOn                                                   *
*                                                                              *
*  Subject: Turns on the Analog comparator.                                    *
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


void micComparatorTurnOn(void)
{
  acsr &= ~(1U << ACD);
  return;
}


/*******************************************************************************
*                                                                              *
*  Name: micComparatorTurnOff                                                  *
*                                                                              *
*  Subject: Turns off the Analog comparator.                                   *
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


void micComparatorTurnOff(void)
{
  acsr = (acsr & ~(1U << ACIE)) | (1U << ACD);
  acsr &= ~(1U << ACBG);     // disable internal reference voltage
  return;
}


/*******************************************************************************
*                                                                              *
*  Name: micCompSrcTrigForInCaptureOn                           *
*                                                                              *
*  Subject: the Analog Comparator output is used as trigger source for the     *
*           Input Capture unit.                                                *
*                                                                              *
*  Input(s):  None                                                             *
*                                                                              *
*  Output(s): None                                                             *
*                                                                              *
*******************************************************************************/

void micCompSrcTrigForInCaptureOn(void)
{
  acsr |= (1U << ACIC);
  return;
}

/*******************************************************************************
*                                                                              *
*  Name: micCompSrcTrigForInCaptureOff                          *
*                                                                              *
*  Subject: the Analog Comparator output is used as trigger source for the     *
*           Input Capture unit.                                                *
*                                                                              *
*  Input(s):  None                                                             *
*                                                                              *
*  Output(s): None                                                             *
*                                                                              *
*******************************************************************************/

void micCompSrcTrigForInCaptureOff(void)
{
  acsr &= ~(1U << ACIC);
  return;
}

/******************************************************************************/
