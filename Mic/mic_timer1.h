#ifndef _ATMEGA164_TIMER1_H_
#define _ATMEGA164_TIMER1_H_
/******************************************************************************/
/*                                                                            */
/* => TIMER1 management                                                       */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*
 * => Types:
 */

// Timer 1 value type
typedef Int16U Timer1Value;


// Timer 1 compare value type
typedef Int16U Timer1CompareValue;


// Timer 1 capture value type
typedef Int16U Timer1CaptureValue;


// Available Timer 1 clock prescaler:
// The clock source can be the  CPU oscillator Fosc or the asynchronous
// timer oscillator (Tosc)
enum
{
  // Timer clock = stopped
  TIMER1_NO_CLOCK =     ((0U << CS12) | (0U << CS11) | (0U << CS10)),
  // Timer clock = Fosc
  TIMER1_CLK_DIV_1 =    ((0U << CS12) | (0U << CS11) | (1U << CS10)),
  // Timer clock = Fosc / 8
  TIMER1_CLK_DIV_8 =    ((0U << CS12) | (1U << CS11) | (0U << CS10)),
  // Timer clock = Fosc / 64
  TIMER1_CLK_DIV_64 =   ((0U << CS12) | (1U << CS11) | (1U << CS10)),
  // Timer clock = Fosc / 256
  TIMER1_CLK_DIV_256 =   ((1U << CS12) | (0U << CS11) | (0U << CS10)),
  // Timer clock = Fosc / 1024
  TIMER1_CLK_DIV_1024 =  ((1U << CS12) | (0U << CS11) | (1U << CS10)),
  // Timer clock = Falling edge of Timer 1 external clock input T1
  TIMER1_CLK_T1_FALLING =  ((1U << CS12) | (1U << CS11) | (0U << CS10)),
  // Timer clock = Rising edge of Timer 1 external clock input T1
  TIMER1_CLK_T1_RISING = ((1U << CS12) | (1U << CS11) | (1U << CS10))
};
typedef Int8U Timer1Clock;


// Available Timer 1 Force Compare
enum
{
  // Timer Force compare for unit A
  TIMER1_FORCE_COMPARE_A = (1U << FOC1A),
  // Timer Force compare for unit B
  TIMER1_FORCE_COMPARE_B = (1U << FOC1B)
};
typedef Int8U Timer1ForceCompare;


// Available modes for Timer 1 waveform generator
enum
{
  // Normal output compare mode (top = 0xFFFF)
  TIMER1_NORMAL_COMPARE = ((0U << WGM13) | (0U << WGM12) |
                           (0U << WGM11) | (0U << WGM10)),

  // Phase correct PWM 8 bit with top at 0xFF
  TIMER1_PHASE_PWM_TOP_255 = ((0U << WGM13) | (0U << WGM12) |
                              (0U << WGM11) | (1U << WGM10)),
  // Phase correct PWM 9 bit with top at 0x1FF
  TIMER1_PHASE_PWM_TOP_511 = ((0U << WGM13) | (0U << WGM12) |
                              (1U << WGM11) | (0U << WGM10)),
  // Phase correct PWM 10 bit with top at 0x3FF
  TIMER1_PHASE_PWM_TOP_1023 = ((0U << WGM13) | (0U << WGM12) |
                               (1U << WGM11) | (1U << WGM10)),

  // Clear timer on compare match with OCR1A
  TIMER1_CLEAR_ON_COMPARE_OCRA = ((0U << WGM13) | (1U << WGM12) |
                                 (0U << WGM11) | (0U << WGM10)),
  // Clear timer on compare match with ICR1
  TIMER1_CLEAR_ON_COMPARE_ICR = ((1U << WGM13) | (1U << WGM12) |
                                  (0U << WGM11) | (0U << WGM10)),

  // Fast PWM 8 bits with top at 0xFF
  TIMER1_FAST_PWM_TOP_255 = ((0U << WGM13) | (1U << WGM12) |
                             (0U << WGM11) | (1U << WGM10)),
  // Fast PWM 9 bits with top at 0x1FF
  TIMER1_FAST_PWM_TOP_511 = ((0U << WGM13) | (1U << WGM12) |
                             (1U << WGM11) | (0U << WGM10)),
  // Fast PWM 10 bits with top at 0x3FF
  TIMER1_FAST_PWM_TOP_1023 = ((0U << WGM13) | (1U << WGM12) |
                              (1U << WGM11) | (1U << WGM10)),

  // Frequency correct PWM  with top at ICR1
  TIMER1_FREQUENCY_PWM_TOP_ICR = ((1U << WGM13) | (0U << WGM12) |
                                  (0U << WGM11) | (0U << WGM10)),
  // Frequency correct PWM  with top at 0CR1A
  TIMER1_FREQUENCY_PWM_TOP_OCRA = ((1U << WGM13) | (0U << WGM12) |
                                   (0U << WGM11) | (1U << WGM10)),

  // Phase correct PWM with top at ICR1
  TIMER1_PHASE_PWM_TOP_ICR = ((1U << WGM13) | (0U << WGM12) |
                              (1U << WGM11) | (0U << WGM10)),
   // Phase correct PWM with top at OCR1A
  TIMER1_PHASE_PWM_TOP_OCRA = ((1U << WGM13) | (0U << WGM12) |
                               (1U << WGM11) | (1U << WGM10)),

  // Fast PWM with top at ICR1
  TIMER1_FAST_PWM_TOP_ICR = ((1U << WGM13) | (1U << WGM12) |
                             (1U << WGM11) | (0U << WGM10)),
  // Fast PWM with top at OCR1A
  TIMER1_FAST_PWM_TOP_OCRA = ((1U << WGM13) | (1U << WGM12) |
                              (1U << WGM11) | (1U << WGM10))
};
typedef Int8U Timer1GeneratorMode;

// used to read current compare behaviour A and B at the time
typedef Int8U Timer1OutputBehavior;

// Available Timer 1 output A (OC1A pin) behavior for compare match
enum
{
  // Normal port output (OC1A disconnected from the port pin)
  TIMER1_OUTPUT_A_DISCONNECTED = ((0U << COM1A1) | (0U << COM1A0)),
  // Toggle OC1A on compare match mode
  TIMER1_OUTPUT_A_TOGGLE = ((0U << COM1A1) | (1U << COM1A0)),
  // Clear OC1A on compare match mode
  TIMER1_OUTPUT_A_CLEAR = ((1U << COM1A1) | (0U << COM1A0)),
  // Set OC1A on compare match mode
  TIMER1_OUTPUT_A_SET = ((1U << COM1A1) | (1U << COM1A0))
};
typedef Int8U Timer1OutputBehaviorA;
// In PWM  modes with top at OCR1A:
// Alternative normal port output (OC1A disconnected from the port pin)
#define TIMER1_PWM_OUTPUT_DISCONNECTED   TIMER1_OUTPUT_TOGGLE

// Available Timer 1 output B (OC1B pin) behavior for compare match
enum
{
  // Normal port output OC1B disconnected from the port pin
  TIMER1_OUTPUT_B_DISCONNECTED = ((0U << COM1B1) | (0U << COM1B0)),
  // Toggle OC1BA on compare match mode:
  // Reserved: Do not use in PWM modes (fast and phase correct)
  TIMER1_OUTPUT_B_TOGGLE = ((0U << COM1B1) | (1U << COM1B0)),
  // Clear OC1B on compare match mode
  TIMER1_OUTPUT_B_CLEAR = ((1U << COM1B1) | (0U << COM1B0)),
  // Set OC1B on compare match mode
  TIMER1_OUTPUT_B_SET = ((1U << COM1B1) | (1U << COM1B0))
};
typedef Int8U Timer1OutputBehaviorB;


// Available maskable interrupts for Timer 1 (in timsk1)
enum
{
  TIMER1_CAPTURE_INTERRUPT = (1U << ICIE1),
  TIMER1_COMPARE_B_INTERRUPT = (1U << OCIE1B),
  TIMER1_COMPARE_A_INTERRUPT = (1U << OCIE1A),
  TIMER1_OVERFLOW_INTERRUPT = (1U << TOIE1)
};
typedef Int8U Timer1Interrupts;


// Available Flags for Timer 1 interrupts (in tifr1)
enum
{
  TIMER1_CAPTURE_FLAG = (1U << ICF1),
  TIMER1_COMPARE_B_FLAG = (1U << OCF1B),
  TIMER1_COMPARE_A_FLAG = (1U << OCF1A),
  TIMER1_OVERFLOW_FLAG = (1U << TOV1)
};
typedef Int8U Timer1Flags;



//------------------------------------------------------------------------------
/*
 * => Functions:
 */

// Set a new value for timer 1
//
void micTimer1SetValue(Timer1Value timer_value);

// Get current value of timer 1
//
Timer1Value micTimer1GetValue(void);

// Set a new compare value for compare unit A of timer 1
//
void micTimer1SetCompareValueA(Timer1CompareValue compare_value);

// Get compare value for timer 1 compare unit A
//
Timer1CompareValue micTimer1GetCompareValueA(void);

// Set a new compare value for compare unit B of timer 1
//
void micTimer1SetCompareValueB(Timer1CompareValue compare_value);

// Get compare value for timer 1 compare unit B
//
Timer1CompareValue micTimer1GetCompareValueB(void);

// Set a new capture value for capture unit of timer 1
//
void micTimer1SetCaptureValue(Timer1CaptureValue icr_value);

// Get last captured value of timer 1
//
Timer1CaptureValue micTimer1GetCaptureValue(void);

// Select Clock source for timer 1
// timer_clock = TIMER1_NO_CLOCK: Timer clock stopped
//               TIMER1_CLK_DIV_1: Timer clock = Fosc
//               TIMER1_CLK_DIV_8: Timer clock = Fosc / 8
//               TIMER1_CLK_DIV_64: Timer clock = Fosc / 64
//               TIMER1_CLK_DIV_256: Timer clock = Fosc / 256
//               TIMER1_CLK_DIV_1024: Timer clock = Fosc / 1024
//               TIMER1_CLK_T1_FALLING: Timer clock = T1 falling edge
//               TIMER1_CLK_T1_RISING: Timer clock = T1 rising edge
//
void micTimer1SetClockDivision(Timer1Clock clock_div);

// Set Timer 1 wave form generator mode
// generator_mode = TIMER1_NORMAL_COMPARE: Normal compare mode
//                  TIMER1_CLEAR_ON_COMPARE: Clear timer on compare match
//                  TIMER1_PHASE_PWM_TOP_255: Fast PWM with top at 0xFF
//                  TIMER1_FAST_PWM_TOP_255: Phase correct PWM with top at 255
//                  TIMER1_PHASE_PWM_TOP_OCRA: Phase correct PWM with OCR1A top
//                  TIMER1_FAST_PWM_TOP_OCRA: Fast PWM with top at OCR1A
//
void micTimer1SetGeneratorMode(Timer1GeneratorMode generator_mode);

// Get current timer 1 output behavior A and B
Timer1OutputBehavior micTimer1GetOutputBehavior( void );


// Set Timer 1 output behavior for unit A (depending on generator mode)
// compare_behavior =  TIMER1_OUTPUT_A_DISCONNECTED = Normal port output
//                     TIMER1_OUTPUT_A_TOGGLE = Toggle OC1A on compare mode
//                     TIMER1_OUTPUT_A_CLEAR = Clear OC1A on compare mode
//                     TIMER1_OUTPUT_A_SET = Set OC1A ont compare mode
//
void micTimer1SetOutputBehaviorA(Timer1OutputBehaviorA compare_behavior);

// Set Timer 1 output behavior for unit B (depending on generator mode)
// compare_behavior =  TIMER1_OUTPUT_B_DISCONNECTED = Normal port output
//                     TIMER1_OUTPUT_B_TOGGLE = Toggle OC1B on compare mode
//                     TIMER1_OUTPUT_B_CLEAR = Clear OC1B on compare mode
//                     TIMER1_OUTPUT_B_SET = Set OC1B on compare mode
//
void micTimer1SetOutputBehaviorB(Timer1OutputBehaviorB compare_behavior);

// Force an ouput compare for the indicated unit(s) of timer 1:
//   compare_unit = TIMER1_FORCE_COMPARE_A to force Compare unit A
//                  TIMER1_FORCE_COMPARE_B to force Compare unit B
//
void micTimer1ForceCompare(Timer1ForceCompare compare_unit);

// Unmask TIMER 1 selected compare A, compare B and overflow interrupts.
// Ored mask forbits: TIMER1_COMPARE_B_INTERRUPT, TIMER1_COMPARE_A_INTERRUPT
// or TIMER1_OVERFLOW_INTERRUPT.
//
void micTimer1UnMaskInterrupts(Timer1Interrupts interrupts);

// Mask Timer 1 selected compare A, compare B and overflow interrupts.
// Ored mask forbits: TIMER1_COMPARE_B_INTERRUPT, TIMER1_COMPARE_A_INTERRUPT
// or TIMER1_OVERFLOW_INTERRUPT.
//
void micTimer1MaskInterrupts(Timer1Interrupts interrupts);

// Save Timer 1 interrupts current state.
// Return current state of timer 1 interrupts
//
Timer1Interrupts micTimer1SaveInterrupts(void);

// Restore Timer 1 interrupts state
// interrupt_state = Timer 1 interrupts to restore
//
void micTimer1RestoreInterrupts(Timer1Interrupts interrupt_state);

// Clear selected Timer 1 interrupt(s) flags
//
void micTimer1ClearInterruptFlags(Timer1Flags interrupt_flags);

// read selected Timer 1 interrupt(s) flags
//
Timer1Flags micTimer1ReadInterruptFlags( void );

// Reset Timer 1 prescaler (Set  PSR54310 alias PSRSYNC)
// Beware that PSR54310 bit will not be cleared by hardware if TSM bit in GTCCR
// is set. In this case this bit should be cleared manually.
// Same function as micTimer1ResetClockPrescaler();
//
void micTimer1ResetClockPrescaler(void);


// Activate the input capture noise canceller (set ICNC1)
void micTimer1ActivateInputNoiseCanceller(void);

// Deactivate the input capture noise canceller (clear ICNC1)
//
void micTimer1DeactivateInputNoiseCanceller(void);

// Set Timer 1 capture on falling edge of the capture signal (set ICES1)
//
void micTimer1SetRisingCaptureEdge(void);

// Set Timer 1 capture on falling edge of the capture signal (clear ICES1)
//
void micTimer1SetFallingCaptureEdge(void);

// Toggle edge of the capture signal (Toggle ICES1).
void micTimer1ToggleCaptureEdge(void);


/******************************************************************************/
#endif  // _ATMEGA164_TIMER1_H_
