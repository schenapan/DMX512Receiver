/*******************************************************************************
***                                                                          ***
**                                                                            **
**                            TIMER 2 MANAGEMENT                              **
**                                                                            **
***                                                                          ***
*******************************************************************************/

// Include header for this micrcontroller
#include "Mic/mic_micro.h"


/*******************************************************************************
*                                                                              *
*  Name: micTimer2SetValue                                                     *
*                                                                              *
*  Subject: Set a new value for timer 2                                        *
*                                                                              *
*                                                                              *
*  Input(s):  timer_value = New value for timer 2                              *
*                                                                              *
*  Output(s): None                                                             *
*                                                                              *
*  Modified Global variables: None                                             *
*                                                                              *
*  Necessary Interrupts: None                                                  *
*                                                                              *
*******************************************************************************/

void micTimer2SetValue(Timer2Value timer_value)
{
  tcnt2 = timer_value;
  return;
}


/*******************************************************************************
*                                                                              *
*  Name: micTimer2GetValue                                                     *
*                                                                              *
*  Subject: Get current value of timer 2                                       *
*                                                                              *
*                                                                              *
*  Input(s):  timer_value = New value for timer 2                              *
*                                                                              *
*  Output(s): None                                                             *
*                                                                              *
*  Modified Global variables: None                                             *
*                                                                              *
*  Necessary Interrupts: None                                                  *
*                                                                              *
*******************************************************************************/

Timer2Value micTimer2GetValue(void)
{
  return tcnt2;
}


/*******************************************************************************
*                                                                              *
*  Name: micTimer2GetCompareValueA                                             *
*                                                                              *
*  Subject: Get a new Copmpare value for timer 2 compare unit A                *
*                                                                              *
*                                                                              *
*  Input(s):  compare_value = New compare value for unit A                     *
*                                                                              *
*  Output(s): None                                                             *
*                                                                              *
*  Modified Global variables: None                                             *
*                                                                              *
*  Necessary Interrupts: None                                                  *
*                                                                              *
*******************************************************************************/

void micTimer2SetCompareValueA(Timer2CompareValue compare_value)
{
  ocr2a = compare_value;
  return;
}


/*******************************************************************************
*                                                                              *
*  Name: micTimer2GetCompareValueA                                             *
*                                                                              *
*  Subject: Get compare value for timer 2 compare unit A                       *
*                                                                              *
*                                                                              *
*  Input(s):  None                                                             *
*                                                                              *
*  Output(s): compare value for compare unit A of timer 2                      *
*                                                                              *
*  Modified Global variables: None                                             *
*                                                                              *
*  Necessary Interrupts: None                                                  *
*                                                                              *
*******************************************************************************/

Timer2CompareValue micTimer2GetCompareValueA(void)
{
  return ocr2a;
}


/*******************************************************************************
*                                                                              *
*  Name: micTimer2SetCompareValueB                                             *
*                                                                              *
*  Subject: Set a new Copmpare value for timer 2 compare unit B                *
*                                                                              *
*                                                                              *
*  Input(s):  compare_value = New compare value for unit B                     *
*                                                                              *
*  Output(s): None                                                             *
*                                                                              *
*  Modified Global variables: None                                             *
*                                                                              *
*  Necessary Interrupts: None                                                  *
*                                                                              *
*******************************************************************************/

void micTimer2SetCompareValueB(Timer2CompareValue compare_value)
{
  ocr2b = compare_value;
  return;
}


/*******************************************************************************
*                                                                              *
*  Name: micTimer2GetCompareValueB                                             *
*                                                                              *
*  Subject: Get compare value for timer 2 compare unit B                       *
*                                                                              *
*                                                                              *
*  Input(s):  None                                                             *
*                                                                              *
*  Output(s): compare value for compare unit B of timer 2                      *
*                                                                              *
*  Modified Global variables: None                                             *
*                                                                              *
*  Necessary Interrupts: None                                                  *
*                                                                              *
*******************************************************************************/

Timer2CompareValue micTimer2GetCompareValueB(void)
{
  return ocr2b;
}


/*******************************************************************************
*                                                                              *
*  Name: micTimer2SetClockDivision                                             *
*                                                                              *
*  Subject: Select Timer 2 source clock prescaler                              *
*                                                                              *
*                                                                              *
*  Input(s): clock_div = TIMER2_NO_CLOCK: Timer clock stopped                  *
*                        TIMER2_CLK_DIV_1: Timer clock = Fosc                  *
*                        TIMER2_CLK_DIV_8: Timer clock = Fosc / 8              *
*                        TIMER2_CLK_DIV_32: Timer clock = Fosc / 32            *
*                        TIMER2_CLK_DIV_64: Timer clock = Fosc / 64            *
*                        TIMER2_CLK_DIV_128: Timer clock = Fosc / 128          *
*                        TIMER2_CLK_DIV_256: Timer clock = Fosc / 256          *
*                        TIMER2_CLK_DIV_1024: Timer clock = Fosc / 1024        *
*                                                                              *
*  Output(s): None                                                             *
*                                                                              *
*  Modified Global variables: None                                             *
*                                                                              *
*  Necessary Interrupts: None                                                  *
*                                                                              *
*******************************************************************************/

void micTimer2SetClockDivision(Timer2Clock clock_div)
{
  tccr2b = (tccr2b & ~((1U << CS22) | (1U << CS21) | (1U << CS20))) |
           (clock_div & ((1U << CS22) | (1U << CS21) | (1U << CS20)));
  return;
}


/*******************************************************************************
*                                                                              *
*  Name: micTimer2SetGeneratorMode                                             *
*                                                                              *
*  Subject: Set waveform generator mode for timer 2                            *
*                                                                              *
*                                                                              *
*  Input(s):  generator_mode = Timer 2 wave form generator to use:             *
*             TIMER2_NORMAL_COMPARE = Normal compare mode                      *
*             TIMER2_CLEAR_ON_COMPARE = Clear timer on OCR2A compare match     *
*             TIMER2_PHASE_PWM_TOP_255 = Phase correct PWM with top at 255     *
*             TIMER2_FAST_PWM_TOP_255 = Phase correct PWM with top at 255      *
*             TIMER2_PHASE_PWM_TOP_OCRA  = Phase correct PWM with top at OCR2A *
*             TIMER2_FAST_PWM_TOP_OCRA = Phase correct PWM with top at OCR2A   *
*                                                                              *
*  Output(s): None                                                             *
*                                                                              *
*  Modified Global variables: None                                             *
*                                                                              *
*  Necessary Interrupts: None                                                  *
*                                                                              *
*******************************************************************************/

void micTimer2GeneratorMode(Timer2GeneratorMode generator_mode)
{
  tccr2b = (tccr2b & ~(1U << WGM22)) | (generator_mode & (1U << WGM22));
  tccr2a = (tccr2a & ~((1U << WGM21) | (1U << WGM20))) |
           (generator_mode & ((1U << WGM21) | (1U << WGM20)));
  return;
}

Int8U micTimer2GetGeneratorMode( void )
{
  return tccr2b & ((1U << EXCLK) | (1U << AS2));
}


/*******************************************************************************
*                                                                              *
*  Name: micTimer2SetOutputBehaviorA                                           *
*                                                                              *
*  Subject: Set timer 2 output A behavior depending on generator mode          *
*                                                                              *
*  Input(s): compare_behavior = Compare match behavior.                        *
*                TIMER2_OUTPUT_A_DISCONNECTED = Normal port output             *
*                TIMER2_OUTPUT_A_TOGGLE = Toggle OC2A on compare mode          *
*                TIMER2_OUTPUT_A_CLEAR = Clear OC2A on compare mode            *
*                TIMER2_OUTPUT_A_SET = Set OC2A ont compare mode               *
*                                                                              *
*  Output(s): None                                                             *
*                                                                              *
*  Modified Global variables: None                                             *
*                                                                              *
*  Necessary Interrupts: None                                                  *
*                                                                              *
*******************************************************************************/

void micTimer2SetOutputBehaviorA(Timer2OutputBehaviorA compare_behavior)
{
  tccr2a = (tccr2a & ~((1U << COM2A1) | (1U << COM2A0))) |
           (compare_behavior & ((1U << COM2A1) | (1U << COM2A0)));
  return;
}


/*******************************************************************************
*                                                                              *
*  Name: micTimer2SetOutputBehaviorB                                           *
*                                                                              *
*  Subject: Set timer 2 output B behavior depending on generator mode          *
*                                                                              *
*  Input(s): compare_behavior = Compare match behavior.                        *
*                TIMER2_OUTPUT_B_DISCONNECTED = Normal port output             *
*                TIMER2_OUTPUT_B_TOGGLE = Toggle OC2B on compare mode          *
*                TIMER2_OUTPUT_B_CLEAR = Clear OC2B on compare mode            *
*                TIMER2_OUTPUT_B_SET = Set OC2B ont compare mode               *
*                                                                              *
*  Output(s): None                                                             *
*                                                                              *
*  Modified Global variables: None                                             *
*                                                                              *
*  Necessary Interrupts: None                                                  *
*                                                                              *
*******************************************************************************/

void micTimer2SetOutputBehaviorB(Timer2OutputBehaviorB compare_behavior)
{
  tccr2a = (tccr2a & ~((1U << COM2B1) | (1U << COM2B0))) |
           (compare_behavior & ((1U << COM2B1) | (1U << COM2B0)));
  return;
}


/*******************************************************************************
*                                                                              *
*  Name: micTimer2ForceCompare                                                 *
*                                                                              *
*  Subject: Force output compare on the specified unit(s).                     *
*                                                                              *
*                                                                              *
*  Input(s):  compare_unit = The unit(s) on which we want to force compare     *
*                              TIMER2_FORCE_COMPARE_A to force Compare unit A  *
*                              TIMER2_FORCE_COMPARE_B to force Compare unit B  *
*                                                                              *
*  Output(s): None                                                             *
*                                                                              *
*  Modified Global variables: None                                             *
*                                                                              *
*  Necessary Interrupts: None                                                  *
*                                                                              *
*******************************************************************************/

void micTimer2ForceCompare(Timer2ForceCompare compare_unit)
{
  tccr2b |= compare_unit & ((1U << FOC2B) | (1U << FOC2A));
  return;
}


/*******************************************************************************
*                                                                              *
*  Name: micTimer2UnmaskInterrupts                                             *
*                                                                              *
*  Subject: Unmask TIMER2 selected interrupts (OC2B, OC2A, T2 OVF).            *
*                                                                              *
*  Input(s):  interrupts = interrupt mask ored for:                            *
*                        TIMER2_COMPARE_B_INTERRUPT: compare match on B        *
*                        TIMER2_COMPARE_A_INTERRUPT: compare match on A        *
*                        TIMER2_OVERFLOW_INTERRUPT: overflow of timer          *
*                                                                              *
*  Output(s): None                                                             *
*                                                                              *
*  Modified Global variables: None                                             *
*                                                                              *
*  Necessary Interrupts: None                                                  *
*                                                                              *
*******************************************************************************/

void micTimer2UnmaskInterrupts(Timer2Interrupts interrupts)
{
  timsk2 |= interrupts & ((1U << OCIE2B) | (1U << OCIE2A) | (1U << TOIE2));
  return;
}


/*******************************************************************************
*                                                                              *
*  Name: micTimer2MaskInterrupt                                                *
*                                                                              *
*  Subject: Mask TIMER2 selected interrupts (OC2B, OC2A, T2 OVF).              *
*                                                                              *
*  Input(s):  interrupts = interrupt mask ored for:                            *
*                        TIMER2_COMPARE_B_INTERRUPT: compare match on B        *
*                        TIMER2_COMPARE_A_INTERRUPT: compare match on A        *
*                        TIMER2_OVERFLOW_INTERRUPT: overflow of timer          *
*                                                                              *
*  Output(s): None                                                             *
*                                                                              *
*  Modified Global variables: None                                             *
*                                                                              *
*  Necessary Interrupts: None                                                  *
*                                                                              *
*******************************************************************************/

void micTimer2MaskInterrupts(Timer2Interrupts interrupts)
{
  timsk2 &= ~(interrupts & ((1U << OCIE2B) | (1U << OCIE2A) | (1U << TOIE2)));
  return;
}


/*******************************************************************************
*                                                                              *
*  Name: micTimer2SaveInterrupts                                               *
*                                                                              *
*  Subject: Save Timer 2 interrupts current state.                             *
*                                                                              *
*                                                                              *
*  Input(s): None                                                              *
*                                                                              *
*  Output(s): Current interrupt state                                          *
*                                                                              *
*  Modified Global variables: None                                             *
*                                                                              *
*  Necessary Interrupts: None                                                  *
*                                                                              *
*******************************************************************************/

Timer2Interrupts micTimer2SaveInterrupts(void)
{
  return timsk2;
}


/*******************************************************************************
*                                                                              *
*  Name: micTimer2RestoreInterrupts                                            *
*                                                                              *
*  Subject: Restore Timer 2 interrupts state                                   *
*                                                                              *
*                                                                              *
*  Input(s): interrupt_state = Timer 2 interrupts state to restore             *
*                                                                              *
*  Output(s): Current interrpt state                                           *
*                                                                              *
*  Modified Global variables: None                                             *
*                                                                              *
*  Necessary Interrupts: None                                                  *
*                                                                              *
*******************************************************************************/

void micTimer2RestoreInterrupts(Timer2Interrupts interrupt_state)
{
   timsk2 = interrupt_state & ((1U << OCIE2B) | (1U << OCIE2A) | (1U << TOIE2));
   return;
}


/*******************************************************************************
*                                                                              *
*  Name: micTimer2ClearInterruptFlags                                          *
*                                                                              *
*  Subject: Clear Timer 2 interrupt flags (OCF2B, OCF2A and TOV2).             *
*                                                                              *
*                                                                              *
*  Input(s):  interrupt_flags = Timer 2 interrupt flags to clear (ored):       *
*                        TIMER2_COMPARE_B_FLAG: compare match on unit B        *
*                        TIMER2_COMPARE_A_FLAG: compare match on unit A        *
*                        TIMER2_OVERFLOW_FLAG: overflow of timer 2             *
*                                                                              *
*  Output(s): None                                                             *
*                                                                              *
*  Modified Global variables: None                                             *
*                                                                              *
*  Necessary Interrupts: None                                                  *
*                                                                              *
*******************************************************************************/

void micTimer2ClearInterruptFlags(Timer2Flags interrupt_flags)
{
  tifr2 = interrupt_flags & ((1U << OCF2B) | (1U << OCF2A) | (1U << TOV2));
  return;
}

Timer2Flags micTimer2ReadInterruptFlags( void )
{
  return tifr2;// & ((1 << OCF2B) | (1 << OCF2A) | (1 << TOV2));
}


/*******************************************************************************
*                                                                              *
*  Name: micTimer2EnableExternalClock.                                         *
*                                                                              *
*  Subject: Enable external clock buffer for timer 2 (set EXCLK).              *
*           Must be done before asynchronous operation is selected             *
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

void micTimer2EnableExternalClock(void)
{
  assr |= (1U << EXCLK);
  return;
}


/*******************************************************************************
*                                                                              *
*  Name: micTimer2DisableExternalClock.                                        *
*                                                                              *
*  Subject: Disable external clock buffer for timer 2 (clear EXCLK).           *
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

void micTimer2DisableExternalClock(void)
{
  assr &= ~(1U << EXCLK);
  return;
}

Int8U micTimer2ReadExternalClock(void)
{
  return assr & ((1U << EXCLK) | (1U << AS2));
}


/*******************************************************************************
*                                                                              *
*  Name: micTimer2SelectExternalClock.                                         *
*                                                                              *
*  Subject: Select external clock source for timer 2 (Set AS2).                *
*           When the value of AS2 is changed, the contents of TCNT2, OCR2A,    *
*            OCR2B, TCCR2A and TCCR2B might be corrupted                       *
*                                                                              *
*           micTimer2EnableExternalClock() must be called prior to call this   *
*           function if it is an external signal clock from input TOSC1        *
*           and don't call it if it is an external crystal clock (TOSC1-TOSC2) *
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

void micTimer2SelectExternalClock(void)
{
  assr |= (1U << AS2);
  return;
}


/*******************************************************************************
*                                                                              *
*  Name: micTimer2SelectInternalClock.                                         *
*                                                                              *
*  Subject: Set Timer into synchronous operation by selecting internal clock   *
*           (clear AS2)                                                        *
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


void micTimer2SelectInternalClock(void)
{
  assr &= ~(1U << AS2);
  return;
}


/*******************************************************************************
*                                                                              *
*  Name: micTimer2GetUpdateBusyFlags.                                          *
*                                                                              *
*  Subject: Get flags indicating if timer 2 in asynchronous mode is busy       *
*           updating one of its registers:                                     *
*           TCNT2, OCR2A, OCR2B, TCCR2A or TCCR2B (a bit 1 means busy).        *
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

Timer2UpdateBusyFlags micTimer2GetUpdateBusyFlags(void)
{
  return assr & ((1U << TCN2UB) | (1U << OCR2AUB) | (1U << OCR2BUB) |
                 (1U << TCR2AUB)| (1U << TCR2BUB));
}


/*******************************************************************************
*                                                                              *
*  Name: micTimer2ResetClockPrescaler.                                         *
*                                                                              *
*  Subject: Reset Timer2 clock prescaler (Set PSRASY alias PSR2)               *
*           Consequently, Timer2 is halted.                                    *
*           PSRASY is cleared by hardware.                                     *
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

void micTimer2ResetClockPrescaler(void)
{
  gtccr |= (1U << PSRASY);
  return;
}


/*****************************************************************************/

