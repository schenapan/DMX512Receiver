/*******************************************************************************
***                                                                          ***
**                                                                            **
**                           TIMER 0 MANAGEMENT                               **
**                                                                            **
***                                                                          ***
*******************************************************************************/

// Include header for this micrcontroller
#include "Mic/mic_micro.h"

// private variables of the module avec pre-initialisation
static struct
{
  // pointeur de fonction a appeler lors d'une interruption sur compA
  p_isr_callback p_timer0_compa_user_isr;
}mic_timer0 = {
  NUL,
};


/*******************************************************************************
*                                                                              *
*  Name: micTimer0SetValue                                                     *
*                                                                              *
*  Subject: Set a new value for timer 0                                        *
*                                                                              *
*                                                                              *
*  Input(s):  timer_value = New value for timer 0                              *
*                                                                              *
*  Output(s): None                                                             *
*                                                                              *
*  Modified Global variables: None                                             *
*                                                                              *
*  Necessary Interrupts: None                                                  *
*                                                                              *
*******************************************************************************/

void micTimer0SetValue(Timer0Value timer_value)
{
  tcnt0 = timer_value;
  return;
}


/*******************************************************************************
*                                                                              *
*  Name: micTimer0GetValue                                                     *
*                                                                              *
*  Subject: Get current value of timer 0                                       *
*                                                                              *
*                                                                              *
*  Input(s):  timer_value = New value for timer 0                              *
*                                                                              *
*  Output(s): None                                                             *
*                                                                              *
*  Modified Global variables: None                                             *
*                                                                              *
*  Necessary Interrupts: None                                                  *
*                                                                              *
*******************************************************************************/

Timer0Value micTimer0GetValue(void)
{
  return tcnt0;
}


/*******************************************************************************
*                                                                              *
*  Name: micTimer0SetCompareValueA                                             *
*                                                                              *
*  Subject: Set a new Copmpare value for timer 0 compare unit A                *
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

void micTimer0SetCompareValueA(Timer0CompareValue compare_value)
{
  ocr0a = compare_value;
  return;
}


/*******************************************************************************
*                                                                              *
*  Name: micTimer0GetCompareValueA                                             *
*                                                                              *
*  Subject: Get compare value for timer 0 compare unit A                       *
*                                                                              *
*                                                                              *
*  Input(s):  None                                                             *
*                                                                              *
*  Output(s): compare value for compare unit A of timer 0                      *
*                                                                              *
*  Modified Global variables: None                                             *
*                                                                              *
*  Necessary Interrupts: None                                                  *
*                                                                              *
*******************************************************************************/

Timer0CompareValue micTimer0GetCompareValueA(void)
{
  return ocr0a;
}


/*******************************************************************************
*                                                                              *
*  Name: micTimer0SetCompareValueB                                             *
*                                                                              *
*  Subject: Set a new Copmpare value for timer 0 compare unit B                *
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

void micTimer0SetCompareValueB(Timer0CompareValue compare_value)
{
  ocr0b = compare_value;
  return;
}


/*******************************************************************************
*                                                                              *
*  Name: micTimer0GetCompareValueB                                             *
*                                                                              *
*  Subject: Get compare value for timer 0 compare unit B                       *
*                                                                              *
*                                                                              *
*  Input(s):  None                                                             *
*                                                                              *
*  Output(s): compare value for compare unit B of timer 0                      *
*                                                                              *
*  Modified Global variables: None                                             *
*                                                                              *
*  Necessary Interrupts: None                                                  *
*                                                                              *
*******************************************************************************/

Timer0CompareValue micTimer0GetCompareValueB(void)
{
  return ocr0b;
}


/*******************************************************************************
*                                                                              *
*  Name: micTimer0SetClockDivision                                             *
*                                                                              *
*  Subject: Select Timer 0 source clock prescaler                              *
*                                                                              *
*                                                                              *
*  Input(s): clock_div = TIMER0_NO_CLOCK: Timer clock stopped                  *
*                        TIMER0_CLK_DIV_1: Timer clock = Fosc                  *
*                        TIMER0_CLK_DIV_8: Timer clock = Fosc / 8              *
*                        TIMER0_CLK_DIV_64: Timer clock = Fosc / 64            *
*                        TIMER0_CLK_DIV_256: Timer clock = Fosc / 256          *
*                        TIMER0_CLK_DIV_1024: Timer clock = Fosc / 1024        *
*                        TIMER0_CLK_T0_FALLING: Timer clock = T0 falling edge  *
*                        TIMER0_CLK_T0_RISING: Timer clock = T0 rising edge    *
*                                                                              *
*  Output(s): None                                                             *
*                                                                              *
*  Modified Global variables: None                                             *
*                                                                              *
*  Necessary Interrupts: None                                                  *
*                                                                              *
*******************************************************************************/

void micTimer0SetClockDivision(Timer0Clock clock_div)
{
  tccr0b = (tccr0b & ~((1U << CS02) | (1U << CS01) | (1U << CS00))) |
           (clock_div & ((1U << CS02) | (1U << CS01) | (1U << CS00)));
  return;
}


/*******************************************************************************
*                                                                              *
*  Name: micTimer0SetGeneratorMode                                             *
*                                                                              *
*  Subject: Set waveform generator mode for timer 0                            *
*                                                                              *
*                                                                              *
*  Input(s):  generator_mode = Timer 0 wave form generator to use:             *
*             TIMER0_NORMAL_COMPARE = Normal compare mode                      *
*             TIMER0_CLEAR_ON_COMPARE = Clear timer on OCR0A compare match     *
*             TIMER0_PHASE_PWM_TOP_255 = Phase correct PWM with top at 255     *
*             TIMER0_FAST_PWM_TOP_255 = Phase correct PWM with top at 255      *
*             TIMER0_PHASE_PWM_TOP_OCRA  = Phase correct PWM with top at OCR0A *
*             TIMER0_FAST_PWM_TOP_OCRA = Phase correct PWM with top at OCR0A   *
*                                                                              *
*  Output(s): None                                                             *
*                                                                              *
*  Modified Global variables: None                                             *
*                                                                              *
*  Necessary Interrupts: None                                                  *
*                                                                              *
*******************************************************************************/

void micTimer0SetGeneratorMode(Timer0GeneratorMode generator_mode)
{
  tccr0b = (tccr0b & ~(1U << WGM02)) | (generator_mode & (1U << WGM02));
  tccr0a = (tccr0a & ~((1U << WGM01) | (1U << WGM00))) |
           (generator_mode & ((1U << WGM01) | (1U << WGM00)));
  return;
}



/*******************************************************************************
*                                                                              *
*  Name: micTimer0SetOutputBehaviorA                                           *
*                                                                              *
*  Subject: Set timer 0 output A behavior depending on generator mode          *
*                                                                              *
*  Input(s): compare_behavior = Compare match behavior.                        *
*                TIMER0_OUTPUT_A_DISCONNECTED = Normal port output             *
*                TIMER0_OUTPUT_A_TOGGLE = Toggle OC0A on compare mode          *
*                TIMER0_OUTPUT_A_CLEAR = Clear OC0A on compare mode            *
*                TIMER0_OUTPUT_A_SET = Set OC0A ont compare mode               *
*                                                                              *
*  Output(s): None                                                             *
*                                                                              *
*  Modified Global variables: None                                             *
*                                                                              *
*  Necessary Interrupts: None                                                  *
*                                                                              *
*******************************************************************************/

void micTimer0SetOutputBehaviorA(Timer0OutputBehaviorA compare_behavior)
{
  tccr0a = (tccr0a & ~((1U << COM0A1) | (1U << COM0A0))) |
           (compare_behavior & ((1U << COM0A1) | (1U << COM0A0)));
  return;
}


/*******************************************************************************
*                                                                              *
*  Name: micTimer0SetOutputBehaviorB                                           *
*                                                                              *
*  Subject: Set timer 0 output B behavior depending on generator mode          *
*                                                                              *
*  Input(s): compare_behavior = Compare match behavior.                        *
*                TIMER0_OUTPUT_B_DISCONNECTED = Normal port output             *
*                TIMER0_OUTPUT_B_TOGGLE = Toggle OC0B on compare mode          *
*                TIMER0_OUTPUT_B_CLEAR = Clear OC0B on compare mode            *
*                TIMER0_OUTPUT_B_SET = Set OC0B ont compare mode               *
*                                                                              *
*  Output(s): None                                                             *
*                                                                              *
*  Modified Global variables: None                                             *
*                                                                              *
*  Necessary Interrupts: None                                                  *
*                                                                              *
*******************************************************************************/

void micTimer0SetOutputBehaviorB(Timer0OutputBehaviorB compare_behavior)
{
  tccr0a = (tccr0a & ~((1U << COM0B1) | (1U << COM0B0))) |
           (compare_behavior & ((1U << COM0B1) | (1U << COM0B0)));
  return;
}


/*******************************************************************************
*                                                                              *
*  Name: micTimer0ForceCompare                                                 *
*                                                                              *
*  Subject: Force output compare on the specified unit(s).                     *
*                                                                              *
*                                                                              *
*  Input(s):  compare_unit = The unit(s) on which we want to force compare     *
*                              TIMER0_FORCE_COMPARE_A to force Compare unit A  *
*                              TIMER0_FORCE_COMPARE_B to force Compare unit B  *
*                                                                              *
*  Output(s): None                                                             *
*                                                                              *
*  Modified Global variables: None                                             *
*                                                                              *
*  Necessary Interrupts: None                                                  *
*                                                                              *
*******************************************************************************/

void micTimer0ForceCompare(Timer0ForceCompare compare_unit)
{
  tccr0b |= compare_unit & ((1U << FOC0B) | (1U << FOC0A));
  return;
}


/*******************************************************************************
*                                                                              *
*  Name: micTimer0UnmaskInterrupts                                             *
*                                                                              *
*  Subject: Unmask TIMER0 selected interrupts (OC0B, OC0A, T0 OVF).            *
*                                                                              *
*  Input(s):  interrupts = interrupt mask ored for:                            *
*                        TIMER0_COMPARE_B_INTERRUPT: compare match on B        *
*                        TIMER0_COMPARE_A_INTERRUPT: compare match on A        *
*                        TIMER0_OVERFLOW_INTERRUPT: overflow of timer          *
*                                                                              *
*  Output(s): None                                                             *
*                                                                              *
*  Modified Global variables: None                                             *
*                                                                              *
*  Necessary Interrupts: None                                                  *
*                                                                              *
*******************************************************************************/

void micTimer0UnmaskInterrupts(Timer0Interrupts interrupts)
{
  timsk0 |= interrupts & ((1U << OCIE0B) | (1U << OCIE0A) | (1U << TOIE0));
  return;
}


/*******************************************************************************
*                                                                              *
*  Name: micTimer0MaskInterrupt                                                *
*                                                                              *
*  Subject: Mask TIMER0 selected interrupts (OC0B, OC0A, T0 OVF).              *
*                                                                              *
*  Input(s):  interrupts = interrupt mask ored for:                            *
*                        TIMER0_COMPARE_B_INTERRUPT: compare match on B        *
*                        TIMER0_COMPARE_A_INTERRUPT: compare match on A        *
*                        TIMER0_OVERFLOW_INTERRUPT: overflow of timer          *
*                                                                              *
*  Output(s): None                                                             *
*                                                                              *
*  Modified Global variables: None                                             *
*                                                                              *
*  Necessary Interrupts: None                                                  *
*                                                                              *
*******************************************************************************/

void micTimer0MaskInterrupts(Timer0Interrupts interrupts)
{
  timsk0 &= ~(interrupts & ((1U << OCIE0B) | (1U << OCIE0A) | (1U << TOIE0)));
  return;
}


/*******************************************************************************
*                                                                              *
*  Name: micTimer0SaveInterrupts                                               *
*                                                                              *
*  Subject: Save Timer 0 interrupts current state.                             *
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

Timer0Interrupts micTimer0SaveInterrupts(void)
{
  return timsk0;
}


/*******************************************************************************
*                                                                              *
*  Name: micTimer0RestoreInterrupts                                            *
*                                                                              *
*  Subject: Restore Timer 0 interrupts state                                   *
*                                                                              *
*                                                                              *
*  Input(s): interrupt_state = Timer 0 interrupts state to restore             *
*                                                                              *
*  Output(s): Current interrpt state                                           *
*                                                                              *
*  Modified Global variables: None                                             *
*                                                                              *
*  Necessary Interrupts: None                                                  *
*                                                                              *
*******************************************************************************/

void micTimer0RestoreInterrupts(Timer0Interrupts interrupt_state)
{
   timsk0 = interrupt_state & ((1U << OCIE0B) | (1U << OCIE0A) | (1U << TOIE0));
   return;
}


/*******************************************************************************
*                                                                              *
*  Name: micTimer0ClearInterruptFlags                                          *
*                                                                              *
*  Subject: Clear Timer 0 interrupt flags (OCF0B, OCF0A and TOV0).             *
*                                                                              *
*                                                                              *
*  Input(s):  interrupt_flags = Timer 0 interrupt flag(s) to be cleared        *
*                        TIMER0_COMPARE_B_FLAG: compare match on unit B        *
*                        TIMER0_COMPARE_A_FLAG: compare match on unit A        *
*                        TIMER0_OVERFLOW_FLAG: overflow of timer 0             *
*                                                                              *
*  Output(s): None                                                             *
*                                                                              *
*  Modified Global variables: None                                             *
*                                                                              *
*  Necessary Interrupts: None                                                  *
*                                                                              *
*******************************************************************************/

void micTimer0ClearInterruptFlags(Timer0Flags interrupt_flags)
{
  tifr0 = interrupt_flags & ((1U << OCF0B) | (1U << OCF0A) | (1U << TOV0));

  return;
}


/*******************************************************************************
*                                                                              *
*  Name: micTimer0ResetClockPrescaler.                                         *
*                                                                              *
*  Subject: Reset Timer0 clock prescaler (Set PSRSYNC alias PSR54310)          *
*           Consequently, Timer0 is halted.                                    *
*           PSRSYNC is cleared by hardware.                                    *
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

void micTimer0ResetClockPrescaler(void)
{
  gtccr |= (1U << PSRSYNC);
  return;
}

//------------------------------------------------------------------------------
// ISR
//------------------------------------------------------------------------------

/*******************************************************************************
*                                                                              *
*  Name: micTimer0SetCompACallback                                             *
*                                                                              *
*  Subject: Fonction permettant d'assigné la fonction a appeler lors d'une     *
*           interruption compA                                                 *
*                                                                              *
*  Input(s): Adresse de la fonction a appeler                                  *
*                                                                              *
*  Output(s): None                                                             *
*                                                                              *
*******************************************************************************/
void micTimer0SetCompACallback( p_isr_callback i_p_callback )
{
  ATOMIC(
    mic_timer0.p_timer0_compa_user_isr = i_p_callback;
  )
}


/*******************************************************************************
*                                                                              *
*  Name: micTimer0CompAISR                                                     *
*                                                                              *
*  Subject: Fonction appelée par l'interruption CompA                          *
*                                                                              *
*  Input(s): None                                                              *
*                                                                              *
*  Output(s): None                                                             *
*                                                                              *
*******************************************************************************/
ISR(TIMER0_COMPA_vect)
{
  if( NUL != mic_timer0.p_timer0_compa_user_isr )
  {
    mic_timer0.p_timer0_compa_user_isr();
  }
}

/*****************************************************************************/

