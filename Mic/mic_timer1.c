/*******************************************************************************
***                                                                          ***
**                                                                            **
**                           TIMER 1 MANAGEMENT                               **
**                                                                            **
***                                                                          ***
*******************************************************************************/

// Include header for this micrcontroller
#include "Mic/mic_micro.h"


/*******************************************************************************
*                                                                              *
*  Name: micTimer1SetValue                                                     *
*                                                                              *
*  Subject: Set a new value for timer 1                                        *
*                                                                              *
*                                                                              *
*  Input(s):  timer_value = New value for timer 1                              *
*                                                                              *
*  Output(s): None                                                             *
*                                                                              *
*  Modified Global variables: None                                             *
*                                                                              *
*  Necessary Interrupts: None                                                  *
*                                                                              *
*******************************************************************************/

void micTimer1SetValue(Timer1Value timer_value)
{
  tcnt1 = timer_value;
  return;
}


/*******************************************************************************
*                                                                              *
*  Name: micTimer1GetValue                                                     *
*                                                                              *
*  Subject: Get current value of timer 1                                       *
*                                                                              *
*                                                                              *
*  Input(s):  timer_value = New value for timer 1                              *
*                                                                              *
*  Output(s): None                                                             *
*                                                                              *
*  Modified Global variables: None                                             *
*                                                                              *
*  Necessary Interrupts: None                                                  *
*                                                                              *
*******************************************************************************/

Timer1Value micTimer1GetValue(void)
{
  return tcnt1;
}


/*******************************************************************************
*                                                                              *
*  Name: micTimer1SetCompareValueA                                             *
*                                                                              *
*  Subject: Set a new Copmpare value for timer 1 compare unit A                *
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

void micTimer1SetCompareValueA(Timer1CompareValue compare_value)
{
  ocr1a = compare_value;
  return;
}


/*******************************************************************************
*                                                                              *
*  Name: micTimer1GetCompareValueA                                             *
*                                                                              *
*  Subject: Get compare value for timer 1 compare unit A                       *
*                                                                              *
*                                                                              *
*  Input(s):  None                                                             *
*                                                                              *
*  Output(s): compare value for compare unit A of timer 1                      *
*                                                                              *
*  Modified Global variables: None                                             *
*                                                                              *
*  Necessary Interrupts: None                                                  *
*                                                                              *
*******************************************************************************/

Timer1CompareValue micTimer1GetCompareValueA(void)
{
  return ocr1a;
}


/*******************************************************************************
*                                                                              *
*  Name: micTimer1SetCompareValueB                                             *
*                                                                              *
*  Subject: Set a new Compare value for timer 1 compare unit B                 *
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


void micTimer1SetCompareValueB(Timer1CompareValue compare_value)
{
  ocr1b = compare_value;
}


/*******************************************************************************
*                                                                              *
*  Name: micTimer1GetCompareValueB                                             *
*                                                                              *
*  Subject: Get compare value for timer 1 compare unit B                       *
*                                                                              *
*                                                                              *
*  Input(s):  None                                                             *
*                                                                              *
*  Output(s): compare value for compare unit B of timer 1                      *
*                                                                              *
*  Modified Global variables: None                                             *
*                                                                              *
*  Necessary Interrupts: None                                                  *
*                                                                              *
*******************************************************************************/

Timer1CompareValue micTimer1GetCompareValueB(void)
{
  return ocr1b;
}

/*******************************************************************************
*                                                                              *
*  Name: micTimer1SetCaptureValue                                              *
*                                                                              *
*  Subject: Set capture register value of timer 1                                      *
*                                                                              *
*  Input(s):  None                                                             *
*                                                                              *
*  Output(s): Last captured value of timer 1                                   *
*                                                                              *
*  Modified Global variables: None                                             *
*                                                                              *
*  Necessary Interrupts: None                                                  *
*                                                                              *
*******************************************************************************/

void micTimer1SetCaptureValue(Timer1CaptureValue icr_value)
{
  icr1 = icr_value;
}

/*******************************************************************************
*                                                                              *
*  Name: micTimer1GetCaptureValue                                              *
*                                                                              *
*  Subject: Get last captured value of timer 1                                 *
*                                                                              *
*  Input(s):  None                                                             *
*                                                                              *
*  Output(s): Last captured value of timer 1                                   *
*                                                                              *
*  Modified Global variables: None                                             *
*                                                                              *
*  Necessary Interrupts: None                                                  *
*                                                                              *
*******************************************************************************/

Timer1CaptureValue micTimer1GetCaptureValue(void)
{
  return icr1;
}


/*******************************************************************************
*                                                                              *
*  Name: micTimer1SetClockDivision                                             *
*                                                                              *
*  Subject: Select Timer 1 source clock prescaler                              *
*                                                                              *
*                                                                              *
*  Input(s): clock_div = TIMER1_NO_CLOCK: Timer clock stopped                  *
*                        TIMER1_CLK_DIV_1: Timer clock = Fosc                  *
*                        TIMER1_CLK_DIV_8: Timer clock = Fosc / 8              *
*                        TIMER1_CLK_DIV_64: Timer clock = Fosc / 64            *
*                        TIMER1_CLK_DIV_256: Timer clock = Fosc / 256          *
*                        TIMER1_CLK_DIV_1024: Timer clock = Fosc / 1024        *
*                        TIMER1_CLK_T1_FALLING: Timer clock = T1 falling edge  *
*                        TIMER1_CLK_T1_RISING: Timer clock = T1 rising edge    *
*                                                                              *
*  Output(s): None                                                             *
*                                                                              *
*  Modified Global variables: None                                             *
*                                                                              *
*  Necessary Interrupts: None                                                  *
*                                                                              *
*******************************************************************************/

void micTimer1SetClockDivision(Timer1Clock clock_div)
{
  tccr1b = (tccr1b & ~((1U << CS12) | (1U << CS11) | (1U << CS10))) |
           (clock_div & ((1U << CS12) | (1U << CS11) | (1U << CS10)));
  return;
}


/*******************************************************************************
*                                                                              *
*  Name: micTimer1SetGeneratorMode                                             *
*                                                                              *
*  Subject: Set waveform generator mode for timer 1                            *
*                                                                              *
*                                                                              *
*  Input(s):  generator_mode = Timer 1 wave form generator to use:             *
*                TIMER1_NORMAL_COMPARE = Normal compare mode                   *
*                TIMER1_CLEAR_ON_COMPARE = Clear timer on compare match        *
*                TIMER1_PWM_TOP_MAX = Fast PWM with top at 0xFFFF              *
*                TIMER1_FAST_PWM_TOP_MAX = Phase correct PWM with top at 255   *
*                TIMER1_PWM_TOP_REGISTER  = Phase correct PWM with top at OCRx *
*                TIMER1_FAST_PWM_TOP_MAX = Fast PWM with top at OCRx           *
*                                                                              *
*  Output(s): None                                                             *
*                                                                              *
*  Modified Global variables: None                                             *
*                                                                              *
*  Necessary Interrupts: None                                                  *
*                                                                              *
*******************************************************************************/

void micTimer1SetGeneratorMode(Timer1GeneratorMode generator_mode)
{
  tccr1b = (tccr1b & ~((1U << WGM13) | (1U << WGM12))) |
           (generator_mode & ((1U << WGM13) | (1U << WGM12)));

  tccr1a = (tccr1a & ~((1U << WGM11) | (1U << WGM10))) |
           (generator_mode & ((1U << WGM11) | (1U << WGM10)));
  return;
}

/*******************************************************************************
*                                                                              *
*  Name: micTimer1GetOutputBehavior                                            *
*                                                                              *
*  Subject: Get timer 1 output behavior A and B                                *
*                                                                              *
*  Input(s):  None                                                             *
*  Output(s): None                                                             *
*                                                                              *
*  Modified Global variables: None                                             *
*                                                                              *
*  Necessary Interrupts: None                                                  *
*                                                                              *
*******************************************************************************/

Timer1OutputBehavior micTimer1GetOutputBehavior( void )
{
  return tccr1a & ((1U << COM1A1) | (1U << COM1A0) | (1U << COM1B1) | (1U << COM1B0));
}


/*******************************************************************************
*                                                                              *
*  Name: micTimer1SetOutputBehaviorA                                           *
*                                                                              *
*  Subject: Set timer 1 output A behavior depending on generator mode          *
*                                                                              *
*  Input(s): compare_behavior = Compare match behavior.                        *
*                TIMER1_OUTPUT_A_DISCONNECTED = Normal port output             *
*                TIMER1_OUTPUT_A_TOGGLE = Toggle OC1A on compare mode          *
*                TIMER1_OUTPUT_A_CLEAR = Clear OC1A on compare mode            *
*                TIMER1_OUTPUT_A_SET = Set OC1A ont compare mode               *
*                                                                              *
*  Output(s): None                                                             *
*                                                                              *
*  Modified Global variables: None                                             *
*                                                                              *
*  Necessary Interrupts: None                                                  *
*                                                                              *
*******************************************************************************/

void micTimer1SetOutputBehaviorA(Timer1OutputBehaviorA compare_behavior)
{
  tccr1a = (tccr1a & ~((1U << COM1A1) | (1U << COM1A0))) |
           (compare_behavior & ((1U << COM1A1) | (1U << COM1A0)));
  return;
}


/*******************************************************************************
*                                                                              *
*  Name: micTimer1SetOutPutBehaviorB                                           *
*                                                                              *
*  Subject: Set timer 1 output B behavior depending on generator mode          *
*                                                                              *
*  Input(s): compare_behavior = Compare match behavior.                        *
*                TIMER1_OUTPUT_B_DISCONNECTED = Normal port output             *
*                TIMER1_OUTPUT_B_TOGGLE = Toggle OC1B on compare mode          *
*                TIMER1_OUTPUT_B_CLEAR = Clear OC1B on compare mode            *
*                TIMER1_OUTPUT_B_SET = Set OC1B ont compare mode               *
*                                                                              *
*  Output(s): None                                                             *
*                                                                              *
*  Modified Global variables: None                                             *
*                                                                              *
*  Necessary Interrupts: None                                                  *
*                                                                              *
*******************************************************************************/

void micTimer1SetOutputBehaviorB(Timer1OutputBehaviorB compare_behavior)
{
  tccr1a = (tccr1a & ~((1U << COM1B1) | (1U << COM1B0))) |
           (compare_behavior & ((1U << COM1B1) | (1U << COM1B0)));
  return;
}


/*******************************************************************************
*                                                                              *
*  Name: micTimer1ForceCompare                                                 *
*                                                                              *
*  Subject: Set a new value for timer 1                                        *
*                                                                              *
*  Input(s):  compare_unit = The unit on which we want to force compare        *
*             TIMER1_FORCE_COMPARE_A to force Compare unit A                   *
*             TIMER1_FORCE_COMPARE_B to force Compare unit B                   *
*                                                                              *
*  Output(s): None                                                             *
*                                                                              *
*  Modified Global variables: None                                             *
*                                                                              *
*  Necessary Interrupts: None                                                  *
*                                                                              *
*******************************************************************************/

void micTimer1ForceCompare(Timer1ForceCompare compare_unit)
{
  tccr1c = (Int8U)(compare_unit & (Int8U)((1U << FOC1B) | (1U << FOC1A)));
  return;
}


/*******************************************************************************
*                                                                              *
*  Name: micTimer1UnMaskInterrupts                                             *
*                                                                              *
*  Subject: Unmask Timer 1 selected interrupts (OC1B, OC1A, T1 OVF).           *
*                                                                              *
*  Input(s):  interrupts = interrupt mask ored for:                            *
*                        TIMER1_COMPARE_B_INTERRUPT: compare match on B        *
*                        TIMER1_COMPARE_A_INTERRUPT: compare match on A        *
*                        TIMER1_OVERFLOW_INTERRUPT: overflow of timer          *
*                                                                              *
*  Output(s): None                                                             *
*                                                                              *
*  Modified Global variables: None                                             *
*                                                                              *
*  Necessary Interrupts: None                                                  *
*                                                                              *
*******************************************************************************/

void micTimer1UnMaskInterrupts(Timer1Interrupts interrupts)
{
  timsk1 |= interrupts &
            ((1U << ICIE1) | (1U << OCIE1B) | (1U << OCIE1A) | (1U << TOIE1));
  return;
}


/*******************************************************************************
*                                                                              *
*  Name: micTimer1MaskInterrupt                                                *
*                                                                              *
*  Subject: Mask Timer 1 selected interrupts (OC1B, OC1A, T1 OVF).             *
*                                                                              *
*  Input(s):  interrupts = interrupt mask ored for:                            *
*                        TIMER1_CAPTURE_INTERRUPT: capture on ICP edge         *
*                        TIMER1_COMPARE_B_INTERRUPT: compare match on B        *
*                        TIMER1_COMPARE_A_INTERRUPT: compare match on A        *
*                        TIMER1_OVERFLOW_INTERRUPT: overflow of timer          *
*                                                                              *
*  Output(s): None                                                             *
*                                                                              *
*  Modified Global variables: None                                             *
*                                                                              *
*  Necessary Interrupts: None                                                  *
*                                                                              *
*******************************************************************************/

void micTimer1MaskInterrupts(Timer1Interrupts interrupts)
{
  timsk1 &= ~(interrupts &
              ((1U << ICIE1) | (1U << OCIE1B) | (1U << OCIE1A) | (1U << TOIE1)));
  return;
}


/*******************************************************************************
*                                                                              *
*  Name: micTimer1SaveInterrupts                                               *
*                                                                              *
*  Subject: Save Timer 1 interrupts current state.                             *
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

Timer1Interrupts micTimer1SaveInterrupts(void)
{
  return timsk1;
}


/*******************************************************************************
*                                                                              *
*  Name: micTimer1RestoreInterrupts                                            *
*                                                                              *
*  Subject: Restore Timer 1 interrupts state                                   *
*                                                                              *
*                                                                              *
*  Input(s): interrupt_state = Timer 1 interrupts state to restore             *
*                                                                              *
*  Output(s): Current interrpt state                                           *
*                                                                              *
*  Modified Global variables: None                                             *
*                                                                              *
*  Necessary Interrupts: None                                                  *
*                                                                              *
*******************************************************************************/

void micTimer1RestoreInterrupts(Timer1Interrupts interrupt_state)
{
   timsk1 = interrupt_state & ((1U << ICIE1) | (1U << OCIE1B) | (1U << OCIE1A) | (1U << TOIE1));
   return;
}


/*******************************************************************************
*                                                                              *
*  Name: micTimer1ClearInterruptFlags                                          *
*                                                                              *
*  Subject: Clear Timer 1 interrupt flags (OCF1B, OCF1A and TOV1).             *
*                                                                              *
*                                                                              *
*  Input(s):  interrupt_flags = Timer 1 interrupt flags to clear               *
*                        TIMER1_COMPARE_B_FLAG: compare match on unit B        *
*                        TIMER1_COMPARE_A_FLAG: compare match on unit A        *
*                        TIMER1_OVERFLOW_FLAG: overflow of timer 1             *
*                        TIMER1_CAPTURE_FLAG: capture of timer 1               *
*                                                                              *
*  Output(s): None                                                             *
*                                                                              *
*  Modified Global variables: None                                             *
*                                                                              *
*  Necessary Interrupts: None                                                  *
*                                                                              *
*******************************************************************************/

void micTimer1ClearInterruptFlags(Timer1Flags interrupt_flags)
{
  tifr1 = (interrupt_flags &
           ((1U << ICF1) | (1U << OCF1B) | (1U << OCF1A) | (1U << TOV1)));
  return;
}

Timer1Flags micTimer1ReadInterruptFlags( void )
{
  return tifr1;// ((1U << ICF1) | (1U << OCF1B) | (1U << OCF1A) | (1U << TOV1)));
}



/*******************************************************************************
*                                                                              *
*  Name: micTimer1ResetClockPrescaler.                                         *
*                                                                              *
*  Subject: Reset Timer1 clock prescaler (Set PSRSYNC alias PSR54310)          *
*           Consequently, Timer1  is halted.                                   *
*           PSRSYNC is cleared by hardware.                                    *
*           This is an alias function for micTimer0ResetClockPrescaler()       *
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

void micTimer1ResetClockPrescaler(void)
{
  gtccr |= (1U << PSRSYNC);
  return;
}


/*******************************************************************************
*                                                                              *
*  Name: micTimer1ActivateInputNoiseCanceller                                  *
*                                                                              *
*  Subject: Activate the input capture noise canceller (set ICNC1).            *
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

void micTimer1ActivateInputNoiseCanceller(void)
{
  tccr1b |= (1U << ICNC1);
  return;
}


/*******************************************************************************
*                                                                              *
*  Name: micTimer1DeactivateInputNoiseCanceller                                *
*                                                                              *
*  Subject: Deactivate the input capture noise canceller (clear ICNC1).        *
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

void micTimer1DeactivateInputNoiseCanceller(void)
{
  tccr1b &= ~(1U << ICNC1);
  return;
}


/*******************************************************************************
*                                                                              *
*  Name: micTimer1SetRisingCaptureEdge                                         *
*                                                                              *
*  Subject: Set capture on Rising edge of the capture signal (set ICES1).      *
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

void micTimer1SetRisingCaptureEdge(void)
{
  tccr1b |= (1U << ICES1);
  return;
}


/*******************************************************************************
*                                                                              *
*  Name: micTimer1SetFallingCaptureEdge                                        *
*                                                                              *
*  Subject: Set capture on falling edge of the capture signal (clear ICES1).   *
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

void micTimer1SetFallingCaptureEdge(void)
{
  tccr1b &= ~(1U << ICES1);
  return;
}


/*******************************************************************************
*                                                                              *
*  Name: micTimer1ToggleCaptureEdge                                            *
*                                                                              *
*  Subject: Toggle edge of the capture signal (clear ICES1).                   *
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

void micTimer1ToggleCaptureEdge(void)
{
  tccr1b ^= (1U << ICES1);
  return;
}


/*****************************************************************************/


