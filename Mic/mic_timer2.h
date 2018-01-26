#ifndef _ATMEGA164_TIMER2_H_
#define _ATMEGA164_TIMER2_H_
/******************************************************************************/
/*                                                                            */
/* => TIMER2 management                                                       */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*
 * => Types:
 */

// Timer 2 value type
typedef Int8U Timer2Value;


// Timer 2 compare value type
typedef Int8U Timer2CompareValue;


// Available Timer 2 clock prescaler:
// The clock source can be the  CPU oscillator Fosc or the asynchronous
// timer oscillator (Tosc)
enum
{
  // Timer clock = stopped
  TIMER2_NO_CLOCK =     ((0U << CS22) | (0U << CS21) | (0U << CS20)),
  // Timer clock = Fosc
  TIMER2_CLK_DIV_1 =    ((0U << CS22) | (0U << CS21) | (1U << CS20)),
  // Timer clock = Fosc / 8
  TIMER2_CLK_DIV_8 =    ((0U << CS22) | (1U << CS21) | (0U << CS20)),
  // Timer clock = Fosc / 32
  TIMER2_CLK_DIV_32 =   ((0U << CS22) | (1U << CS21) | (1U << CS20)),
  // Timer clock = Fosc / 64
  TIMER2_CLK_DIV_64 =   ((1U << CS22) | (0U << CS21) | (0U << CS20)),
  // Timer clock = Fosc / 128
  TIMER2_CLK_DIV_128 =  ((1U << CS22) | (0U << CS21) | (1U << CS20)),
  // Timer clock = Fosc / 256
  TIMER2_CLK_DIV_256 =  ((1U << CS22) | (1U << CS21) | (0U << CS20)),
  // Timer clock = Fosc / 1024
  TIMER2_CLK_DIV_1024 = ((1U << CS22) | (1U << CS21) | (1U << CS20))
};
typedef Int8U Timer2Clock;


// Available Timer 2 Force Compare
enum
{
  // Timer Force compare for unit A
  TIMER2_FORCE_COMPARE_A = (1U << FOC2A),
  // Timer Force compare for unit B
  TIMER2_FORCE_COMPARE_B = (1U << FOC2B)
};
typedef Int8U Timer2ForceCompare;


// Available modes for Timer 2 waveform generator
enum
{
  // Normal output compare mode
  TIMER2_NORMAL_COMPARE = ((0U << WGM22) | (0U << WGM21) | (0U << WGM20)),
  // Clear timer on compare match with OCR2A
  TIMER2_CLEAR_ON_COMPARE = ((0U << WGM22) | (1U << WGM21) | (0U << WGM20)),
  // Phase correct PWM with top at 255
  TIMER2_PWM_TOP_255 = ((0U << WGM22) | (0U << WGM21) | (1U << WGM20)),
  // Phase correct PWM with top at OCR2A
  TIMER2_PWM_TOP_OCRA = ((1U << WGM22) | (0U << WGM21) | (1U << WGM20)),
  // Fast PWM with top at 255
  TIMER2_FAST_PWM_TOP_255 = ((0U << WGM22) | (1U << WGM21) | (1U << WGM20)),
  // Phase correct with top at OCR2A
  TIMER2_FAST_PWM_TOP_OCRA = ((1U << WGM22) | (1U << WGM21) | (1U << WGM20))
};
typedef Int8U Timer2GeneratorMode;


// Available Timer 2 output A (OC2A pin) behavior onr compare match
enum
{
  // Normal port output (OC2A disconnected from the port pin)
  TIMER2_OUTPUT_A_DISCONNECTED = ((0U << COM2A1) | (0U << COM2A0)),
  // Toggle OC2A on compare match mode
  TIMER2_OUTPUT_A_TOGGLE = ((0U << COM2A1) | (1U << COM2A0)),
  // Clear OC2A on compare match mode
  TIMER2_OUTPUT_A_CLEAR = ((1U << COM2A1) | (0U << COM2A0)),
  // Set OC2A on compare match mode
  TIMER2_OUTPUT_A_SET = ((1U << COM2A1) | (1U << COM2A0))
};
typedef Int8U Timer2OutputBehaviorA;
// In PWM  modes with top at OCR2A:
// Alternative normal port output (OC2A disconnected from the port pin)
#define TIMER2_PWM_OUTPUT_DISCONNECTED   TIMER2_OUTPUT_TOGGLE

// Available Timer 2 output B (OC2B pin) behavior on compare match
enum
{
  // Normal port output OC2B disconnected from the port pin
  TIMER2_OUTPUT_B_DISCONNECTED = ((0U << COM2B1) | (0U << COM2B0)),
  // Toggle OC2A on compare match mode:
  // Reserved: Do not use in PWM modes (fast and phase correct)
  TIMER2_OUTPUT_B_TOGGLE = ((0U << COM2B1) | (1U << COM2B0)),
  // Clear OC2A on compare match mode
  TIMER2_OUTPUT_B_CLEAR = ((1U << COM2A1) | (0U << COM2B0)),
  // Set OC2A on compare match mode
  TIMER2_OUTPUT_B_SET = ((1U << COM2B1) | (1U << COM2B0))
};
typedef Int8U Timer2OutputBehaviorB;


// Available maskable interrupts for TIMER2 (in timsk2)
enum
{
  TIMER2_COMPARE_B_INTERRUPT = (1U << OCIE2B),
  TIMER2_COMPARE_A_INTERRUPT = (1U << OCIE2A),
  TIMER2_OVERFLOW_INTERRUPT = (1U << TOIE2)
};
typedef Int8U Timer2Interrupts;


// Available Flags for TIMER2 interrupts (in tifr2)
enum
{
  TIMER2_COMPARE_B_FLAG = (1U << OCF2B),
  TIMER2_COMPARE_A_FLAG = (1U << OCF2A),
  TIMER2_OVERFLOW_FLAG = (1U << TOV2)
};
typedef Int8U Timer2Flags;




// In asynchronous mode, these flags indicate that timer 2 is busy updating
// one of its registers:
// TCNT2, OCR2A, OCR2B, TCCR2A or TCCR2B (a bit 1 means busy)
enum
{
  // Timer/Counter register is being updated
  TIMER2_TCNT_BUSY_FLAG = (1U << TCN2UB),
  // Compare A register is being updated
  TIMER2_OCRA_BUSY_FLAG = (1U << OCR2AUB),
  // Compare B register is being updated
  TIMER2_OCRB_BUSY_FLAG = (1U << OCR2BUB),
  // Control A register is being updated
  TIMER2_TCRA_BUSY_FLAG = (1U << TCR2AUB),
  // Control B register is being updated
  TIMER2_TCRB_BUSY_FLAG = (1U << TCR2BUB)
};
typedef Int8U Timer2UpdateBusyFlags;



//------------------------------------------------------------------------------
/*
 * => Functions:
 */

// Set a new value for timer 2

void micTimer2SetValue(Timer2Value timer_value);

// Get current value of timer 2
//
Timer2Value micTimer2GetValue(void);

// Set a new compare value for compare unit A of timer 2
//
void micTimer2SetCompareValueA(Timer2CompareValue compare_value);

// Get compare value for timer 2 compare unit A
//
Timer2CompareValue micTimer2GetCompareValueA(void);

// Set a new compare value for compare unit B of timer 2

void micTimer2SetCompareValueB(Timer2CompareValue compare_value);

// Get compare value for timer 2 compare unit B

Timer2CompareValue micTimer2GetCompareValueB(void);

// Select  synchronous clock source from Timer 2 prescaler
//
void micTimer2SetClockDivision(Timer2Clock clock_div);

// Set timer 2 wave form generator mode
// generator_mode = TIMER2_NORMAL_COMPARE: Normal compare mode
//                  TIMER2_CLEAR_ON_COMPARE: Clear timer on compare match
//                  TIMER2_PHASE_PWM_TOP_255: Fast PWM with top at 255
//                  TIMER2_FAST_PWM_TOP_255: Phase correct PWM with top at 255
//                  TIMER2_PHASE_PWM_TOP_OCRA: Phase correct PWM with OCR2A top
//                  TIMER2_FAST_PWM_TOP_OCRA: Fast PWM with top at OCR2A
//
void micTimer2GeneratorMode(Timer2GeneratorMode generator_mode);

// read teh generator mode
Int8U micTimer2GetGeneratorMode( void );

// Set Timer 2 output behavior for unit A (depending on generator mode)
// compare_behavior =  TIMER2_OUTPUT_A_DISCONNECTED = Normal port output
//                     TIMER2_OUTPUT_A_TOGGLE = Toggle OC2A on compare mode
//                     TIMER2_OUTPUT_A_CLEAR = Clear OC2A on compare mode
//                     TIMER2_OUTPUT_A_SET = Set OC2A ont compare mode
//
void micTimer2SetOutputBehaviorA(Timer2OutputBehaviorA compare_behavior);

// Set Timer 2 output behavior for unit B (depending on generator mode)
// compare_behavior =  TIMER2_OUTPUT_B_DISCONNECTED = Normal port output
//                     TIMER2_OUTPUT_B_TOGGLE = Toggle OC2B on compare mode
//                     TIMER2_OUTPUT_B_CLEAR = Clear OC2B on compare mode
//                     TIMER2_OUTPUT_B_SET = Set OC2B ont compare mode

void micTimer2SetOutputBehaviorB(Timer2OutputBehaviorB compare_behavior);

// Force an ouput compare for the indicated unit(s) of timer 2:
//   compare_unit = TIMER2_FORCE_COMPARE_A to force Compare unit A
//                  TIMER2_FORCE_COMPARE_B to force Compare unit B
//
void micTimer2ForceCompare(Timer2ForceCompare compare_unit);

// Unmask TIMER2 selected compare A, compare B and overflow interrupts.
// Ored mask forbits: TIMER2_COMPARE_B_INTERRUPT, TIMER2_COMPARE_A_INTERRUPT
// or TIMER2_OVERFLOW_INTERRUPT.
//
void micTimer2UnmaskInterrupts(Timer2Interrupts interrupts);

// Mask TIMER2 selected compare A, compare B and overflow interrupts.
// Ored mask forbits: TIMER2_COMPARE_B_INTERRUPT, TIMER2_COMPARE_A_INTERRUPT
// or TIMER2_OVERFLOW_INTERRUPT.
//
void micTimer2MaskInterrupts(Timer2Interrupts interrupts);

// Save Timer 2 interrupts current state.
// Return current state of timer2 interrupts

Timer2Interrupts micTimer2SaveInterrupts(void);

// Restore Timer2 interrupts state
// interrupt_state = Timer 2 interrupts to restore

void micTimer2RestoreInterrupts(Timer2Interrupts interrupt_state);

// Clear selected TIMER 2 interrupt flags
// interrupt_flags = TIMER2_COMPARE_B_FLAG: compare match on unit B
//                   TIMER2_COMPARE_A_FLAG: compare match on unit A
//                   TIMER2_OVERFLOW_FLAG: overflow of timer 2
//
void micTimer2ClearInterruptFlags(Timer2Flags interrupt_flags);

// read IT_timer2 flag
Timer2Flags micTimer2ReadInterruptFlags( void );


// Enable external clock source buffer for Timer 2 (set EXCLK)
// Must be done before asynchronous operation is selected

void micTimer2EnableExternalClock(void);

// Disable external clock source buffer for Timer 2 (clear EXCLK)
void micTimer2DisableExternalClock(void);

Int8U micTimer2ReadExternalClock(void);

// Set Timer into asynchronous operation by selecting external clock
// as source (set AS2)
// micTimer2EnableExternalClock() must be called prior to call this function

void micTimer2SelectExternalClock(void);

// Set Timer into synchronous operation by selecting internal clock(clear AS2)

void micTimer2SelectInternalClock(void);

// Get flags indicating if timer 2 in asynchronous mode is busy updating one
// of its registers:
// TCNT2, OCR2A, OCR2B, TCCR2A or TCCR2B (a bit 1 means busy)

Timer2UpdateBusyFlags micTimer2GetUpdateBusyFlags(void);

// Reset Timer2 prescaler (Set PSRASY alias PSR2)
// Beware that PSRASY bit will not be cleared by hardware if TSM bit in GTCCR is
// set (Cf mic_cpu).

void micTimer2ResetClockPrescaler(void);



/******************************************************************************/
#endif  // _ATMEGA164_TIMER2_H_
