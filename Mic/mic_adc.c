/*******************************************************************************
***                                                                          ***
**                                                                            **
**                               ADC MANAGEMENT                               **
**                                                                            **
***                                                                          ***
*******************************************************************************/

// Include header for this micrcontroller
#include "Mic/mic_micro.h"


/*******************************************************************************
*                                                                              *
*  Name: micAdcTurnOn                                                          *
*                                                                              *
*  Subject: Turns on the AD converter.                                         *
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

void micAdcTurnOn(void)
{
  prr &= ~(1U << PRADC);
  adcsra |= (1U << ADEN);

  return;
}

/*******************************************************************************
*                                                                              *
*  Name: micAdcTurnOff                                                         *
*                                                                              *
*  Subject: turns off the AD converter.                                        *
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

void micAdcTurnOff(void)
{
  prr &= ~(1U << PRADC);
  adcsra &= ~((1U << ADEN) | (1U<< ADIE));
  prr |= (1U << PRADC);

  return;
}


/*******************************************************************************
*                                                                              *
*  Name: micAdcSetClock                                                        *
*                                                                              *
*  Subject: Select conversion clock for AD converter                           *
*                                                                              *
*                                                                              *
*  Input(s): adc_clock= CPU clock division to use for ADC.                     *
*                                                                              *
*  Output(s): None                                                             *
*                                                                              *
*  Modified Global variables: None                                             *
*                                                                              *
*  Necessary Interrupts: None                                                  *
*                                                                              *
*******************************************************************************/

void micAdcSetClock(AdcClock adc_clock)
{
  adcsra = (adcsra & ~ADC_CLOCK_DIV_MASK) | (adc_clock & ADC_CLOCK_DIV_MASK);

  return;
}



/*******************************************************************************
*                                                                              *
*  Name: micAdcSetChannel                                                      *
*                                                                              *
*  Subject: Select channel for AD conversion                                   *
*                                                                              *
*                                                                              *
*  Input(s): adc_channel = ADC Channel to use.                                 *
*                                                                              *
*  Output(s): None                                                             *
*                                                                              *
*  Modified Global variables: None                                             *
*                                                                              *
*  Necessary Interrupts: None                                                  *
*                                                                              *
*******************************************************************************/

void micAdcSetChannel(AdcChannel adc_channel)
{
  admux = (admux & ~ADC_CHANNEL_MASK) | (adc_channel & ADC_CHANNEL_MASK);

  return;
}


/*******************************************************************************
*                                                                              *
*  Name: micAdcSetReference                                                    *
*                                                                              *
*  Subject: Select voltage reference for AD converter                          *
*                                                                              *
*                                                                              *
*  Input(s): adc_reference = Reference to use for the AD conversion.           *
*                                                                              *
*  Output(s): None                                                             *
*                                                                              *
*  Modified Global variables: None                                             *
*                                                                              *
*  Necessary Interrupts: None                                                  *
*                                                                              *
*******************************************************************************/

void micAdcSetReference(AdcReference adc_reference)
{
  // if ADC is shut down ( PRR(ADC_bit) set to 1 )
  if ( 0U != (prr & (1U<< PRADC)) )
  {
    prr &= ~(1U<< PRADC);
    admux = (admux & ~ADC_REF_MASK) | (adc_reference & ADC_REF_MASK);
    prr |= (1U<< PRADC);
  }
  else
  {
    admux = (admux & ~ADC_REF_MASK) | (adc_reference & ADC_REF_MASK);
  }

  return;
}


/*******************************************************************************
*                                                                              *
*  Name: micAdcSelectFormat                                                    *
*                                                                              *
*  Subject: Select Result format of the AD coversion i.e. left or right        *
*           adjusted.                                                          *
*                                                                              *
*  Input(s):  adc_format = Format of the result of the AD conversion.          *
*             - ADC_RIGHT_ADJUST_RESULT = right adjusted result.               *
*             - ADC_LEFT_ADJUST_RESULT = left adjusted result.                 *
*                                                                              *
*  Output(s): None                                                             *
*                                                                              *
*  Modified Global variables: None                                             *
*                                                                              *
*  Necessary Interrupts: None                                                  *
*                                                                              *
*******************************************************************************/

void micAdcSetFormat(AdcFormat adc_format)
{
  admux = (admux & ~ADC_FORMAT_MASK) | (adc_format & ADC_FORMAT_MASK);

  return;
}



/*******************************************************************************
*                                                                              *
*  Name: micAdcSetFormatReferenceChannel                                       *
*                                                                              *
*  Subject: Set Channel, Voltage reference and result format of the AD         *
*           conversion.                                                        *
*                                                                              *
*  Input(s):  adc_format = Format of the result of the AD conversion.          *
*                                                                              *
*  Output(s): None                                                             *
*                                                                              *
*  Modified Global variables: None                                             *
*                                                                              *
*  Necessary Interrupts: None                                                  *
*                                                                              *
*******************************************************************************/

void micAdcSetFormatReferenceChannel(AdcReference adc_reference,
                                     AdcChannel adc_channel,
                                     AdcFormat adc_format)
{
  admux = (adc_channel & ADC_CHANNEL_MASK) |
          (adc_reference & ADC_REF_MASK) |
          (adc_format & ADC_FORMAT_MASK);

  return;
}



/*******************************************************************************
*                                                                              *
*  Name: micAdcStartConversion                                                 *
*                                                                              *
*  Subject: Start conversion on currently selected channel.                    *
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

void micAdcStartConversion(void)
{
  adcsra |= ((1U<< ADIF) | (1U<< ADSC));
  return;
}


/*******************************************************************************
*                                                                              *
*  Name: micAdcClearConversionCompletedFlag                                    *
*                                                                              *
*  Subject: Clear ADC interrupt flag.                                          *
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

void micAdcClearConversionCompletedFlag(void)
{
  // To avoid to restart a conversion when clearing ADIF
  adcsra = (adcsra & ~(1U<< ADSC)) | (1U<< ADIF);
  return;
}


/*******************************************************************************
*                                                                              *
*  Name: micAdcConversionIsInProgress                                          *
*                                                                              *
*  Subject: Check for a conversion in progress on the current channel.         *
*                                                                              *
*                                                                              *
*  Input(s):  None                                                             *
*                                                                              *
*  Output(s): TRUE if a conversion is in progress                              *
*                                                                              *
*  Modified Global variables: None                                             *
*                                                                              *
*  Necessary Interrupts: None                                                  *
*                                                                              *
*******************************************************************************/

Boolean micAdcConversionIsInProgress(void)
{
  return (adcsra & (1U<< ADSC));
}


/*******************************************************************************
*                                                                              *
*  Name: micAdcConversionIsCompleted                                           *
*                                                                              *
*  Subject: Check for a conversion complete                                    *
*                                                                              *
*                                                                              *
*  Input(s):  None                                                             *
*                                                                              *
*  Output(s): TRUE if a conversion is complete                                 *
*                                                                              *
*  Modified Global variables: None                                             *
*                                                                              *
*  Necessary Interrupts: None                                                  *
*                                                                              *
*******************************************************************************/

Boolean micAdcConversionIsCompleted(void)
{
  return (adcsra & (1U<< ADIF));
}


/*******************************************************************************
*                                                                              *
*  Name: micAdcUnmaskInterrupt                                                 *
*                                                                              *
*  Subject: Enable ADC interrupts if interrupts are enabled                    *
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

void micAdcUnmaskInterrupt(void)
{
  adcsra |= (1U<< ADIE);

  return;
}


/*******************************************************************************
*                                                                              *
*  Name: micAdcMAskInterrupt                                                   *
*                                                                              *
*  Subject: Disable ADC interrupts (mask it).                                  *
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

void micAdcMaskInterrupt(void)
{
  adcsra &= ~(1U<< ADIE);

  return;
}


/*******************************************************************************
*                                                                              *
*  Name: micAdcInterrupteAreUnmasked                                           *
*                                                                              *
*  Subject: Check if ADC interrupts are unmasked.                              *
*                                                                              *
*                                                                              *
*  Input(s):  None                                                             *
*                                                                              *
*  Output(s): TRUE if ADC interrupts are unmasked.                             *
*                                                                              *
*  Modified Global variables: None                                             *
*                                                                              *
*  Necessary Interrupts: None                                                  *
*                                                                              *
*******************************************************************************/

Boolean micAdcInterrupteAreUnmasked(void)
{
  return (adcsra & (1U<< ADIE));
}


/*******************************************************************************
*                                                                              *
*  Name: micAdcSaveState                                                       *
*                                                                              *
*  Subject: Save the ADC state to manage priority between ADC conversion tasks *
*                                                                              *
*                                                                              *
*  Input(s):  Pointer to the where save the current ADC state.                 *
*                                                                              *
*  Output(s): None                                                             *
*                                                                              *
*  Modified Global variables: None                                             *
*                                                                              *
*  Necessary Interrupts: None                                                  *
*                                                                              *
*******************************************************************************/

void micAdcSaveState(AdcState *state_ptr)
{
  // Current Mux position, voltage reference  and result format
  state_ptr->mux = admux;
  // Current auto triger source.
  state_ptr->trigger_source = adcsrb & ADC_TRIGGER_MASK;
  // Current interrupt mask, enable bit, auto-trigger enable bit and clock
  // prescaler in use
  state_ptr->controls = adcsra & ~((1U<< ADSC) | (1U<< ADIF));
  return;
}



/*******************************************************************************
*                                                                              *
*  Name: micAdcRestoreState                                                    *
*                                                                              *
*  Subject: Restore previoulsly save ADC state                                 *
*                                                                              *
*                                                                              *
*  Input(s):  Pointer to the where the previous ADC state is saved.            *
*                                                                              *
*  Output(s): None                                                             *
*                                                                              *
*  Modified Global variables: None                                             *
*                                                                              *
*  Necessary Interrupts: None                                                  *
*                                                                              *
*******************************************************************************/

void micAdcRestoreState(AdcState *state_ptr)
{
  // Restore previous MUX position, voltage reference and result format
  admux = state_ptr->mux;
  // Restore previous auto triger source
  adcsrb = (adcsrb & ~(ADC_TRIGGER_MASK)) | state_ptr->trigger_source;
  // Restore previous interrupt mask, enable bit, auto-trigger enable bit and
  // clock prescaler in use
  adcsra = state_ptr->controls;
  return;
}



/*******************************************************************************
*                                                                              *
*  Name: micAdcSetTriggerSource                                                *
*                                                                              *
*  Subject: Set trigger source for AD coversions.                              *
*                                                                              *
*  Input(s): adc_trigger_source = Trigger source for next AD conversions.      *
*                                                                              *
*  Output(s): None                                                             *
*                                                                              *
*  Modified Global variables: None                                             *
*                                                                              *
*  Necessary Interrupts: None                                                  *
*                                                                              *
*******************************************************************************/

void micAdcSetTriggerSource(AdcTrigger adc_trigger_source)
{
  adcsrb = (adcsrb &  ~ADC_TRIGGER_MASK) |
           (adc_trigger_source &  ADC_TRIGGER_MASK);

  return;
}


/*******************************************************************************
*                                                                              *
*  Name: micAdcEnableAutoTrigger                                               *
*                                                                              *
*  Subject: Enable ADC Autotrigger. The trigger source should be selected      *
*           previously by calling micAdcSetTriggerSource()                     *
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

void micAdcEnableAutoTrigger(void)
{
  adcsra |= (1U<< ADATE);

  return;
}


/*******************************************************************************
*                                                                              *
*  Name: micAdcDisableAutoTrigger                                              *
*                                                                              *
*  Subject: Disable ADC Autotrigger mode                                       *
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

void micAdcDisableAutoTrigger(void)
{
  adcsra &= ~(1U<< ADATE);
  adcsrb &= ~ADC_TRIGGER_MASK;

  return;
}


/*******************************************************************************
*                                                                              *
*  Name: micAdcReadData8                                                       *
*                                                                              *
*  Subject: Read the 8 bit result of the conversion                            *
*                                                                              *
*  Prequisite: ADC result must be left adjusted (see micAdcSetFormat).         *
*                                                                              *
*  Input(s): None                                                              *
*                                                                              *
*  Output(s):  8 bit result of the conversion                                  *
*                                                                              *
*  Modified Global variables: None                                             *
*                                                                              *
*  Necessary Interrupts: None                                                  *
*                                                                              *
*******************************************************************************/

AdcRawResult micAdcReadData8(void)
{
  return (AdcRawResult)adch;
}


/*******************************************************************************
*                                                                              *
*  Name: micAdcReadData16                                                      *
*                                                                              *
*  Subject: Read the 16 bit result of the conversion                           *
*                                                                              *
*  Prequisite: ADC result must be right adjusted (see micAdcSetFormat).        *
*                                                                              *
*  Input(s): None                                                              *
*                                                                              *
*  Output(s):  8 bit result of the conversion                                  *
*                                                                              *
*  Modified Global variables: None                                             *
*                                                                              *
*  Necessary Interrupts: None                                                  *
*                                                                              *
*******************************************************************************/

AdcRightAjustedResult micAdcReadData16(void)
{
  return (AdcRightAjustedResult)adc;
}


/*******************************************************************************
*                                                                              *
*  Name: micAdcSetAnalogPins                                                   *
*                                                                              *
*  Subject: Disable Digital buffer for ADC pin                                 *
*                                                                              *
*  Input(s): adc_analog_pins = Bit map of ADC pin which digital buffer is to   *
*            be switched off.                                                  *
*                                                                              *
*  Output(s): None                                                             *
*                                                                              *
*  Modified Global variables: None                                             *
*                                                                              *
*  Necessary Interrupts: None                                                  *
*                                                                              *
*******************************************************************************/
void micAdcSetAnalogPins( AdcAnalogPin adc_analog_pins_mask )
{
  didr0 |= adc_analog_pins_mask;

  return;
}

/*******************************************************************************
*                                                                              *
*  Name: micAdcClearAnalogPins                                                 *
*                                                                              *
*  Subject: Disable Digital buffer for ADC pin                                 *
*                                                                              *
*  Input(s): adc_analog_pins = Bit map of ADC pin which digital buffer is to   *
*            be switched off.                                                  *
*                                                                              *
*  Output(s): None                                                             *
*                                                                              *
*  Modified Global variables: None                                             *
*                                                                              *
*  Necessary Interrupts: None                                                  *
*                                                                              *
*******************************************************************************/

void micAdcClearAnalogPins(AdcAnalogPin adc_analog_pins_mask)
{
  didr0 &= (Int8U)(~adc_analog_pins_mask);
  return;
}

/******************************************************************************/
