#ifndef _ATMEGA164_USART1_H_
#define _ATMEGA164_USART1_H_
/******************************************************************************/
/*                                                                            */
/* => UART 1 management                                                       */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*
 * => Types:
 */

//------------------------------------------------------------------------------
// Available USART 1 modes
enum
{
  // Standard asynchronous UART mode
  USART1_MODE_ASYNCHRONOUS = ((0U << UMSEL11) | (0U << UMSEL10)),
  // Synchronous UART mode
  USART1_MODE_SYNCHRONOUS = ((0U << UMSEL11) | (1U << UMSEL10)),
  // Used as a Master SPI
  USART1_MODE_MASTER_SPI = ((1U << UMSEL11) | (1U << UMSEL10))
};
typedef Int8U Usart1Mode;
// Mask selecting bits used for USART 1 mode selection
#define USART1_MODE_MASK       ((1U << UMSEL11) | (1U << UMSEL10))


//------------------------------------------------------------------------------
// Available USART 1 active clock edge in synchronous mode
enum
{
  // Clock idle level is 0
  USART1_CLOCK_POLARITY_0 = (0U << UCPOL1),
  // Clock idle level is 1
  USART1_CLOCK_POLARITY_1 = (1U << UCPOL1)
};
typedef Int8U Usart1ClockPolarity;
// Value to use for asynchronous mode
#define USART1_NO_CLOCK        (0U << UCPOL1)
// Mask selecting bits used for USART 1 mode selection
#define USART1_MODE_MASK       ((1U << UMSEL11) | (1U << UMSEL10))


//------------------------------------------------------------------------------

typedef Int16U Usart1BaudRate;

// Available USART1 Baud rate in normal speed asynchronous mode
// (UART1: U2X1 = 0) UBRR1 register is a 12 bits register
enum
{
// 300 baud:
UART1_BAUD_300 = (((FOSC_HZ + 150UL) / (16UL * 300UL) - 1UL) & 0x0FFFUL),
// 600 baud:
UART1_BAUD_600 = (((FOSC_HZ + 300UL) / (16UL * 600UL) - 1UL) & 0xFFFUL),
// 1200 baud:
UART1_BAUD_1200 = (((FOSC_HZ + 600UL) / (16UL * 1200UL) - 1UL) & 0xFFFUL),
// 2400 baud:
UART1_BAUD_2400 = (((FOSC_HZ + 1200UL) / (16UL * 2400UL) - 1UL) & 0xFFFUL),
// 4800 baud:
UART1_BAUD_4800 = (((FOSC_HZ + 2400UL) / (16UL * 4800UL) - 1UL) & 0xFFFUL),
// 9600 baud:
UART1_BAUD_9600 = (((FOSC_HZ + 4800UL) / (16UL * 9600UL) - 1UL) & 0xFFFUL),
// 14400 baud:
UART1_BAUD_14400 = (((FOSC_HZ + 7200UL) / (16UL * 14400UL) - 1UL) & 0xFFFUL),
// 19200 baud:
UART1_BAUD_19200 = (((FOSC_HZ + 9600UL) / (16UL * 19200UL) - 1UL) & 0xFFFUL),
// 28800 baud:
UART1_BAUD_28800 = (((FOSC_HZ + 14400UL) / (16UL * 28800UL) - 1UL) & 0xFFFUL),
// 38400 baud:
UART1_BAUD_38400 = (((FOSC_HZ + 19200UL) / (16UL * 38400UL) - 1U) & 0x0FFFU),
// 57600 baud:
UART1_BAUD_57600 = (((FOSC_HZ + 28800UL) / (16UL * 57600UL) - 1UL) & 0xFFFUL),
// 76800 baud:
UART1_BAUD_76800 = (((FOSC_HZ + 38400UL) / (16UL * 78600UL) - 1UL) & 0xFFFUL),
// 115200 baud:
UART1_BAUD_115200 = (((FOSC_HZ + 57600UL) / (16UL * 115200UL) - 1UL) & 0xFFFUL)
};

// Available USART1 Baud rate in high speed asynchronous mode(UART_HS: U2X1 = 1)
// UBRR1 register is a 12 bits register
enum
{
  // 300 baud:
UART1_HS_BAUD_300 = (((FOSC_HZ + 150UL) / (8UL * 300UL) - 1UL) & 0xFFFUL),
// 600 baud:
UART1_HS_BAUD_600 = (((FOSC_HZ + 300UL) / (8UL * 600UL) - 1UL) & 0xFFFUL),
// 1200 baud:
UART1_HS_BAUD_1200 = (((FOSC_HZ + 600UL) / (8UL * 1200UL) - 1UL) & 0xFFFUL),
// 2400 baud:
UART1_HS_BAUD_2400 = (((FOSC_HZ + 1200UL) / (8UL * 2400UL) - 1UL) & 0xFFFUL),
// 4800 baud:
UART1_HS_BAUD_4800 = (((FOSC_HZ + 2400UL) / (8UL * 4800UL) - 1UL) & 0xFFFUL),
// 9600 baud:
UART1_HS_BAUD_9600 = (((FOSC_HZ + 4800UL) / (8UL * 9600UL) - 1UL) & 0xFFFUL),
// 14400 baud:
UART1_HS_BAUD_14400 = (((FOSC_HZ + 7200UL) / (8UL * 14400UL) - 1UL) & 0xFFFUL),
// 19200 baud:
UART1_HS_BAUD_19200 = (((FOSC_HZ + 9599UL) / (8UL * 19200UL) - 1UL) & 0xFFFUL),
// 28800 baud:
UART1_HS_BAUD_28800 = (((FOSC_HZ + 14400UL) / (8UL * 28800UL) - 1UL) & 0xFFFUL),
// 38400 baud:
UART1_HS_BAUD_38400 = (((FOSC_HZ + 19200UL) / (8UL * 38400UL) - 1UL) & 0xFFFUL),
// 57600 baud:
UART1_HS_BAUD_57600 = (((FOSC_HZ + 28800UL) / (8UL * 57600UL) - 1UL) & 0xFFFUL),
// 76800 baud:
UART1_HS_BAUD_76800 = (((FOSC_HZ + 38400UL) / (8UL * 78600UL) - 1UL) & 0xFFFUL),
// 115200 baud:
UART1_HS_BAUD_115200 = (((FOSC_HZ + 57600UL) / (8UL * 115200UL) - 1UL) & 0xFFFUL)
};

// Available USART 1 Baud rate in synchronous mode (USRT1)
// UBRR1 register is a 12 bits register
enum
{
 // 300 baud
 USRT1_BAUD_300 = (((FOSC_HZ + 150UL) / (2UL * 300UL) - 1UL) & 0xFFFUL),
 // 600 baud
 USRT1_BAUD_600 = (((FOSC_HZ + 300UL) / (2UL * 600UL) - 1UL) & 0xFFFUL),
 // 1200 baud
 USRT1_BAUD_1200 = (((FOSC_HZ + 600UL) / (2UL * 1200UL) - 1UL) & 0xFFFUL),
 // 2400 baud
 USRT1_BAUD_2400 = (((FOSC_HZ + 1200UL) / (2UL * 2400UL) - 1UL) & 0xFFFUL),
 // 4800 baud
 USRT1_BAUD_4800 = (((FOSC_HZ + 2400UL) / (2UL * 4800UL) - 1UL) & 0xFFFUL),
 // 9600 baud
 USRT1_BAUD_9600 = (((FOSC_HZ + 4800UL) / (2UL * 9600UL) - 1UL) & 0xFFFUL),
 // 14400 baud
 USRT1_BAUD_14400 = (((FOSC_HZ + 7200UL) / (2UL * 14400UL) - 1UL) & 0xFFFUL),
 // 19200 baud
 USRT1_BAUD_19200 = (((FOSC_HZ + 9599UL) / (2UL * 19200UL) - 1UL) & 0xFFFUL),
 // 28800 baud
 USRT1_BAUD_28800 = (((FOSC_HZ + 14400UL) / (2UL * 28800UL) - 1UL) & 0xFFFUL),
 // 38400 baud
 USRT1_BAUD_38400 = (((FOSC_HZ + 19200UL) / (2UL * 38400UL) - 1UL) & 0xFFFUL),
 // 57600 baud
 USRT1_BAUD_57600 = (((FOSC_HZ + 28800UL) / (2UL * 57600UL) - 1UL) & 0xFFFUL),
 // 76800 baud
 USRT1_BAUD_76800 = (((FOSC_HZ + 38400UL) / (2UL * 78600UL) - 1UL) & 0xFFFUL),
 // 115200 baud
 USRT1_BAUD_115200 = (((FOSC_HZ + 57600UL) / (2UL * 115200UL) - 1UL) & 0xFFFUL)
};


//------------------------------------------------------------------------------
// Available USART 1 parity modes
enum
{
  // No parity bit
  USART1_NO_PARITY = ((0U << UPM11) | (0U << UPM10)),
  // Even parity
  USART1_EVEN_PARITY = ((1U << UPM11) | (0U << UPM10)),
  // Odd parity
  USART1_ODD_PARITY = ((1U << UPM11) | (1U << UPM10))
};
typedef Int8U Usart1ParityMode;
// Mask selecting bits used for USART 0 parity mode selection
#define USART1_PARITY_MODE_MASK        ((1U << UPM11) | (1U << UPM10))


//------------------------------------------------------------------------------
// Available USART 1 Stop bits modes
enum
{
  // 1 stop bit
  USART1_1_STOP = (0U << USBS1),
  // 2 stop bits
  USART1_2_STOPS = (1U << USBS1)
};
typedef Int8U Usart1StopBits;
// Mask selecting bits used for USART 0 stop bit mode selection
#define USART1_STOP_BITS_MASK        (1U << USBS1)

//------------------------------------------------------------------------------
// Available USART 1 Data size in bits
enum
{
// 5  bit data
USART1_5_BITS_DATA = ((0U << UCSZ12) | (((0U << UCSZ11) | (0U << UCSZ10)) >> 1)),
// 6  bit data
USART1_6_BITS_DATA = ((0U << UCSZ12) | (((0U << UCSZ11) | (1U << UCSZ10)) >> 1)),
// 7  bit data
USART1_7_BITS_DATA = ((0U << UCSZ12) | (((1U << UCSZ11) | (0U << UCSZ10)) >> 1)),
// 8  bit data
USART1_8_BITS_DATA = ((0U << UCSZ12) | (((1U << UCSZ11) | (1U << UCSZ10)) >> 1)),
// 9  bit data
USART1_9_BITS_DATA = ((1U << UCSZ12) | (((0U << UCSZ11) | (0U << UCSZ10)) >> 1))
};
typedef Int8U Usart1DataSize;


//------------------------------------------------------------------------------
// Available USART 1 error: 0 means no error
enum
{
  // Framing Error
  USART1_FRAMING_ERROR = (1U << FE1),
  // Data Overrun  Error
  USART1_OVERRUN_ERROR = (1U << DOR1),
  // Data Parity  Error (significant if  enabled)
  USART1_PARITY_ERROR = (1U << UPE1)
};
typedef Int8U Usart1Error;
// Mask selecting framing error bit in an UsartError data
#define USART1_FRAMING_ERROR_MASK   USART1_FRAMING_ERROR
// Mask selecting data overrun error bit in an UsartError data
#define USART1_OVERRUN_ERROR_MASK   USART1_FRAMING_ERROR
// Mask selecting parity error bit in an UsartError data
#define USART1_PARITY_ERROR_MASK   USART1_FRAMING_ERROR


//------------------------------------------------------------------------------
// Available maskable interrupts for USART1
enum
{
  USART1_RX_INTERRUPT = (1U << RXCIE1),
  USART1_TX_INTERRUPT = (1U << TXCIE1),
  USART1_EMPTY_INTERRUPT = (1U << UDRIE1)
};
typedef Int8U Usart1Interrupts;


//------------------------------------------------------------------------------
// Standard USART0 Master SPI Mode available(UCPOL1, UCPHA1):
// Mode 0 = SCK idle level = 0 and sampling edge = leading one
// Mode 1 = SCK idle level = 0 and sampling edge = trailing one
// Mode 2 = SCK idle level = 1 and sampling edge = leading one
// Mode 3 = SCK idle level = 1 and sampling edge = trailing one
enum
{
  // SPI MODE0 (UCPOL = UCPHA = 0):
  // SCK idle level = 0 and bits are sampled on leading edge of SCK:
  USART1_SPI_MODE0 = (0U << UCPOL1) | (0U << UCPHA1),
  // SPI MODE1 (CPOL = 0, CPHA = 1):
  // SCK idle level = 0 and bits are sampled on trailing edge of SCK:
  USART1_SPI_MODE1 = (0U << UCPOL1) | (1U << UCPHA1),
  // SPI MODE2 (CPOL = 1, CPHA = 0):
  // SCK idle level = 1 and bits are sampled on leading edge of SCK:
  USART1_SPI_MODE2 = (1U << UCPOL1) | (0U << UCPHA1),
  // SPI MODE3 (CPOL = CPHA = 1):
  // SCK idle level = 1 and bits are sampled on trailing edge of SCK:
  USART1_SPI_MODE3 = (1U << UCPOL1) | (1U << UCPHA1)
};
typedef Int8U Usart1SpiMode;
// Mask selecting bits used for Master SPI mode selection
#define USART1_SPI_MODE_MASK      ( (1U << UCPOL1)| (1U << UCPHA1))


//------------------------------------------------------------------------------
// Available values transmit order of data bits on the SPI
enum
{
  // SPI Data transfer order is MSB first
  USART1_SPI_MSB_FIRST = (0U << UDORD1),
  // SPI Data transfer order is LSB first
  USART1_SPI_LSB_FIRST = (1U << UDORD1)
};
typedef Int8U Usart1SpiDataOrder;


// USART state Type to be used Powering up or Down USART0
typedef Int8U Usart1State;
#define USART1_STATE_MASK  ((1U << RXCIE1) | (1U << TXCIE1) | (1U << UDRIE1) | \
                            (1U << RXEN1) | (1U << TXEN1))


//------------------------------------------------------------------------------
/*
 * => Functions:
 */

// Read USART 1 data byte for data from 5 to 8 bits long
Int8U micUsart1ReadData8(void);

// Write a byte into USART 1 data Tx register
void micUsart1WriteData8(Int8U usart_data8);

// Read USART 1 data when they are 9 bits long
Int16U micUsart1ReadData16(void);

// Write a 9 bit long into USART 1 data Tx register
void micUsart1WriteData16(Int16U usart_data);

// Read error information about the last recived character from USART 1:
// Framming error, Data overrun and parity
Usart1Error micUsart1ReadError(void);

//  Power up UART 1
void micUsart1PowerUp(void);

//  Power down UART 1
void micUsart1PowerDown(void);

// Turn on both the USART 1 receiver and transmitter
void micUsart1TurnOnRxTx(void);

// Turn off both the USART 1 receiver and transmitter and reduce
// power consumtion at the same time
void micUsart1TurnOffRxTx(void);

// Turns USART 1 Receiver on
void micUsart1TurnOnRx(void);

// Turns USART 1 Receiver off
void micUsart1TurnOffRx(void);

// Turns USART 1 transmitter on
void micUsart1TurnOnTx(void);

// Turns USART 1 transmitter off
void micUsart1TurnOffTx(void);

// Set USART 1 mode to use:
//   usart_mode = USART1_MODE_ASYNCHRONOUS
//                USART1_MODE_SYNCHRONOUS
//                USART1_MODE_MASTER_SPI
void micUsart1SetMode(Usart1Mode usart_mode);

// Set USART 1 synchronous mode clock polarity
//   clock_polarity = USART1_CLOCK_POLARITY_0 (idle level = 0)
//                    USART1_CLOCK_POLARITY_1 (idle level = 1)
void micUsart1SetSynchronousClockPolarity(Usart1ClockPolarity polarity);

// Set Baud rate for USART 1 whatever the mode is:
// normal asynchronous, high speed asynchronous ou synchronous
void micUsart1SetBaudRate(Usart1BaudRate baud_rate);

// Set normal speed asynchronous mode
void micUsart1SetNormalSpeedMode(void);

// Set high speed asynchronous mode
void micUsart1SetHighSpeedMode(void);

// Set USART 1 data size in bits:
// data_size  = Size of data in bits: USART1_5_BITS_DATA
//                                    USART1_6_BITS_DATA
//                                    USART1_7_BITS_DATA
//                                    USART1_8_BITS_DATA
//                                    USART1_9_BITS_DATA
void micUsart1SetDataSize(Usart1DataSize data_size);

// Set USART 0 parity mode:
//  parity_mode  = parity mode to use among: USART1_NO_PARITY
//                                           USART1_EVEN_PARITY
//                                           USART1_ODD_PARITY
void micUsart1SetParityMode(Usart1ParityMode parity_mode);

// Set USART 0 number of stop bit(s) :
//   stop_bits  = Number of stop bits to use among: USART1_1_STOP
//                                                  USART1_2_STOPS
void micUsart1SetStopBits(Usart1StopBits stop_bits);

// Configure USART 1 for mode, data size, parity, stop bits,
// synchronous clock polarity an baud rate.
//
//  usart_mode = USART1_MODE_ASYNCHRONOUS
//               USART1_MODE_SYNCHRONOUS
//               USART1_MODE_MASTER_SPI
//
//
//  clock_polarity = USART1_CLOCK_POLARITY_0 (idle level = 0)
//                   USART1_CLOCK_POLARITY_1 (idle level = 1)
//
//  baud_rate = baud rate selected in the appropriate enumeration for type
//  Usart1BaudRate
void micUsart1Configure(UsartMode usart_mode, UsartDataSize data_size,
                       UsartParityMode parity_mode, UsartStopBits stop_bits,
                       UsartClockPolarity clock_polarity, UsartBaudRate baud_rate);

// Configure UART1 for baud rate, data size, parity, stop bits
//  baud_rate = baud rate selected in the appropriate enumeration for type
//  Usart1BaudRate
//  data_size  = Size of data in bits: USART1_5_BITS_DATA
//                                     USART1_6_BITS_DATA
//                                     USART1_7_BITS_DATA
//                                     USART1_8_BITS_DATA
//                                     USART1_9_BITS_DATA
//
//  parity_mode  = parity mode to use among: USART1_NO_PARITY
//                                           USART1_EVEN_PARITY
//                                           USART1_ODD_PARITY
//
//
//  stop_bits  = Number of stop bits to use among: USART1_1_STOP
//                                                 USART1_2_STOPS
void micUart1Configure(Usart1BaudRate baud_rate,
                       Usart1DataSize data_size,
                       Usart1ParityMode parity_mode,
                       Usart1StopBits stop_bits);


// Set USART 1 Multi processor communication mode: enable address detection
void micUsart1SetMultiProcessorMode(void);

// Cancel USART 1 Multi processor communication mode
void micUsart1CancelMultiProcessorMode(void);

// USART 0 Data Receipt is completed
Boolean micUsart1ReceiptIsCompleted(void);

// USART 1 Data Transmission is completed
Boolean micUsart1TransmissionIsCompleted(void);

// USART 1 Data register is empty
Boolean micUsart1RegisterIsEmpty(void);

// Unmask USART RX interrupts if interrupts are enabled
void micUsart1UnmaskRxInterrupt(void);

// Mask USART 1 RX Complete interrupts
void micUsart1MaskRxInterrupt(void);

// Unmask USART 1 TX interrupts if interrupts are enabled
void micUsart1UnmaskTxInterrupt(void);

// Mask USART 1 TX complete interrupts
void micUsart1MaskTxInterrupt(void);

// Clear USART 1 Tx complete flag empty
void micUsart1ClearTxCompletedFlag(void);

// Unmask USART 1 data register empty interrupts
void micUsart1UnmaskEmptyRegisterInterrupt(void);

// Mask USART 1 data register empty interrupts
void micUsart1MaskEmptyRegisterInterrupt(void);

// Unmask USART 1 selected Rx, Tx and Empty Register interrupts. Ored mask for
// bits: USART1_RX_INTERRUPT, USART1_TX_INTERRUPT and USART1_EMPTY_INTERRUPT
void micUsart1UnmaskInterrupts(Usart1Interrupts usart_interrupts);

// Mask USART 1 selected Rx, Tx and Empty Register interrupts. Ored mask for
// bits: USART1_RX_INTERRUPT, USART1_TX_INTERRUPT and USART1_EMPTY_INTERRUPT
void micUsart1MaskInterrupts(Usart1Interrupts interrupts);

// Allow for saving  the present USART 1 state. The state consist in the
// interrupts and the enabled part of USART 1 (Rx, Tx or both)
Usart1State micUsart1SaveState(void);

// Restore previously saved USART 1 state. The state consist in the
// interrupts and the enabled part of USART 1 (Rx, Tx or both)
void micUsart1RestoreState(Usart1State previous_state);


// Select Master SPI Mode to use (UCPOL1, UCPHA1) for USART 1.
// master_spi_mode = USART1_SPI_MODE0: Idle SCK = 0, sampling = leading edge
//                   USART1_SPI_MODE1: Idle SCK = 0, sampling = trailing edge
//                   USART1_SPI_MODE2: Idle SCK = 1, sampling = leading edge
//                   USART1_SPI_MODE3: Idle SCK = 1, sampling = trailing edge
void micUsart1MasterSpiSetMode(Usart1SpiMode spi_mode);

// Select bit transfer order for data in Master SPI mode for USART 1.
// master_spi_data_order = USART1_SPI_LSB_FIRST to transmit LSB bit first.
//                         USART1_SPI_MSB_FIRST to transmit MSB bit first.
void micUsart1MasterSpiSetDataOrder(Usart1SpiDataOrder spi_data_order);

// Set the Master SPI configuration: Mode , Clock rate(baud), Data order for
// USART 1
// master_spi_mode = USART1_SPI_MODE0: Idle SCK = 0, sampling = leading edge
//                   USART1_SPI_MODE1: Idle SCK = 0, sampling = trailing edge
//                   USART1_SPI_MODE2: Idle SCK = 1, sampling = leading edge
//                   USART1_SPI_MODE3: Idle SCK = 1, sampling = trailing edge
//
// master_spi_data_order = USART1_SPI_LSB_FIRST to transmit LSB bit first.
//                         USART1_SPI_MSB_FIRST to transmit MSB bit first.
//
// baud_rate = baud rate selected in the appropriate enumeration for type
//             Usart1BaudRate
void micUsart1MasterSpiConfigure(Usart1SpiMode spi_mode,
                                 Usart1SpiDataOrder spi_data_order,
                                 Usart1BaudRate baud_rate);


/******************************************************************************/
#endif // _ATMEGA164_USART1_H_
