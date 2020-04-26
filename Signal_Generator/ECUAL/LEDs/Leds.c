/*
 * Leds.c
 *
 *  Created on: Dec 31, 2019
 *      Author: MO._.Hamdy "Wazeer"
 */


#include "Leds.h"

/***************************************************************************************/
/* brief!  Initialize The output pins for LEDS                                         */
/* param!  void                            			                                   */
/* return! u8 Indication of the execution if it fails or not                           */
/***************************************************************************************/
uint8_t Init_LEDS(void)
{
	DIO_INIT_Pin(LED_1,OUTPUT_PIN);
	DIO_INIT_Pin(LED_2,OUTPUT_PIN);
	DIO_INIT_Pin(LED_3,OUTPUT_PIN);
	DIO_INIT_Pin(LED_4,OUTPUT_PIN);

	return 0;
}

/***************************************************************************************/
/* brief!  Toggle LED1                                                                 */
/* param!  LED number                            			                           */
/* return! u8 Indication of the execution if it fails or not                           */
/***************************************************************************************/
uint8_t LED1_Toggle(void)
{
	DIO_Toggle_Pin(LED_1);
	return 0 ;
}

/***************************************************************************************/
/* brief!  Toggle LED2                                                                 */
/* param!  LED number                            			                           */
/* return! u8 Indication of the execution if it fails or not                           */
/***************************************************************************************/
uint8_t LED2_Toggle(void)
{
	DIO_Toggle_Pin(LED_2);
	return 0 ;
}

/***************************************************************************************/
/* brief!  Toggle LED3                                                                 */
/* param!  LED number                            			                           */
/* return! u8 Indication of the execution if it fails or not                           */
/***************************************************************************************/
uint8_t LED3_Toggle(void)
{
	DIO_Toggle_Pin(LED_3);
	return 0 ;
}

/***************************************************************************************/
/* brief!  Toggle LED4                                                                 */
/* param!  LED number                            			                           */
/* return! u8 Indication of the execution if it fails or not                           */
/***************************************************************************************/
uint8_t LED4_Toggle(void)
{
	DIO_Toggle_Pin(LED_4);
	return 0 ;
}
