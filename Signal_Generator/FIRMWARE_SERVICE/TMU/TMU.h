/*
 * TMU.h
 *
 *  Created on: Dec 31, 2019
 *      Author: MO._.Hamdy "Wazeer"
 */

#ifndef __FIRMWARE_TMU_TMU_H__
#define __FIRMWARE_TMU_TMU_H__


/*
 *	Header files inclusions
 */
#include "TMU _retval.h"
#include "TMU_cfg.h"
#include "Data_Types.h"


/*
*	Used macros
*/
#define READY 		0U
#define NOT_READY 	1U

#define PERIODIC 	0xFFU
#define ONE_SHOT 	1U

#define NOT_OPERATED 	0U
#define OPERATED 		1U

#define OK 				0U
#define NOT_YET 		1U

/* to make sure we obtained accurate time */
#define ISR_RESET_FLAG 		100000UL

/***************************************************************************************/
/* brief!  TMU Initialization                                                          */
/* param!  (I/P) desired resolution in microseconds                                    */
/* return! u8 Indication of the execution if it fails or not                           */
/***************************************************************************************/
extern error_t TMU_Init(uint32_t au32_Resolution);

/***************************************************************************************/
/* brief!  TMU Deinitialization                                                        */
/* param!  void                                                                        */
/* return! u8 Indication of the execution if it fails or not                           */
/***************************************************************************************/
extern error_t TMU_Deinit(void);

/***************************************************************************************/
/* brief!  Adds a certain function with a certain interval as an event                 */
/* param!  (I/P) pointer to the function that is desired to be executed                */
/* param!  u32 (I/P) delay time before executing the desired function                  */
/* param!  u8 (I/P) user wants to execute this function periodically or one shot       */
/* return! u8 Indication of the execution if it fails or not                           */
/***************************************************************************************/
extern error_t TMU_Start(u8_pfunc_t pfun_Timer_App, uint32_t au32_Resolution , uint8_t au8_Periodicity );

/***************************************************************************************/
/* brief!  Stops a certain event from being executed                                   */
/* param!  (I/P) pointer to function that is desired to be stopped                     */
/* return! u8 Indication of the execution if it fails or not                           */
/***************************************************************************************/
extern error_t TMU_Stop(u8_pfunc_t pfun_Timer_App);

/***************************************************************************************/
/* brief!  Restart a certain event after it has been stopped                           */
/* param!  (I/P) pointer to function that is desired to be restart                     */
/* return! u8 Indication of the execution if it fails or not                           */
/***************************************************************************************/
extern error_t TMU_Restart(u8_pfunc_t pfun_Timer_App);

/***************************************************************************************/
/* brief!  TMU Manager                                                                 */
/* param!  void                                                                        */
/* return! u8 Indication of the execution if it fails or not                           */
/***************************************************************************************/
extern error_t TMU_Dispatcher(void) ;


#endif /* __FIRMWARE_TMU_TMU_H__ */
