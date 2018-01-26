#ifndef _ATMEGA164_ADC_H_
#define _ATMEGA164_ADC_H_
/******************************************************************************/
/*                                                                            */
/* => ADC management                                                          */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*
 * => Types:
 */

//  for ADC Reference selection
enum
{
  // AREF pin reference
  ADC_REF_AREF = (0U << REFS1) | (0U << REFS0),
  // AVCC pin reference.
  ADC_REF_AVCC = (0U << REFS1) | (1U << REFS0),
  // Internal reference.
  ADC_REF_INT_1V1 = (1U << REFS1) | (0U << REFS0),
  // Internal reference.
  ADC_REF_INT_2V56 = (1U << REFS1) | (1U << REFS0)
};
typedef Int8U AdcReference;
// Mask selecting bits used for ADC reference selection
#define ADC_REF_MASK      ((1U << REFS1) | (1U << REFS0))


//  for ADC channel selection
enum
{
  // Channel 0  (ADC0):
  ADC_CHANNEL_0 = 0U,
  // Channel 1 (ADC1):
  ADC_CHANNEL_1 = 1U,
  // Channel 2 (ADC2):
  ADC_CHANNEL_2 = 2U,
  // Channel 3 (ADC3):
  ADC_CHANNEL_3 = 3U,
  // Channel 4 (ADC4):
  ADC_CHANNEL_4 = 4U,
  // Channel 5 (ADC5):
  ADC_CHANNEL_5 = 5U,
  // Channel 5 (ADC6):
  ADC_CHANNEL_6 = 6U,
  // Channel 7 (ADC7):
  ADC_CHANNEL_7 = 7U,
  // Differential channel ADC0(+) ADC0(-):
  ADC_DIFF_CHANNEL_00_10X = 8U,
  // Differential channel ADC1(+) ADC0(-):
  ADC_DIFF_CHANNEL_10_10X = 9U,
  // Differential channel ADC1(+) ADC0(-):
  ADC_DIFF_CHANNEL_10_200X = 11U,
  // Differential channel ADC2(+) ADC2(-):
  ADC_DIFF_CHANNEL_22_10X = 12U,
  // Differential channel ADC3(+) ADC2(-):
  ADC_DIFF_CHANNEL_32_10X = 13U,
  // Differential channel ADC2(+) ADC2(-):
  ADC_DIFF_CHANNEL_22_200X = 14U,
  // Differential channel ADC3(+) ADC2(-):
  ADC_DIFF_CHANNEL_32_200X = 15U,
  // Differential channel ADC0(+) ADC1(-):
  ADC_DIFF_CHANNEL_01_1X = 16U,
  // Differential channel ADC1(+) ADC1(-):
  ADC_DIFF_CHANNEL_11_1X = 17U,
  // Differential channel ADC2(+) ADC1(-):
  ADC_DIFF_CHANNEL_21_1X = 18U,
  // Differential channel ADC3(+) ADC1(-):
  ADC_DIFF_CHANNEL_31_1X = 19U,
  // Differential channel ADC4(+) ADC1(-):
  ADC_DIFF_CHANNEL_41_1X = 20U,
  // Differential channel ADC5(+) ADC1(-):
  ADC_DIFF_CHANNEL_51_1X = 21U,
  // Differential _51channel ADC6(+) ADC1(-):
  ADC_DIFF_CHANNEL_61_1X = 22U,
  // Differential channel ADC7(+) ADC1(-):
  ADC_DIFF_CHANNEL_71_1X = 23U,
  // Differential channel ADC0(+) ADC2(-):
  ADC_DIFF_CHANNEL_02_1X = 24U,
  // Differential channel ADC1(+) ADC2(-):
  ADC_DIFF_CHANNEL_12_1X = 25U,
  // Differential channel ADC2(+) ADC2(-):
  ADC_DIFF_CHANNEL_22_1X = 26U,
  // Differential channel ADC3(+) ADC2(-):
  ADC_DIFF_CHANNEL_32_1X = 27U,
  // Differential channel ADC4(+) ADC2(-):
  ADC_DIFF_CHANNEL_42_1X = 28U,
  // Differential channel ADC5(+) ADC2(-):
  ADC_DIFF_CHANNEL_52_1X = 29U,
  // Channel for bandgap 1.22v voltage reference:
  ADC_CHANNEL_BANDGAP_REF = 30U,
  // Channel Gnd voltage (0V):
  ADC_CHANNEL_GND = 31U
};
typedef Int8U AdcChannel;
// Mask selecting bits used for Channel selection
#define ADC_CHANNEL_MASK  ((1U << MUX4) | (1U << MUX3) | (1U << MUX2) |\
                           (1U << MUX1) | (1U << MUX0))


// for ADC channel selection
enum
{
  // Right adjusted AD conversion result
  ADC_RIGHT_ADJUSTED_RESULT = (0U << ADLAR),
  // Left adjusted AD conversion result
  ADC_LEFT_ADJUSTED_RESULT = (1U << ADLAR)
};
typedef Int8U AdcFormat;
// Mask selecting bits used for Channel selection
#define ADC_FORMAT_MASK    (1U << ADLAR)


// Fosc Division used for ADC conversion clock selection
enum
{
  // ADC clock = Fosc / 2
  ADC_CLK_DIV_2 = (0U << ADPS2) | (0U << ADPS1) | (1U << ADPS0),
  // ADC clock = Fosc / 4
  ADC_CLK_DIV_4 = (0U << ADPS2) | (1U << ADPS1) | (0U << ADPS0),
  // ADC clock = Fosc / 8
  ADC_CLK_DIV_8 = (0U << ADPS2) | (1U << ADPS1) | (1U << ADPS0),
  // ADC clock = Fosc / 16
  ADC_CLK_DIV_16 = (1U << ADPS2) | (0U << ADPS1) | (0U << ADPS0),
  // ADC clock = Fosc / 32
  ADC_CLK_DIV_32 = (1U << ADPS2) | (0U << ADPS1) | (1U << ADPS0),
  // ADC clock = Fosc / 64
  ADC_CLK_DIV_64 = (1U << ADPS2) | (1U << ADPS1) | (0U << ADPS0),
  // ADC clock = Fosc / 128
  ADC_CLK_DIV_128 = (1U << ADPS2) | (1U << ADPS1) | (1U << ADPS0)
};
typedef Int8U AdcClock;
// Mask selecting bits used for ADC conversion clock selection
#define ADC_CLOCK_DIV_MASK  ((1U << ADPS2) | (1U << ADPS1) | (1U << ADPS0))


//  for ADC Trigger source (cf ADSRB)
enum
{
  // ADC in free running mode: a new conversion starts when the previous one
  // is completed
  ADC_TRIG_FREE_RUNNING = (0U << ADTS2) | (0U << ADTS1) | (0U << ADTS0),
  // AD conversion triggered by the Analog Comparator
  ADC_TRIG_ANALOG_COMP = (0U << ADTS2) | (0U << ADTS1) | (1U << ADTS0),
  // AD conversion triggered by the external interrupt INT0
  ADC_TRIG_INT0 = (0U << ADTS2) | (1U << ADTS1) | (0U << ADTS0),
  // AD conversion triggered by the timer 0 compare match event
  ADC_TRIG_TIMER0_COMPARE = (0U << ADTS2) | (1U << ADTS1) | (1U << ADTS0),
  // AD conversion triggered by a timer 0 overfow
  ADC_TRIG_TIMER0_OVERFLOW = (1U << ADTS2) | (0U << ADTS1) | (0U << ADTS0),
  // AD conversion triggered by the timer 1 compare match event
  ADC_TRIG_TIMER1_COMPARE = (1U << ADTS2) | (0U << ADTS1) | (1U << ADTS0),
  // AD conversion triggered by a timer 1 overfow
  ADC_TRIG_TIMER1_OVERFLOW = (1U << ADTS2) | (1U << ADTS1) | (0U << ADTS0),
  // AD conversion triggered by ta timer 1 capture event
  ADC_TRIG_TIMER1_CAPTURE = (1U << ADTS2) | (1U << ADTS1) | (1U << ADTS0)
};
typedef Int8U AdcTrigger;

// Mask selecting bits used for ADC conversion trigger source selection
#define ADC_TRIGGER_MASK  ((1U << ADTS2) | (1U << ADTS1) | (1U << ADTS0))



// Value for setting ADC Pins with analog buffer only
enum
{
  // To force Analog only mode for ADC0
  ADC_ANALOG_PIN_ADC0 = (1U < ADC0D),
  // To force Analog only mode for ADC1
  ADC_ANALOG_PIN_ADC1 = (1U < ADC1D),
  // To force Analog only mode for ADC2
  ADC_ANALOG_PIN_ADC2 = (1U < ADC2D),
  // To force Analog only mode for ADC3
  ADC_ANALOG_PIN_ADC3 = (1U < ADC3D),
  // To force Analog only mode for ADC4
  ADC_ANALOG_PIN_ADC4 = (1U < ADC4D),
  // To force Analog only mode for ADC5
  ADC_ANALOG_PIN_ADC5 = (1U < ADC5D),
  // To force Analog only mode for ADC6
  ADC_ANALOG_PIN_ADC6 = (1U < ADC6D),
  // To force Analog only mode for ADC3
  ADC_ANALOG_PIN_ADC7 = (1U < ADC7D)
};
typedef Int8U AdcAnalogPin; // Type for ADC Pins setting


// Type for 8 bits ADC Result
typedef Int8U AdcRawResult;
// Type for 16 bits ADC Result
typedef Int16U AdcRightAjustedResult;


// Type for saving ADC state to manage priority between conversion if
// One is interrupted and mus t be resatarted
typedef struct
{
  // MUX channel, ADC voltage reference and result format
  Int8U mux;
  // AD enable bit, Auto trigger enable bit, Interrupt mask and clock source
  Int8U controls;
  // Trigger source if auto trigerring is enabled
  Int8U trigger_source;
}AdcState;



//------------------------------------------------------------------------------
/*
 * => Functions:
 */

// Turns on the AD converter.

void micAdcTurnOn(void);

// Turns off the AD converter.

void micAdcTurnOff(void);

// Select conversion clock for AD converter

void micAdcSetClock(AdcClock adc_clock);

// Select specified channel for AD conversion

void micAdcSetChannel(AdcChannel adc_channel);

// Select voltage reference for AD converter

void micAdcSetReference(AdcReference adc_reference);

// Select Result format of the AD coversion i.e. left or right adjusted

void micAdcSetFormat(AdcFormat adc_format);

// Start conversion on currently selected channel.

void micAdcStartConversion(void);

// Clear ADC interrupt flag.

void micAdcClearConversionCompletedFlag(void);

// Check for a conversion in progress on the current channel.

Boolean micAdcConversionIsInProgress(void);

// Check for a conversion complete on the current channel.

Boolean micAdcConversionIsCompleted(void);

// Enable ADC interrupts if interrupts are enabled

void micAdcUnmaskInterrupt(void);

// Disable ADC interrupts

void micAdcMaskInterrupt(void);

// Check if ADC interrupts are unmasked. Return TRUE if this is the case
Boolean micAdcInterrupteAreUnmasked(void);

// Set trigger source for AD coversions.

void micAdcSetTriggerSource(AdcTrigger adc_trigger_source);

// Enable ADC Autotrigger source.
// The trigger source should be selected before use.

void micAdcEnableAutoTrigger(void);

// Disable ADC Autotrigger source.

void micAdcDisableAutoTrigger(void);

// Disable Digital buffer for ADC pin

void micAdcSetAnalogPins( AdcAnalogPin adc_analog_pins_mask );

// enable Digital buffer for ADC pin

void micAdcClearAnalogPins(AdcAnalogPin adc_analog_pins_mask);

// Read the 8 bit result of the conversion

AdcRawResult micAdcReadData8(void);

// Read the 16 bit result of the conversion

AdcRightAjustedResult micAdcReadData16(void);

// Set Channel, Voltage reference and result format of the ADconversion

void micAdcSetFormatReferenceChannel(AdcReference adc_reference,
                                     AdcChannel adc_channel,
                                     AdcFormat adc_format);

// Save the ADC state to manage priority between ADC conversion tasks
// It's necessary to define an AdcState variable prior to use this function

void micAdcSaveState(AdcState *state_ptr);

// Restore previously saved ADC state

void micAdcRestoreState(AdcState *state_ptr);




/******************************************************************************/
#endif // _ATMEGA164_ADC_H_
