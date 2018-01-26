#ifndef _MIC_CPU_H_
#define _MIC_CPU_H_
/******************************************************************************/
/*                                                                            */
/* => cpu management :                                                        */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/******************************************************************************/
/*                                                                            */
/* => General commands                                                        */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*
 * => Types:
 */


//------------------------------------------------------------------------------
/*
 * => Functions:
 */

// No operation command
void micNop(void);

// Goblal Pull up enable (Clear bit  PUD)
void micGlobalPullUpsEnable(void);

// Goblal Pull up disable(Set bit PUD)
void micGlobalPullUpsDisable(void);



/******************************************************************************/
/*                                                                            */
/* => Flag reset source management                                            */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*
 * => Types:
 */

// JTAG source
#define RESET_SOURCE_JTAG  (1U << JTRF)
// Watchdog source
#define RESET_SOURCE_WATCHDOG  (1U << WDRF)
// surveilleur de tension
#define RESET_SOURCE_BROWN_OUT (1U << BORF)
// pin extern reset
#define RESET_SOURCE_EXTERNAL  (1U << EXTRF)
// retour de Vcc
#define RESET_SOURCE_POWER_ON  (1U << PORF)

typedef Int8U ResetSourceFlags;

#define ALL_RESET_SOURCE   (RESET_SOURCE_JTAG | RESET_SOURCE_WATCHDOG | RESET_SOURCE_BROWN_OUT|\
                            RESET_SOURCE_EXTERNAL | RESET_SOURCE_POWER_ON )


/******************************************************************************/
/*                                                                            */
/* => Watchdog management                                                     */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*
 * => Types:
 */

// Available watchdog clock cycles (in Kcycles) before watchdog timer overflow:
enum
{
  WDTPR_2K    = (0U << WDP3) | (0U << WDP2) | (0U << WDP1) | (0U << WDP0),
  WDTPR_4K    = (0U << WDP3) | (0U << WDP2) | (0U << WDP1) | (1U << WDP0),
  WDTPR_8K    = (0U << WDP3) | (0U << WDP2) | (1U << WDP1) | (0U << WDP0),
  WDTPR_16K   = (0U << WDP3) | (0U << WDP2) | (1U << WDP1) | (1U << WDP0),
  WDTPR_32K   = (0U << WDP3) | (1U << WDP2) | (0U << WDP1) | (0U << WDP0),
  WDTPR_64K   = (0U << WDP3) | (1U << WDP2) | (0U << WDP1) | (1U << WDP0),
  WDTPR_128K  = (0U << WDP3) | (1U << WDP2) | (1U << WDP1) | (0U << WDP0),
  WDTPR_256K  = (0U << WDP3) | (1U << WDP2) | (1U << WDP1) | (1U << WDP0),
  WDTPR_512K  = (1U << WDP3) | (0U << WDP2) | (0U << WDP1) | (0U << WDP0),
  WDTPR_1024K = (1U << WDP3) | (0U << WDP2) | (0U << WDP1) | (1U << WDP0)
};
typedef Int8U WatchdogPrescaler;

//------------------------------------------------------------------------------
/*
 * => Functions:
 */

// Set watchdog prescaler and thus start watchdog
void micSetWatchdogPrescaler( WatchdogPrescaler watchdog_prescaler );

// Stops watchdog
void micStopWatchdog(void);

// Reset watchdog to avoid a hardawre reset
void micResetWatchdog(void);

// return reset source flag
Int8U micReadResetSource(void);
// raz the reset source flag
void micRazResetSourceFlag(void);


/******************************************************************************/
/*                                                                            */
/* => CPU clock management                                                    */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*
 * => Types:
 */

// => Available CPU clock prescaler values:
enum
{
  // No division:
  CLKPR_DIV_1 = (0U << CLKPS3) | (0U << CLKPS2) | (0U << CLKPS1) | (0U << CLKPS0),
  // Division by 2:
  CLKPR_DIV_2 = (0U << CLKPS3) | (0U << CLKPS2) | (0U << CLKPS1) | (1U << CLKPS0),
  // Division by 4:
  CLKPR_DIV_4 = (0U << CLKPS3) | (0U << CLKPS2) | (1U << CLKPS1) | (0U << CLKPS0),
  // Division by 8:
  CLKPR_DIV_8 = (0U << CLKPS3) | (0U << CLKPS2) | (1U << CLKPS1) | (1U << CLKPS0),
  // Division by 16:
  CLKPR_DIV_16 = (0U << CLKPS3) | (1U << CLKPS2) | (0U << CLKPS1) | (0U << CLKPS0),
  // Division by 32:
  CLKPR_DIV_32 = (0U << CLKPS3) | (1U << CLKPS2) | (0U << CLKPS1) | (1U << CLKPS0),
  // Division by 64:
  CLKPR_DIV_64 = (0U << CLKPS3) | (1U << CLKPS2) | (1U << CLKPS1) | (0U << CLKPS0),
  // Division by 128:
  CLKPR_DIV_128 = (0U << CLKPS3) | (1U << CLKPS2) | (1U << CLKPS1) | (1U << CLKPS0),
  // Division by 256:
  CLKPR_DIV_256 = (1U << CLKPS3) | (0U << CLKPS2) | (0U << CLKPS1) | (0U << CLKPS0)
};
typedef Int8U CpuClockPrescaler;

//------------------------------------------------------------------------------
/*
 * => Functions:
 */

// Set CPU clock prescaler
void micSetCpuClockPrescaler(CpuClockPrescaler prescaler_value);
// Get CPU clock prescaler
Int8U micGetCpuClockPrescaler( void );



/******************************************************************************/
/*                                                                            */
/* => Peripherals management                                                  */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*
 * => Types:
 */
// Available Peripheral control mask to be ored
enum
{
  PERIPHERAL_TWI     = (1U << PRTWI),     // TWI periperal
  PERIPHERAL_SPI     = (1U << PRSPI),     // SPI periperal
  PERIPHERAL_ADC     = (1U << PRADC),     // ADC periperal
  PERIPHERAL_TIMER0  = (1U << PRTIM0),    // Timer 0 periperal
  PERIPHERAL_TIMER1  = (1U << PRTIM1),    // Timer 1 periperal
  PERIPHERAL_TIMER2  = (1U << PRTIM2),    // Timer 2 periperal
  PERIPHERAL_USART0  = (1U << PRUSART0),  // USART 0 periperal
  PERIPHERAL_USART1  = (1U << PRUSART1)   // USART 1 periperal
};
typedef Int8U PeripheralsFlags;
// For selecting all peripherals
#define ALL_PERIPHERALS ((1U << PRTWI) | (1U << PRSPI) | (1U << PRADC) | \
                         (1U << PRTIM0) | (1U << PRTIM1) | (1U << PRTIM2) | \
                         (1U << PRUSART0) | (1U << PRUSART1))

//  Available energy reduction modes:
//
//  - Idle = CPU sleeps but the peripherals don't
//  - ADC noise reduction = CPU sand the peripherals sleep except the ADC
//  - Power down = CPU sand the peripherals sleep
//  - Power save = CPU sand the peripherals sleep except asynchronous Timer 2
//  - Stand by = CPU sand the peripherals sleep but the oscillator remains on
enum
{
  IDLE                = (0U << SM2) | (0U << SM1) | (0U << SM0),
  ADC_NOISE_REDUCTION = (0U << SM2) | (0U << SM1) | (1U << SM0),
  POWER_DOWN          = (0U << SM2) | (1U << SM1) | (0U << SM0),
  POWER_SAVE          = (0U << SM2) | (1U << SM1) | (1U << SM0),
  STAND_BY            = (1U << SM2) | (1U << SM1) | (0U << SM0)
};
typedef Int8U SleepMode;


//------------------------------------------------------------------------------
/*
 * => Functions:
 */

// Turn Off the specified peripherals (ORed flags cf PRR register)
//   peripherals_flags = Flag for peripherals to be turned off among:
//                        PERIPHERAL_TWI for TWI periperal
//                        PERIPHERAL_SPI for SPI periperal
//                        PERIPHERAL_ADC for ADC periperal
//                        PERIPHERAL_TIMER0 for Timer 0 periperal
//                        PERIPHERAL_TIMER1 for Timer 1 periperal
//                        PERIPHERAL_TIMER2 for Timer 2 periperal
//                        PERIPHERAL_USART0 for USART 0 periperal
//                        PERIPHERAL_USART1 for USART 1 periperal
//
void micPeripheralsTurnOff(PeripheralsFlags peripherals_flags);


// Turn on the specified peripherals (ORed flags cf PRR register)
//   peripherals_flags = Flag for peripherals to be turned on among:
//                        PERIPHERAL_TWI for TWI periperal
//                        PERIPHERAL_SPI for SPI periperal
//                        PERIPHERAL_ADC for ADC periperal
//                        PERIPHERAL_TIMER0 for Timer 0 periperal
//                        PERIPHERAL_TIMER1 for Timer 1 periperal
//                        PERIPHERAL_TIMER2 for Timer 2 periperal
//                        PERIPHERAL_USART0 for USART 0 periperal
//                        PERIPHERAL_USART1 for USART 1 periperal
//
void micPeripheralsTurnOn(PeripheralsFlags peripherals_flags);

// Control the power supply of all the peripherals.
//  off_peripherals_flags = Flag for peripherals to be turned off among:
//                           PERIPHERAL_TWI for TWI periperal
//                           PERIPHERAL_SPI for SPI periperal
//                           PERIPHERAL_ADC for ADC periperal
//                           PERIPHERAL_TIMER0 for Timer 0 periperal
//                           PERIPHERAL_TIMER1 for Timer 1 periperal
//                           PERIPHERAL_TIMER2 for Timer 2 periperal
//                           PERIPHERAL_USART0 for USART 0 periperal
//                           PERIPHERAL_USART1 for USART 1 periperal
void micPeripheralsControlPower(PeripheralsFlags off_peripherals_flags);

// Read PRR register
PeripheralsFlags micPeripheralsReadControlPower( void );


// Place the CPU in energy reduction mode specified by sleep_mode
void micEnterSleepMode(SleepMode sleep_mode);



/******************************************************************************/
/*                                                                            */
/* => Global Interrupts management                                            */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*
 * => Types:
 */

// Interrupt State type (used when saving them)
typedef Int8U InterruptState;


//------------------------------------------------------------------------------
/*
 * => Functions:
 */

// Enable interrupts
void micEnableInterrupts(void);

// Disable interrupts
void micDisableInterrupts(void);


/******************************************************************************/
/*                                                                            */
/* => Timers synchronization management                                       */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*
 * => Types:
 */


//------------------------------------------------------------------------------
/*
 * => Functions:
 */

// Activate Timers syncronization mode (Set TSM in GTCCR).
// This ensures that the corresponding Timer/Counters are halted and can
// be configured to the same value without the risk of one of them advancing
// during configuration. When the TSM bit is cleared, the PSRASY(PSR2)
// and PSRSYNC bits are cleared by hardware, and the Timer/Counters start
// counting simultaneously.
// micTimer0ResetClockPrescaler(), micTimer1ResetClockPrescaler() and/or
// micTimer2ResetClockPrescaler() must be called following this function to
// effectively stop the timer(s)
void micEnterTimerSynchronizationMode(void);

// Leave Timers syncronization mode (Clea TSM in GTCCR).
// Once it's done, the Timer/Counters start counting simultaneously.
// micEnterTimerSynchronizationMode() and then ...
// micTimer0ResetClockPrescaler(), micTimer1ResetClockPrescaler() and/or
// micTimer2ResetClockPrescaler() must be called prior prior to call this
// function.
void micLeaveTimerSynchronizationMode(void);



/******************************************************************************/
/*                                                                            */
/* => Global Purpose I/O registers management                                 */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*
 * => Types:
 */


//------------------------------------------------------------------------------
/*
 * => Functions:
 */

// Set a new value for General purpose I/O register 2 (GPIOR2)
void micGeneralRegister2SetValue(Int8U value);

// Get value of General purpose I/O register 2 (GPIOR2)
Int8U micGeneralRegister2GetValue(void);

// Set a new value for General purpose I/O register 1 (GPIOR1)
void micGeneralRegister1SetValue(Int8U value);

// Get value of General purpose I/O register 1 (GPIOR1)
Int8U micGeneralRegister1GetValue(void);

// Set a new value for General purpose I/O register 0 (GPIOR0)
void micGeneralRegister0SetValue(Int8U value);

// Get value of General purpose I/O register 0 (GPIOR0)
Int8U micGeneralRegister0GetValue(void);



/******************************************************************************/
#endif  // _MIC_CPU_H_
