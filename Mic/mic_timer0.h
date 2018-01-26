#ifndef _ATMEGA164_TIMER0_H_
#define _ATMEGA164_TIMER0_H_
/******************************************************************************/
/*                                                                            */
/* => TIMER0 management                                                       */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*
 * => Types:
 */

// Minimum clock division necessary for Timer to have an overflow
// longer than 2 ms
#define SYSTEM_TIMER0_MIN_DIV (FOSC_HZ / (256UL * 2000UL))

// Timer2 clock division to  use for for the system timer
#if (SYSTEM_TIMER0_MIN_DIV > 192UL)

  #define SYSTEM_TIMER0_DIVISOR      1024UL
  #define SYSTEM_TIMER0_CLOCK_DIV    TIMER0_CLK_DIV_1024

#elif (SYSTEM_TIMER0_MIN_DIV > 96UL)

  #define SYSTEM_TIMER0_DIVISOR      256UL
  #define SYSTEM_TIMER0_CLOCK_DIV    TIMER0_CLK_DIV_256

#elif (SYSTEM_TIMER0_MIN_DIV > 32UL)

  #define SYSTEM_TIMER0_DIVISOR      64UL
  #define SYSTEM_TIMER0_CLOCK_DIV    TIMER0_CLK_DIV_64

#elif (SYSTEM_TIMER0_MIN_DIV > 1UL)

  #define SYSTEM_TIMER0_DIVISOR      8UL
  #define SYSTEM_TIMER0_CLOCK_DIV    TIMER0_CLK_DIV_8

#else

  #define SYSTEM_TIMER0_DIVISOR      1
  #define SYSTEM_TIMER0_CLOCK_DIV    TIMER0_CLK_DIV_1

#endif

// Numbers of timer 2 steps required for a 1 ms duration
#define SYSTEM_TIMER0_UT ( ( SYSTEM_TIMER0_DIVISOR * 1000000UL ) / FOSC_HZ )
#define SYSTEM_TIMER0_PERIOD ( (SYSTEM_TIMER0_UT * 256UL) / 1000UL ) // in ms

/******************************************************************************/
/*                                                                            */
/* => TIMER0 management                                                       */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*
 * => Types:
 */

// Timer 0 value type
typedef Int8U Timer0Value;


// Timer 0 compare value type
typedef Int8U Timer0CompareValue;


// Available Timer 0 clock prescaler:
// The clock source can be the  CPU oscillator Fosc or the asynchronous
// timer oscillator (Tosc)
enum
{
  // Timer clock = stopped
  TIMER0_NO_CLOCK =     ((0U << CS02) | (0U << CS01) | (0U << CS00)),
  // Timer clock = Fosc
  TIMER0_CLK_DIV_1 =    ((0U << CS02) | (0U << CS01) | (1U << CS00)),
  // Timer clock = Fosc / 8
  TIMER0_CLK_DIV_8 =    ((0U << CS02) | (1U << CS01) | (0U << CS00)),
  // Timer clock = Fosc / 64
  TIMER0_CLK_DIV_64 =   ((0U << CS02) | (1U << CS01) | (1U << CS00)),
  // Timer clock = Fosc / 256
  TIMER0_CLK_DIV_256 =   ((1U << CS02) | (0U << CS01) | (0U << CS00)),
  // Timer clock = Fosc / 1024
  TIMER0_CLK_DIV_1024 =  ((1U << CS02) | (0U << CS01) | (1U << CS00)),
  // Timer clock = Falling edge of Timer 0 external clock input T0
  TIMER0_CLK_T0_FALLING =  ((1U << CS02) | (1U << CS01) | (0U << CS00)),
  // Timer clock = Rising edge of Timer 0 external clock input T0
  TIMER0_CLK_T0_RISING = ((1U << CS02) | (1U << CS01) | (1U << CS00))
};
typedef Int8U Timer0Clock;


// Available Timer 0 Force Compare
enum
{
  // Timer Force compare for unit A
  TIMER0_FORCE_COMPARE_A = (1U << FOC0A),
  // Timer Force compare for unit B
  TIMER0_FORCE_COMPARE_B = (1U << FOC0B)
};
typedef Int8U Timer0ForceCompare;


// Available modes for Timer 0 waveform generator
enum
{
  // Normal output compare mode
  TIMER0_NORMAL_COMPARE = ((0U << WGM02) | (0U << WGM01) | (0U << WGM00)),
  // Phase correct PWM with top at 255
  TIMER0_PHASE_PWM_TOP_255 = ((0U << WGM02) | (0U << WGM01) | (1U << WGM00)),
  // Clear timer on compare match with OCR0A
  TIMER0_CLEAR_ON_COMPARE = ((0U << WGM02) | (1U << WGM01) | (0U << WGM00)),
  // Fast PWM with top at 255
  TIMER0_FAST_PWM_TOP_255 = ((0U << WGM02) | (1U << WGM01) | (1U << WGM00)),
  // Phase correct PWM with top at OCR0A
  TIMER0_PHASE_PWM_TOP_OCRA = ((1U << WGM02) | (0U << WGM01) | (1U << WGM00)),
  // Phase correct with top at OCR0A
  TIMER0_FAST_PWM_TOP_OCRA = ((1U << WGM02) | (1U << WGM01) | (1U << WGM00))
};
typedef Int8U Timer0GeneratorMode;


// Available Timer 0 output A (OC0A pin) behavior on compare match
enum
{
  // Normal port output (OC0A disconnected from the port pin)
  TIMER0_OUTPUT_A_DISCONNECTED = ((0U << COM0A1) | (0U << COM0A0)),
  // Toggle OC0A on compare match mode
  TIMER0_OUTPUT_A_TOGGLE = ((0U << COM0A1) | (1U << COM0A0)),
  // Clear OC0A on compare match mode
  TIMER0_OUTPUT_A_CLEAR = ((1U << COM0A1) | (0U << COM0A0)),
  // Set OC0A on compare match mode
  TIMER0_OUTPUT_A_SET = ((1U << COM0A1) | (1U << COM0A0))
};
typedef Int8U Timer0OutputBehaviorA;
// In PWM  modes with top at OCR0xA
// Alternative normal port output (OC0A disconnected from the port pin)
#define TIMER0_PWM_OUTPUT_DISCONNECTED   TIMER0_OUTPUT_TOGGLE

// Available Timer 0 output B (OC0B pin) behavior on compare match
enum
{
  // Normal port output (OC0B disconnected from the port pin)
  TIMER0_OUTPUT_B_DISCONNECTED = ((0U << COM0B1) | (0U << COM0B0)),
  // Toggle OC0A on compare mode:
  // Reserved: Do not use in PWM modes (fast and phase correct)
  TIMER0_OUTPUT_B_TOGGLE = ((0U << COM0B1) | (1U << COM0B0)),
  // Clear OC0A on compare match mode
  TIMER0_OUTPUT_B_CLEAR = ((1U << COM0A1) | (0U << COM0B0)),
  // Set OC0A on compare match mode
  TIMER0_OUTPUT_B_SET = ((1U << COM0B1) | (1U << COM0B0))
};
typedef Int8U Timer0OutputBehaviorB;


// Available maskable interrupts for TIMER0 (in timsk0)
enum
{
  TIMER0_COMPARE_B_INTERRUPT = (1U << OCIE0B),
  TIMER0_COMPARE_A_INTERRUPT = (1U << OCIE0A),
  TIMER0_OVERFLOW_INTERRUPT = (1U << TOIE0)
};
typedef Int8U Timer0Interrupts;


// Available Flags for TIMER0 interrupts (in tifr0)
enum
{
  TIMER0_COMPARE_B_FLAG = (1U << OCF0B),
  TIMER0_COMPARE_A_FLAG = (1U << OCF0A),
  TIMER0_OVERFLOW_FLAG = (1U << TOV0)
};
typedef Int8U Timer0Flags;



//------------------------------------------------------------------------------
/*
 * => Functions:
 */

// Set a new value for timer 0

void micTimer0SetValue(Timer0Value timer_value);

// Get current value of timer 0
//
Timer0Value micTimer0GetValue(void);

// Set a new compare value for compare unit A of timer 0

void micTimer0SetCompareValueA(Timer0CompareValue compare_value);

// Get compare value for timer 0 compare unit A

Timer0CompareValue micTimer0GetCompareValueA(void);

// Set a new compare value for compare unit B of timer 0

void micTimer0SetCompareValueB(Timer0CompareValue compare_value);

// Get compare value for timer 0 compare unit B

Timer0CompareValue micTimer0GetCompareValueB(void);

// Select clock source for timer 0
// timer_clock = TIMER0_NO_CLOCK: Timer clock stopped
//               TIMER0_CLK_DIV_1: Timer clock = Fosc
//               TIMER0_CLK_DIV_8: Timer clock = Fosc / 8
//               TIMER0_CLK_DIV_64: Timer clock = Fosc / 64
//               TIMER0_CLK_DIV_256: Timer clock = Fosc / 256
//               TIMER0_CLK_DIV_1024: Timer clock = Fosc / 1024
//               TIMER0_CLK_T0_FALLING: Timer clock = T0 falling edge
//               TIMER0_CLK_T0_RISING: Timer clock = T0 rising edge

void micTimer0SetClockDivision(Timer0Clock clock_div);

// Set timer 0 waveform generator mode
// generator_mode = TIMER0_NORMAL_COMPARE: Normal compare mode
//                  TIMER0_CLEAR_ON_COMPARE: Clear timer on compare match
//                  TIMER0_PHASE_PWM_TOP_255: Fast PWM with top at 255
//                  TIMER0_FAST_PWM_TOP_255: Phase correct PWM with top at 255
//                  TIMER0_PHASE_PWM_TOP_OCRA: Phase correct PWM with OCR0A top
//                  TIMER0_FAST_PWM_TOP_OCRA: Fast PWM with top at OCR0A

void micTimer0SetGeneratorMode(Timer0GeneratorMode generator_mode);

// Set timer 0 output behavior for unit A (depending on generator mode)
// compare_behavior =  TIMER0_OUTPUT_A_DISCONNECTED = Normal port output
//                     TIMER0_OUTPUT_A_TOGGLE = Toggle OC0A on compare mode
//                     TIMER0_OUTPUT_A_CLEAR = Clear OC0A on compare mode
//                     TIMER0_OUTPUT_A_SET = Set OC0A ont compare mode

void micTimer0SetOutputBehaviorA(Timer0OutputBehaviorA compare_behavior);

// Set timer 0 output behavior for unit B (depending on generator mode)
// compare_behavior =  TIMER0_OUTPUT_B_DISCONNECTED = Normal port output
//                     TIMER0_OUTPUT_B_TOGGLE = Toggle OC0B on compare mode
//                     TIMER0_OUTPUT_B_CLEAR = Clear OC0B on compare mode
//                     TIMER0_OUTPUT_B_SET = Set OC0B ont compare mode

void micTimer0SetOutputBehaviorB(Timer0OutputBehaviorB compare_behavior);

// Force an ouput compare for the indicated unit(s) of timer 0:
//   compare_unit = TIMER0_FORCE_COMPARE_A to force Compare unit A
//                  TIMER0_FORCE_COMPARE_B to force Compare unit B

void micTimer0ForceCompare(Timer0ForceCompare compare_unit);

// Unmask TIMER 0 selected compare A, compare B and overflow interrupts (ored).
// interrupts = TIMER0_COMPARE_B_INTERRUPT, TIMER0_COMPARE_A_INTERRUPT
//              or TIMER0_OVERFLOW_INTERRUPT.

void micTimer0UnmaskInterrupts(Timer0Interrupts interrupts);

// Mask TIMER 0 selected compare A, compare B and overflow interrupts (ored).
// interrupts = TIMER0_COMPARE_B_INTERRUPT, TIMER0_COMPARE_A_INTERRUPT
//              or TIMER0_OVERFLOW_INTERRUPT.

void micTimer0MaskInterrupts(Timer0Interrupts interrupts);

// Save Timer 0 interrupts current state.
// Return current state of timer 0 interrupts

Timer0Interrupts micTimer0SaveInterrupts(void);

// Restore Timer 0 interrupts state
// interrupt_state = Timer 0 interrupts to restore

void micTimer0RestoreInterrupts(Timer0Interrupts interrupt_state);

// Clear selected TIMER 0 interrupt flags
// interrupt_flags = TIMER0_COMPARE_B_FLAG: compare match on unit B
//                   TIMER0_COMPARE_A_FLAG: compare match on unit A
//                   TIMER0_OVERFLOW_FLAG: overflow of timer 0

void micTimer0ClearInterruptFlags(Timer0Flags interrupt_flags);

// Reset Timer0 prescaler (Set  PSR54310 alias PSRSYNC)
// Beware that PSRSYNC bit will not be cleared by hardware if TSM bit in GTCCR
// is set (Cf mic_cpu).

void micTimer0ResetClockPrescaler(void);

// Fonction permettant d'assigné la fonction a appeler lors d'une interruption compA                                                 *
// i_p_callback: Adresse de la fonction a appeler
void micTimer0SetCompACallback( p_isr_callback i_p_callback );

/******************************************************************************/
#endif  // _ATMEGA164_TIMER0_H_
