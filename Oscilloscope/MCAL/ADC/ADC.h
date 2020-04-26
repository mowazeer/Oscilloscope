/*
 * ADC.h
 *
 *  Created on: Apr 18, 2020
 *      Author: MO._.Hamdy "Wazeer"
 */

#ifndef __MCAL_ADC_ADC_H__
#define __MCAL_ADC_ADC_H__

#include "Data_Types.h"
#include "DIO_interface.h"
#include "ADC_retval.h"

/*
*	Declaring the structure that will hold the information about certain event
*/
typedef struct{
	uint8_t u8_Channel ;			/* ADC used channel */
	uint8_t u8_VoltRef;				/* The voltage reference */
	uint8_t u8_LeftRight_Adjust; 	/* Left or Right_Adjust */
	uint8_t u8_PSC ;         		/* The desired prescaler */
	uint8_t u8_Interrupt_Mode;  	/* Interrupt or Polling */
	uint8_t u8_Trigger_Source ;   	/* ADC Trigger Source */
	}str_ADC_cfg_t;


/* ADC Init. state */
#define ADC_IS_INTIALIZED 			1U
#define ADC_NOT_INTIALIZED 			0U

 /* ADC Channel */
#define ADC_CH_MASK 	0X1FU
#define ADC_CH0			DIO_PA0
#define ADC_CH1     	DIO_PA1
#define ADC_CH2			DIO_PA2
#define ADC_CH3    		DIO_PA3
#define ADC_CH4			DIO_PA4
#define ADC_CH5     	DIO_PA5
#define ADC_CH6			DIO_PA6
#define ADC_CH7     	DIO_PA7

/* Reference Voltage */
#define ADC_VCC_MASK 			(0X02U << 6U)
#define ADC_EXTERNAL_VCC      	(0X00U << 6U)
#define ADC_INTERNAL_VCC		(0X01U << 6U)
#define RESERVED				(0X02U << 6U)
#define ADC_INTERNAL_2_56VCC    (0X03U << 6U)

/* ADC Left/Right Adjust Result */
#define ADC_RIGHT_ADJUST		0U
#define ADC_LEFT_ADJUST      	1U

/*
*	ADC prescaler
*/
#define ADC_PSC_MASK 			0X07U
#define ADC_PSC_0 				0X00U
#define ADC_PSC_2 				0X01U
#define ADC_PSC_4 				0X02U
#define ADC_PSC_8 				0X03U
#define ADC_PSC_16 				0X04U
#define ADC_PSC_32 				0X05U
#define ADC_PSC_64 				0X06U
#define ADC_PSC_128 			0X07U

/* ADC Interrupt / Polling Mode */
#define ADC_INTERRUPT 			0X00U
#define ADC_POLLING 			0X01U

/* ADC Trigger Mode and Source */
#define ADC_TRIGGER_MASK 				(0X70U << 5U)
#define ADC_MANUAL_TRIGGER 				(0XFFU)
#define ADC_FREE_RUNNING 				(0X00U << 5U)
#define ADC_ANALOG_COMPARATOR 			(0X01U << 5U)
#define ADC_EXT_INTERRUPT_0 			(0X02U << 5U)
#define ADC_TIMER_0_COMPARE_MATCH		(0X03U << 5U)
#define ADC_TIMER_0_OVERFLOW 			(0X04U << 5U)
#define ADC_TIMER_1B_COMPARE_MATCH 		(0X05U << 5U)
#define ADC_TIMER_1_OVERFLOW 			(0X06U << 5U)
#define ADC_TIMER_1_CAPTURE 			(0X07U << 5U)


/* ADMUX */
#define REFS1   7
#define REFS0   6
#define ADLAR   5
#define MUX4    4
#define MUX3    3
#define MUX2    2
#define MUX1    1
#define MUX0    0

/* ADCSRA */
#define ADEN    7
#define ADSC    6
#define ADATE   5
#define ADIF    4
#define ADIE    3
#define ADPS2   2
#define ADPS1   1
#define ADPS0   0


/***************************************************************************************/
/* brief!  ADC Initialization                                                          */
/* param!  (I/P) pointer to structure that hold ADC Configuration                      */
/* return! u8 Indication of the execution if it fails or not                           */
/***************************************************************************************/
extern error_t ADC_Init(str_ADC_cfg_t *pstr_ADC_cfg);

/***************************************************************************************/
/* brief!  ADC Deinitialization                                                        */
/* param!  void                                                                        */
/* return! u8 Indication of the execution if it fails or not                           */
/***************************************************************************************/
extern error_t ADC_Deinit(void);

/***************************************************************************************/
/* brief!  ADC Change the configuration of the ADC to a certain channel                */
/* param!  u8 (i/p) The desired channel to be changed                                  */
/* return! u8 Indication of the execution if it fails or not                           */
/***************************************************************************************/
extern error_t ADC_Change_Channel(uint8_t au8_Channel);

/***************************************************************************************/
/* brief!  ADC Start Conversion                                                        */
/* param!  void                                                                        */
/* return! u8 Indication of the execution if it fails or not                           */
/***************************************************************************************/
extern error_t ADC_Start_Conversion(void);

/***************************************************************************************/
/* brief!  ADC Stop Conversion                                                        */
/* param!  void                                                                        */
/* return! u8 Indication of the execution if it fails or not                           */
/***************************************************************************************/
extern error_t ADC_Stop_Conversion(void);

/***************************************************************************************/
/* brief!  ADC Read Value	                                                           */
/* param!  (o/p) pu16 pointer to u16 that hold ADC Value                               */
/* return! u8 Indication of the execution if it fails or not                           */
/***************************************************************************************/
extern error_t ADC_Read(uint16_t volatile *pu16_Digital_Reading);

/***************************************************************************************/
/* brief!  TMU Set the function that will execute in the ISR                           */
/* param!  pointer to function that will execute in the ISR                            */
/* return! u8 Indication of the execution if it fails or not                           */
/***************************************************************************************/
extern error_t ADC_SetCallBack(pfunc_u8_u8_t pfun_ADC_App);


#endif /* __MCAL_ADC_ADC_H__ */
