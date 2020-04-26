/*
 * PWM.h
 *
 *  Created on: Apr 20, 2020
 *      Author: MO._.Hamdy "Wazeer"
 */

#ifndef __FIRMWARE_PWM_PWM_H__
#define __FIRMWARE_PWM_PWM_H__


/*
 *	Header files inclusions
 */
#include "PWM_Cfg.h"
#include "PWM_retval.h"
#include "Data_Types.h"


#define PWM_NOT_INTIALIZED 	0U
#define PWM_IS_INTIALIZED 	1U

#define PWM_CHANNEL_NOT_INTIALIZED 	0U
#define PWM_CHANNEL_IS_INTIALIZED 	1U

#define PWM_CHANNEL_READY 		0U
#define PWM_CHANNEL_RUNNING 	1U


/***************************************************************************************/
/* brief!  PWM Initialization                                                          */
/* param!  (I/P) desired resolution in microseconds                                    */
/* return! u8 Indication of the execution if it fails or not                           */
/***************************************************************************************/
extern error_t PWM_Init(uint32_t au32_Resolution);

/***************************************************************************************/
/* brief!  PWM Deinitialization                                                        */
/* param!  void                                                                        */
/* return! u8 Indication of the execution if it fails or not                           */
/***************************************************************************************/
extern error_t PWM_Deinit(void);

/***************************************************************************************/
/* brief!  PWM Channel Initialization                								   */
/* param!  u8 (I/P) PWM Channel Number "0:31"						                   */
/* param!  u8 (I/P) PWM signal Pin out Number "0:31" 				                   */
/* param!  u8 (I/P) PWM signal Duty Cycle "0:100"               				       */
/* param!  u32(I/P) PWM signal time period 										       */
/* return! u8 Indication of the execution if it fails or not                           */
/***************************************************************************************/
extern error_t PWM_Channel_Init(uint8_t au8_Channel, uint8_t au8_PinNum, uint8_t au8_DutyCycle, uint32_t au32_Period);

/***************************************************************************************/
/* brief!  Start generate PWM Signal on the defined Channel			                   */
/* param!  u8 (I/P) PWM used Channel 								                   */
/* return! u8 Indication of the execution if it fails or not                           */
/***************************************************************************************/
extern error_t PWM_Channel_Start(uint8_t au8_Channel);

/***************************************************************************************/
/* brief!  Stop generate PWM Signal on the defined Channel			                   */
/* param!  u8 (I/P) PWM used Channel 								                   */
/* return! u8 Indication of the execution if it fails or not                           */
/***************************************************************************************/
extern error_t PWM_Channel_Stop(uint8_t au8_Channel);


#endif /* __FIRMWARE_PWM_PWM_H__ */
