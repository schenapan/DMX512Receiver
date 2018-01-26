#ifndef _MIC_MICRO_H_
#define _MIC_MICRO_H_

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

// Compilo
#include "compilo.h"


/******************************************************************************/
/*                                                                            */
/* => include the right file according to the micro type                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#ifdef AVR_ATMEGA_324

  // definition des type pour la famille atmega164
  #include "mic_type.h"

  // bit field of the micro
//  #include "iom324p.h"

  // inclusion des peripherique pour les 164
/** SEB : on va inclure les fichier h des periph dont on a besion */
  #include "mic_peripheral.h"

#endif


//------------------------------------------------------------------------------

#ifdef AVR_ATMEGA_644

  // definition des type pour la famille atmega644
  #include "Mic/ATMEGA164/mic_type.h"

  // bit field of the micro
  #include "Mic/ATMEGA164/iom644p.h"

  // inclusion des peripherique pour les 164
  #include "Mic/ATMEGA164/mic_peripheral.h"

#endif

//-----------------------------------------------------------------------------

#ifdef AVR_ATMEGA_1284

  // definition des type pour la famille atmega1284
  #include "Mic/ATMEGA164/mic_type.h"

  // bit field of the micro
  #include "Mic/ATMEGA164/iom1284p.h"

  // inclusion des peripherique pour le 1284
  #include "Mic/ATMEGA164/mic_peripheral.h"

#endif

//------------------------------------------------------------------------------

#ifdef AVR_ATMEGA_88

  // definition des type pour la famille atmega88
  #include "Mic/ATMEGA168/mic_type.h"

  // bit field of the micro
  #include "Mic/ATMEGA168/iom88p.h"

  // inclusion des peripherique pour le 88
  #include "Mic/ATMEGA168/mic_peripheral.h"

#endif

//------------------------------------------------------------------------------


#ifdef AVR_ATMEGA_168

  // definition des type pour la famille atmega168
  #include "Mic/ATMEGA168/mic_type.h"

  // bit field of the micro
  #include "Mic/ATMEGA168/iom168p.h"

  // inclusion des peripherique pour le 168
  #include "Mic/ATMEGA168/mic_peripheral.h"

#endif


//------------------------------------------------------------------------------


#ifdef AVR_ATMEGA_2561

  // bit field of the micro
  #include "Mic/ATMEGA2561/iom2561.h"

  // definition des type pour la famille atmega2561
  #include "Mic/ATMEGA2561/mic_type.h"

  // inclusion des peripherique pour les 2561
  #include "Mic/ATMEGA2561/mic_peripheral.h"

#endif

//------------------------------------------------------------------------------


#ifdef CORTEXM3

  // definition des BIT, ATOMIC et autre macro
  #include "app/framework/include/af.h"

// bit field of the micro
//  #include "Mic/ATMEGA2561/iom2561.h"

  // definition des type pour la famille EM35x
  #include "Mic/CORTEXM3/mic_type.h"

  // inclusion des peripheriques
  #include "Mic/CORTEXM3/mic_peripheral.h"

#endif




/*******************************************************************************
*                                                                              *
*                      Public Functions of the Module                          *
*                                                                              *
*******************************************************************************/

// call to reset the product, in case of wanted reset
void softReset( Int8U error_index );


/*******************************************************************************
*                                                                              *
*                            Generic definition                                *
*                                                                              *
*******************************************************************************/



/*******************************************************************************
*                                                                              *
*                            Very usefull Macros                               *
*                                                                              *
*******************************************************************************/

/**
 * return the highest of two number
 */
#ifndef MAX
  #define MAX(x,y) ((x)>(y)?(x):(y))
#endif

/**
 * return the lowest of two number
 */
#ifndef MIN
  #define MIN(x,y) ((x)<(y)?(x):(y))
#endif

/**
 * return the nearest integer number of a decimal one
 */
// #define ROUND(x) ((10*x+5)/10)  // seb a utiliser pour le round up


// effectue une copie de deux zone memoire, a utiliser quand les zone ne se recouvre pas
void memCpy( Int8U dest_ptr[], Int8U src_ptr[], Int8U len );

// effectue un deplacement memoire en faisant attention de ne pas détruire de donnée
void memMove( Int8U dest_ptr[], Int8U src_ptr[], Int8U len );

Int8U memCmp( Int8U dest_ptr[], Int8U src_ptr[], Int8U len );

// remplit un buffer avec une valeur constante
void memSet( Int8U dest_ptr[], Int8U value_to_fill, Int8U len );

//
void delayMicroSecond(Int32U us);

/**
 * @name  Bit Manipulation Macros
 */
//@{

/**
 * @brief Useful to reference a single bit of a byte.
 */
#define BIT(x) (1U << (x))  // Unsigned avoids compiler warnings re BIT(15)

/**
 * @brief Useful to reference a single bit of an Int32U type.
 */
#ifndef BIT32
  #define BIT32(x) (((Int32U) 1) << (x))
#endif

/**
 * @brief Sets \c bit in the \c reg register or byte.
 * @note Assuming \c reg is an IO register, some platforms (such as the
 * AVR) can implement this in a single atomic operation.
*/
#ifndef SETBIT
  #define SETBIT(reg, bit)      ((reg) |= BIT(bit))
#endif

/**
 * @brief Sets the bits in the \c reg register or the byte
 * as specified in the bitmask \c bits.
 * @note This is never a single atomic operation.
 */
#ifndef SETBITS
  #define SETBITS(reg, bits)    ((reg) |= (bits))
#endif

/**
 * @brief Clears a bit in the \c reg register or byte.
 * @note Assuming \c reg is an IO register, some platforms (such as the AVR)
 * can implement this in a single atomic operation.
 */
#ifndef CLEARBIT
  #define CLEARBIT(reg, bit)    ((reg) &= ~(BIT(bit)))
#endif

/**
 * @brief Clears the bits in the \c reg register or byte
 * as specified in the bitmask \c bits.
 * @note This is never a single atomic operation.
 */
#ifndef CLEARBITS
  #define CLEARBITS(reg, bits)  ((reg) &= ~(bits))
#endif

/**
 * @brief Returns the value of \c bit within the register or byte \c reg.
*/
#ifndef READBIT
  #define READBIT(reg, bit)     ((reg) & (BIT(bit)))
#endif

/**
 * @brief Returns the value of the bitmask \c bits within
 * the register or byte \c reg.
 */
#ifndef READBITS
  #define READBITS(reg, bits)   ((reg) & (bits))
#endif

//@} \\END Bit Manipulation Macros


/**
 * @name  Byte Manipulation Macros
 */
//@{

/**
 * @brief Returns the low byte of the 16-bit value \c n as an \c Int8U.
 */
#ifndef LOW_BYTE
  #define LOW_BYTE(n)                     ((Int8U)((n) & 0xFFU))
#endif

/**
 * @brief Returns the high byte of the 16-bit value \c n as an \c Int8U.
 */
#ifndef HIGH_BYTE
  #define HIGH_BYTE(n)                    ((Int8U)(LOW_BYTE((n) >> 8U)))
#endif

/**
 * @brief Returns the value built from the two \c Int8U
 * values \c high and \c low.
 */
#ifndef HIGH_LOW_TO_INT
  #define HIGH_LOW_TO_INT(high, low)     (((((Int8U) (high)) << 8U) + ((Int8U) (low))))
#endif

/**
 * @brief Returns the low byte of the 32-bit value \c n as an \c Int8U.
 */
#ifndef BYTE_0
  #define BYTE_0(n)                     ((Int8U)((n) & 0xFFU))
#endif

/**
 * @brief Returns the second byte of the 32-bit value \c n as an \c Int8U.
 */
#ifndef BYTE_1
  #define BYTE_1(n)                    ((Int8U)(BYTE_0((n) >> 8U)))
#endif

/**
 * @brief Returns the third byte of the 32-bit value \c n as an \c Int8U.
 */
#ifndef BYTE_2
  #define BYTE_2(n)                    ((Int8U)(BYTE_0((n) >> 16U)))
#endif

/**
 * @brief Returns the high byte of the 32-bit value \c n as an \c Int8U.
 */
#ifndef BYTE_3
  #define BYTE_3(n)                    ((Int8U)(BYTE_0((n) >> 24U)))
#endif

//@} \\END Byte manipulation macros

/******************************************************************************/
#endif  // _MIC_MICRO_H_
