/*******************************************************************************
***                                                                          ***
**                                                                            **
**                             USART 0 MANAGEMENT                             **
**                                                                            **
***                                                                          ***
*******************************************************************************/

// Include header for this microcontroller
#include "Mic/mic_micro.h"


/*******************************************************************************
*                                                                              *
*  Name: micUsartReadData8                                                     *
*                                                                              *
*  Subject: Read a byte from the UART 0 RX register                            *
*                                                                              *
*  Prerequisite: character size must be less than 9 bits                       *
*                                                                              *
*  Input(s):  None                                                             *
*                                                                              *
*  Output(s): Read USART0 data.                                                *
*                                                                              *
*  Modified Global variables: None                                             *
*                                                                              *
*  Necessary Interrupts: None                                                  *
*                                                                              *
*******************************************************************************/

Int8U micUsartReadData8(void)
{
  return udr0;
}


/*******************************************************************************
*                                                                              *
*  Name: micUsartWriteData8                                                    *
*                                                                              *
*  Subject: Write a byte into the UART 0 data Tx register                      *
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

void micUsartWriteData8(Int8U usart_data8)
{
  udr0 = usart_data8;
  return;
}



/*******************************************************************************
*                                                                              *
*  Name: micUsartReadData16                                                    *
*                                                                              *
*  Subject: Read a 9 bit data from the UART 0 RX register                      *
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

Int16U micUsartReadData16(void)
{
  Int16U read_data;

  read_data = (((Int16U)ucsr0b & (1U << (Int16U)RXB80)) << 7U);
  read_data |= (Int16U)udr0;

  return read_data;
}


/*******************************************************************************
*                                                                              *
*  Name: micUsartWriteData16                                                   *
*                                                                              *
*  Subject: Write a 9 bits data into the UART 0 data Tx register               *
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

void micUsartWriteData16(Int16U usart_data)
{
  // Set 9th bit. TXB80 is bit 0 of UCSR0B
  ucsr0b = (ucsr0b & ~(1U << TXB80)) | ((Int8U)(usart_data >> 8U) & 0x01U);

  //Set low byte
  udr0 = (Int8U)usart_data;
  return;
}



/*******************************************************************************
*                                                                              *
*  Name: micUsartReadError                                                     *
*                                                                              *
*  Subject: Read Error bits for the last received characterwith USART 0.       *
*                                                                              *
*  Prerequisite:                                                               *
*                                                                              *
*  Input(s):  None                                                             *
*                                                                              *
*  Output(s): Error bits -> Framing, Data Overrun and Parity                   *
*                                                                              *
*  Modified Global variables: None                                             *
*                                                                              *
*  Necessary Interrupts: None                                                  *
*                                                                              *
*******************************************************************************/

UsartError micUsartReadError(void)
{
  return (ucsr0a & ((1U << FE0) | (1U << DOR0) | (1U << UPE0)));
}


/*******************************************************************************
*                                                                              *
*  Name:micUsartPowerUp                                                        *
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

void micUsartPowerUp(void)
{
  prr &= ~(1U << PRUSART0);
  return;
}


/*******************************************************************************
*                                                                              *
*  Name: micUsartTurnOnRx                                                      *
*                                                                              *
*  Subject: Turn the UART 0 receiver on                                        *
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

void micUsartTurnOnRx(void)
{
  prr &= ~(1U << PRUSART0);
  ucsr0b |= (1U << RXEN0);
  return;
}


/*******************************************************************************
*                                                                              *
*  Name: micUsartTurnOffRx                                                     *
*                                                                              *
*  Subject: Turn the UART 0 receiver off                                       *
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

void micUsartTurnOffRx(void)
{
  ucsr0b &= ~(1U << RXEN0);
  return;
}


/*******************************************************************************
*                                                                              *
*  Name: micUsartTurnOnTx                                                      *
*                                                                              *
*  Subject: Turn the UART 0 transmitter on                                     *
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

void micUsartTurnOnTx(void)
{
  prr &= ~(1U << PRUSART0);
  ucsr0b |= (1U << TXEN0);
  return;
}


/*******************************************************************************
*                                                                              *
*  Name: micUsartTurnOffTx                                                     *
*                                                                              *
*  Subject: Turn the UART 0 transmitter off                                    *
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

void micUsartTurnOffTx(void)
{
  ucsr0b &= ~(1U << TXEN0);
  return;
}


/*******************************************************************************
*                                                                              *
*  Name: micUsartTurnOnRxTx                                                    *
*                                                                              *
*  Subject: Turn on both the USART 0 receiver and transmitter                  *
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

void micUsartTurnOnRxTx(void)
{
  prr &= ~(1U << PRUSART0);
  ucsr0b |= ((1U << TXEN0) | (1U << RXEN0));
  return;
}


/*******************************************************************************
*                                                                              *
*  Name: micUsartTurnOffRxTx                                                   *
*                                                                              *
*  Subject: Turn off both the USART 0 receiver and transmitter                 *
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

void micUsartTurnOffRxTx(void)
{
  prr |= (1U << PRUSART0);
  ucsr0b &= ~((1U << TXEN0) | (1U << RXEN0));
  return;
}


/*******************************************************************************
*                                                                              *
*  Name: micUsartSetMode                                                       *
*                                                                              *
*  Subject: Set USART 0 mode                                                   *
*                                                                              *
*  Prerequisite: None                                                          *
*                                                                              *
*  Input(s): usart_mode = UART mode to use among:  USART_MODE_ASYNCHRONOUS     *
*                                                  USART_MODE_SYNCHRONOUS      *
*                                                  USART_MODE_MASTER_SPI       *
*                                                                              *
*  Output(s): None                                                             *
*                                                                              *
*  Modified Global variables: None                                             *
*                                                                              *
*  Necessary Interrupts: None                                                  *
*                                                                              *
*******************************************************************************/

void micUsartSetMode(UsartMode usart_mode)
{
  ucsr0c = (ucsr0c & ~USART_MODE_MASK) | (usart_mode & USART_MODE_MASK);

  // If asynchronous mode is selected UCPOL must be reset
  if ( usart_mode == USART_MODE_ASYNCHRONOUS )
  {
    ucsr1c &= ~(1U << UCPOL0);
  }

  return;
}



/*******************************************************************************
*                                                                              *
*  Name: micUsartSetSynchronousClockPolarity                                   *
*                                                                              *
*  Subject: Set USART 0 synchronous mode clock polarity                        *
*                                                                              *
*  Prerequisite: None                                                          *
*                                                                              *
*  Input(s): polarity = Clock polarity in synchronous mode among:              *
*                                    USART_CLOCK_POLARITY_0 (idle level = 0)   *
*                                    USART_CLOCK_POLARITY_1 (idle level = 1)   *
*                                                                              *
*  Output(s): None                                                             *
*                                                                              *
*  Modified Global variables: None                                             *
*                                                                              *
*  Necessary Interrupts: None                                                  *
*                                                                              *
*******************************************************************************/

void micUsartSetSynchronousClockPolarity(UsartClockPolarity polarity)
{
  ucsr0c = (ucsr0c & ~(1U << UCPOL0)) | (polarity & (1U << UCPOL0));
  return;
}



/*******************************************************************************
*                                                                              *
*  Name: micUsartSetBaudRate                                                   *
*                                                                              *
*  Subject: Set USART 0 baud rate                                              *
*                                                                              *
*  Prerequisite: None                                                          *
*                                                                              *
*  Input(s): baud_rate = USART0 baud rate                                      *
*                                                                              *
*  Output(s): None                                                             *
*                                                                              *
*  Modified Global variables: None                                             *
*                                                                              *
*  Necessary Interrupts: None                                                  *
*                                                                              *
*******************************************************************************/

void micUsartSetBaudRate(UsartBaudRate baud_rate)
{
  ubrr0 = baud_rate;
  return;
}


/*******************************************************************************
*                                                                              *
*  Name: micUsartSetNormalSpeedMode                                            *
*                                                                              *
*  Subject: Set USART 0 Normal speed asynchronous mode                         *
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

void micUsartSetNormalSpeedMode(void)
{
  ucsr0a &= ~(1U << U2X0);
  return;
}


/*******************************************************************************
*                                                                              *
*  Name: micUsartSetHighSpeedMode                                              *
*                                                                              *
*  Subject: Set USART 0 High speed asynchronous mode                           *
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

void micUsartSetHighSpeedMode(void)
{
  ucsr0a |= (1U << U2X0);
  return;
}


/*******************************************************************************
*                                                                              *
*  Name: micUsartSetDataSize                                                   *
*                                                                              *
*  Subject: Set USART 0 data size in bits                                      *
*                                                                              *
*  Prerequisite: None                                                          *
*                                                                              *
*  Input(s): data_size  = Size of data in bits: USART_5_BITS_DATA              *
*                                               USART_6_BITS_DATA              *
*                                               USART_7_BITS_DATA              *
*                                               USART_8_BITS_DATA              *
*                                               USART_9_BITS_DATA              *
*                                                                              *
*  Output(s): None                                                             *
*                                                                              *
*  Modified Global variables: None                                             *
*                                                                              *
*  Necessary Interrupts: None                                                  *
*                                                                              *
*******************************************************************************/

void micUsartSetDataSize(UsartDataSize data_size)
{
  ucsr0b = (ucsr0b & ~(1U << UCSZ02)) |
           (data_size & (1U << UCSZ02));

  ucsr0c = (ucsr0c & ~((1U << UCSZ01) | (1U << UCSZ00))) |
           ((Int8U)(data_size << 1U) & ((1U << UCSZ01) | (1U << UCSZ00)));
  return;
}


/*******************************************************************************
*                                                                              *
*  Name: micUsartSetParityMode                                                 *
*                                                                              *
*  Subject: Set USART 0 parity mode                                            *
*                                                                              *
*  Prerequisite: None                                                          *
*                                                                              *
*  Input(s): parity_mode  = parity mode to use among: USART_NO_PARITY          *
*                                                     USART_EVEN_PARITY        *
*                                                     USART_ODD_PARITY         *
*                                                                              *
*  Output(s): None                                                             *
*                                                                              *
*  Modified Global variables: None                                             *
*                                                                              *
*  Necessary Interrupts: None                                                  *
*                                                                              *
*******************************************************************************/


void micUsartSetParityMode(UsartParityMode parity_mode)
{
  ucsr0c = (ucsr0c & ~USART_PARITY_MODE_MASK) |
           (parity_mode & USART_PARITY_MODE_MASK);
  return;
}



/*******************************************************************************
*                                                                              *
*  Name: micUsartSetStopBits                                                   *
*                                                                              *
*  Subject: Set USART 0 stop bit(s) mode                                       *
*                                                                              *
*  Prerequisite: None                                                          *
*                                                                              *
*  Input(s): stop_bits  = Number of stop bits to use among: USART_1_STOP_BIT   *
*                                                           USART_2_STOP_BIT   *
*                                                                              *
*  Output(s): None                                                             *
*                                                                              *
*  Modified Global variables: None                                             *
*                                                                              *
*  Necessary Interrupts: None                                                  *
*                                                                              *
*******************************************************************************/

void micUsartSetStopBits(UsartStopBits stop_bits)
{
  ucsr0c = (ucsr0c & ~USART_STOP_BITS_MASK) |
           (stop_bits & USART_STOP_BITS_MASK);
  return;
}



/*******************************************************************************
*                                                                              *
*  Name: micUartConfigure                                                      *
*                                                                              *
*  Subject: Configure UART0 for baud rate, data size, parity, stop bits        *
*                                                                              *
*  Prerequisite: None                                                          *
*                                                                              *
*  Input(s):                                                                   *
*     baud_rate = baud rate selected in the appropriate enumeration for type   *
*                 Usart1BaudRate                                               *
*                                                                              *
*     data_size  = Size of data in bits: USART_5_BITS_DATA                     *
*                                        USART_6_BITS_DATA                     *
*                                        USART_7_BITS_DATA                     *
*                                        USART_8_BITS_DATA                     *
*                                        USART_9_BITS_DATA                     *
*                                                                              *
*    parity_mode  = parity mode to use among: USART_NO_PARITY                  *
*                                             USART_EVEN_PARITY                *
*                                             USART_ODD_PARITY                 *
*                                                                              *
*    stop_bits  = Number of stop bits to use among: USART_1_STOP               *
*                                                   USART_2_STOPS              *
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

void micUartConfigure(UsartBaudRate baud_rate,
                      UsartDataSize data_size,
                      UsartParityMode parity_mode,
                      UsartStopBits stop_bits)
{
  // Set baud Rate
  ubrr0 = baud_rate;

  // Set data size (1/2)
  ucsr0b = (ucsr1b & ~(1U << UCSZ02)) |  (data_size & (1U << UCSZ02));

  // Set USART mode, plarity, stop bits, data size(2/2) and synchronous clock
  // polarity
  ucsr0c = USART_MODE_ASYNCHRONOUS + parity_mode + stop_bits
           + (Int8U)(data_size << 1U) + USART_NO_CLOCK ;

  return;
}


/*******************************************************************************
*                                                                              *
*  Name: micUsartConfigure                                                     *
*                                                                              *
*  Subject: Set USART 0 stop bit(s) mode                                       *
*                                                                              *
*  Prerequisite: None                                                          *
*                                                                              *
*  Input(s): usart_mode =                                                      *
*            stop_bits  = Number of stop bits to use among: USART1_1_STOP_BIT  *
*                                                           USART1_2_STOP_BIT  *
*                                                                              *
*  Output(s): None                                                             *
*                                                                              *
*  Modified Global variables: None                                             *
*                                                                              *
*  Necessary Interrupts: None                                                  *
*                                                                              *
*******************************************************************************/

void micUsartConfigure(UsartMode usart_mode, UsartDataSize data_size,
                       UsartParityMode parity_mode, UsartStopBits stop_bits,
                       UsartClockPolarity clock_polarity, UsartBaudRate baud_rate)
{
  // Set data size (1/2)
  ucsr0b = (ucsr0b & ~(1U << UCSZ02)) |  (data_size & (1U << UCSZ02));

  // Set USART mode, plarity, stop bits, data size(2/2) and synchronous clock
  // polarity
  ucsr0c = usart_mode + parity_mode + stop_bits +
                                     (Int8U)( (data_size&0x03U) << UCSZ00 ) +
                                                                clock_polarity ;

  // Set baud Rate
  ubrr0 = baud_rate;
  return;
}


/*******************************************************************************
*                                                                              *
*  Name: micUsartSetMultiProcessorMode                                         *
*                                                                              *
*  Subject: Set USART 0 multi-processor communication mode                     *
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

void micUsartSetMultiProcessorMode(void)
{
  ucsr0a = ucsr0a | (1U << MPCM0);
}


/*******************************************************************************
*                                                                              *
*  Name: micUsartCancelMultiProcessorMode                                      *
*                                                                              *
*  Subject: Cancel USART 0 multi-processor adresse detection mode              *
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

void micUsartCancelMultiProcessorMode(void)
{
  ucsr0a = ucsr0a & ~(1U << MPCM0);
  return;
}


/*******************************************************************************
*                                                                              *
*  Name: micUsartReceiptIsCompleted                                            *
*                                                                              *
*  Subject: USART 0 Data Receipt is completed                                  *
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

Boolean micUsartReceiptIsCompleted(void)
{
  return (ucsr0a & (1U << RXC0));
}


/*******************************************************************************
*                                                                              *
*  Name: micUsartTransmissionIsCompleted                                       *
*                                                                              *
*  Subject: USART 0 Data Receipt is completed                                  *
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

Boolean micUsartTransmissionIsCompleted(void)
{
  return (ucsr0a & (1U << TXC0));
}

/*******************************************************************************
*                                                                              *
*  Name: micUsartClearTxFlag                                       *
*                                                                              *
*  Subject:                                  *
*                                                                              *
*                                                                              *
*  Input(s):  None                                                             *
*                                                                              *
*  Output(s):                                *
*                                                                              *
*  Modified Global variables: None                                             *
*                                                                              *
*  Necessary Interrupts: None                                                  *
*                                                                              *
*******************************************************************************/

void micUsartClearTxFlag(void)
{
  ucsr0a |= (1U << TXC0);
}

/*******************************************************************************
*                                                                              *
*  Name: micUsartRegisterIsEmpty                                               *
*                                                                              *
*  Subject: USART 0 Data Receipt is completed                                  *
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

Boolean micUsartRegisterIsEmpty(void)
{
  return (ucsr0a & (1U << UDRE0));
}


/*******************************************************************************
*                                                                              *
*  Name: micUsartUnmaskRxInterrupt                                             *
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

void micUsartUnmaskRxInterrupt(void)
{
  ucsr0b |= (1U << RXCIE0);

  return;
}


/*******************************************************************************
*                                                                              *
*  Name: micUsartMaskRxInterrupt                                               *
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

void micUsartMaskRxInterrupt(void)
{
  ucsr0b &= ~(1U << RXCIE0);

  return;
}


/*******************************************************************************
*                                                                              *
*  Name: micUsartUnmaskTxInterrupt                                             *
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

void micUsartUnmaskTxInterrupt(void)
{
  ucsr0b |= (1U << TXCIE0);

  return;
}


/*******************************************************************************
*                                                                              *
*  Name: micUsartMaskTxInterrupt                                               *
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

void micUsartMaskTxInterrupt(void)
{
  ucsr0b &= ~(1U << TXCIE0);

  return;
}


/*******************************************************************************
*                                                                              *
*  Name: micUsartClearTxCompletedFlag                                          *
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

void micUsartClearTxCompletedFlag(void)
{
  ucsr0a |= (1U << TXC0);

  return;
}


/*******************************************************************************
*                                                                              *
*  Name: micUsartUnmaskEmptyRegisterInterrupt                                  *
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

void micUsartUnmaskEmptyRegisterInterrupt(void)
{
  ucsr0b |= (1U << UDRIE0);

  return;
}


/*******************************************************************************
*                                                                              *
*  Name: micUsartMaskEmptyRegisterInterrupt                                    *
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

void micUsartMaskEmptyRegisterInterrupt(void)
{
  ucsr0b &= ~(1U << UDRIE0);

  return;
}


/*******************************************************************************
*                                                                              *
*  Name: micUsartUnmaskInterrupts                                              *
*                                                                              *
*  Subject: Unmask USART selected Rx, Tx and Empty Register interrupts.        *
*                                                                              *
*  Input(s):  usart_interrupts_mask = interrupt mask ored for:                 *
*                                        USART_RX_INTERRUPT                    *
*                                        USART_TX_INTERRUPT                    *
*                                        USART_EMPTY_INTERRUPT                 *
*                                                                              *
*  Output(s): None                                                             *
*                                                                              *
*  Modified Global variables: None                                             *
*                                                                              *
*  Necessary Interrupts: None                                                  *
*                                                                              *
*******************************************************************************/

void micUsartUnmaskInterrupts(UsartInterrupts usart_interrupts)
{
  ucsr0b |= usart_interrupts & ((1U << TXCIE0) | (1U << RXCIE0) | (1U << UDRIE0));
  return;
}


/*******************************************************************************
*                                                                              *
*  Name: micUsartMaskInterrupt                                                 *
*                                                                              *
*  Subject: Mask USART selected Rx, Tx and Empty Register interrupts.          *
*                                                                              *
*  Input(s):  usart_interrupts_mask = interrupt mask ored for:                 *
*                                        USART_RX_INTERRUPT                    *
*                                        USART_TX_INTERRUPT                    *
*                                        USART_EMPTY_INTERRUPT                 *
*                                                                              *
*  Output(s): None                                                             *
*                                                                              *
*  Modified Global variables: None                                             *
*                                                                              *
*  Necessary Interrupts: None                                                  *
*                                                                              *
*******************************************************************************/

void micUsartMaskInterrupts(UsartInterrupts interrupts)
{
  ucsr0b &= ~(interrupts & ((1U << TXCIE0) | (1U << RXCIE0) | (1U << UDRIE0)));
  return;
}


/*******************************************************************************
*                                                                              *
*  Name: micUsartMasterSpiSetMode                                              *
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

void micUsartMasterSpiSetMode(UsartSpiMode spi_mode)
{
  ucsr0c = (ucsr0c & ~(USART_SPI_MODE_MASK)) | (spi_mode & USART_SPI_MODE_MASK);
  return;
}


/*******************************************************************************
*                                                                              *
*  Name: micUsartSaveState                                                     *
*                                                                              *
*  Subject: Read the present USART0 state. The state consist in                *
*           the interrupts, the enabled part of the USART.                     *
*                                                                              *
*  Input(s):  None                                                             *
*                                                                              *
*  Output(s): Present USART 0 state                                            *
*                                                                              *
*  Modified Global variables: None                                             *
*                                                                              *
*  Necessary Interrupts: None                                                  *
*                                                                              *
*******************************************************************************/

UsartState micUsartSaveState(void)
{
  return ucsr0b;
}


/*******************************************************************************
*                                                                              *
*  Name: micUsartRestoreState                                                  *
*                                                                              *
*  Subject: Restore previously saved USART0 state. The state consist in        *
*           the interrupts and the enabled part (Rx, Tx) of the USART.         *
*                                                                              *
*  Input(s):  None                                                             *
*                                                                              *
*  Output(s): Present USART 0 state                                            *
*                                                                              *
*  Modified Global variables: None                                             *
*                                                                              *
*  Necessary Interrupts: None                                                  *
*                                                                              *
*******************************************************************************/

void micUsartRestoreState(UsartState previous_state)
{
  ucsr0b = (ucsr0b & USART_STATE_MASK)| previous_state;
  return;
}



/*******************************************************************************
*                                                                              *
*  Name: micUsartMasterSpiSetDataOrder                                         *
*                                                                              *
*  Subject: Select bit transfer order for data in Master SPI mode.             *
*                                                                              *
*                                                                              *
*  Input(s): data_order = USART_SPI_LSB_FIRST to transmit LSB bit first.       *
*                       = USART_SPI_MSB_FIRST to transmit MSB bit first.       *
*                                                                              *
*  Output(s): None                                                             *
*                                                                              *
*  Modified Global variables: None                                             *
*                                                                              *
*  Necessary Interrupts: None                                                  *
*                                                                              *
*******************************************************************************/

void micUsartMasterSpiSetDataOrder(UsartSpiDataOrder spi_data_order)
{
  ucsr0c = (ucsr0c & ~(1U << UDORD0)) | (spi_data_order & (1U << UDORD0));
  return;
}


/*******************************************************************************
*                                                                              *
*  Name: micUsartMasterSpiConfigure                                            *
*                                                                              *
*  Subject: Enables and set the SPI configuration.                             *
*           Beware: maximum allowed speed is Fosc/4 when in slave mode.        *
*                                                                              *
*                                                                              *
*  Input(s): master_slave = SPI_MASTER if we are a master.                     *
*                           SPI_SLAVE if we are a slave.                       *
*                                                                              *
*            spi_mode =  USART_SPI_MODE 0 (mode 0: UCPOL= 0 & UCPHA = 0)       *
*                        USART_SPI_MODE 1 (mode 1: UCPOL= 0 & UCPHA = 1)       *
*                        USART_SPI_MODE 2 (mode 2: UCPOL= 1 & UCPHA = 0)       *
*                        USART_SPI_MODE 3 (mode 3: UCPOL= 1 & UCPHA = 1)       *
*                                                                              *
*            data_order = USART_SPI_LSB_FIRST to transmit LSB bit first.       *
*                       = USART_SPI_MSB_FIRST to transmit MSB bit first.       *
*                                                                              *
*            baud_rate = USART0 baud rate: synchronous mode baud rate i.e.     *
*                                          (Fosc/2*baud) - 1                   *
*                                                                              *
*  Output(s): None                                                             *
*                                                                              *
*  Modified Global variables: None                                             *
*                                                                              *
*  Necessary Interrupts: None                                                  *
*                                                                              *
*******************************************************************************/

void micUsartMasterSpiConfigure(UsartSpiMode spi_mode,
                                UsartSpiDataOrder spi_data_order,
                                UsartBaudRate baud_rate)
{
 // Set  mode  and data transer order
 ucsr0c = (ucsr0c & ~(USART_SPI_MODE_MASK | (1U << UDORD0))) |
          ((Int8U)(spi_mode | spi_data_order) & (USART_SPI_MODE_MASK | (1U << UDORD0)));

   // Set clock rate (synchronous mode baud rate)
   ubrr0 = baud_rate;
   return;
}


/******************************************************************************/

