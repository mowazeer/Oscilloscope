/*
 * EXT_INTE.h
 *
 *  Created on: Jan 19, 2020
 *      Author: MO._.Hamdy
 */

#ifndef __MCAL_INTERRUPT_INTE_EXT_INTE_H__
#define __MCAL_INTERRUPT_INTE_EXT_INTE_H__

/*
*	Header files inclusions
*/
#include "EXT_INTE_retval.h"
#include "Data_Types.h"

/* MCUCR */
#define ISC00   0U
#define ISC01   1U
#define ISC10   2U
#define ISC11   3U

/* MCUCSR */
#define ISC2    6U

/* GICR */
#define INT2    5U
#define INT0    6U
#define INT1    7U

/* GIFR */
#define INTF2   5U
#define INTF0   6U
#define INTF1   7U

/* Interrupt Request Number */
#define INTE_0    0U
#define INTE_1    1U
#define INTE_2    2U

/*
*	INTE_0 sense control
*/
#define INTE0_SENCE_MASK 		0X03U
#define INTE0_LOW_LEVEL 		0X00U
#define INTE0_LOGICAL_CHANGE 	0X01U
#define INTE0_FALLING_EDGE 		0X02U
#define INTE0_RISING_EDGE 		0X03U
/*
*	INTE_1 sense control
*/
#define INTE1_SENCE_MASK 		(0X03U << 2U)
#define INTE1_LOW_LEVEL 		(0X00U << 2U)
#define INTE1_LOGICAL_CHANGE 	(0X01U << 2U)
#define INTE1_FALLING_EDGE 		(0X02U << 2U)
#define INTE1_RISING_EDGE 		(0X03U << 2U)
/*
*	INTE_2 sense control
*/
#define INTE2_SENCE_MASK 		(0X01U << 6U)
#define INTE2_FALLING_EDGE 		(0X00U << 6U)
#define INTE2_RISING_EDGE 		(0X01U << 6U)

/*
 * Interrupt is INTIALIZED
 */
#define INTE_IS_INTIALIZED 		1U
#define INTE_NOT_INTIALIZED 		0U

/*
 * number of Interrupts
 */
#define INTE_INIT_BUFFER 		3U

/***************************************************************************************/
/* brief!  function that initialize and the interrupt request                          */
/* param!  u8 (i/p) Interrupt request number                                           */
/* param!  u8 (i/p) Interrupt Sense Control                                            */
/* return! u8 Indication of the execution if it fails or not                           */
/***************************************************************************************/
extern error_t Ext_Inte_Init(uint8_t au8_Inte_RequestNum, uint8_t au8_InteSense_Control);

/***************************************************************************************/
/* brief!  function that deinitialize and the interrupt request                        */
/* param!  u8 (i/p) Interrupt request number                                           */
/* return! u8 Indication of the execution if it fails or not                           */
/***************************************************************************************/
extern error_t Ext_Inte_Deinit(uint8_t au8_Inte_RequestNum);

/***************************************************************************************/
/* brief!  function that change the interrupt Sense Control                            */
/* param!  u8 (i/p) Interrupt request number                                           */
/* param!  u8 (i/p) Interrupt Sense Control                                            */
/* return! u8 Indication of the execution if it fails or not                           */
/***************************************************************************************/
extern error_t Ext_Inte_ChangeSense_Control(uint8_t au8_Inte_RequestNum, uint8_t au8_InteSense_Control);

/***************************************************************************************/
/* brief!  Set the function that will execute in the ISR                               */
/* param!  pointer to function that will execute in the ISR                            */
/* param!  u8 (i/p) Interrupt Request Number                                           */
/* return! u8 Indication of the execution if it fails or not                           */
/***************************************************************************************/
extern error_t Int_SetCallBack(pfunc_t pfun_Int_App, uint8_t au8_Inte_RequestNum);


#endif /* __MCAL_INTERRUPT_INTE_EXT_INTE_H__ */
