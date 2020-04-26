/*
 * Leds.h
 *
 *  Created on: Dec 31, 2019
 *      Author: MO._.Hamdy "Wazeer"
 */

#ifndef __ECUAL_LEDS_LEDS_H__
#define __ECUAL_LEDS_LEDS_H__


#include "DIO_Interface.h"

/*
*	LED number
*/
#define LED_1 	DIO_PB4
#define LED_2 	DIO_PB5
#define LED_3 	DIO_PB6
#define LED_4 	DIO_PB7

/***************************************************************************************/
/* brief!  Initialize The output pins for LEDS                                         */
/* param!  void                            			                                   */
/* return! u8 Indication of the execution if it fails or not                           */
/***************************************************************************************/
extern uint8_t Init_LEDS(void);

/***************************************************************************************/
/* brief!  Toggle LED1                                                                 */
/* param!  LED number                            			                           */
/* return! u8 Indication of the execution if it fails or not                           */
/***************************************************************************************/
extern uint8_t LED1_Toggle(void);

/***************************************************************************************/
/* brief!  Toggle LED2                                                                 */
/* param!  LED number                            			                           */
/* return! u8 Indication of the execution if it fails or not                           */
/***************************************************************************************/
extern uint8_t LED2_Toggle(void);

/***************************************************************************************/
/* brief!  Toggle LED3                                                                 */
/* param!  LED number                            			                           */
/* return! u8 Indication of the execution if it fails or not                           */
/***************************************************************************************/
extern uint8_t LED3_Toggle(void);

/***************************************************************************************/
/* brief!  Toggle LED4                                                                 */
/* param!  LED number                            			                           */
/* return! u8 Indication of the execution if it fails or not                           */
/***************************************************************************************/
extern uint8_t LED4_Toggle(void);


#endif /* __ECUAL_LEDS_LEDS_H__ */
