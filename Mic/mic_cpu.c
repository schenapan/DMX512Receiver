/*******************************************************************************
***                                                                          ***
**                                                                            **
**                           CPU MANAGEMENT                                   **
**                                                                            **
***                                                                          ***
*******************************************************************************/

// Include header for this micrcontroller
#include "Mic/mic_micro.h"


/*******************************************************************************
*                                                                              *
*  Name: micNop                                                                *
*                                                                              *
*  Subject: No operation command                                               *
*                                                                              *
*                                                                              *
*  Input(s): None                                                              *
*                                                                              *
*  Output(s): None                                                             *
*                                                                              *
*  Modified Global variables: None                                             *
*                                                                              *
*  Necessary Interrupts: None                                                  *
*                                                                              *
*******************************************************************************/

void micNop(void)
{
  __no_operation();

  return;
}


/*******************************************************************************
*                                                                              *
*  Name: micGlobalPullUpsEnable                                                *
*                                                                              *
*  Subject: Enable pull-up on all ports                                        *
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

void micGlobalPullUpsEnable(void)
{
  mcucr &= ~(1U << PUD);

  return;
}


/*******************************************************************************
*                                                                              *
*  Name: micGlobalPullUpsDisable                                               *
*                                                                              *
*  Subject: Enable pull-up on all ports                                        *
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

void micGlobalPullUpsDisable(void)
{
  mcucr |= (1U << PUD);

  return;
}


/******************************************************************************/


/*----------------------------------------------------------------------------*/


/*******************************************************************************
***                                                                          ***
**                                                                            **
**                          WATCHDOG MANAGEMENT                               **
**                                                                            **
***                                                                          ***
*******************************************************************************/

/*******************************************************************************
*                                                                              *
*  Name: micSetWatchdogPrescaler                                               *
*                                                                              *
*  Subject: Start watchdog after having previously set the prescaler           *
*                                                                              *
*                                                                              *
*  Input(s):  watchdog_prescaler =  Watchdog value for wdtcsr register         *
*                                                                              *
*  Output(s): None                                                             *
*                                                                              *
*  Modified Global variables: None                                             *
*                                                                              *
*  Necessary Interrupts: None                                                  *
*                                                                              *
*******************************************************************************/

// Force speed optimization
// #pragma optimize = speed none
void micSetWatchdogPrescaler( WatchdogPrescaler watchdog_prescaler )
{
 __watchdog_reset();
  wdtcsr |= ((1U << WDCE) | (1U << WDE));
  wdtcsr = watchdog_prescaler | (1U << WDE) | (1U << WDIF);

  return;
}



/*******************************************************************************
*                                                                              *
*  Name: micStopWatchdog                                                       *
*                                                                              *
*  Subject: Stops watchdog                                                     *
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

// Force speed optimization
// #pragma optimize = speed none
void micStopWatchdog(void)
{
 __watchdog_reset();
  mcusr &= ~(1U << WDRF);
  wdtcsr |= ((1U << WDCE) | (1U << WDE));
  wdtcsr = 0x00U;

  return;
}


/*******************************************************************************
*                                                                              *
*  Subject: reset the reset source register                                    *
*           in order to know why a future reset occur                          *
*  Input(s):  None                                                             *
*                                                                              *
*  Output(s): None                                                             *
*                                                                              *
*  Modified Global variables: None                                             *
*                                                                              *
*  Necessary Interrupts: None                                                  *
*                                                                              *
*******************************************************************************/
// Force speed optimization
// #pragma optimize=s 2
void micRazResetSourceFlag(void)
{
  mcusr &= ~(ALL_RESET_SOURCE);
  
  return;
}


/*******************************************************************************
*                                                                              *
*  Subject: return the reset source                                            *
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

// Force speed optimization
// #pragma optimize = speed none
Int8U micReadResetSource(void)
{
  Int8U rvalue=0U;

  if ( 0U != (mcusr & RESET_SOURCE_JTAG))
  {
    rvalue |= RESET_SOURCE_JTAG;
  }
  if ( 0U != (mcusr & RESET_SOURCE_WATCHDOG))
  {
    rvalue |= RESET_SOURCE_WATCHDOG;
  }
  if ( 0U != (mcusr & RESET_SOURCE_BROWN_OUT))
  {
    rvalue |= RESET_SOURCE_BROWN_OUT;
  }
  if ( 0U != (mcusr & RESET_SOURCE_EXTERNAL))
  {
    rvalue |= RESET_SOURCE_EXTERNAL;
  }
  if ( 0U != (mcusr & RESET_SOURCE_POWER_ON))
  {
    rvalue |= RESET_SOURCE_POWER_ON;
  }

  return rvalue;
}


/*******************************************************************************
*                                                                              *
*  Name: micResetWatchdog                                                      *
*                                                                              *
*  Subject: Reset watchdog to avoid a hardawre reset                           *
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

void micResetWatchdog(void)
{
 __watchdog_reset();

  return;
}


/******************************************************************************/

/*----------------------------------------------------------------------------*/


/*******************************************************************************
***                                                                          ***
**                                                                            **
**                          CPU CLOCK MANAGEMENT                              **
**                                                                            **
***                                                                          ***
*******************************************************************************/

/*******************************************************************************
*                                                                              *
*  Name: micSetCpuClockPrescaler                                               *
*                                                                              *
*  Subject: Set the CPU clock prescaler                                        *
*                                                                              *
*                                                                              *
*  Input(s):  prescaler_value =  CPU clock prescaler setting                   *
*                                                                              *
*  Output(s): None                                                             *
*                                                                              *
*  Modified Global variables: None                                             *
*                                                                              *
*  Necessary Interrupts: None                                                  *
*                                                                              *
*******************************************************************************/

void micSetCpuClockPrescaler(CpuClockPrescaler prescaler_value)
{
  clkpr = (1U << CLKPCE);
  clkpr = (prescaler_value & 0x0FU);

  return;
}

/*******************************************************************************
*                                                                              *
*  Name: micGetCpuClockPrescaler                                               *
*                                                                              *
*  Subject: Get the CPU clock prescaler                                        *
*                                                                              *
*                                                                              *
*  Input(s):  None                                                             *
*                                                                              *
*  Output(s): prescaler_value =  CPU clock prescaler setting                   *
*                                                                              *
*  Modified Global variables: None                                             *
*                                                                              *
*  Necessary Interrupts: None                                                  *
*                                                                              *
*******************************************************************************/

Int8U micGetCpuClockPrescaler( void )
{
  return clkpr;
}

/******************************************************************************/


/*----------------------------------------------------------------------------*/


/*******************************************************************************
***                                                                          ***
**                                                                            **
**                             POWER MANAGEMENT                               **
**                                                                            **
***                                                                          ***
*******************************************************************************/

/*******************************************************************************
*                                                                              *
*  Name: micPowerDownPeripherals                                               *
*                                                                              *
*  Subject: Power down the specified peripherals                               *
*                                                                              *
*                                                                              *
*  Input(s):  peripherals_flags =  Flags for the peripherals to be stopped     *
*                                                                              *
*  Output(s): None                                                             *
*                                                                              *
*  Modified Global variables: None                                             *
*                                                                              *
*  Necessary Interrupts: None                                                  *
*                                                                              *
*******************************************************************************/

void micPeripheralsTurnOff(PeripheralsFlags peripherals_flags)
{
  prr |= peripherals_flags;
  return;
}


/*******************************************************************************
*                                                                              *
*  Name: micPeripheralsTurnOn                                                  *
*                                                                              *
*  Subject: Turn on the specified peripherals                                  *
*                                                                              *
*                                                                              *
*  Input(s):  peripherals_flags =  Flags for the peripherals to be stopped     *
*                                                                              *
*  Output(s): None                                                             *
*                                                                              *
*  Modified Global variables: None                                             *
*                                                                              *
*  Necessary Interrupts: None                                                  *
*                                                                              *
*******************************************************************************/

void micPeripheralsTurnOn(PeripheralsFlags peripherals_flags)
{
  prr &= (Int8U)(~peripherals_flags);
  return;
}


/*******************************************************************************
*                                                                              *
*  Name: micPeripheralsControlPower                                            *
*                                                                              *
*  Subject: Control the power supply of all the peripherals.                   *
*                                                                              *
*                                                                              *
*  Input(s):  off_peripherals_flags =  Flags for the peripherals to be stopped *
*                                                                              *
*  Output(s): None                                                             *
*                                                                              *
*  Modified Global variables: None                                             *
*                                                                              *
*  Necessary Interrupts: None                                                  *
*                                                                              *
*******************************************************************************/

void micPeripheralsControlPower(PeripheralsFlags off_peripherals_flags)
{
  prr = off_peripherals_flags;
  return;
}

/*******************************************************************************
*                                                                              *
*  Name: micPeripheralsReadControlPower                                        *
*                                                                              *
*  Subject: read the Control the power supply of all the peripherals.          *
*                                                                              *
*                                                                              *
*  Input(s):  None                                                             *
*                                                                              *
*  Output(s): The actual value of the control register                         *
*                                                                              *
*  Modified Global variables: None                                             *
*                                                                              *
*  Necessary Interrupts: None                                                  *
*                                                                              *
*******************************************************************************/

PeripheralsFlags micPeripheralsReadControlPower( void )
{
  return prr;
}

/*******************************************************************************
*                                                                              *
*  Name: micEnterSleepMode                                                     *
*                                                                              *
*  Subject: Enter the specified energy saving mode                             *
*                                                                              *
*                                                                              *
*  Input(s):  sleep_mode = Energy saving mode to be entered                    *
*                                                                              *
*  Output(s): None                                                             *
*                                                                              *
*  Modified Global variables: None                                             *
*                                                                              *
*  Necessary Interrupts: None                                                  *
*                                                                              *
*******************************************************************************/
// Force speed optimization
// #pragma optimize = speed none
void micEnterSleepMode(SleepMode sleep_mode)
{
  #ifndef DEBUG
    // backup de la valeur de mcucr, pour couper le BOD sans ecraser les autres bits
    // pour que le BOD soit ecrit rapidement (3cylces apres __sleep() doit etre executé
    Int8U mcucr_temp;
    // Registre MCUCR sur AVR family : 48-88-168-328 et 164-324-644-1284
    // bit : 7   6       5     4   3 2    1     0
    //      JTD  BODS  BODSE  PUD  – –  IVSEL  IVCE

    // set le bit pour desactive le BOD et recherche des autrs bit a 1
    // afin de ne pas les ecraser lors de la derniere ecriture du registre
    // mcucr avant l'instruction sleep
    mcucr_temp = ( mcucr | (1U << BODS) );

    // detection des bit a 1
    //if ( mcucr_temp & (1U << JTD) )
    //{
    //  mcucr_temp |= (1U << JTD);
    //}
    //if ( mcucr_temp & (1U << PUD) )
    //{
    //  mcucr_temp |= (1U << PUD);
    //}
    //if ( mcucr_temp & (1U << IVSEL) )
    //{
    //  mcucr_temp |= (1U << IVSEL);
    //}
    //if ( mcucr_temp & (1U << IVCE) )
    //{
    //  mcucr_temp |= (1U << IVCE);
    //}
  #endif

  smcr = sleep_mode | (1U << SE);

  #ifndef DEBUG
    // procedure standard prendre trop de temps avant l'instruction sleep
    // le bod n'et pas desacté !!, donc commenter
    // mcucr |= ((1U << BODS) | (1U << BODSE));
    // mcucr = (1U << BODS);
    // mcucr &= ~(1U << BODSE);

    // donc nouvelle façon de faire
    mcucr |= ((1U << BODS) | (1U << BODSE));   // pas de contrainte de temps d'excution
    // là il faut excuter le __sleep() dans 3 cylces micro maximum
    // obligation de faire un "=" affectation directe et non "|=" d'où:
    mcucr = mcucr_temp;
  #endif

  // Note: The sleep instruction is executed before any pending interrupts.
  __enable_interrupt();
  __sleep();
  smcr &= ~(1U << SE);

  return;
}


/******************************************************************************/


/*----------------------------------------------------------------------------*/


/*******************************************************************************
***                                                                          ***
**                                                                            **
**                     GLOBAL INTERRUPT MANAGEMENT                            **
**                                                                            **
***                                                                          ***
*******************************************************************************/
/*******************************************************************************
*                                                                              *
*  Name: micEnableInterrupts                                                   *
*                                                                              *
*  Subject: Enable interrupts                                                  *
*                                                                              *
*                                                                              *
*  Input(s): None                                                              *
*                                                                              *
*  Output(s): None                                                             *
*                                                                              *
*  Modified Global variables: None                                             *
*                                                                              *
*  Necessary Interrupts: None                                                  *
*                                                                              *
*******************************************************************************/

void micEnableInterrupts(void)
{
  __enable_interrupt();
  return;
}


/*******************************************************************************
*                                                                              *
*  Name: micDisableInterrupts                                                  *
*                                                                              *
*  Subject: Enable interrupts                                                  *
*                                                                              *
*                                                                              *
*  Input(s): None                                                              *
*                                                                              *
*  Output(s): None                                                             *
*                                                                              *
*  Modified Global variables: None                                             *
*                                                                              *
*  Necessary Interrupts: None                                                  *
*                                                                              *
*******************************************************************************/

void micDisableInterrupts(void)
{
  __disable_interrupt();
  return;
}


/******************************************************************************/


/*----------------------------------------------------------------------------*/


/*******************************************************************************
***                                                                          ***
**                                                                            **
**                 TIMER(S)SYNCHRONIZATION MANAGEMENT                         **
**                                                                            **
***                                                                          ***
*******************************************************************************/

/*******************************************************************************
*                                                                              *
*  Name: micEnterTimerSynchronizationMode                                      *
*                                                                              *
*  Subject:  Enter Timers syncronization mode (Set TSM in GTCCR).              *
*            This ensures that the corresponding Timer/Counters are halted and *
*            can be configured to the same value without the risk of one of    *
*            them advancing during configuration. When the TSM bit is cleared, *
*            PSRASY(PSR2) and PSRSYNC(PSR54310) bits are cleared by hardware,  *
*            and the Timer/Counters start counting simultaneously.             *
*                                                                              *
*    micTimer0ResetClockPrescaler(), micTimer1ResetClockPrescaler() and/or     *
*    micTimer2ResetClockPrescaler() must be called following this function to  *
*    effectively stop the timer(s).                                            *
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

void micEnterTimerSynchronizationMode(void)
{
  gtccr = (1U << TSM);
  return;
}


/*******************************************************************************
*                                                                              *
*  Name: micEnterTimerSynchronizationMode                                      *
*                                                                              *
*  Subject:  Leave Timers syncronization mode (Clear TSM in GTCCR).            *
*            Once it's done, the Timer/Counters start counting simultaneously. *
*                                                                              *
*    micEnterTimerSynchronizationMode() and then ...                           *
*    micTimer0ResetClockPrescaler(), micTimer1ResetClockPrescaler() and/or     *
*    micTimer2ResetClockPrescaler() must be called prior to call this function *
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

void micLeaveTimerSynchronizationMode(void)
{
  gtccr = (0U << TSM);
  return;
}


/******************************************************************************/


/*----------------------------------------------------------------------------*/


/*******************************************************************************
***                                                                          ***
**                                                                            **
**                GENERAL PURPOSE I/O REGISTER MANAGEMENT                     **
**                                                                            **
***                                                                          ***
*******************************************************************************/

/*******************************************************************************
*                                                                              *
*  Name: micGeneralRegister2SetValue                                           *
*                                                                              *
*  Subject: Set a new value for General purpose I/O register 2 (GPIOR2)        *
*                                                                              *
*                                                                              *
*  Input(s):  value = New value for GPIOR2                                     *
*                                                                              *
*  Output(s): None                                                             *
*                                                                              *
*  Modified Global variables: None                                             *
*                                                                              *
*  Necessary Interrupts: None                                                  *
*                                                                              *
*******************************************************************************/

void micGeneralRegister2SetValue(Int8U value)
{
  gpior2 = value;
  return;
}


/*******************************************************************************
*                                                                              *
*  Name: micGeneralRegister2GetValue                                           *
*                                                                              *
*  Subject: Get value of General purpose I/O register 2 (GPIOR2)               *
*                                                                              *
*                                                                              *
*  Input(s):  None                                                             *
*                                                                              *
*  Output(s): value of GPIOR2                                                  *
*                                                                              *
*  Modified Global variables: None                                             *
*                                                                              *
*  Necessary Interrupts: None                                                  *
*                                                                              *
*******************************************************************************/

Int8U micGeneralRegister2GetValue(void)
{
  return gpior2;
}


/*******************************************************************************
*                                                                              *
*  Name: micGeneralRegister1SetValue                                           *
*                                                                              *
*  Subject: Set a new value for General purpose I/O register 1 (GPIOR1)        *
*                                                                              *
*                                                                              *
*  Input(s):  value = New value for GPIOR1                                     *
*                                                                              *
*  Output(s): None                                                             *
*                                                                              *
*  Modified Global variables: None                                             *
*                                                                              *
*  Necessary Interrupts: None                                                  *
*                                                                              *
*******************************************************************************/


void micGeneralRegister1SetValue(Int8U value)
{
  gpior1 = value;
  return;
}


/*******************************************************************************
*                                                                              *
*  Name: micGeneralRegister1GetValue                                           *
*                                                                              *
*  Subject: Get value of General purpose I/O register 1 (GPIOR1)               *
*                                                                              *
*                                                                              *
*  Input(s):  None                                                             *
*                                                                              *
*  Output(s): value of GPIOR1                                                  *
*                                                                              *
*  Modified Global variables: None                                             *
*                                                                              *
*  Necessary Interrupts: None                                                  *
*                                                                              *
*******************************************************************************/

Int8U micGeneralRegister1GetValue(void)
{
  return gpior1;
}


/*******************************************************************************
*                                                                              *
*  Name: micGeneralRegister0SetValue                                           *
*                                                                              *
*  Subject: Set a new value for General purpose I/O register 0 (GPIOR0)        *
*                                                                              *
*                                                                              *
*  Input(s):  value = New value for GPIOR0                                     *
*                                                                              *
*  Output(s): None                                                             *
*                                                                              *
*  Modified Global variables: None                                             *
*                                                                              *
*  Necessary Interrupts: None                                                  *
*                                                                              *
*******************************************************************************/

void micGeneralRegister0SetValue(Int8U value)
{
  gpior0 = value;
  return;
}


/*******************************************************************************
*                                                                              *
*  Name: micGeneralRegister1GetValue                                           *
*                                                                              *
*  Subject: Get value of General purpose I/O register 1 (GPIOR1)               *
*                                                                              *
*                                                                              *
*  Input(s):  None                                                             *
*                                                                              *
*  Output(s): value of GPIOR0                                                  *
*                                                                              *
*  Modified Global variables: None                                             *
*                                                                              *
*  Necessary Interrupts: None                                                  *
*                                                                              *
*******************************************************************************/

Int8U micGeneralRegister0GetValue(void)
{
  return gpior0;
}




/******************************************************************************/

