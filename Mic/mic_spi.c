/*******************************************************************************
***                                                                          ***
**                                                                            **
**                             SPI MANAGEMENT                                 **
**                                                                            **
***                                                                          ***
*******************************************************************************/

// Include header for this micrcontroller
#include "Mic/mic_micro.h"


/*******************************************************************************
*                                                                              *
*  Name: micSpiTurnOn                                                          *
*                                                                              *
*  Subject: Turns on the SPI serial bus.                                       *
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

void micSpiTurnOn(void)
{
  // To Clear WCOL and SPIF the next time SPDR will be accessed
  spsr = spsr;

  // Power up SPI
  prr &= ~(1U << PRSPI);

  // Enable SPI
  spcr |= (1U << SPE0);

  return;
}


/*******************************************************************************
*                                                                              *
*  Name: micSpiTurnOff                                                         *
*                                                                              *
*  Subject: turns off the SPI serial bus.                                      *
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

void micSpiTurnOff(void)
{
  // Power up SPI
  prr &= ~(1U << PRSPI);

  // Turn off SPI peripherals
  spcr &= ~((1U << SPE0) | (1U << SPIE0));

  // Reduce power compsumption
  prr |= (1U << PRSPI);
  return;
}


/*******************************************************************************
*                                                                              *
*  Name: micSpiSetClockRate                                                    *
*                                                                              *
*  Subject: Select SPI clock frequency division from Fosc.                     *
*           Beware: maximum allowed speed is Fosc/4 when in slave mode.        *
*                                                                              *
*                                                                              *
*  Input(s): spi_clock = CPU clock division to use for SPI.                    *
*                          SPI_CLK_DIV_2 => Fosc/2                             *
*                          SPI_CLK_DIV_4 => Fosc/4                             *
*                          SPI_CLK_DIV_8 => Fosc/8                             *
*                          SPI_CLK_DIV_16 => Fosc/16                           *
*                          SPI_CLK_DIV_32 => Fosc/32                           *
*                          SPI_CLK_DIV_64 => Fosc/64                           *
*                                                                              *
*  Output(s): None                                                             *
*                                                                              *
*  Modified Global variables: None                                             *
*                                                                              *
*  Necessary Interrupts: None                                                  *
*                                                                              *
*******************************************************************************/

void micSpiSetClockRate( SpiClock spi_clock )
{
  // Set SPI Clock prescaler
  spcr = (spcr & ~SPI_CLOCK_DIV_MASK) | (spi_clock & SPI_CLOCK_DIV_MASK);

  // Set frequency doubling bit as required
  spsr = 0x00U;
  if ( 0U != (spi_clock & (1U << SPR2)) )
  {
    spsr = (1U << SPI2X0);
  }
  return;
}


/*******************************************************************************
*                                                                              *
*  Name: micSpiDoubleClockRate                                                 *
*                                                                              *
*  Subject: Double SPI  clock rate.                                            *
*           Beware: maximum allowed speed is Fosc/4 when in slave mode.        *
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

static void micSpiDoubleClockRate(void)
{
  spsr = (1U << SPI2X0);
  return;
}


/*******************************************************************************
*                                                                              *
*  Name: micSpiSetFunction                                                     *
*                                                                              *
*  Subject: Set SPI Function (master or Slave)                                 *
*                                                                              *
*                                                                              *
*  Input(s): spi_function =  SPI_MASTER if we are a master.                    *
*                            SPI_SLAVE if we are a slave.                      *
*                                                                              *
*  Output(s): None                                                             *
*                                                                              *
*  Modified Global variables: None                                             *
*                                                                              *
*  Necessary Interrupts: None                                                  *
*                                                                              *
*******************************************************************************/

void micSpiSetFunction( SpiFunction spi_function )
{
  spcr = (spcr & ~(1U << MSTR0)) | (spi_function & (1U << MSTR0));
  return;
}


/*******************************************************************************
*                                                                              *
*  Name: micSpiSetMode                                                         *
*                                                                              *
*  Subject: Select SPI Mode to use (CPOL, CPHA).                               *
*                                                                              *
*                                                                              *
*  Input(s): spi_mode = CPU clock division to use for SPI.                     *
*     - SPI_MODE0 = Idle SCK = 0 and bits are sampled on leading edge of SCK   *
*     - SPI MODE1 = Idle SCK = 0 and bits are sampled on trailing edge of SCK  *
*     - SPI MODE2 = Idle SCK = 1 and bits are sampled on leading edge of SCK   *
*     - SPI MODE3 = Idle SCK = 1 and bits are sampled on trailing edge of SCK  *
*                                                                              *
*  Output(s): None                                                             *
*                                                                              *
*  Modified Global variables: None                                             *
*                                                                              *
*  Necessary Interrupts: None                                                  *
*                                                                              *
*******************************************************************************/

void micSpiSetMode(SpiMode spi_mode)
{
  spcr = (spcr & ~(SPI_MODE_MASK)) | (spi_mode & SPI_MODE_MASK);
  return;
}


/*******************************************************************************
*                                                                              *
*  Name: micSpiSetDataOrder                                                    *
*                                                                              *
*  Subject: Select bit transfer order for data.                                *
*                                                                              *
*                                                                              *
*  Input(s): data_order = SPI_LSB_FIRST to transmit LSB bit first.             *
*                       = SPI_MSB_FIRST to transmit MSB bit first.             *
*                                                                              *
*  Output(s): None                                                             *
*                                                                              *
*  Modified Global variables: None                                             *
*                                                                              *
*  Necessary Interrupts: None                                                  *
*                                                                              *
*******************************************************************************/

void micSpiSetDataOrder(SpiDataOrder data_order)
{
  spcr = (spcr & ~(1U << DORD0)) | (data_order & (1U << DORD0));
  return;
}


/*******************************************************************************
*                                                                              *
*  Name: micSpiConfigure                                                       *
*                                                                              *
*  Subject: Enables and set the SPI configuration.                             *
*           Beware: maximum allowed speed is Fosc/4 when in slave mode.        *
*                                                                              *
*                                                                              *
*  Input(s): master_slave = SPI_MASTER if we are a master.                     *
*                           SPI_SLAVE if we are a slave.                       *
*                                                                              *
*            spi_mode =  SPI_MODE 0 (mode 0: CPOL= 0 & CPHA = 0)               *
*                        SPI_MODE 1 (mode 1: CPOL= 0 & CPHA = 1)               *
*                        SPI_MODE 2 (mode 2: CPOL= 1 & CPHA = 0)               *
*                        SPI_MODE 3 (mode 3: CPOL= 1 & CPHA = 1)               *
*                                                                              *
*            spi_clock = SPI_CLK_DIV_2 => Fosc/2                               *
*                        SPI_CLK_DIV_4 => Fosc/4                               *
*                        SPI_CLK_DIV_8 => Fosc/8                               *
*                        SPI_CLK_DIV_16 => Fosc/16                             *
*                        SPI_CLK_DIV_32 => Fosc/32                             *
*                        SPI_CLK_DIV_64 => Fosc/64                             *
*                                                                              *
*            data_order = SPI_LSB_FIRST to transmit LSB bit first.             *
*                         SPI_MSB_FIRST to transmit MSB bit first.             *
*                                                                              *
*                                                                              *
*  Output(s): None                                                             *
*                                                                              *
*  Modified Global variables: None                                             *
*                                                                              *
*  Necessary Interrupts: None                                                  *
*                                                                              *
*******************************************************************************/

void micSpiConfigure(SpiFunction master_slave, SpiMode spi_mode,
                     SpiClock spi_clock, SpiDataOrder data_order)
{
  // Set function, mode , basic clock rate and data transer order
  spcr = (spcr & ((1U << SPIE0) | (1U << SPE0))) |
         data_order | master_slave | spi_mode |
         (spi_clock & SPI_CLOCK_DIV_MASK);

  // Set SPI frequency doubling bit as required
  spsr = 0x00U;
  if( 0U != (spi_clock & (1U << SPR2)) )
  {
    // Double clock rate
    micSpiDoubleClockRate();
  }

  return;
}


/*******************************************************************************
*                                                                              *
*  Name: micSPiUnmaskInterrupt                                                 *
*                                                                              *
*  Subject: Unmask SPI interrupts                                              *
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

void micSpiUnmaskInterrupt(void)
{
  spcr |= (1U << SPIE0);

  return;
}


/*******************************************************************************
*                                                                              *
*  Name: micSpiMaskInterrupt                                                   *
*                                                                              *
*  Subject: Mask SPI interrupts.                                               *
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

void micSpiMaskInterrupt(void)
{
  spcr &= ~(1U << SPIE0);

  return;
}


/*******************************************************************************
*                                                                              *
*  Name: micSpiTransferIsCompleted                                             *
*                                                                              *
*  Subject: Check for a SPI transfer complete                                  *
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

Boolean micSpiTransferIsCompleted(void)
{
  return (Boolean)(spsr & (1U << SPIF0));
}


/*******************************************************************************
*                                                                              *
*  Name: micSpiWriteColisionIsDetected                                         *
*                                                                              *
*  Subject: Check for a write colision during previous transfer.               *
*                                                                              *
*                                                                              *
*  Input(s):  None                                                             *
*                                                                              *
*  Output(s): TRUE if a write colision happened.                               *
*                                                                              *
*  Modified Global variables: None                                             *
*                                                                              *
*  Necessary Interrupts: None                                                  *
*                                                                              *
*******************************************************************************/

Boolean micSpiWriteColisionIsDetected(void)
{
  return (Boolean)(spsr & (1U << WCOL0));
}


/*******************************************************************************
*                                                                              *
*  Name: micSpiEnableStatusFlagsClearing                                       *
*                                                                              *
*  Subject: Enable clearing of SPIF and WCOL flags in status register the      *
*           next time SPDR will be accessed.                                   *
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

void micSpiEnableStatusFlagsClearing(void)
{
  // Accesse SPSR to enable clearing of SPIF and WCOL flags in status register
  // the next time SPDR will be accessed.
  spsr = spsr;
  return;
}


/*******************************************************************************
*                                                                              *
*  Name: micSpiSaveState                                                       *
*                                                                              *
*  Subject: Read the present SPI state.                                        *
*                                                                              *
*  Input(s):  None                                                             *
*                                                                              *
*  Output(s): Present SPI state                                                *
*                                                                              *
*  Modified Global variables: None                                             *
*                                                                              *
*  Necessary Interrupts: None                                                  *
*                                                                              *
*******************************************************************************/

SpiState micSpiSaveState(void)
{
  SpiState r_value;
  Int16U l_spsr;

  l_spsr = ((Int16U)spsr & (1U << (Int16U)SPI2X0)) << 8U;
  r_value = l_spsr | spcr;

  return r_value;
}


/*******************************************************************************
*                                                                              *
*  Name: micSpiRestoreState                                                    *
*                                                                              *
*  Subject: Restore previously saved SPI state.                                *
*                                                                              *
*  Input(s):  None                                                             *
*                                                                              *
*  Output(s): Previously saved SPI state                                       *
*                                                                              *
*  Modified Global variables: None                                             *
*                                                                              *
*  Necessary Interrupts: None                                                  *
*                                                                              *
*******************************************************************************/

void micSpiRestoreState(SpiState previous_state)
{
  spsr = (Int8U)(previous_state >> 8);
  spcr = (Int8U)previous_state;
  return;
}



/*******************************************************************************
*                                                                              *
*  Name: micSpiWriteData                                                       *
*                                                                              *
*  Subject: Write the data to send in the SPI register (SPDR)                  *
*                                                                              *
*                                                                              *
*  Input(s):  data = Data byte to be written                                   *
*                                                                              *
*  Output(s): None                                                             *
*                                                                              *
*  Modified Global variables: None                                             *
*                                                                              *
*  Necessary Interrupts: None                                                  *
*                                                                              *
*******************************************************************************/

void micSpiWriteData(Int8U written_data)
{
  spdr = written_data;
  return;
}


/*******************************************************************************
*                                                                              *
*  Name: micSpiReadData                                                        *
*                                                                              *
*  Subject: Read the received data from the SPI register (SPDR)                *
*                                                                              *
*                                                                              *
*  Input(s):  None                                                             *
*                                                                              *
*  Output(s): Read data from SPDR                                              *
*                                                                              *
*  Modified Global variables: None                                             *
*                                                                              *
*  Necessary Interrupts: None                                                  *
*                                                                              *
*******************************************************************************/

Int8U micSpiReadData(void)
{
  return spdr;
}


/******************************************************************************/

