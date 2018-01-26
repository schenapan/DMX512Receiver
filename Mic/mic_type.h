#ifndef _MIC_TYPES_H_
#define _MIC_TYPES_H_
/******************************************************************************/
/*                                                                            */
/* => generic type definition                                                 */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// Autorise définition des bits des registres de l'ATmega324P par "IOM324.H"
#ifndef ENABLE_BIT_DEFINITIONS
  #define ENABLE_BIT_DEFINITIONS
#endif

/*----------------------------------------------------------------------------*/
/*                                                                            */
/*                         Lower case name for SFRs                           */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#define udr1    UDR1        // USART1 I/O Data Register
#define ubrr1   UBRR1       // USART1 Baud Rate Register
#define ucsr1c  UCSR1C      // USART1 Control and Status Register C
#define ucsr1b  UCSR1B      // USART1 Control and Status Register B
#define ucsr1a  UCSR1A      // UsART1 Control and Status Register A

#define udr0    UDR0        // USART0 I/O Data Register
#define ubrr0   UBRR0       // USART0 Baud Rate Register
#define ucsr0c  UCSR0C      // USART0 Control and Status Register C
#define ucsr0b  UCSR0B      // USART0 Control and Status Register B
#define ucsr0a  UCSR0A      // UsART0 Control and Status Register A

#define twamr   TWAMR       // TWI Address Mask Register
#define twcr    TWCR        // TWI Control Register
#define twdr    TWDR        // TWI Data Register
#define twar    TWAR        // TWI Address Register
#define twsr    TWSR        // TWI status Register
#define twbr    TWBR        // TWI Bit rate Register

#define assr    ASSR        // ASynchronous mode Status Register (for T2)

#define ocr2b    OCR2B      // Timer/Counter2 Output Compare B Register
#define ocr2a    OCR2A      // Timer/Counter2 Output Compare A Register
#define tcnt2    TCNT2      // Timer/Counter 2
#define tccr2b   TCCR2B     // Timer/Counter 2 Control Register
#define tccr2a   TCCR2A     // Timer/Counter 2 Control Register

#define ocr1b   OCR1B       // Timer/Counter1 Output Compare Register B
#define ocr1a   OCR1A       // Timer/Counter1 Output Compare Register A
#define icr1    ICR1        // Timer/Counter1 1 Input Capture Register
#define tcnt1   TCNT1       // Timer/Counter 1
#define tccr1c  TCCR1C      // Timer/Counter 1 Control and Status Register C
#define tccr1b  TCCR1B      // Timer/Counter 1 Control and Status Register B
#define tccr1a  TCCR1A      // Timer/Counter 1 Control Register A

#define didr1   DIDR1       // Digital Input Disable Register 1
#define didr0   DIDR0       // Digital Input Disable Register 0

#define admux   ADMUX       // ADC MUX
#define adcsrb  ADCSRB      // ADC Control and Status Register B
#define adcsra  ADCSRA      // ADC Control and Status Register A
#define adc     ADC         // ADC Data register
#define adch    ADCH        // ADC Data high byte register
#define adcl    ADCL        // ADC Data low byte register

#define timsk2  TIMSK2      // Timer/Counter 2 Interrupt MaSK register
#define timsk1  TIMSK1      // Timer/Counter 1 Interrupt MaSK register
#define timsk0  TIMSK0      // Timer/Counter 0 Interrupt MaSK register

#define pcmsk3  PCMSK3      // Port Change Interrupt MaSK register 3
#define pcmsk2  PCMSK2      // Port Change Interrupt MaSK register 2
#define pcmsk1  PCMSK1      // Port Change Interrupt MaSK register 1
#define pcmsk0  PCMSK0      // Port Change Interrupt MaSK register 0
#define pcicr   PCICR       // Port Change Interrupt Control register
#define pcifr   PCIFR       // Port Change Interrupt Flag register

#define eicra   EICRA       // External Interrupt Control Register A
#define eimsk   EIMSK       // External Interrupt MaSK register
#define eifr    EIFR        // External Interrupt Flag Register

#define osccal   OSCCAL     // OSCillator CALibration Register

#define prr     PRR0         // Power Reduction Register

#define clkpr   CLKPR       // CLock Prescale Register

#define wdtcsr  WDTCSR      // Watchdog Timer Control Register

//#define sreg    SREG        // Status REGister

//#define sp      SP          // Stack Pointer
//#define sph     SPH         // Stack Pointer High byte
//#define spl     SPL         // Stack Pointer Low byte

//#define rampz   RAMPZ     // Extended Z Pointer register(high byte) for ELPM
//                          // & SPM instructions

#define spmcsr  SPMCSR      // Store Program Memory Control & Status Register

#define mcucr   MCUCR       // MCU general Control Register
#define mcusr   MCUSR       // MCU general Status Register

#define smcr    SMCR        // Sleep Mode Control Register

#define ocdr    OCDR        // On Chip Debug Register

//#define mondr   MONDR       // MONitor Data Register ?

#define acsr    ACSR        // Analog Comparator Control and Status Register

#define spdr    SPDR0        // SPI I/O Data Register
#define spsr    SPSR0        // SPI Status Register
#define spcr    SPCR0        // SPI Control Register

#define gpior2  GPIOR2      // General I/O register 2
#define gpior1  GPIOR1      // General I/O register 1
#define gpior0  GPIOR0      // General I/O register 0

#define ocr0b   OCR0B       // Timer/Counter0 Output Compare B Register
#define ocr0a   OCR0A       // Timer/Counter0 Output Compare A Register
#define tcnt0   TCNT0       // Timer/Counter 0
#define tccr0b  TCCR0B      // Timer/Counter 0 Control Register B
#define tccr0a  TCCR0A      // Timer/Counter 0 Control Register B

#define gtccr   GTCCR       // General Timer/Counter control Register

#define eear    EEAR        // EEPROM Address Register
#define eedr    EEDR        // EEPROM Data Register
#define eecr    EECR        // EEPROM Control Register

#define tifr2   TIFR2       // Timer/Counter Interrupt Flag register 2
#define tifr1   TIFR1       // Timer/Counter Interrupt Flag register 1
#define tifr0   TIFR0       // Timer/Counter Interrupt Flag register 0

#define pind    PIND        // Input Pins, Port D
#define ddrd    DDRD        // Data Direction Register, Port D
#define portd   PORTD       // Data Register, Port D

#define pinc    PINC        // Input Pins, Port C
#define ddrc    DDRC        // Data Direction Register, Port C
#define portc   PORTC       // Data Register, Port C

#define pinb    PINB        // Input Pins, Port B
#define ddrb    DDRB        // Data Direction Register, Port B
#define portb   PORTB       // Data Register, Port B

#define pina    PINA        // Input Pins, Port A
#define ddra    DDRA        // Data Direction Register, Port A
#define porta   PORTA       // Data Register, Port A

#define osccal  OSCCAL      // Internal RC Calibration register


/*----------------------------------------------------------------------------*/

// Bit alias for use USART0 Master SPI Mode: Clock pahse selection bit
// #define UCPHA0      UCSZ00
// Bit alias for use USART0 Master SPI Mode: Data order bit
#define UDORD0      UCSZ10


// Bit alias for use USART0 Master SPI Mode: Clock pahse selection bit
// #define UCPHA1      UCSZ01
// Bit alias for use USART0 Master SPI Mode: Data order bit
#define UDORD1      UCSZ11



/******************************************************************************/


/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/


/*******************************************************************************
*                                                                              *
*                        Exported constants for the module                     *
*                                                                              *
*******************************************************************************/

/** vitesse du cpu */
#define FOSC_HZ                       8000000UL

/** timeout du watchdog */
#define PRODUCT_WDTPR      WDTPR_256K

/*******************************************************************************
*                                                                              *
*                        Exported types for the module                         *
*                                                                              *
*******************************************************************************/

/*
 * Basic types for the microcontroler
 */

// Unsigned 8 bits integer type
typedef unsigned char Int8U;
// Unsigned 16 bits integer type
typedef unsigned int Int16U;
// Unsigned 32 bits integer type
typedef unsigned long Int32U;

// Signed 8 bits integer type
typedef signed char Int8S;
// Signed 16 bits integer type
typedef signed int Int16S;
// Signed 32 bits integer type
typedef signed long Int32S;

// Boolean type
typedef Int8U Boolean;
  #define FALSE       0U
  #define TRUE        1U

// Null pointer
#ifndef NUL
  #define NUL     ((void *)0U)
#endif

// definit un type de pointeur de fonction pour abstraire les interruptions micro
typedef void (*p_isr_callback)(void);

/******************************************************************************/
#endif  // _MIC_TYPES_H_
