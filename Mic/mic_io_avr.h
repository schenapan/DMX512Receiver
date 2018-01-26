#ifndef _MIC_IO_AVR_H_
#define _MIC_IO_AVR_H_
/******************************************************************************/
/*                                                                            */
/* => IO management                                                           */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/******************************************************************************/
/*                                                                            */
/*  Constant and type                                                         */
/*                                                                            */
/******************************************************************************/

/**
* \brief defintion des offset d'acces au registre du port AVR
*/
#define AVR_PIN(I_PORT) (_SFR_IO8(I_PORT*3))
#define AVR_DDR(I_PORT) (_SFR_IO8((I_PORT*3U)+1U))
#define AVR_PORT(I_PORT) (_SFR_IO8((I_PORT*3U)+2U))

/******************************************************************************/
/*  Public function                                                           */
/******************************************************************************/

/**
* \brief fonction d'initialisation du module
*/
#define  micIoInit() do{  PORTA = 0U; \
	                        DDRA = 0U;  \
							            PORTB = 0U; \
	                        DDRB = 0U;  \
							            PORTC = 0U; \
	                        DDRC = 0U;  \
							            PORTD = 0U; \
	                        DDRD = 0U;  \
                       } while(0);

/**
* \brief configure une io en sortie
*
* \param[IN] i_io : io complete
*
* \return TRUE si success
*/
#define  micIoConfigOutput( I_IO ) do{ AVR_DDR(((SIo)I_IO).port) |= (1U << ((SIo)I_IO).pin); \
                                             } while(0);

/**
* \brief configure une io en entree
*
* \param[IN] i_io : io complete
* \param[IN] i_pull_up_mode : activation de la pull-up interne
*
* \return TRUE si success
*/
#define  micIoConfigInput( I_IO, I_PULL_UP_MODE ) do{ AVR_DDR(((SIo)I_IO).port) &= ~(1U << ((SIo)I_IO).pin); \
	                                                            AVR_PORT(((SIo)I_IO).port) &= ~(1U << ((SIo)I_IO).pin); \
																                              AVR_PORT(((SIo)I_IO).port) |= (I_PULL_UP_MODE << ((SIo)I_IO).pin); \
                                                            } while(0);

/**
* \brief affecte un etat a une io
*
* \param[IN] i_io : io complete
* \param[IN] i_level : niveau de sortie souhaite
*
* \return TRUE si success
*/
#define  micIoSet( I_IO, I_LVL ) do{  AVR_PORT(((SIo)I_IO).port) &= ~(((~I_LVL)&0x01U) << ((SIo)I_IO).pin); \
	                                            AVR_PORT(((SIo)I_IO).port) |= (I_LVL << ((SIo)I_IO).pin); \
                                           } while(0);

/**
* \brief Toggle l'etat d'une io
*
* \param[IN] i_io : io complete
*
* \return TRUE si success
*/
#define  micIoToggle( I_IO ) do{ AVR_PORT(((SIo)I_IO).port) ^= (1U << ((SIo)I_IO).pin); \
                                       } while(0);

/**
* \brief lit la valeur d'un io
*
* \param[IN] i_io : io complete
*
* \return level of the io, (IO_LVL_GND by default )
*/
#define micIoGet( I_IO ) ((AVR_PIN(((SIo)I_IO).port)>>((SIo)I_IO).pin)&0x01U)

/**
* \brief ecrit sur un port
*
* \param[IN] i_port : port concerne
* \param[IN i_value : valeur a ecrire
*
* \return TRUE if success
*/
#define  micIoWrite( I_PORT, I_VALUE ) do{  AVR_PORT(I_PORT) = I_VALUE; \
                                         } while(0);

/**
* \brief lit sur un port
*
* \param[IN] I_PORT : port concerne
*
* \return valeur lue sur le port
*/
#define  micioRead( I_PORT, I_VALUE ) do{ return AVR_PORT(I_PORT); } while(0);


/******************************************************************************/
#endif  // _MIC_IO_AVR_H_
