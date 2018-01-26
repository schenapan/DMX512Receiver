#ifndef _ATMEGA164_SPI_H_
#define _ATMEGA164_SPI_H_
/******************************************************************************/
/**                                                                          **/
/** => SPI 0 management                                                      **/
/**                                                                          **/
/**--------------------------------------------------------------------------**/
/*
 * => Types:
 */

// Added bit of clock prescaler for SPI of
#define SPR2   (SPR10 + 1U)
//  SPI clock selection (division of CPU clock)
enum
{
  // SPI clock = CPU clock / 2
  SPI_CLK_DIV_2 = (1U << SPR2) | (0U << SPR10) | (0U << SPR00),
  // SPI clock = CPU clock / 4
  SPI_CLK_DIV_4 = (0U << SPR2) | (0U << SPR10) | (0U << SPR00),
  // SPI clock = CPU clock / 8
  SPI_CLK_DIV_8 = (1U << SPR2) | (0U << SPR10) | (1U << SPR00),
  // SPI clock = Fosc / 16
  SPI_CLK_DIV_16 = (0U << SPR2) | (0U << SPR10) | (1U << SPR00),
  // SPI clock = Fosc / 32
  SPI_CLK_DIV_32 = (1U << SPR2) | (1U << SPR10) | (0U << SPR00),
  // SPI clock = Fosc / 64
  SPI_CLK_DIV_64 = (0U << SPR2) | (1U << SPR10) | (0U << SPR00),
  // SPI clock = Fosc / 128
  SPI_CLK_DIV_128 = (0U << SPR2) | (1U << SPR10) | (1U << SPR00)
};
typedef Int8U SpiClock;
// Mask selecting bits used for SPI conversion clock selection in SPCR
#define SPI_CLOCK_DIV_MASK  ((1U << SPR10) | (1U << SPR00))


// Standard  SPI Mode available(CPOL0, CPHA0):
// Mode 0 = SCK idle level = 0 and sampling edge = leading one
// Mode 1 = SCK idle level = 0 and sampling edge = trailing one
// Mode 2 = SCK idle level = 1 and sampling edge = leading one
// Mode 3 = SCK idle level = 1 and sampling edge = trailing one
enum
{
  // SPI MODE0 (CPOL = CPHA = 0),
  // SCK idle level = 0 and bits are sampled on leading edge of SCK:
  SPI_MODE0 = (0U << CPOL0) | (0U << CPHA0),
  // SPI MODE1 (CPOL = 0, CPHA = 1),
  // SCK idle level = 0 and bits are sampled on trailing edge of SCK:
  SPI_MODE1 = (0U << CPOL0) | (1U << CPHA0),
  // SPI MODE2 (CPOL = 0, CPHA = 1),
  // SCK idle level = 1 and bits are sampled on leading edge of SCK:
  SPI_MODE2 = (1U << CPOL0) | (0U << CPHA0),
  // SPI MODE3 (CPOL = CPHA = 1),
  // SCK idle level = 1 and bits are sampled on trailing edge of SCK:
  SPI_MODE3 = (1U << CPOL0) | (1U << CPHA0)
};
typedef Int8U SpiMode;
// Mask selecting bits used for SPI mode selection
#define SPI_MODE_MASK      ((1U << CPOL0) | (1U << CPHA0))


// Available values to select between Master or Slave SPI function
enum
{
  // SPI Master Mode
  SPI_SLAVE = (0U << MSTR0),
  // SPI Master Mode
  SPI_MASTER = (1U << MSTR0)
};
typedef Int8U SpiFunction;
// Mask selecting bits used for SPI function selection
#define SPI_FUNCTION_MASK      (1U << MSTR)


// Available values transmit order of data bits on the SPI
enum
{
  // SPI Data transfer order is MSB first
  SPI_MSB_FIRST = (0U << DORD0),
  // SPI Data transfer order is LSB first
  SPI_LSB_FIRST = (1U << DORD0)
};
typedef Int8U SpiDataOrder;


// SPI state to manage Priority between accessing SPI
typedef Int16U SpiState;


//------------------------------------------------------------------------------
/*
 * => Functions:
 */

// Turns on the SPI peripheral.

void micSpiTurnOn(void);

// Turns off the SPI peripheral.
void micSpiTurnOff(void);

// Set SPI clock rate from Fosc division :
//   spi_clock = SPI_CLK_DIV_2 => Fosc/2
//               SPI_CLK_DIV_4 => Fosc/4
//               SPI_CLK_DIV_8 => Fosc/8
//               SPI_CLK_DIV_16 => Fosc/16
//               SPI_CLK_DIV_32 => Fosc/32
//               SPI_CLK_DIV_64 => Fosc/64
// Beware: maximum allowed speed is Fosc/4 when in slave mode
void micSpiSetClockRate( SpiClock spi_clock );

// Double SPI serial bus clock rate.
// Beware: maximum allowed speed is Fosc/4 when in slave mode

// static void micSpiDoubleClockRate(void);

// Set SPI function to master (spi_function = SPI_MASTER)
// or slave (spi_function = SPI_SLAVE)

void micSpiSetFunction( SpiFunction spi_function );

// Select SPI Mode to use (CPOL, CPHA).
// SPI_MODE0 = Idle SCK = 0 and bits are sampled on leading edge of SCK
// SPI MODE1 = Idle SCK = 0 and bits are sampled on trailing edge of SCK
// SPI MODE2 = Idle SCK = 1 and bits are sampled on leading edge of SCK
// SPI MODE3 = Idle SCK = 1 and bits are sampled on trailing edge of SCK
// Beware: maximum allowed speed is Fosc/4 when in slave mode.

void micSpiSetMode(SpiMode spi_mode);

// Select bit transfer order for data.
// data_order = SPI_LSB_FIRST to transmit LSB bit first.
//            = SPI_MSB_FIRST to transmit MSB bit first.

void micSpiSetDataOrder(SpiDataOrder data_order);

// Set the SPI configuration: Master/Slave, Mode , clock rate, Data order
void micSpiConfigure(SpiFunction master_slave, SpiMode spi_mode,
                     SpiClock spi_clock, SpiDataOrder data_order);

// Unmask SPI interrupt flag.

void micSpiUnmaskInterrupt(void);

// Mask SPI interrupt flag.

void micSpiMaskInterrupt(void);

// Check for a write colision during previous transfer. Return TRUE in this case

Boolean micSpiWriteColisionIsDetected(void);

// Check if the SPI transfer is complete (SPIF0 = 1).
// Return TRUE if transfer is complete

Boolean micSpiTransferIsCompleted(void);

// Accesse SPSR to enable clearing of SPIF and WCOL flags in status register
// the next time the SPI data register SPDR will be accessed.

void micSpiEnableStatusFlagsClearing(void);

// Read the present SPI state.

SpiState micSpiSaveState(void);

// Restore a previously saved state SPI state.

void micSpiRestoreState(SpiState previous_state);

// Write the data to send in the SPI register (SPDR)

void micSpiWriteData(Int8U written_data);

// Read the received data from the SPI register (SPDR)

Int8U micSpiReadData(void);


/******************************************************************************/
#endif // _ATMEGA164_SPI_H_
