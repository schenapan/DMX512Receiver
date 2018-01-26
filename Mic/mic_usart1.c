/*******************************************************************************
***                                                                          ***
**                                                                            **
**                           USART 1 MANAGEMENT                               **
**                                                                            **
***                                                                          ***
*******************************************************************************/

// Include header for this micrcontroller
#include "Mic/mic_micro.h"


/*******************************************************************************
*                                                                              *
*  Name: micUsart1ReadData8                                                    *
*                                                                              *
*  Subject: Read a byte from the UART 1 RX register                            *
*                                                                              *
*  Prerequisite: character size must be less than 9 bits                       *
*                                                                              *
*  Input(s):  None                                                             *
*                                                                              *
*  Output(s): Read USART1 data.                                                *
*                                                                              *
*  Modified Global variables: None                                             *
*                                                                              *
*  Necessary Interrupts: None                                                  *
*                                                                              *
*******************************************************************************/

Int8U micUsart1ReadData8(void)
{
  return udr1;
}


/*******************************************************************************
*                                                                              *
*  Name: micUsart1WriteData8                                                   *
*                                                                              *
*  Subject: Write a byte into the UART 1 data Tx register                      *
*                                                                              *
*  Prerequisite: character size must be less than 9 bits                       *
*                                                                              *
*  Input(s):  usart_data8 = 8 bit usart data to send                           *
*                                                                              *
*  Output(s): None                                                             *
*                                                                              *
*  Modified Global variables: None                                             *
*                                                                              *
*  Necessary Interrupts: None                                                  *
*                                                                              *
*******************************************************************************/

void micUsart1WriteData8(Int8U usart_data8)
{
  udr1 = usart_data8;
  return;
}



/*******************************************************************************
*                                                                              *
*  Name: micUsart1ReadData16                                                   *
*                                                                              *
*  Subject: Read a 9 bit data from the USART 1 RX register                     *
*                                                                              *
*  Prerequisite: character size must be 9 bits                                 *
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

Int16U micUsart1ReadData16(void)
{
  Int16U read_data;

  read_data = (((Int16U)ucsr1b & (1U << (Int16U)RXB81)) << 7);
  read_data |= (Int16U)udr1;

  return read_data;
}


/*******************************************************************************
*                                                                              *
*  Name: micUsart1WriteData16                                                  *
*                                                                              *
*  Subject: Write a 9 bits data into the UART 1 data Tx register               *
*                                                                              *
*  Prerequisite: character size must be less than 9 bits                       *
*                                                                              *
*  Input(s):  usart_data8 = 8 bit usart data to send                           *
*                                                                              *
*  Output(s): None                                                             *
*                                                                              *
*  Modified Global variables: None                                             *
*                                                                              *
*  Necessary Interrupts: None                                                  *
*                                                                              *
*******************************************************************************/

void micUsart1WriteData16(Int16U usart_data)
{
  // Set 9th bit. TXB81 is bit 1 of UCSR1B
  ucsr1b = (ucsr1b & ~(1U << TXB81)) | ((Int8U)(usart_data >> 8U) & 0x01U);

  //Set low byte
  udr1 = (Int8U)usart_data;
  return;
}



/*******************************************************************************
*                                                                              *
*  Name: micUsart1ReadError                                                    *
*                                                                              *
*  Subject: Read Error bits for the last received character with USART 1.      *
*                                                                              *
*  Prerequisite:                                                               *
*                                                                              *
*  Input(s):  None                                                             *
*                                                                              *
*  Output(s): bitmap of errors  -> Framing, Data Overrun and Parity            *
*                                                                              *
*  Modified Global variables: None                                             *
*                                                                              *
*  Necessary Interrupts: None                                                  *
*                                                                              *
*******************************************************************************/

Usart1Error micUsart1ReadError(void)
{
  return (ucsr1a & ((1U << FE1) | (1U << DOR1) | (1U << UPE1)));
}


/*******************************************************************************
*                                                                              *
*  Name:micUsart1WakeUp                                                        *
*                                                                              *
*  Subject: Power up the UART 1                                                *
*                                                                              *
*  Prerequisite: None                                                          *
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

void micUsart1PowerUp(void)
{
  prr &= ~(1U << PRUSART1);
  return;
}


/*******************************************************************************
*                                                                              *
*  Name:micUsart1Powerdown                                                     *
*                                                                              *
*  Subject:Powerdown UART 1                                                    *
*                                                                              *
*  Prerequisite: None                                                          *
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

void micUsart1PowerDown(void)
{
  prr |= (1U << PRUSART1);
  return;
}


/*******************************************************************************
*                                                                              *
*  Name: micUsart1TurnOnRx                                                     *
*                                                                              *
*  Subject: Turn the UART 1 receiver on                                        *
*                                                                              *
*  Prerequisite: None                                                          *
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

void micUsart1TurnOnRx(void)
{
  micUsart1PowerUp();
  ucsr1b |= (1U << RXEN1);
  return;
}


/*******************************************************************************
*                                                                              *
*  Name: micUsart1TurnOffRx                                                    *
*                                                                              *
*  Subject: Turn the UART 1 receiver off                                       *
*                                                                              *
*  Prerequisite: None                                                          *
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

void micUsart1TurnOffRx(void)
{
  ucsr1b &= ~(1U << RXEN1);
  return;
}


/*******************************************************************************
*                                                                              *
*  Name: micUsart1TurnOnTx                                                     *
*                                                                              *
*  Subject: Turn the UART 1 transmitter on                                     *
*                                                                              *
*  Prerequisite: None                                                          *
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

void micUsart1TurnOnTx(void)
{
  micUsart1PowerUp();
  ucsr1b |= (1U << TXEN1);
  return;
}


/*******************************************************************************
*                                                                              *
*  Name: micUsart1TurnOffTx                                                    *
*                                                                              *
*  Subject: Turn the UART 1 transmitter off                                    *
*                                                                              *
*  Prerequisite: None                                                          *
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

void micUsart1TurnOffTx(void)
{
  ucsr1b &= ~(1U << TXEN1);
  return;
}


/*******************************************************************************
*                                                                              *
*  Name: micUsart1TurnOnRxTx                                                   *
*                                                                              *
*  Subject: Turn on both the USART 1 receiver and transmitter                  *
*                                                                              *
*  Prerequisite: None                                                          *
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

void micUsart1TurnOnRxTx(void)
{
  micUsart1PowerUp();
  ucsr1b |= ((1U << TXEN1) | (1U << RXEN1));
  return;
}


/*******************************************************************************
*                                                                              *
*  Name: micUsart1TurnOffRxTx                                                  *
*                                                                              *
*  Subject: Turn off both the USART 1 receiver and transmitter                 *
*                                                                              *
*  Prerequisite: None                                                          *
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

void micUsart1TurnOffRxTx(void)
{
  micUsart1PowerDown();
  ucsr1b &= ~((1U << TXEN1) | (1U << RXEN1));
  return;
}


/*******************************************************************************
*                                                                              *
*  Name: micUsart1SetMode                                                      *
*                                                                              *
*  Subject: Set USART 1 mode                                                   *
*                                                                              *
*  Prerequisite: None                                                          *
*                                                                              *
*  Input(s): usart_mode = UART mode to use among:  USART1_MODE_ASYNCHRONOUS    *
*                                                  USART1_MODE_SYNCHRONOUS     *
*                                                  USART1_MODE_MASTER_SPI      *
*                                                                              *
*  Output(s): None                                                             *
*                                                                              *
*  Modified Global variables: None                                             *
*                                                                              *
*  Necessary Interrupts: None                                                  *
*                                                                              *
*******************************************************************************/

void micUsart1SetMode(Usart1Mode usart_mode)
{
  ucsr1c = (ucsr1c & ~USART1_MODE_MASK) | (usart_mode & USART1_MODE_MASK);

  // If asynchronous mode is selected UCPOL must be reset
  if ( usart_mode == USART1_MODE_ASYNCHRONOUS )
  {
    ucsr1c &= ~(1U << UCPOL1);
  }
  return;
}



/*******************************************************************************
*                                                                              *
*  Name: micUsart1SetSynchronousClockPolarity                                  *
*                                                                              *
*  Subject: Set USART 1 synchronous mode clock polarity                        *
*                                                                              *
*  Prerequisite: None                                                          *
*                                                                              *
*  Input(s): polarity = Clock polarity in synchronous mode among:              *
*                                   USART1_CLOCK_POLARITY_0 (idle level = 0)   *
*                                   USART1_CLOCK_POLARITY_1 (idle level = 1)   *
*                                                                              *
*  Output(s): None                                                             *
*                                                                              *
*  Modified Global variables: None                                             *
*                                                                              *
*  Necessary Interrupts: None                                                  *
*                                                                              *
*******************************************************************************/

void micUsart1SetSynchronousClockPolarity(Usart1ClockPolarity polarity)
{
  ucsr1c = (ucsr1c & ~(1U << UCPOL1)) | (polarity & (1U << UCPOL1));
  return;
}



/*******************************************************************************
*                                                                              *
*  Name: micUsart1SetBaudRate                                                  *
*                                                                              *
*  Subject: Set USART 1 baud rate                                              *
*                                                                              *
*  Prerequisite: None                                                          *
*                                                                              *
*  Input(s): baud_rate = USART1 baud rate                                      *
*                                                                              *
*  Output(s): None                                                             *
*                                                                              *
*  Modified Global variables: None                                             *
*                                                                              *
*  Necessary Interrupts: None                                                  *
*                                                                              *
*******************************************************************************/

void micUsart1SetBaudRate(Usart1BaudRate baud_rate)
{
  ubrr1 = baud_rate;
  return;
}


/*******************************************************************************
*                                                                              *
*  Name: micUsart1SetNormalSpeedMode                                           *
*                                                                              *
*  Subject: Set USART 1 Normal speed asynchronous mode                         *
*                                                                              *
*  Prerequisite: None                                                          *
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

void micUsart1SetNormalSpeedMode(void)
{
  ucsr1a &= ~(1U << U2X1);
  return;
}


/*******************************************************************************
*                                                                              *
*  Name: micUsart1SetHighSpeedMode                                             *
*                                                                              *
*  Subject: Set USART 1 High speed asynchronous mode                           *
*                                                                              *
*  Prerequisite: Choose carrefully amoing available Baud Rate to meet the      *
*                precision requirement.                                        *
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

void micUsart1SetHighSpeedMode(void)
{
  ucsr1a |= (1U << U2X1);
  return;
}


/*******************************************************************************
*                                                                              *
*  Name: micUsart1SetDataSize                                                  *
*                                                                              *
*  Subject: Set USART 1 data size in bits                                      *
*                                                                              *
*  Prerequisite: None                                                          *
*                                                                              *
*  Input(s): data_size  = Size of data in bits: USART1_5_BITS_DATA             *
*                                               USART1_6_BITS_DATA             *
*                                               USART1_7_BITS_DATA             *
*                                               USART1_8_BITS_DATA             *
*                                               USART1_9_BITS_DATA             *
*                                                                              *
*  Output(s): None                                                             *
*                                                                              *
*  Modified Global variables: None                                             *
*                                                                              *
*  Necessary Interrupts: None                                                  *
*                                                                              *
*******************************************************************************/

void micUsart1SetDataSize(Usart1DataSize data_size)
{
  ucsr1b = (ucsr1b & ~(1U << UCSZ12)) |
           (data_size & (1U << UCSZ12));

  ucsr1c = (ucsr1c & ~((1U << UCSZ11) | (1U << UCSZ10))) |
           ((Int8U)(data_size << 1U) & ((1U << UCSZ11) | (1U << UCSZ10)));
  return;
}


/*******************************************************************************
*                                                                              *
*  Name: micUsart1SetParityMode                                                *
*                                                                              *
*  Subject: Set USART 1 parity mode                                            *
*                                                                              *
*  Prerequisite: None                                                          *
*                                                                              *
*  Input(s): parity_mode  = parity mode to use among: USART1_NO_PARITY         *
*                                                     USART1_EVEN_PARITY       *
*                                                     USART1_ODD_PARITY        *
*                                                                              *
*  Output(s): None                                                             *
*                                                                              *
*  Modified Global variables: None                                             *
*                                                                              *
*  Necessary Interrupts: None                                                  *
*                                                                              *
*******************************************************************************/

void micUsart1SetParityMode(Usart1ParityMode parity_mode)
{
  ucsr1c = (ucsr1c & ~USART1_PARITY_MODE_MASK) |
           (parity_mode & USART1_PARITY_MODE_MASK);
  return;
}



/*******************************************************************************
*                                                                              *
*  Name: micUsart1SetStopBits                                                  *
*                                                                              *
*  Subject: Set USART 1 stop bit(s) mode                                       *
*                                                                              *
*  Prerequisite: None                                                          *
*                                                                              *
*  Input(s): stop_bits  = Number of stop bits to use among: USART1_1_STOP      *
*                                                           USART1_2_STOPS     *
*                                                                              *
*  Output(s): None                                                             *
*                                                                              *
*  Modified Global variables: None                                             *
*                                                                              *
*  Necessary Interrupts: None                                                  *
*                                                                              *
*******************************************************************************/

void micUsart1SetStopBits(Usart1StopBits stop_bits)
{
  ucsr1c = (ucsr1c & ~USART1_STOP_BITS_MASK) |
           (stop_bits & USART1_STOP_BITS_MASK);
  return;
}


/*******************************************************************************
*                                                                              *
*  Name: micUsart1Configure                                                    *
*                                                                              *
*  Subject: Set USART 1 stop bit(s) mode                                       *
*                                                                              *
*  Prerequisite: None                                                          *
*                                                                              *
*  Input(s):                                                                   *
*  Input(s): baud_rate = baud rate to use                                      *
*            data_size = Size in bits of an UART1 word                         *
*            stop_bits  = Number of stop bits to use among: USART1_1_STOP      *
*                                                           USART1_2_STOPS     *
*            Parity_mode = Parity mode to use                                  *
*            usart_mode = USART1_MODE_ASYNCHRONOUS if asynchronous             *
*                       = USART1_MODE_SYNCHRONOUS if synchronous               *
*                       = USART1_MODE_MASTER_SPI if used as SPI bus            *
*             clock_parity = parity of of the synchronous mode clock           *
*                                                                              *
*                                                                              *
*  Output(s): None                                                             *
*                                                                              *
*  Modified Global variables: None                                             *
*                                                                              *
*  Necessary Interrupts: None                                                  *
*                                                                              *
*******************************************************************************/

void micUsart1Configure(UsartMode usart_mode,
                        UsartDataSize data_size,
                        UsartParityMode parity_mode,
                        UsartStopBits stop_bits,
                        UsartClockPolarity clock_polarity,
                        UsartBaudRate baud_rate)
{
  // Set data size (1/2)
  ucsr1b = (ucsr1b & ~(1U << UCSZ12)) |  (data_size & (1U << UCSZ12));

  // Set USART mode, plarity, stop bits, data size(2/2) and synchronous clock
  // polarity
  ucsr1c = usart_mode + parity_mode + stop_bits +
                                     (Int8U)( (data_size&0x03U) << UCSZ10 ) +
                                                                clock_polarity ;

  // Set baud Rate
  ubrr1 = baud_rate;
  return;
}


/*******************************************************************************
*                                                                              *
*  Name: micUart1Configure                                                     *
*                                                                              *
*  Subject: Configure UART1 for baud rate, data size, parity, stop bits        *
*                                                                              *
*  Prerequisite: None                                                          *
*                                                                              *
*  Input(s):                                                                   *
*     baud_rate = baud rate selected in the appropriate enumeration for type   *
*                 Usart1BaudRate                                               *
*                                                                              *
*     data_size  = Size of data in bits: USART1_5_BITS_DATA                    *
*                                        USART1_6_BITS_DATA                    *
*                                        USART1_7_BITS_DATA                    *
*                                        USART1_8_BITS_DATA                    *
*                                        USART1_9_BITS_DATA                    *
*                                                                              *
*    parity_mode  = parity mode to use among: USART1_NO_PARITY                 *
*                                             USART1_EVEN_PARITY               *
*                                             USART1_ODD_PARITY                *
*                                                                              *
*    stop_bits  = Number of stop bits to use among: USART1_1_STOP              *
*                                                   USART1_2_STOPS             *
*                                                                              *
*                                                                              *
*                                                                              *
*  Output(s): None                                                             *
*                                                                              *
*  Modified Global variables: None                                             *
*                                                                              *
*  Necessary Interrupts: None                                                  *
*                                                                              *
*******************************************************************************/

void micUart1Configure(Usart1BaudRate baud_rate,
                       Usart1DataSize data_size,
                       Usart1ParityMode parity_mode,
                       Usart1StopBits stop_bits)
{
  // Set baud Rate
  ubrr1 = baud_rate;

  // Set data size (1/2)
  ucsr1b = (ucsr1b & ~(1U << UCSZ12)) |  (data_size & (1U << UCSZ12));

  // Set USART mode, plarity, stop bits, data size(2/2) and synchronous clock
  // polarity
  ucsr1c = USART1_MODE_ASYNCHRONOUS + parity_mode + stop_bits
           + (Int8U)(data_size << 1U) + USART1_NO_CLOCK ;

  return;
}


/*******************************************************************************
*                                                                              *
*  Name: micUsart1SetMultiProcessorMode                                        *
*                                                                              *
*  Subject: Set USART 1 multi-processor communication mode                     *
*           Enable adresse detection                                           *
*                                                                              *
*  Prerequisite: None                                                          *
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

void micUsart1SetMultiProcessorMode(void)
{
  ucsr1a = ucsr1a | (1U << MPCM1);
  return;
}


/*******************************************************************************
*                                                                              *
*  Name: micUsart1CancelMultiProcessorMode                                     *
*                                                                              *
*  Subject: Cancel USART 1 multi-processor adresse detection mode              *
*                                                                              *
*  Prerequisite: None                                                          *
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

void micUsart1CancelMultiProcessorMode(void)
{
  ucsr1a = ucsr1a & ~(1U << MPCM1);
  return;
}


/*******************************************************************************
*                                                                              *
*  Name: micUsart1ReceiptIsCompleted                                           *
*                                                                              *
*  Subject: USART 1 Data Receipt is completed                                  *
*                                                                              *
*                                                                              *
*  Input(s):  None                                                             *
*                                                                              *
*  Output(s): TRUE if a conversion is completed                                *
*                                                                              *
*  Modified Global variables: None                                             *
*                                                                              *
*  Necessary Interrupts: None                                                  *
*                                                                              *
*******************************************************************************/

Boolean micUsart1ReceiptIsCompleted(void)
{
  return (0U != (ucsr1a & (1U << RXC1))) ? TRUE : FALSE;
}


/*******************************************************************************
*                                                                              *
*  Name: micUsart1TransmissionIsCompleted                                      *
*                                                                              *
*  Subject: USART 1 Data Receipt is completed                                  *
*                                                                              *
*                                                                              *
*  Input(s):  None                                                             *
*                                                                              *
*  Output(s): TRUE if a conversion is completed                                *
*                                                                              *
*  Modified Global variables: None                                             *
*                                                                              *
*  Necessary Interrupts: None                                                  *
*                                                                              *
*******************************************************************************/

Boolean micUsart1TransmissionIsCompleted(void)
{
  return (0U != (ucsr1a & (1U << TXC1))) ? TRUE : FALSE;
}


/*******************************************************************************
*                                                                              *
*  Name: micUsart1RegisterIsEmpty                                              *
*                                                                              *
*  Subject: USART 1 Data Receipt is completed                                  *
*                                                                              *
*                                                                              *
*  Input(s):  None                                                             *
*                                                                              *
*  Output(s): TRUE if a conversion is completed                                *
*                                                                              *
*  Modified Global variables: None                                             *
*                                                                              *
*  Necessary Interrupts: None                                                  *
*                                                                              *
*******************************************************************************/

Boolean micUsart1RegisterIsEmpty(void)
{
  return (0U != (ucsr1a & (1U << UDRE1))) ? TRUE : FALSE;
}


/*******************************************************************************
*                                                                              *
*  Name: micUsart1UnmaskRxInterrupt                                            *
*                                                                              *
*  Subject: Unmask USART RX interrupts if interrupts are enabled               *
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

void micUsart1UnmaskRxInterrupt(void)
{
  ucsr1b |= (1U << RXCIE1);

  return;
}


/*******************************************************************************
*                                                                              *
*  Name: micUsart1MaskRxInterrupt                                              *
*                                                                              *
*  Subject:  Mask USART RX Complete interrupts.                                *
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

void micUsart1MaskRxInterrupt(void)
{
  ucsr1b &= ~(1U << RXCIE1);

  return;
}


/*******************************************************************************
*                                                                              *
*  Name: micUsart1UnmaskTxInterrupt                                            *
*                                                                              *
*  Subject: Unmask USART TX interrupts if interrupts are enabled               *
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

void micUsart1UnmaskTxInterrupt(void)
{
  ucsr1b |= (1U << TXCIE1);

  return;
}


/*******************************************************************************
*                                                                              *
*  Name: micUsart1MaskTxInterrupt                                              *
*                                                                              *
*  Subject:  Mask USART RX Complete interrupts.                                *
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

void micUsart1MaskTxInterrupt(void)
{
  ucsr1b &= ~(1U << TXCIE1);

  return;
}


/*******************************************************************************
*                                                                              *
*  Name: micUsart1ClearTxFlag                                         *
*                                                                              *
*  Subject: Clear Transmit complete flag (TXC).                                *
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

void micUsart1ClearTxCompletedFlag(void)
{
  ucsr1a |= (1U << TXC1);

  return;
}


/*******************************************************************************
*                                                                              *
*  Name: micUsart1UnmaskEmptyRegisterInterrupt                                 *
*                                                                              *
*  Subject: Unmask USART data register empty interrupts                        *
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

void micUsart1UnmaskEmptyRegisterInterrupt(void)
{
  ucsr1b |= (1U << UDRIE1);

  return;
}


/*******************************************************************************
*                                                                              *
*  Name: micUsart1MaskEmptyRegisterInterrupt                                   *
*                                                                              *
*  Subject:  Disable USART RX Complete interrupts (mask it).                   *
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

void micUsart1MaskEmptyRegisterInterrupt(void)
{
  ucsr1b &= ~(1U << UDRIE1);

  return;
}


/*******************************************************************************
*                                                                              *
*  Name: micUsart1UnmaskInterrupts                                             *
*                                                                              *
*  Subject: Unmask USART selected Rx, Tx and Empty Register interrupts.        *
*                                                                              *
*  Input(s):  usart_interrupts_mask = interrupt mask ored for bits:            *
*                                        USART1_RX_INTERRUPT                   *
*                                        USART1_TX_INTERRUPT                   *
*                                        USART1_EMPTY_INTERRUPT                *
*                                                                              *
*  Output(s): None                                                             *
*                                                                              *
*  Modified Global variables: None                                             *
*                                                                              *
*  Necessary Interrupts: None                                                  *
*                                                                              *
*******************************************************************************/

void micUsart1UnmaskInterrupts(Usart1Interrupts usart_interrupts)
{
  ucsr1b |= usart_interrupts & ((1U << TXCIE1) | (1U << RXCIE1) | (1U << UDRIE1));
  return;
}


/*******************************************************************************
*                                                                              *
*  Name: micUsart1MaskInterrupt                                                *
*                                                                              *
*  Subject: Mask USART selected Rx, Tx and Empty Register interrupts.          *
*                                                                              *
*  Input(s):  usart_interrupts_mask = interrupt mask ored for:                 *
*                                        USART1_RX_INTERRUPT                   *
*                                        USART1_TX_INTERRUPT                   *
*                                        USART1_EMPTY_INTERRUPT                *
*                                                                              *
*  Output(s): None                                                             *
*                                                                              *
*  Modified Global variables: None                                             *
*                                                                              *
*  Necessary Interrupts: None                                                  *
*                                                                              *
*******************************************************************************/

void micUsart1MaskInterrupts(Usart1Interrupts interrupts)
{
  ucsr1b &= ~(interrupts & ((1U << TXCIE1) | (1U << RXCIE1) | (1U << UDRIE1)));
  return;
}


/*******************************************************************************
*                                                                              *
*  Name: micUsart1MasterSpiSetMode                                             *
*                                                                              *
*  Subject: Select SPI clock frequency division from Fosc.                     *
*           Beware: maximum allowed speed is Fosc/4 when in slave mode.        *
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

void micUsart1MasterSpiSetMode(Usart1SpiMode spi_mode)
{
  ucsr1c = (ucsr1c & ~(USART1_SPI_MODE_MASK)) |
           (spi_mode & USART_SPI_MODE_MASK);
  return;
}


/*******************************************************************************
*                                                                              *
*  Name: micUsart1SaveState                                                    *
*                                                                              *
*  Subject: Read the present USART1 state. The state consist in                *
*           the interrupts, the enabled part of the USART 1.                   *
*                                                                              *
*  Input(s):  None                                                             *
*                                                                              *
*  Output(s): Present USART 1 state                                            *
*                                                                              *
*  Modified Global variables: None                                             *
*                                                                              *
*  Necessary Interrupts: None                                                  *
*                                                                              *
*******************************************************************************/

Usart1State micUsart1SaveState(void)
{
  return ucsr1b;
}


/*******************************************************************************
*                                                                              *
*  Name: micUsart1RestoreState                                                 *
*                                                                              *
*  Subject: Restore previously saved USART1 state. The state consist in        *
*           the interrupts and the enabled part (Rx, Tx) of the USART 1.       *
*                                                                              *
*  Input(s):  None                                                             *
*                                                                              *
*  Output(s): Present USART 1 state                                            *
*                                                                              *
*  Modified Global variables: None                                             *
*                                                                              *
*  Necessary Interrupts: None                                                  *
*                                                                              *
*******************************************************************************/

void micUsart1RestoreState(Usart1State previous_state)
{
  ucsr1b = (ucsr1b & USART1_STATE_MASK)| previous_state;
  return;
}



/*******************************************************************************
*                                                                              *
*  Name: micUsart1MasterSpiSetDataOrder                                        *
*                                                                              *
*  Subject: Select bit transfer order for data in Master SPI mode.             *
*                                                                              *
*                                                                              *
*  Input(s): data_order = USART1_SPI_LSB_FIRST to transmit LSB bit first.      *
*                       = USART1_SPI_MSB_FIRST to transmit MSB bit first.      *
*                                                                              *
*  Output(s): None                                                             *
*                                                                              *
*  Modified Global variables: None                                             *
*                                                                              *
*  Necessary Interrupts: None                                                  *
*                                                                              *
*******************************************************************************/

void micUsart1MasterSpiSetDataOrder(Usart1SpiDataOrder spi_data_order)
{
  ucsr1c = (ucsr1c & ~(1U << UDORD1)) | (spi_data_order & (1U << UDORD1));
  return;
}


/*******************************************************************************
*                                                                              *
*  Name: micUsart1MasterSpiConfigure                                           *
*                                                                              *
*  Subject: Enables and set the SPI configuration.                             *
*           Beware: maximum allowed speed is Fosc/4 when in slave mode.        *
*                                                                              *
*                                                                              *
*  Input(s): master_slave = SPI_MASTER if we are a master.                     *
*                           SPI_SLAVE if we are a slave.                       *
*                                                                              *
*            spi_mode =  USART1_SPI_MODE 0 (mode 0: UCPOL= 0 & UCPHA = 0)      *
*                        USART1_SPI_MODE 1 (mode 1: UCPOL= 0 & UCPHA = 1)      *
*                        USART1_SPI_MODE 2 (mode 2: UCPOL= 1 & UCPHA = 0)      *
*                        USART1_SPI_MODE 3 (mode 3: UCPOL= 1 & UCPHA = 1)      *
*                                                                              *
*            data_order = USART1_SPI_LSB_FIRST to transmit LSB bit first.      *
*                       = USART1_SPI_MSB_FIRST to transmit MSB bit first.      *
*                                                                              *
*            baud_rate = USART1 baud rate: synchronous mode baud rate i.e.     *
*                                          (Fosc/2*baud) - 1                   *
*                                                                              *
*  Output(s): None                                                             *
*                                                                              *
*  Modified Global variables: None                                             *
*                                                                              *
*  Necessary Interrupts: None                                                  *
*                                                                              *
*******************************************************************************/

void micUsart1MasterSpiConfigure(Usart1SpiMode spi_mode,
                                 Usart1SpiDataOrder spi_data_order,
                                 Usart1BaudRate baud_rate)
{
  // Set  mode  and data transer order
  ucsr1c = (ucsr1c & ~(USART1_SPI_MODE_MASK | (1U << UDORD1))) |
          ((Int8U)(spi_mode | spi_data_order) &
           (USART1_SPI_MODE_MASK | (Int8U)(1U << UDORD1)));

  // Set clock rate (synchronous mode baud rate)
  ubrr1 = baud_rate;

  return;
}


/******************************************************************************/


