/*
 * TFT_cfg.h
 *
 *  Created on: Apr 20, 2020
 *      Author: MO._.Hamdy "Wazeer"
 */

#ifndef TFT_CFG_H_
#define TFT_CFG_H_

#include "DIO_Interface.h"
#include "DIO_private.h"


/***************************************************************************************/
/* Configure TFT DATA PORT & Direction         		                                   */
/***************************************************************************************/
#define TFT_DATA_PORT   	PORTC
#define TFT_DATA_PORT_DIR   DDRC

/***************************************************************************************/
/* Configure TFT Control PINS & Direction         		                               */
/***************************************************************************************/
#define TFT_CTRL_PORT   	PORTD
#define TFT_CTRL_PORT_DIR   DDRD

#define TFT_RST       DIO_PA7
#define TFT_CS		  DIO_PA6
#define TFT_RS        DIO_PA5
#define TFT_WR        DIO_PA4
#define TFT_RD  	  DIO_PA3

/***************************************************************************************/
/* Configure TFT DISPLAY MODE         		                                           */
/***************************************************************************************/
#define TFT_DISPLAY_MODE 	TFT_LANDSCAPE


#endif /* TFT_CFG_H_ */
