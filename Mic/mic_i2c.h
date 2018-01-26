#ifndef _ATMEGA164_TWI_H_
#define _ATMEGA164_TWI_H_
/******************************************************************************/
/*                                                                            */
/* => TWI (I2C) management                                                    */
/*                                                                            */
/******************************************************************************/

/*******************************************************************************
*                                                                              *
*                         Constants declaration                                *
*                                                                              *
*******************************************************************************/

// Mask to select bits from the status register of the TWI bus (TWSx )
#define I2C_STATUS_BITS_MASK               0xF8U


/*----------------------------------------------------------------------------*/

// Address for General call on the I2C bus
#define I2C_GENERAL_CALL_ADDRESS    0x00U
  // Bit from adress register (TWAR) used to manage the "General Call"
  #define I2C_GENERAL_CALL_ENABLED    (1U << TWGCE)
  #define I2C_GENERAL_CALL_DISABLED   (0U << TWGCE)

// Number of R/W bit in the I2C address byte
#define I2C_ADDR_RW_BIT       0U
// Mask to select the bit that giving the transfer direction (bit for R/W)
#define I2C_ADDRESS_RW_MASK   (1U << I2C_ADDR_RW_BIT)
  // Bit de Sens de transfert de l'adresse
  #define I2C_WRITE_BIT         (0U << I2C_ADDR_RW_BIT) // Writing to address
  #define I2C_READ_BIT          (1U << I2C_ADDR_RW_BIT) // Reading from  address

// Mask to select address bits from address register (TWAR) without the transfer
// direction (bit for R/W)
#define I2C_ADDRESS_MASK        0xFEU


/*----------------------------------------------------------------------------*/
/*                                                                            */
/*                          Codes de Status                                   */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// Mask to select bits from the status register of the TWI bus (TWSx )
#define I2C_STATUS_BITS_MASK         0xF8U

/*----------------------------------------------------------------------------*/

// Generic staus codes for "I2C Master":
#define I2CS_START                   0x08U // A "START" has been transmitted

#define I2CS_REPEATED_START          0x10U // A "Repeated START" has been
                                           // transmitted

#define I2CS_ARBITRATION_LOST        0x38U // Arbitration lost as a master


// Status code for "I2C Master" transmitter:
#define I2CS_MTX_ADDR_ACK            0x18U // A "SLA + W" has been transmitted
                                           // and a "ACK" has been received

#define I2CS_MTX_ADDR_NACK           0x20U // "SLA + W" has been transmitted and
                                           // a "NACK" has been received

#define I2CS_MTX_DATA_ACK            0x28U // A byte has been transmitted
                                           // and a "ACK" has been received

#define I2CS_MTX_DATA_NACK           0x30U // A data byte has been transmitted
                                           // and "NACK" has been received


// Status code for "I2C Master" receiver:
#define I2CS_MRX_ADDR_ACK            0x40U // A "SLA + R" has been transmitted
                                           // and a ACK has been received

#define I2CS_MRX_ADDR_NACK           0x48U // A "SLA + R" has been transmitted
                                           // and a NACK has been received

#define I2CS_MRX_DATA_ACK            0x50U // A data byte has been received
                                           // and ACK has been transmitted

#define I2CS_MRX_DATA_NACK           0x58U // A data byte has been received
                                           // and NACK has been transmitted

/*----------------------------------------------------------------------------*/

// Status code for  "I2C Slave" transmitter
#define I2CS_STX_ADDR_ACK            0xA8U // My own "SLA + R" has been received
                                           // and a ACK has been sent

#define I2CS_STX_ADDR_ACK_M_ARB_LOST 0xB0U // Arbitration lost in "SLA + R/W"
                                           // as a master. My own "SLA + R"
                                           // has been received and a
                                           // ACK has been sent

#define I2CS_STX_DATA_ACK            0xB8U // The data byte in TWDR has been
                                           // transmitted and a ACK has been
                                           // received

#define I2CS_STX_DATA_NACK           0xC0U // The data byte in TWDR has been
                                           // transmitted and a NACK  has been
                                           // transmitted

#define I2CS_STX_DATA_ACK_LAST_BYTE  0xC8U // Le dernier data byte de TWDR has
                                           // been transmitted (TWEA=0) and a
                                           // ACK has been received



// Status code for  "I2C Slave" receiver
#define I2CS_SRX_ADDR_ACK            0x60U // My own "SLA + W" has been received
                                           // and a ACK has been sent.

#define I2CS_SRX_ADDR_ACK_M_ARB_LOST 0x68U // Arbitration lost for "SLA + R/W"
                                           // as a master and my own "SLA + W"
                                           // has been received and a ACK
                                           // has been sent.

#define I2CS_SRX_GEN_ACK             0x70U // L'adresse d'appel général has been
                                           // received and a ACK has been sent.

#define I2CS_SRX_GEN_ACK_M_ARB_LOST  0x78U // Arbitration lost for "SLA + R/W"
                                           // as a master and the general
                                           // call address has been
                                           // received and a ACK has been sent.

#define I2CS_SRX_ADDR_DATA_ACK       0x80U // Previously addressed with my own
                                           // "SLA + W".
                                           // A data byte has been received and
                                           // a ACK has been sent

#define I2CS_SRX_ADDR_DATA_NACK      0x88U // Previously addressed withmy own
                                           // "SLA + W".
                                           // A data byte has been received and
                                           // a NACK has been sent.

#define I2CS_SRX_GEN_DATA_ACK        0x90U // Previously addressedavec
                                           // the general call address.
                                           // A data byte has been received and
                                           // a ACK has been sent.

#define I2CS_SRX_GEN_DATA_NACK       0x98U // Previously addressedavec
                                           // the general call address.
                                           // A data byte has been received and
                                           // a NACK has been sent.

#define I2CS_SRX_STOP_RESTART        0xA0U // A "STOP" condition ou ae
                                           // condition "Repeated START" has
                                           // been received while we where
                                           // addressed as a slave

/*----------------------------------------------------------------------------*/

// Miscelleneous Status Code for I2C
#define I2CS_NO_STATE                0xF8U // No information available.
                                           // TWINT = "0"

#define I2CS_BUS_ERROR               0x00U // Bus Error due to an illegal
                                           // condition "START" or "STOP"



/******************************************************************************/

/*----------------------------------------------------------------------------*/

/*******************************************************************************
*                                                                              *
*                           Public data types                                  *
*                                                                              *
*******************************************************************************/

// definition d'un type pour l'identifier le controleur i2c
typedef Int8U I2cMasterId;


// TWI clock prescaler (division of CPUclock)
enum
{
  // TWI clock = CPUclock / 1
  I2C_CLK_PS_DIV_1 = (0U << TWPS1) | (0U << TWPS0),
  // TWI clock = CPUclock / 4
  I2C_CLK_PS_DIV_4 = (0U << TWPS1) | (1U << TWPS0),
  // TWI clock = Fosc / 16
  I2C_CLK_PS_DIV_16 = (1U << TWPS1) | (0U << TWPS0),
  // TWI clock = Fosc / 64
  I2C_CLK_PS_DIV_64 = (1U << TWPS1) | (1U << TWPS0),

  //----------------------------------------------
  I2C_CLK_PS_NO_SCALER = 0xFFU
};
// Type for TWI clock prescaler values
typedef Int8U I2cClockScaler;
  // Mask selecting bits used for TWI conversion clock selection in SPCR
  #define I2C_CLK_PS_MASK  ((1U << TWPS1) | (1U << TWPS0))


// Type for TWI Rate generator setting value
typedef Int8U I2cRate;

//---------------------

// Type for TWI s control: address  + R/W bit
typedef Int8U I2cAddressRW;

//---------------------

// Type for TWI slave Address of our device
typedef Int8U I2cAddress;


// Type for TWI Address Mask value to use for slave address matching
typedef Int8U I2cAddressMask;


//---------------------

// Type for TWI Status
typedef Int8U I2cStatus;

//---------------------

// Type for TWI Data byte
typedef Int8U I2cData;

/*----------------------------------------------------------------------------*/
/*
 * => Functions:
 */

// Init the I2C (TWI) interface: Disable it and Disable IT. Release SDA line.
void micI2cInit(void);

// Reset the I2C (TWI) interface whitout changing interrupt mask nor
//  Enable/Disable state.
void micI2cReset(void);

//--------------

// Turns on the TWI peripheral.
void micI2cTurnOn(void);

// Turns off the TWI peripheral.
void micI2cTurnOff(void);

//--------------

// Enables the TWI interrupts for I2C serial bus.
void  micI2cEnableInterrupt(void);

// Disnables the TWI interrupts for I2C serial bus.
void  micI2cDisableInterrupt(void);

// Return TRUE if TWI interrupts are enabled.
Boolean  micI2cInterruptIsEnabled(void);

//--------------

// Set TWI clock from CPUclock(Fosc) division:
//   i2c_clock = I2C_CLK_PS_DIV_1 => Fosc/1
//               I2C_CLK_PS_DIV_4 => Fosc/4
//               I2C_CLK_PS_DIV_16 => Fosc/16
//               I2C_CLK_PS_DIV_64 => Fosc/64
void micI2cSetClockScaler(I2cClockScaler i2c_clock_scaler);

// Set TWI rate (depends on CPUclock and TWI Prescaler)
// The SCL line frequency is computed as follows:
// Fscl = (Fosc/TWI_PS) / 16 + (2 * i2c_rate)
void micI2cSetSclRate(I2cRate i2c_rate);

//--------------

// Set slave address of my device
void micI2cSetOwnAddress(I2cAddress i2c_address);

// Set the mask to apply to slave address for comparison:
// bit = 0 do not compare with the corrresponding bit of n my slave address.
// Accept bit whatever the value of address bit is.
void micI2cSetSlaveAddressMask(I2cAddressMask i2c_address_mask);

// Enable General Call address (0x00) recognition
void  micI2cEnableGeneralCallRecognition(void);

// Disnable General Call address (0x00) recognition
void  micI2cDisableGeneralCallRecognition(void);

//--------------

// Write control byte to I2c data register
void micI2cWriteAddressRw(I2cAddressRW i2c_address_rw);

// Write a byte in the I2C data register
void micI2cWriteDataByte(I2cData i2c_data_byte);

// Read control byte from the I2C data register
I2cAddressRW micI2cGetAddressRw(void);

// Read a byte in the I2C data register
I2cData micI2cGetDataByte(void);

//--------------

// Test if the TWI is currently busy
Boolean micI2cIsBusy(void);

// Return TWI Interface status
I2cStatus micI2cGetSatus(void);

// Return TRUE if a write collision has happened when writting to the data
// register
Boolean micI2cWriteCollisionHasHappened(void);

//--------------

// Initiate a start or repeated start condition on the I2C bus
void micI2cInitiateStart(void);

// Initiate a stop condition on the bus
void micI2cInitiateStop(void);

// Initiate a a data or address transfer on the I2C  bus
void micI2cMasterTxInitiateTransfer(void);

// Initiate a data or address transfer that will be acknowleged in master Rx
// mode
void micI2cMasterRxIntiateAckTransfer(void);

// Initiate a data or address transfer that won't be acknowleged in master Rx
// mode
void micI2cMasterRxIntiateNackTransfer(void);

//--------------

// Acknowledge next data transfer in slave mode
void micI2cSlaveAckNextTransfer(void);

// Doesn't acknowledge next data transfer in slave mode.
// Used to signal last transfer
void micI2cSlaveNackNextTransfer(void);


/******************************************************************************/
/******************************************************************************/
#endif  // _ATMEGA164_TWI_H_
