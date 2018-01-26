/*******************************************************************************
*                                                                              *
*  Module Type: Programme                                                      *
*                                                                              *
*------------------------------------------------------------------------------*
*                                                                              *
*  Quick Description:                                                          *
*    Abstraction layer for the I2C (TWI) registers of the micrcontroller       *
*                                                                              *
*                                                                              *
*                                                                              *
*------------------------------------------------------------------------------*
*                                                                              *
*  Goal: Basic abstraction                                                     *
*        master mode only                                                      *
*                                                                              *
*  Requires:  TWI is dedicated to communication with I2C bus                   *
*                                                                              *
*------------------------------------------------------------------------------*
*                                                                              *
*  Date:  2011 / 01 / 26                                                       *
*  Author: D. BLANCHET                                                         *
*  Last modification:  .... / .. / ..                                          *
*                                                                              *
*  Version: 1                                                                  *
*                                                                              *
*                                                                              *
********************************************************************************
*                                                                              *
*  Modifications:                                                              *
*                                                                              *
*  Date:    .... / .. / ..                                                     *
*  Author:                                                                     *
*  Object:                                                                     *
*                                                                              *
********************************************************************************
*                                                                              *
*                          File to be included                                 *
*                                                                              *
*******************************************************************************/

// Include header for this micrcontroller
#include "Mic/mic_micro.h"



/*******************************************************************************
*                                                                              *
*  Name:micI2cInit                                                             *
*                                                                              *
*  Subject: Init the I2C (TWI) interface: Disable it and Disable IT.           *
*           ReleaseSDA line.                                                   *
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

void micI2cInit(void)
{
  // Power Down I2C(TWI) module
  prr |= (1U << PRTWI);

  // Power up I2C(TWI) module
  prr &= ~(1U << PRTWI);

  // Re-initialise TWCR
  twcr = ( (0U << TWEN) |                                 // Disable I2C
           (0U << TWIE) |                                 // Disable Interupt.
           (0U << TWINT) |                                // Disable Interupt.
           (0U << TWEA) | (0U << TWSTA) | (0U << TWSTO) | // No Signal requests.
           (0U << TWWC) );                                // Read only flag

  return;
}


/*******************************************************************************
*                                                                              *
*  Name:micI2cReset                                                            *
*                                                                              *
*  Subject: Reset the TWI interface whitout changing interrupt mask nor E/D    *
*           state.                                                             *
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

void micI2cReset(void)
{
  // Re-initialise TWCR
  twcr &= ((1U << TWEN) |                                 // E/D unchanged
           (0U << TWIE) |                                 // Disable Interupt.
           (0U << TWINT) |                                // Disable Interupt.
           (0U << TWEA) | (0U << TWSTA) | (0U << TWSTO) | // No Signal requests.
           (0U << TWWC));                                 // Read only flag

  return;
}


/******************************************************************************/

/*----------------------------------------------------------------------------*/

/*******************************************************************************
*                                                                              *
*  Name: micI2cTurnOn                                                          *
*                                                                              *
*  Subject: Turns on the TWI serial bus.                                       *
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

void micI2cTurnOn(void)
{
  // Power up TWI (I2C) module
  prr &= ~(1U << PRTWI);

  // Enable TWI
  twcr |= (1U << TWEN);

  return;
}


/*******************************************************************************
*                                                                              *
*  Name: micI2cTurnOff                                                         *
*                                                                              *
*  Subject: turns off the TWI serial bus.                                      *
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

void micI2cTurnOff(void)
{
  // Turn off TWI peripherals
  twcr &= ~(1U << TWEN);

  // Reduce power consumption
  prr |= (1U << PRTWI);
  return;
}


/******************************************************************************/

/*----------------------------------------------------------------------------*/

/*******************************************************************************
*                                                                              *
*  Name: micI2cEnableInterrupt                                                 *
*                                                                              *
*  Subject: Turns on the TWI interrupts for I2C serial bus.                    *
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

void micI2cEnableInterrupt(void)
{
  // Enable TWI interrupts
  twcr = (twcr & ~(1U << TWINT)) | (1U << TWIE);

  return;
}


/*******************************************************************************
*                                                                              *
*  Name: micI2cDisableInterrupt                                                *
*                                                                              *
*  Subject: Turns on the TWI interrupts for I2C serial bus.                    *
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

void micI2cDisableInterrupt(void)
{
  // Enable TWI interrupts
  twcr = twcr & ~((1U << TWINT) | (1U << TWIE)) ;

  return;
}


/*******************************************************************************
*                                                                              *
*  Name: micI2cDisableInterrupt                                                *
*                                                                              *
*  Subject: Test if TWI interrupts are enabled.                                *
*                                                                              *
*                                                                              *
*  Input(s):  None                                                             *
*                                                                              *
*  Output(s): TRUE if TWI interrupts are enabled                               *
*                                                                              *
*  Modified Global variables: None                                             *
*                                                                              *
*  Necessary Interrupts: None                                                  *
*                                                                              *
*******************************************************************************/

Boolean micI2cInterruptIsEnabled(void)
{
  Boolean i2c_int_is_enabled = FALSE;

  if ( (1U << TWIE) == (twcr & (1U << TWIE)) )
  {
     //  TWI interrupts are enabled
     i2c_int_is_enabled = TRUE;
  }

  return i2c_int_is_enabled;
}



/******************************************************************************/

/*----------------------------------------------------------------------------*/

/*******************************************************************************
*                                                                              *
*  Name: micI2cSetClockScaler                                                  *
*                                                                              *
*  Subject: Select TWI clock frequency division from Fosc.                     *
*                                                                              *
*                                                                              *
*  Input(s): i2c_clock = CPU clock division to use for TWI.                    *
*                          I2C_CLK_DIV_1 => Fosc/1                             *
*                          I2C_CLK_DIV_4 => Fosc/4                             *
*                          I2C_CLK_DIV_16 => Fosc/16                           *
*                          I2C_CLK_DIV_64 => Fosc/64                           *
*                                                                              *
*  Output(s): None                                                             *
*                                                                              *
*  Modified Global variables: None                                             *
*                                                                              *
*  Necessary Interrupts: None                                                  *
*                                                                              *
*******************************************************************************/

void micI2cSetClockScaler(I2cClockScaler i2c_clock_scaler)
{
  // Set TWI Clock prescaler
  twsr = i2c_clock_scaler & I2C_CLK_PS_MASK;

  return;
}


/*******************************************************************************
*                                                                              *
*  Name: micI2cSetSclRate                                                      *
*                                                                              *
*  Subject: Set TWI rate (depends on CPU clock and TWI Prescaler)              *
*                                                                              *
*                                                                              *
*  Input(s): i2c_rate = TWI's SCL line frequency (Fscl).                       *
*                                                                              *
*            The SCL line frequency is computed as follows:                    *
*            Fscl = (Fosc/TWI_PS) / 16 + (2 * i2c_rate)                        *
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

void micI2cSetSclRate(I2cRate i2c_rate)
{
  // Set TWI Clock prescaler
  twbr = i2c_rate;

  return;
}


/******************************************************************************/

/*----------------------------------------------------------------------------*/

/*******************************************************************************
*                                                                              *
*  Name: micI2cSetOwnAddress                                                   *
*                                                                              *
*  Subject: Set slave address of our own device                                *
*                                                                              *
*                                                                              *
*  Input(s): i2c_address = slave address of our own device                     *
*                                                                              *
*  Output(s): None                                                             *
*                                                                              *
*  Modified Global variables: None                                             *
*                                                                              *
*  Necessary Interrupts: None                                                  *
*                                                                              *
*******************************************************************************/

void micI2cSetOwnAddress(I2cAddress i2c_address)
{
  // Set TWI Clock prescaler
  twar = i2c_address ;

  return;
}


/*******************************************************************************
*                                                                              *
*  Name: micI2cSetSlaveAddressMask                                             *
*                                                                              *
*  Subject: Set the mask to apply to slave address matching                    *
*                                                                              *
*                                                                              *
*  Input(s): i2c_address mask = value of of the mask to apply to slave address *
*                                                                              *
*            bit = 1: do compare with the corrresponding bit of n my slave     *
*                  address.                                                    *
*            bit = 0: do not compare with the corrresponding bit of n my slave *
*                  address. Accept bit whatever the value of address bit is.   *
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

void micI2cSetSlaveAddressMask(I2cAddressMask i2c_address_mask)
{
  // Set TWI Clock prescaler
  twamr = i2c_address_mask ;

  return;
}


/*******************************************************************************
*                                                                              *
*  Name: micI2cEnableGeneralCallRecognition                                    *
*                                                                              *
*  Subject: Enable General Call address (0x00) recognition                     *
*                                                                              *
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

void  micI2cEnableGeneralCallRecognition(void)
{
  twar |= (1U << TWGCE);

  return;
}


/*******************************************************************************
*                                                                              *
*  Name: micI2cDisableGeneralCallRecognition                                   *
*                                                                              *
*  Subject: Disable General Call address (0x00) recognition                    *
*                                                                              *
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

void  micI2cDisableGeneralCallRecognition(void)
{
  twar &= ~(1U << TWGCE);

  return;
}



/******************************************************************************/

/*----------------------------------------------------------------------------*/

/*******************************************************************************
*                                                                              *
*  Name: micI2cWriteAddressRw                                                  *
*                                                                              *
*  Subject: Write control byte to I2c data register                            *
*                                                                              *
*  Input(s):  i2c_address_rw = I2C control byte: addtresss + R/W               *
*                                                                              *
*  Output(s): None                                                             *
*                                                                              *
*  Modified Global variables: None                                             *
*                                                                              *
*  Necessary Interrupts: None                                                  *
*                                                                              *
*******************************************************************************/

void micI2cWriteAddressRw(I2cAddressRW i2c_address_rw)
{
  // Write data on the bus
  twdr = i2c_address_rw;

  return;
}


/*******************************************************************************
*                                                                              *
*  Name: micI2cWriteDataByte                                                   *
*                                                                              *
*  Subject: Write a byte in the I2C data register                              *
*                                                                              *
*  Input(s): i2c_data_byte = byte to write in the TWI data register            *
*                                                                              *
*  Output(s): None                                                             *
*                                                                              *
*  Modified Global variables: None                                             *
*                                                                              *
*  Necessary Interrupts: None                                                  *
*                                                                              *
*******************************************************************************/

void micI2cWriteDataByte(I2cData i2c_data_byte)
{
  // Write data on the bus
  twdr = i2c_data_byte;

  return;
}


/*******************************************************************************
*                                                                              *
*  Name:  micI2cGetAddressRw                                                   *
*                                                                              *
*  Subject: Read control byte from the I2C data register                       *
*                                                                              *
*                                                                              *
*  Input(s):  None                                                             *
*                                                                              *
*  Output(s): Read byte from the TWI dat register                              *
*                                                                              *
*  Modified Global variables: None                                             *
*                                                                              *
*  Necessary Interrupts: None                                                  *
*                                                                              *
*******************************************************************************/

I2cAddressRW micI2cGetAddressRw(void)
{
  // Write data on the bus
  return twdr;
}


/*******************************************************************************
*                                                                              *
*  Name: micI2cGetDataByte                                                     *
*                                                                              *
*  Subject: Read a byte in the I2C data register                               *
*                                                                              *
*                                                                              *
*  Input(s):  None                                                             *
*                                                                              *
*  Output(s): Read byte from the TWI dat register                              *
*                                                                              *
*  Modified Global variables: None                                             *
*                                                                              *
*  Necessary Interrupts: None                                                  *
*                                                                              *
*******************************************************************************/

I2cData micI2cGetDataByte(void)
{
  // Write data on the bus
  return twdr;
}


/******************************************************************************/

/*----------------------------------------------------------------------------*/

/*******************************************************************************
*                                                                              *
*  Name: micI2cIsBusy                                                          *
*                                                                              *
*  Subject: Test if the TWI is currently busy                                  *
*                                                                              *
*                                                                              *
*  Input(s):  None                                                             *
*                                                                              *
*  Output(s): TRUE if the TWI is currently busy                                *
*                                                                              *
*  Modified Global variables: None                                             *
*                                                                              *
*  Necessary Interrupts: None                                                  *
*                                                                              *
*******************************************************************************/

Boolean micI2cIsBusy(void)
{
  Boolean i2c_is_busy = FALSE;

  if ( (0U << TWINT) == (twcr & (1U << TWINT)) )
  {
    i2c_is_busy = TRUE;
  }

  return i2c_is_busy;
}


/*******************************************************************************
*                                                                              *
*  Name: micI2cGetStatus                                                       *
*                                                                              *
*  Subject: Return TWI Interface status                                        *
*                                                                              *
*                                                                              *
*  Input(s):  None                                                             *
*                                                                              *
*  Output(s): Read byte from the TWI dat register                              *
*                                                                              *
*  Modified Global variables: None                                             *
*                                                                              *
*  Necessary Interrupts: None                                                  *
*                                                                              *
*******************************************************************************/

I2cStatus micI2cGetSatus(void)
{
  // Write data on the bus
  return twsr & I2C_STATUS_BITS_MASK;
}



/*******************************************************************************
*                                                                              *
*  Name: micI2cWriteCollisionHasHappened                                       *
*                                                                              *
*  Subject: Return TRUE if a write collision has happened                      *
*                                                                              *
*                                                                              *
*  Input(s):  None                                                             *
*                                                                              *
*  Output(s): Read byte from the TWI dat register                              *
*                                                                              *
*  Modified Global variables: None                                             *
*                                                                              *
*  Necessary Interrupts: None                                                  *
*                                                                              *
*******************************************************************************/

Boolean micI2cWriteCollisionHasHappened(void)
{
  Boolean write_collision_is_detected = FALSE;

  if ( (1U << TWWC) == (twcr & (1U << TWWC)) )
  {
     write_collision_is_detected = TRUE;
  }

  return write_collision_is_detected;
}


/******************************************************************************/

/*----------------------------------------------------------------------------*/

/*******************************************************************************
*                                                                              *
*  Name:  micI2cInitiateStart                                                  *
*                                                                              *
*  Subject: Initiate a start or repeated start condition on the bus            *
*                                                                              *
*                                                                              *
*  Input(s):  None                                                             *
*                                                                              *
*  Output(s): TRUE if the TWI is currently busy                                *
*                                                                              *
*  Modified Global variables: None                                             *
*                                                                              *
*  Necessary Interrupts: None                                                  *
*                                                                              *
*******************************************************************************/

void micI2cInitiateStart(void)
{
  Int8U twcr_ie;

  twcr_ie = twcr & (1U << TWIE);

  twcr = twcr_ie | ((1U << TWINT) | (1U << TWSTA) | (1U << TWEN));

  return;
}


/*******************************************************************************
*                                                                              *
*  Name:  micI2cInitiateStop                                                   *
*                                                                              *
*  Subject: Initiate a stop condition on the bus                               *
*                                                                              *
*                                                                              *
*  Input(s):  None                                                             *
*                                                                              *
*  Output(s): TRUE if the TWI is currently busy                                *
*                                                                              *
*  Modified Global variables: None                                             *
*                                                                              *
*  Necessary Interrupts: None                                                  *
*                                                                              *
*******************************************************************************/

void micI2cInitiateStop(void)
{
  Int8U twcr_ie;

  twcr_ie = twcr & (1U << TWIE);

  twcr = twcr_ie | ((1U << TWINT) | (1U << TWSTO) | (1U << TWEN));

  return;
}

/*******************************************************************************
*                                                                              *
*  Name: micI2cMasterTxInitiateTransfer                                        *
*                                                                              *
*  Subject: Initiate a a data or address transfer on the I2C  bus              *
*                                                                              *
*                                                                              *
*  Input(s):  None                                                             *
*                                                                              *
*  Output(s): TRUE if the TWI is currently busy                                *
*                                                                              *
*  Modified Global variables: None                                             *
*                                                                              *
*  Necessary Interrupts: None                                                  *
*                                                                              *
*******************************************************************************/

void micI2cMasterTxInitiateTransfer(void)
{
  Int8U twcr_ie;

  twcr_ie = twcr & (1U << TWIE);

  twcr = twcr_ie | ((1U << TWINT) | (1U << TWEN));

  return;
}


/*******************************************************************************
*                                                                              *
*  Name: micI2cMasterRxIntiateAckTransfer                                      *
*                                                                              *
*  Subject: Initiate a data or address transfer that will be acknowleged in    *
*           master Rx mode                                                     *
*                                                                              *
*  Input(s):  None                                                             *
*                                                                              *
*  Output(s): TRUE if the TWI is currently busy                                *
*                                                                              *
*  Modified Global variables: None                                             *
*                                                                              *
*  Necessary Interrupts: None                                                  *
*                                                                              *
*******************************************************************************/

void micI2cMasterRxIntiateAckTransfer(void)
{
  Int8U twcr_ie;

  twcr_ie = twcr & (1U << TWIE);

  twcr = twcr_ie | ((1U << TWINT) | (1U << TWEA) | (1U << TWEN) );

  return;
}


/*******************************************************************************
*                                                                              *
*  Name: micI2cMasterRxIntiateNackTransfer                                     *
*                                                                              *
*  Subject: Initiate a data or address transfer that won't be acknowleged in   *
*           master Rx mode                                                     *
*                                                                              *
*  Input(s):  None                                                             *
*                                                                              *
*  Output(s): TRUE if the TWI is currently busy                                *
*                                                                              *
*  Modified Global variables: None                                             *
*                                                                              *
*  Necessary Interrupts: None                                                  *
*                                                                              *
*******************************************************************************/

void micI2cMasterRxIntiateNackTransfer(void)
{
  Int8U twcr_ie;

  twcr_ie = twcr & (1U << TWIE);

  twcr = twcr_ie | ((1U << TWINT) | (1U << TWEN) );

  return;
}



/*******************************************************************************
*                                                                              *
*  Name: micI2cSlaveAckNextTransfer                                            *
*                                                                              *
*  Subject: Acknowledge next data transfer in slave mode                       *
*                                                                              *
*                                                                              *
*  Input(s):  None                                                             *
*                                                                              *
*  Output(s): TRUE if the TWI is currently busy                                *
*                                                                              *
*  Modified Global variables: None                                             *
*                                                                              *
*  Necessary Interrupts: None                                                  *
*                                                                              *
*******************************************************************************/

void micI2cSlaveAckNextTransfer(void)
{
  Int8U twcr_ie;

  twcr_ie = twcr & (1U << TWIE);

  twcr = twcr_ie | ((1U << TWEA) | (1U << TWEN));

  return;
}


/*******************************************************************************
*                                                                              *
*  Name: micI2cSlaveNackNextTransfer                                           *
*                                                                              *
*  Subject: Doesn't acknowledge next data transfer in slave mode               *
*           Used to signal last transfer                                       *
*                                                                              *
*  Input(s):  None                                                             *
*                                                                              *
*  Output(s): TRUE if the TWI is currently busy                                *
*                                                                              *
*  Modified Global variables: None                                             *
*                                                                              *
*  Necessary Interrupts: None                                                  *
*                                                                              *
*******************************************************************************/

void micI2cSlaveNackNextTransfer(void)
{
  Int8U twcr_ie;

  twcr_ie = twcr & (1U << TWIE);

  twcr = twcr_ie | (1U << TWEN);

  return;
}


/******************************************************************************/
/******************************************************************************/

