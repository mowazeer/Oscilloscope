/*
 * SOS.h
 *
 *  Created on: Jan 7, 2020
 *      Author: MO._.Hamdy "Wazeer"
 */

#ifndef __FIRMWARE_SOS_SOS_H__
#define __FIRMWARE_SOS_SOS_H__


/*
 *	Header files inclusions
 */
#include "SOS_cfg.h"
#include "SOS_retval.h"
#include "Data_Types.h"


/*
*	Used macros
*/
#define READY 		0U
#define NOT_READY 	1U
#define WAITING 	2U
#define RUNNING 	3U

#define PERIODIC 	0xFFU
#define ONE_SHOT 	1U

#define NOT_OPERATED 	0U
#define OPERATED 		1U

#define FIRST_READYTASK 	0U
#define SECOND_READYTASK 	1U

/* to make sure we obtained accurate time */
#define SOS_ISR_RESET_FLAG 		100000UL
#define SOS_ISR_RESET_VALUE 	1U

/***************************************************************************************/
/* brief!  SOS Initialization                                                          */
/* param!  (I/P) desired resolution in microseconds                                    */
/* return! u8 Indication of the execution if it fails or not                           */
/***************************************************************************************/
extern error_t SOS_Init(uint32_t au32_Resolution);

/***************************************************************************************/
/* brief!  SOS Deinitialization                                                        */
/* param!  void                                                                        */
/* return! u8 Indication of the execution if it fails or not                           */
/***************************************************************************************/
extern error_t SOS_Deinit(void);

/***************************************************************************************/
/* brief!  Adds a certain function with a certain interval as an event                 */
/* param!  (I/P) pointer to the function that is desired to be executed                */
/* param!  u32 (I/P) delay time before executing the desired function                  */
/* param!  u8 (I/P) user wants to execute this function periodically or one shot       */
/* return! u8 Indication of the execution if it fails or not                           */
/***************************************************************************************/
extern error_t SOS_CreatTask(u8_pfunc_t pfun_SosApp, uint32_t au32_TicksNum , uint8_t u8_Priority, uint8_t au8_Periodicity );

/***************************************************************************************/
/* brief!  Delete a certain event from being executed                                  */
/* param!  (I/P) pointer to function that is desired to be stopped                     */
/* return! u8 Indication of the execution if it fails or not                           */
/***************************************************************************************/
extern error_t SOS_DeleteTask(u8_pfunc_t pfun_Timer_App);

/***************************************************************************************/
/* brief!  SOS Manager                                                                 */
/* param!  void                                                                        */
/* return! u8 Indication of the execution if it fails or not                           */
/***************************************************************************************/
extern error_t SOS_Run(void) ;


#endif /* __FIRMWARE_SOS_SOS_H__ */
