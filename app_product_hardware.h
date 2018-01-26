#ifndef _app_product_hardware_H_
#define _app_product_hardware_H_

// include micro peripheral
#include "Mic/mic_micro.h"

// include driver

// DEFINE DMX address of module
#define DMX_ADDRESS 1

// definit le nombre de led a gerer en variation
#define NB_DIMMABLE_LED	2


/**
* definition du nombre de timer system utiliser par les utilisateurs
*/
#define E_NB_USER_TIMER 4U

/******************************************************************************/
/*                                                                            */
/* => Em260 management                                                        */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#define EM260_IO_nHOST_INT    ((SIo)IO_D_2)
#define EM260_IO_nRESET       ((SIo)IO_C_3)
#define EM260_IO_nSSEL        ((SIo)IO_B_4)
#define EM260_IO_nWAKE        ((SIo)IO_B_1)
#define EM260_IO_MISO         ((SIo)IO_B_6)
#define EM260_IO_MOSI         ((SIo)IO_B_5)
#define EM260_IO_SCK          ((SIo)IO_B_7)

/**
* definit les led presente
*/
#define RF_LED ((SIo)IO_B_3)
#define DBG_LED ((SIo)IO_B_2)

#define APP_LED_1 ((SIo)IO_A_0)

#endif  // _app_product_hardware_H_
