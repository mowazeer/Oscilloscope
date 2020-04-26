/*
 * TIMER.h
 *
 *  Created on: Dec 31, 2019
 *      Author: MO._.Hamdy "Wazeer"
 */

#ifndef __MCAL_TIMER_TIMER_H__
#define __MCAL_TIMER_TIMER_H__


/*
*	Header files inclusions
*/
#include "Data_Types.h"
#include "TIMER_retval.h"

/*
*	Defining the frequency of the CPU
*/
#define F_CPU	 8000000UL
#define NULL	 0U

/*
*	TIMSK bits
*/
#define TOIE0   	0U
#define OCIE0   	1U
#define TOIE1   	2U
#define OCIE1B  	3U
#define OCIE1A  	4U
#define TICIE1  	5U
#define TOIE2   	6U
#define OCIE2   	7U

/*
*	TIFR bits
*/
#define TOV0    	0U
#define OCF0    	1U
#define TOV1    	2U
#define OCF1B   	3U
#define OCF1A   	4U
#define ICF1    	5U
#define TOV2    	6U
#define OCF2    	7U

/*
*	TCCR0 bits
*/
#define CS00    	0U
#define CS01    	1U
#define CS02    	2U
#define WGM01   	3U
#define COM00   	4U
#define COM01  	 	5U
#define WGM00   	6U
#define FOC0    	7U

/*
*	TCCR1A bits
*/
#define WGM10   	0U
#define WGM11   	1U
#define FOC1B   	2U
#define FOC1A   	3U
#define COM1B0  	4U
#define COM1B1  	5U
#define COM1A0  	6U
#define COM1A1  	7U

/*
*	TCCR1B bits
*/
#define CS10    	0U
#define CS11    	1U
#define CS12    	2U
#define WGM12   	3U
#define WGM13   	4U
#define ICES1   	6U
#define ICNC1   	7U

/*
*	TCCR2 bits
*/
#define CS20    	0U
#define CS21    	1U
#define CS22    	2U
#define WGM21   	3U
#define COM20   	4U
#define COM21   	5U
#define WGM20   	6U
#define FOC2    	7U

/*
*	Timer2 Asynchronous Status Register bits
*/
#define TCR2UB  	0U
#define OCR2UB  	1U
#define TCN2UB  	2U
#define AS2     	3U

/*
*	Timer Channels number
*/
#define CHANNELS_NUMBER 	3U
/*
*	Timer Channels
*/
#define TIMER0 		0U
#define TIMER1 		1U
#define TIMER2 		2U
/*
* 	Timer Mode
*/
#define INTERRUPT 	0U
#define POLLING 	1U
/*
* 	Mode Timer/Counter
*/
#define TIMER_MODE 		0U
#define COUNTER_MODE 	1U
/*
* 	Timers Max value
*/
#define TIMER0_MAX_VALUE 	255U
#define TIMER1_MAX_VALUE 	65535U
#define TIMER2_MAX_VALUE 	255U

/*
*	The upcoming 9 macros is used in the calculations of number of ticks needed for a specific time
*/
#define FREQ_OVER_MILLI (F_CPU / 1000UL)
#define FREQ_OVER_MICRO (F_CPU / 1000000UL)

#define PRESCALE_0    	1UL
#define PRESCALE_8    	8UL
#define PRESCALE_32   	32UL
#define PRESCALE_64   	64UL
#define PRESCALE_128  	128UL
#define PRESCALE_256  	256UL
#define PRESCALE_1024 	1024UL

/*
*	Timer 0 prescaler
*/
#define T0_PSC_MASK 			0X07U
#define T0_PSC_NO_CLK  			0X00U
#define T0_PSC_0 				0X01U
#define T0_PSC_8 				0X02U
#define T0_PSC_64 				0X03U
#define T0_PSC_256 				0X04U
#define T0_PSC_1024 			0X05U
#define T0_PSC_EXT_ON_FALLING 	0X06U
#define T0_PSC_EXT_ON_RISING 	0X07U

/*
*	Timer 1 prescaler
*/
#define T1_PSC_MASK 			0X07U
#define T1_PSC_NO_CLK  			0X00U
#define T1_PSC_0 				0X01U
#define T1_PSC_8 				0X02U
#define T1_PSC_64 				0X03U
#define T1_PSC_256 				0X04U
#define T1_PSC_1024 			0X05U
#define T1_PSC_EXT_ON_FALLING 	0X06U
#define T1_PSC_EXT_ON_RISING 	0X07U

/*
*	Timer 2 prescaler
*/
#define T2_PSC_MASK 			0X07U
#define T2_PSC_NO_CLK  			0X00U
#define T2_PSC_0 				0X01U
#define T2_PSC_8 				0X02U
#define T2_PSC_32 				0X03U
#define T2_PSC_64 				0X04U
#define T2_PSC_128 				0X05U
#define T2_PSC_256 				0X06U
#define T2_PSC_1024 			0X07U


/*
*	Definition of the timer configuration structure
*/
typedef struct{
	uint8_t u8_Channel ;      	/* Timer 0, 1 or 2        */
	uint8_t u8_PSC ;          	/* The desired prescaler  */
	uint8_t u8_Timer_Mode ;   	/* Timer or counter mode  */
	uint8_t u8_Interrupt_Mode;  /* Interrupt or Polling   */
	} Timer_cfg_s;

/* global variable that hold the number of over flow count */
extern volatile uint32_t gu32_T0_OVF_Count;

/***************************************************************************************/
/* brief!  A function that takes pointer to struct to configure the desired timer      */
/* param!  (I/P) u8 Timer channel "The desired timer to be started"                    */
/* return! u8 Indication of the execution if it fails or not                           */
/***************************************************************************************/
extern error_t Timer_Init(Timer_cfg_s *pstr_Timer_cfg);

/***************************************************************************************/
/* brief!  Function that start a chosen timer                                          */
/* param!  (I/P) u8 Timer channel "The desired timer to be started"                    */
/* param!  (I/P) u8 The desired ticks to be counted                                    */
/* return! u8 Indication of the execution if it fails or not                           */
/***************************************************************************************/
extern error_t Timer_Start(uint8_t u8_Channel , uint16_t u16_Ticks);

/***************************************************************************************/
/* brief!  Function that stop a chosen timer                                           */
/* param!  (I/P) u8 Timer channel                                                      */
/* return! u8 Indication of the execution if it fails or not                           */
/***************************************************************************************/
extern error_t Timer_Stop(uint8_t u8_Channel);

/***************************************************************************************/
/* brief!  Function that reset a chosen timer                                          */
/* param!  (I/P) u8 Timer channel                                                      */
/* return! u8 Indication of the execution if it fails or not                           */
/***************************************************************************************/
extern error_t Timer_Reset(uint8_t u8_Channel) ;

/***************************************************************************************/
/* brief!  function that calculates the time per tick, in nano second                  */
/* param!  (I/P) u8 Timer channel                                                      */
/* param!  (O/P) u32* The value of the time per tick                                   */
/* return! u8 Indication of the execution if it fails or not                           */
/***************************************************************************************/
extern error_t Timer_Get_Tick_Time(uint8_t u8_Channel, uint32_t *pu32_Timer_Time_ns);

/***************************************************************************************/
/* brief!  TMU Set the function that will execute in the ISR                           */
/* param!  pointer to function that will execute in the ISR                            */
/* param!  u8 (i/p) Timer channel Number                                               */
/* return! u8 Indication of the execution if it fails or not                           */
/***************************************************************************************/
extern error_t TIMER_SetCallBack(pfunc_t pfun_Timer_App, uint8_t au8_Channel_Num);

void TIMER0_OVF(void);


#endif /* __MCAL_TIMER_TIMER_H__ */
