#ifndef _ATMEGA164_USART0_H_
#define _ATMEGA164_USART0_H_
/******************************************************************************/
/*                                                                            */
/* => UART 0 management                                                       */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*
 * => Types:
 */


// Available USART 0 modes
enum
{
  // Standard asynchronous UART mode
  USART_MODE_ASYNCHRONOUS = ((0U << UMSEL01) | (0U << UMSEL00)),
  // Synchronous UART mode
  USART_MODE_SYNCHRONOUS = ((0U << UMSEL01) | (1U << UMSEL00)),
  // Used as a Master SPI
  USART_MODE_MASTER_SPI = ((1U << UMSEL01) | (1U << UMSEL00))
};
typedef Int8U UsartMode;
// Mask selecting bits used for USART 0 mode selection
#define USART_MODE_MASK        ((1U << UMSEL01) | (1U << UMSEL00))

// Available USART 0 active clock edge in synchronous mode
enum
{
  // Clock idle level is 0
  USART_CLOCK_POLARITY_0 = (0U << UCPOL0),
  // Clock idle level is 1
  USART_CLOCK_POLARITY_1 = (1U << UCPOL0)
};
typedef Int8U UsartClockPolarity;
// Value to use for asynchronous mode
#define USART_NO_CLOCK         (Int8U)(0U << UCPOL0)
// Mask selecting bits used for USART 0 mode selection
#define USART_MODE_MASK        ((1U << UMSEL01) | (1U << UMSEL00))


// Available USART0 Baud rate in normal speed asynchronous mode (UART: U2X0 = 0)
// UBRR0 register is a 12 bits register
enum
{
  // 300 baud
  UART_BAUD_300 = (((FOSC_HZ + 150UL) / (16UL * 300UL) - 1UL) & 0xFFFUL),
  // 600 baud
  UART_BAUD_600 = (((FOSC_HZ + 300UL) / (16UL * 600UL) - 1UL) & 0xFFFUL),
  // 1200 baud
  UART_BAUD_1200 = (((FOSC_HZ + 600UL) / (16UL * 1200UL) - 1UL) & 0xFFFUL),
  // 2400 baud
  UART_BAUD_2400 = (((FOSC_HZ + 1200UL) / (16UL * 2400UL) - 1UL) & 0xFFFUL),
  // 4800 baud
  UART_BAUD_4800 = (((FOSC_HZ + 2400UL) / (16UL * 4800UL) - 1UL) & 0xFFFUL),
  // 9600 baud
  UART_BAUD_9600 = (((FOSC_HZ + 4800UL) / (16UL * 9600UL) - 1UL) & 0xFFFUL),
  // 14400 baud
  UART_BAUD_14400 = (((FOSC_HZ + 7200UL) / (16UL * 14400UL) - 1UL) & 0xFFFUL),
  // 19200 baud
  UART_BAUD_19200 = (((FOSC_HZ + 9600UL) / (16UL * 19200UL) - 1UL) & 0xFFFUL),
  // 28800 baud
  UART_BAUD_28800 = (((FOSC_HZ + 14400UL) / (16UL * 28800UL) - 1UL) & 0xFFFUL),
  // 38400 baud
  UART_BAUD_38400 = (((FOSC_HZ + 19200UL) / (16UL * 38400UL) - 1UL) & 0xFFFUL),
  // 57600 baud
  UART_BAUD_57600 = (((FOSC_HZ + 28800UL) / (16UL * 57600UL) - 1UL) & 0xFFFUL),
  // 76800 baud
  UART_BAUD_76800 = (((FOSC_HZ + 38400UL) / (16UL * 78600UL) - 1UL) & 0xFFFUL),
  // 115200 baud
  UART_BAUD_115200 = (((FOSC_HZ + 57600UL) / (16UL * 115200UL) - 1UL) & 0xFFFUL)
};
// Available USART0 Baud rate in high speed asynchronous mode(UART_HS: U2X0 = 1)
// UBRR0 register is a 12 bits register
enum
{
  // 300 baud
  UART_HS_BAUD_300 = (((FOSC_HZ + 150UL) / (8UL * 300UL) - 1UL) & 0xFFFUL),
  // 600 baud
  UART_HS_BAUD_600 = (((FOSC_HZ + 300UL) / (8UL * 600UL) - 1UL) & 0xFFFUL),
  // 1200 baud
  UART_HS_BAUD_1200 = (((FOSC_HZ + 600UL) / (8UL * 1200UL) - 1UL) & 0xFFFUL),
  // 2400 baud
  UART_HS_BAUD_2400 = (((FOSC_HZ + 1200UL) / (8UL * 2400UL) - 1UL) & 0xFFFUL),
  // 4800 baud
  UART_HS_BAUD_4800 = (((FOSC_HZ + 2400UL) / (8UL * 4800UL) - 1UL) & 0xFFFUL),
  // 9600 baud
  UART_HS_BAUD_9600 = (((FOSC_HZ + 4800UL) / (8UL * 9600UL) - 1UL) & 0xFFFUL),
  // 14400 baud
  UART_HS_BAUD_14400 = (((FOSC_HZ + 7200UL) / (8UL * 14400UL) - 1UL) & 0xFFFUL),
  // 19200 baud
  UART_HS_BAUD_19200 = (((FOSC_HZ + 9599UL) / (8UL * 19200UL) - 1UL) & 0xFFFUL),
  // 28800 baud
  UART_HS_BAUD_28800 = (((FOSC_HZ + 14400UL) / (8UL * 28800UL) - 1UL) & 0xFFFUL),
  // 38400 baud
  UART_HS_BAUD_38400 = (((FOSC_HZ + 19200UL) / (8UL * 38400UL) - 1UL) & 0xFFFUL),
  // 57600 baud
  UART_HS_BAUD_57600 = (((FOSC_HZ + 28800UL) / (8UL * 57600UL) - 1UL) & 0xFFFUL),
  // 76800 baud
  UART_HS_BAUD_76800 = (((FOSC_HZ + 38400UL) / (8UL * 78600UL) - 1UL) & 0xFFFUL),
  // 115200 baud
  UART_HS_BAUD_115200 = (((FOSC_HZ + 57600UL) / (8UL * 115200UL) - 1UL) & 0xFFFUL)
};
// Available USART 0 Baud rate in synchronous mode (USRT)
// UBRR0 register is a 12 bits register
enum
{
  // 300 baud
  USRT_BAUD_300 = (((FOSC_HZ + 150UL) / (2UL * 300UL) - 1UL) & 0xFFFUL),
  // 600 baud
  USRT_BAUD_600 = (((FOSC_HZ + 300UL) / (2UL * 600UL) - 1UL) & 0xFFFUL),
  // 1200 baud
  USRT_BAUD_1200 = (((FOSC_HZ + 600UL) / (2UL * 1200UL) - 1UL) & 0xFFFUL),
  // 2400 baud
  USRT_BAUD_2400 = (((FOSC_HZ + 1200UL) / (2UL * 2400UL) - 1UL) & 0xFFFUL),
  // 4800 baud
  USRT_BAUD_4800 = (((FOSC_HZ + 2400UL) / (2UL * 4800UL) - 1UL) & 0xFFFUL),
  // 9600 baud
  USRT_BAUD_9600 = (((FOSC_HZ + 4800UL) / (2UL * 9600UL) - 1UL) & 0xFFFUL),
  // 14400 baud
  USRT_BAUD_14400 = (((FOSC_HZ + 7200UL) / (2UL * 14400UL) - 1UL) & 0xFFFUL),
  // 19200 baud
  USRT_BAUD_19200 = (((FOSC_HZ + 9599UL) / (2UL * 19200UL) - 1UL) & 0xFFFUL),
  // 28800 baud
  USRT_BAUD_28800 = (((FOSC_HZ + 14400UL) / (2UL * 28800UL) - 1UL) & 0xFFFUL),
  // 38400 baud
  USRT_BAUD_38400 = (((FOSC_HZ + 19200UL) / (2UL * 38400UL) - 1UL) & 0xFFFUL),
  // 57600 baud
  USRT_BAUD_57600 = (((FOSC_HZ + 28800UL) / (2UL * 57600UL) - 1UL) & 0xFFFUL),
  // 76800 baud
  USRT_BAUD_76800 = (((FOSC_HZ + 38400UL) / (2UL * 78600UL) - 1UL) & 0xFFFUL),
  // 115200 baud
  USRT_BAUD_115200 = (((FOSC_HZ + 57600UL) / (2UL * 115200UL) - 1UL) & 0xFFFUL)
};
typedef Int16U UsartBaudRate;



// Available USART 0 parity modes
enum
{
  // No parity bit
  USART_NO_PARITY = ((0U << UPM01) | (0U << UPM00)),
  // Even parity
  USART_EVEN_PARITY = ((1U << UPM01) | (0U << UPM00)),
  // Odd parity
  USART_ODD_PARITY = ((1U << UPM01) | (1U << UPM00))
};
typedef Int8U UsartParityMode;
// Mask selecting bits used for USART 0 parity mode selection
#define USART_PARITY_MODE_MASK        ((1U << UPM01) | (1U << UPM00))


// Available USART 0 Stop bits modes
enum
{
  // 1 stop bit
  USART_1_STOP_BIT = (0U << USBS0),
  // 2 stop bits
  USART_2_STOP_BIT = (1U << USBS0)
};
typedef Int8U UsartStopBits;
// Mask selecting bits used for USART 0 stop bit mode selection
#define USART_STOP_BITS_MASK    (1U << USBS0)


// Available USART 0 Data size in bits
enum
{
  // 5  bit data
  USART_5_BITS_DATA = ((0U << UCSZ02) | (((0U << UCSZ01) | (0U << UCSZ00)) >> 1)),
  // 6  bit data
  USART_6_BITS_DATA = ((0U << UCSZ02) | (((0U << UCSZ01) | (1U << UCSZ00)) >> 1)),
  // 7  bit data
  USART_7_BITS_DATA = ((0U << UCSZ02) | (((1U << UCSZ01) | (0U << UCSZ00)) >> 1)),
  // 8  bit data
  USART_8_BITS_DATA = ((0U << UCSZ02) | (((1U << UCSZ01) | (1U << UCSZ00)) >> 1)),
  // 9  bit data
  USART_9_BITS_DATA = ((1U << UCSZ02) | (((0U << UCSZ01) | (0U << UCSZ00)) >> 1))
};
typedef Int8U UsartDataSize;


// Available USART 0 error: 0 means no error
enum
{
  // Framing Error
  USART_FRAMING_ERROR = (1U << FE0),
  // Data Overrun  Error
  USART_OVERRUN_ERROR = (1U << DOR0),
  // Data Parity  Error (significant if  enabled)
  USART_PARITY_ERROR = (1U << UPE0)
};
typedef Int8U UsartError;
// Mask selecting framing error bit in an UsartError data
#define USART_FRAMING_ERROR_MASK   USART_FRAMING_ERROR
// Mask selecting data overrun error bit in an UsartError data
#define USART_OVERRUN_ERROR_MASK   USART_FRAMING_ERROR
// Mask selecting parity error bit in an UsartError data
#define USART_PARITY_ERROR_MASK   USART_FRAMING_ERROR


// Available maskable interrupts for USART0
enum
{
  USART_RX_INTERRUPT = (1U << RXCIE0),
  USART_TX_INTERRUPT = (1U << TXCIE0),
  USART_EMPTY_INTERRUPT = (1U << UDRIE0)
};
typedef Int8U UsartInterrupts;


// Standard USART0 Master SPI Mode available(UCPOL0, UCPHA0):
// Mode 0 = SCK idle level = 0 and sampling edge = leading one
// Mode 1 = SCK idle level = 0 and sampling edge = trailing one
// Mode 2 = SCK idle level = 1 and sampling edge = leading one
// Mode 3 = SCK idle level = 1 and sampling edge = trailing one
enum
{
  // SPI MODE0 (UCPOL = UCPHA = 0),
  // SCK idle level = 0 and bits are sampled on leading edge of SCK:
  USART_SPI_MODE0 = (0U << UCPOL0) | (0U << UCPHA0),
  // SPI MODE1 (CPOL = 0, CPHA = 1),
  // SCK idle level = 0 and bits are sampled on trailing edge of SCK:
  USART_SPI_MODE1 = (0U << UCPOL0) | (1U << UCPHA0),
  // SPI MODE2 (CPOL = 1, CPHA = 0),
  // SCK idle level = 1 and bits are sampled on leading edge of SCK:
  USART_SPI_MODE2 = (1U << UCPOL0) | (0U << UCPHA0),
  // SPI MODE3 (CPOL = CPHA = 1),
  // SCK idle level = 1 and bits are sampled on trailing edge of SCK:
  USART_SPI_MODE3 = (1U << UCPOL0) | (1U << UCPHA0)
};
typedef Int8U UsartSpiMode;
// Mask selecting bits used for SPI mode selection
#define USART_SPI_MODE_MASK      ( (1U << UCPOL0)| (1U << UCPHA0))


// Available values transmit order of data bits on the SPI
enum
{
  // SPI Data transfer order is MSB first
  USART_SPI_MSB_FIRST = (0U << UDORD0),
  // SPI Data transfer order is LSB first
  USART_SPI_LSB_FIRST = (1U << UDORD0)
};
typedef Int8U UsartSpiDataOrder;


// USART state Type to be used Powering up or Down USART0
typedef Int8U UsartState;
#define USART_STATE_MASK  ((1U << RXCIE0) | (1U << TXCIE0) | (1U << UDRIE0) | \
                           (1U << RXEN0) | (1U << TXEN0))


//------------------------------------------------------------------------------
/*
 * => Functions:
 */

// Read USART 0 data byte for data from 5 to 8 bits long

Int8U micUsartReadData8(void);

// Write a byte into USART0 data Tx register

void micUsartWriteData8(Int8U usart_data8);

// Read USART 0 data when they are 9 bits long

Int16U micUsartReadData16(void);

// Write a 9 bit long into USART0 data Tx register

void micUsartWriteData16(Int16U usart_data);

// Read error information about the last recived character from USART 0:
// Framming error, Data overrun and parity

UsartError micUsartReadError(void);

// Turn on both the USART 0 receiver and transmitter

void micUsartTurnOnRxTx(void);

// Turn off both the USART 0 receiver and transmitter and reduce
// power consumtion at the same time

void micUsartTurnOffRxTx(void);

// Turns USART 0 Receiver on

void micUsartTurnOnRx(void);

// Turns USART 0 Receiver off

void micUsartTurnOffRx(void);

// Turns USART 0 transmitter on

void micUsartTurnOnTx(void);

// Turns USART 0 transmitter off

void micUsartTurnOffTx(void);

// Set USART 0 mode:
//   usart_mode = USART_MODE_ASYNCHRONOUS
//                USART_MODE_SYNCHRONOUS
//                USART_MODE_MASTER_SPI

void micUsartSetMode(UsartMode usart_mode);

//  Set USART 0 synchronous mode clock polarity
//   clock_polarity = USART_CLOCK_POLARITY_0 (idle level = 0)
//                    USART_CLOCK_POLARITY_1 (idle level = 1)

void micUsartSetSynchronousClockPolarity (UsartClockPolarity polarity);

// Set Baud rate for USART 0 whatever the mode is:
// normal asynchronous, high speed asynchronous ou synchronous
// baud_rate = baud rate selected in the appropriate enumeration for type
//             UsartBaudRate
void micUsartSetBaudRate(UsartBaudRate baud_rate);

// Set normal speed asynchronous mode

void micUsartSetNormalSpeedMode(void);

// Set high speed asynchronous mode

void micUsartSetHighSpeedMode(void);

// Set USART 0 data size in bits:
// data_size  = Size of data in bits: USART_5_BITS_DATA
//                                    USART_6_BITS_DATA
//                                    USART_7_BITS_DATA
//                                    USART_8_BITS_DATA
//                                    USART_9_BITS_DATA

void micUsartSetDataSize(UsartDataSize data_size);

// Set USART 0 parity mode:
//  parity_mode  = parity mode to use among: USART_NO_PARITY
//                                           USART_EVEN_PARITY
//                                           USART_ODD_PARITY

void micUsartSetParityMode(UsartParityMode parity_mode);

// Set USART 0 number of stop bit(s) :
//   stop_bits  = Number of stop bits to use among: USART_1_STOP_BIT
//                                                  USART_2_STOP_BIT

void micUsartSetStopBits(UsartStopBits stop_bits);

// Configure UART for mode, data size, parity, stop bits,
// synchronous clock polarity an baud rate
//
//  usart_mode = USART_MODE_ASYNCHRONOUS
//               USART_MODE_SYNCHRONOUS
//               USART_MODE_MASTER_SPI
//
//  data_size  = Size of data in bits: USART_5_BITS_DATA
//                                     USART_6_BITS_DATA
//                                     USART_7_BITS_DATA
//                                     USART_8_BITS_DATA
//                                     USART_9_BITS_DATA
//
//  parity_mode  = parity mode to use among: USART_NO_PARITY
//                                           USART_EVEN_PARITY
//                                           USART_ODD_PARITY
//
//
//  stop_bits  = Number of stop bits to use among: USART_1_STOP
//                                                 USART_2_STOPS
//
//  clock_polarity = USART_CLOCK_POLARITY_0 (idle level = 0)
//                   USART_CLOCK_POLARITY_1 (idle level = 1)
//
//  baud_rate = baud rate selected in the appropriate enumeration for type
//              UsartBaudRate

void micUsartConfigure(UsartMode usart_mode,
                       UsartDataSize data_size,
                       UsartParityMode parity_mode,
                       UsartStopBits stop_bits,
                       UsartClockPolarity clock_polarity,
                       UsartBaudRate baud_rate);

// Configure UART for baud rate, data size, parity, stop bits
//  baud_rate = baud rate selected in the appropriate enumeration for type
//  Usart1BaudRate
//  data_size  = Size of data in bits: USART_5_BITS_DATA
//                                     USART_6_BITS_DATA
//                                     USART_7_BITS_DATA
//                                     USART_8_BITS_DATA
//                                     USART_9_BITS_DATA
//
//  parity_mode  = parity mode to use among: USART_NO_PARITY
//                                           USART_EVEN_PARITY
//                                           USART_ODD_PARITY
//
//
//  stop_bits  = Number of stop bits to use among: USART_1_STOP
//                                                 USART_2_STOPS
void micUartConfigure(UsartBaudRate baud_rate,
                      UsartDataSize data_size,
                      UsartParityMode parity_mode,
                      UsartStopBits stop_bits);

// Set USART 0 Multi processor communication mode: enable address detection

void micUsartSetMultiProcessorMode(void);

// Cancel USART 0 Multi processor communication mode

void micUsartCancelMultiProcessorMode(void);

// USART 0 Data Receipt is completed

Boolean micUsartReceiptIsCompleted(void);

// USART 0 Data Transmission is completed

Boolean micUsartTransmissionIsCompleted(void);

// USART 0 Data register is empty

Boolean micUsartRegisterIsEmpty(void);

void micUsartClearTxFlag(void);

// Unmask USART 0 RX interrupts if interrupts are enabled

void micUsartUnmaskRxInterrupt(void);

// Mask USART 0 RX Complete interrupts

void micUsartMaskRxInterrupt(void);

// Unmask USART 0 TX interrupts if interrupts are enabled

void micUsartUnmaskTxInterrupt(void);

// Mask USART 0 TX complete interrupts

void micUsartMaskTxInterrupt(void);

// Clear USART 0 Tx complete flag empty

void micUsartClearTxCompletedFlag(void);

// Unmask USART 0 data register empty interrupts

void micUsartUnmaskEmptyRegisterInterrupt(void);

// Mask USART 0 data register empty interrupts

void micUsartMaskEmptyRegisterInterrupt(void);

// Unmask USART 0 selected Rx, Tx and Empty Register interrupts. Ored mask for
// bits: USART_RX_INTERRUPT, USART_TX_INTERRUPT and USART_EMPTY_INTERRUPT

void micUsartUnmaskInterrupts(UsartInterrupts usart_interrupts);

// Mask USART 0 selected Rx, Tx and Empty Register interrupts. Ored mask for
// bits: USART_RX_INTERRUPT, USART_TX_INTERRUPT and USART_EMPTY_INTERRUPT

void micUsartMaskInterrupts(UsartInterrupts interrupts);

// Allow for saving  the present USART 0 state. The state consist in the
// interrupts and the enabled part of the USART0 (Rx, Tx or both)

UsartState micUsartSaveState(void);

// Restore previously saved USART0 state. The state consist in the
// interrupts and the enabled part of the USART0 (Rx, Tx or both)

void micUsartRestoreState(UsartState previous_state);


// Select Master SPI Mode to use (UCPOL0, UCPHA0) for USART 0.
// master_spi_mode = USART_SPI_MODE0: Idle SCK = 0, sampling = leading edge
//                   USART_SPI_MODE1: Idle SCK = 0, sampling = trailing edge
//                   USART_SPI_MODE2: Idle SCK = 1, sampling = leading edge
//                   USART_SPI_MODE3: Idle SCK = 1, sampling = trailing edge

void micUsartMasterSpiSetMode(UsartSpiMode spi_mode);

// Select bit transfer order for data in Master SPI mode for USART 0.
//   master_spi_data_order = USART_SPI_LSB_FIRST to transmit LSB bit first.
//                           USART_SPI_MSB_FIRST to transmit MSB bit first.

void micUsartMasterSpiSetDataOrder(UsartSpiDataOrder spi_data_order);

// Set the Master SPI configuration: Mode , Clock rate(baud), Data order for
// USART 0
// master_spi_mode = USART_SPI_MODE0: Idle SCK = 0, sampling = leading edge
//                   USART_SPI_MODE1: Idle SCK = 0, sampling = trailing edge
//                   USART_SPI_MODE2: Idle SCK = 1, sampling = leading edge
//                   USART_SPI_MODE3: Idle SCK = 1, sampling = trailing edge
//
// master_spi_data_order = USART_SPI_LSB_FIRST to transmit LSB bit first.
//                         USART_SPI_MSB_FIRST to transmit MSB bit first.
//
// baud_rate = baud rate selected in the appropriate enumeration for type
//             UsartBaudRate
void micUsartMasterSpiConfigure(UsartSpiMode spi_mode,
                                UsartSpiDataOrder spi_data_order,
                                UsartBaudRate baud_rate);


//  Power up USART
void micUsartPowerUp(void);


/******************************************************************************/
#endif  // _ATMEGA164_USART_0_H_

