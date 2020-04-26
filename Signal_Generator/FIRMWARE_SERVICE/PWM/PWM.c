/*
 * PWM.c
 *
 *  Created on: Apr 20, 2020
 *      Author: MO._.Hamdy "Wazeer"
 */


#include "PWM.h"
#include "PWM_PbCfg.h"
#include "Interrupt.h"
#include "DIO_Interface.h"

/*
*	Declaring the structure that will hold the information about certain PWM channel
*/
typedef struct
{
	uint8_t  u8_Pwm_Pin ; 						/* PWM pin out number "0:31" */
	uint8_t  u8_Pwm_Duty_Cycle ; 				/* PWM signal Duty Cycle "0:100" */
	uint32_t u32_Pwm_Period ; 					/* PWM signal time period */
	uint32_t u32_Pwm_OFF_Event ; 				/* PWM off event flag */
	uint8_t  u8_Pwm_Channel_States ; 			/* PWM channel state "ready/running" */
	volatile uint32_t u32_Pwm_Channel_Count ; 	/* PWM updated channel ticks number */
}str_PwmEvent_t;

/*
*	Static variable that tells if the PWM module is initialized or not
*/
static uint8_t gu8_PWM_InitFlag = PWM_NOT_INTIALIZED ;

/*
*	Static array that tells if the PWM channels is initialized or not
*/
static uint8_t gu8_PWM_Channel_InitFlag[PWM_CHANNELS_NUM] = {PWM_CHANNEL_NOT_INTIALIZED} ;

/*
 *	Static variables that hold the time resolution limits
 */
static uint32_t gu32_MinResolution = NULL ;
static uint32_t gu32_MaxResolution = NULL ;

/*
 *	Static variable that will hold the ISR counter
 */
static uint8_t gu8_ISR_Count = NULL ;

/*
 *	static variable that will hold the number of ticks needed to achieve the desired resolution
 */
static uint16_t gu16_TicksCount = NULL ;

/*
*	Allocating space for the Channel configuration
*/
static str_PwmEvent_t gastr_PWM_Channel[PWM_CHANNELS_NUM] ;

/***************************************************************************************/
/* brief!  what ISR handling                                                           */
/* param!  void                            			                                   */
/* return! void                                                                        */
/***************************************************************************************/
static void PWM_TIMER_CallBack(void)
{
	Disable_GlobalInterrupt();

	/*TODO just increment the flags */
	/* loop on the PWM channels */
	for (gu8_ISR_Count = NULL ; gu8_ISR_Count <= PWM_CHANNELS_NUM ; gu8_ISR_Count++)
	{
		/* check if the current PWM channel is in running state */
		if(PWM_CHANNEL_RUNNING == gastr_PWM_Channel[gu8_ISR_Count].u8_Pwm_Channel_States)
		{
			/* increment the current PWM counter */
			gastr_PWM_Channel[gu8_ISR_Count].u32_Pwm_Channel_Count ++;

			/* check if the current PWM signal meet his period time */
			if (NULL == (gastr_PWM_Channel[gu8_ISR_Count].u32_Pwm_Channel_Count % gastr_PWM_Channel[gu8_ISR_Count].u32_Pwm_Period))
			{
				/* PWM ON time */
				DIO_Write_Pin(gastr_PWM_Channel[gu8_ISR_Count].u8_Pwm_Pin, HIGH_PIN);
				gastr_PWM_Channel[gu8_ISR_Count].u32_Pwm_Channel_Count = INITIAL;
			}
			/* check if the current PWM signal meet his Duty Cycle time */
			else if(NULL == (gastr_PWM_Channel[gu8_ISR_Count].u32_Pwm_Channel_Count % gastr_PWM_Channel[gu8_ISR_Count].u32_Pwm_OFF_Event))
			{
				/* PWM OFF time */
				DIO_Write_Pin(gastr_PWM_Channel[gu8_ISR_Count].u8_Pwm_Pin, LOW_PIN);
			}
		}
		/* PWM channel is in ready state */
		else
		{
			/* Do nothing */
		}
	}
	Enable_GlobalInterrupt();
}

/***************************************************************************************/
/* brief!  PWM Initialization                                                          */
/* param!  (I/P) desired resolution in microseconds                                    */
/* return! u8 Indication of the execution if it fails or not                           */
/***************************************************************************************/
error_t PWM_Init(uint32_t au32_Resolution)
{
	/*
	 *	Development Error Tracer
	 */
	error_t au8_Det = ERROR_OK ;

	/* A variable that will hold the time per tick for the chosen timer */
	uint32_t au32_TickTime = NULL ;

	/*
	*	Calculating the minimum and maximum resolution for the chosen timer configuration
	*/
	gu32_MinResolution = ( (PWM_PRESCALE_VALUE) / FREQ_OVER_MICRO ) ;

	if (TIMER0 == PWM_Config.u8_Channel)
	{
		gu32_MaxResolution = gu32_MinResolution * TIMER0_MAX_VALUE ;

	}
	else if(TIMER1 == PWM_Config.u8_Channel)
	{
		gu32_MaxResolution = gu32_MinResolution * TIMER1_MAX_VALUE ;
	}
	else if(TIMER2 == PWM_Config.u8_Channel)
	{
		gu32_MaxResolution = gu32_MinResolution * TIMER2_MAX_VALUE ;
	}
	else
	{
		/* Handling of entering wrong timer channel is already done in Timer_Init function in Timer.c */
		au8_Det = E_CHANNEL;
	}

	/*
	 *	Checking if the passed resolution is in the allowed range for the resolution
	 */

	if ((au32_Resolution >= gu32_MinResolution) && (au32_Resolution <= gu32_MaxResolution) && (ERROR_OK == au8_Det))
	{
		/*
		*	Initializing the timer with the configuration defined in PWM_cfg.c
		*/
		Timer_Init(&PWM_Config);

		Timer_Get_Tick_Time(PWM_Config.u8_Channel , &au32_TickTime) ; /* Now au32_TickTime holds the value of tick time in nano seconds*/

		//au32_TickTime /= PWM_RESOLUTION_IN_MICRO ; /* so we divide it by 1000 to get it in micro sec. */

		gu16_TicksCount = (au32_Resolution * PWM_RESOLUTION_IN_MICRO )/ au32_TickTime ;

		au8_Det = TIMER_SetCallBack(PWM_TIMER_CallBack, PWM_Config.u8_Channel);
		au8_Det = Timer_Start(PWM_Config.u8_Channel , gu16_TicksCount);
	}
	else
	{
		/* Handling of entering wrong resolution */
		au8_Det = E_PWM_RESOLUTION ;
	}

	/* Fire the PWM module Init. Flag if there is no error */
	if (ERROR_OK == au8_Det)
	{
		gu8_PWM_InitFlag = PWM_IS_INTIALIZED ;
	}
	else
	{
		gu8_PWM_InitFlag = PWM_NOT_INTIALIZED ;
	}

	return au8_Det ;
}

/***************************************************************************************/
/* brief!  PWM Deinitialization                                                        */
/* param!  void                                                                        */
/* return! u8 Indication of the execution if it fails or not                           */
/***************************************************************************************/
error_t PWM_Deinit(void)
{
	/*
	 *	Development Error Tracer
	 */
	error_t au8_Det = ERROR_OK ;

	/*
	*	Making sure that the PWM is Initialized
	*/
	if (PWM_IS_INTIALIZED == gu8_PWM_InitFlag)
	{
		au8_Det = Timer_Stop(PWM_Config.u8_Channel);
		gu8_PWM_InitFlag = PWM_NOT_INTIALIZED;
	}
	else
	{
		/* Handling of Deinitialize PWM module before initialize it */
		au8_Det = E_PWM_NOT_INTIALIZED;
	}

	return au8_Det ;
}

/***************************************************************************************/
/* brief!  PWM Channel Initialization                								   */
/* param!  u8 (I/P) PWM Channel Number "0:31"						                   */
/* param!  u8 (I/P) PWM signal Pin out Number "0:31" 				                   */
/* param!  u8 (I/P) PWM signal Duty Cycle "0:100"               				       */
/* param!  u32(I/P) PWM signal time period 										       */
/* return! u8 Indication of the execution if it fails or not                           */
/***************************************************************************************/
error_t PWM_Channel_Init(uint8_t au8_Channel, uint8_t au8_PinNum, uint8_t au8_DutyCycle, uint32_t au32_Period)
{
	/*
	 *	Development Error Tracer
	 */
	error_t au8_Det = ERROR_OK ;

	/*
	*	Making sure that the PWM module is Initialized
	*/
	if (PWM_IS_INTIALIZED == gu8_PWM_InitFlag)
	{
		/*
		*	Making sure that the passed Duty Cycle is in range (0%:100%)
		*/
		if ((INITIAL <= au8_DutyCycle) && (100 >= au8_DutyCycle))
		{
			/* Making sure we pass a real time value */
			if (au32_Period >= INITIAL)
			{
				/* Checking if the array of channels "buffer" is full or not */
				if(PWM_CHANNELS_NUM > au8_Channel )
				{
					/*
					 *	Passing the Channel information to the Channels array
					 */
					gastr_PWM_Channel[au8_Channel].u8_Pwm_Pin            = au8_PinNum ;
					gastr_PWM_Channel[au8_Channel].u8_Pwm_Duty_Cycle     = au8_DutyCycle ;
					gastr_PWM_Channel[au8_Channel].u32_Pwm_Period        = au32_Period ;
					gastr_PWM_Channel[au8_Channel].u32_Pwm_OFF_Event     = ((gastr_PWM_Channel[au8_Channel].u8_Pwm_Duty_Cycle * gastr_PWM_Channel[au8_Channel].u32_Pwm_Period)/100U);
					gastr_PWM_Channel[au8_Channel].u32_Pwm_Channel_Count = INITIAL ;
					gastr_PWM_Channel[au8_Channel].u8_Pwm_Channel_States = PWM_CHANNEL_READY ;

					/* Make the used pin as output pin */
					au8_Det = DIO_INIT_Pin(au8_PinNum, OUTPUT_PIN);
					//au8_Det = DIO_INIT_Pin(gastr_PWM_Channel[au8_Channel].u8_Pwm_Pin, OUTPUT_PIN);
				}
				else
				{
					/* Handling number of events limit*/
					au8_Det = E_PWM_CHANNELS_NUM ;
				}
			}
			else
			{
				/* Handling entering Frequency "Time Period " doesn't match the limits */
				au8_Det = E_PWM_PERIOD ;
			}
		}
		else
		{
			/* Handling entering wrong duty cycle */
			au8_Det = E_PWM_DUTY_CYCLE ;
		}
	}
	else
	{
		/* Handling of Start PWM module before initialize it */
		au8_Det = E_PWM_NOT_INTIALIZED;
	}

	/* Fire the PWM Channel Init. Flag if there is no error */
	if (ERROR_OK == au8_Det)
	{
		gu8_PWM_Channel_InitFlag[au8_Channel] = PWM_CHANNEL_IS_INTIALIZED ;

		au8_Channel ++ ; /* Increment the index to the next free element in the events array */
	}
	else
	{
		gu8_PWM_Channel_InitFlag[au8_Channel] = PWM_CHANNEL_NOT_INTIALIZED ;
	}
	return au8_Det ;
}

/***************************************************************************************/
/* brief!  Start generate PWM Signal on the defined Channel			                   */
/* param!  u8 (I/P) PWM used Channel 								                   */
/* return! u8 Indication of the execution if it fails or not                           */
/***************************************************************************************/
error_t PWM_Channel_Start(uint8_t au8_Channel)
{
	/*
	 *	Development Error Tracer
	 */
	error_t au8_Det = ERROR_OK ;

	/*
	*	Checking if the array of Channels "buffer" is full or not
	*/
	if(PWM_CHANNELS_NUM > au8_Channel )
	{
		/*
		 *	Making sure that the PWM Channel is Initialized
		 */
		if (PWM_CHANNEL_IS_INTIALIZED == gu8_PWM_Channel_InitFlag[au8_Channel])
		{

			/*
			 *	change the PWM Channel state from Ready to Running
			 */
			gastr_PWM_Channel[au8_Channel].u8_Pwm_Channel_States = PWM_CHANNEL_RUNNING ;
			gastr_PWM_Channel[au8_Channel].u32_Pwm_Channel_Count = INITIAL ;

			/* we make the pin high here to don't miss the first ISR count */
			au8_Det = DIO_Write_Pin(gastr_PWM_Channel[au8_Channel].u8_Pwm_Pin, HIGH_PIN);

		}
		else
		{
			/* Handling of Start PWM channel before initialize it */
			au8_Det = E_PWM_CHANNEL_NOT_INTIALIZED;
		}
	}
	else
	{
		/* Handling number of channel limit*/
		au8_Det = E_PWM_CHANNELS_NUM ;
	}

	return au8_Det ;
}

/***************************************************************************************/
/* brief!  Stop generate PWM Signal on the defined Channel			                   */
/* param!  u8 (I/P) PWM used Channel 								                   */
/* return! u8 Indication of the execution if it fails or not                           */
/***************************************************************************************/
error_t PWM_Channel_Stop(uint8_t au8_Channel)
{
	/*
	 *	Development Error Tracer
	 */
	error_t au8_Det = ERROR_OK ;

	/*
	*	Checking if the array of events "buffer" is full or not
	*/
	if(PWM_CHANNELS_NUM > au8_Channel )
	{
		/*
		 *	Making sure that the PWM Channel is Initialized
		 */
		if (PWM_CHANNEL_IS_INTIALIZED == gu8_PWM_Channel_InitFlag[au8_Channel])
		{

			/*
			 *	change the PWM Channel state from Running to Ready
			 */
			gastr_PWM_Channel[au8_Channel].u8_Pwm_Channel_States = PWM_CHANNEL_READY ;
			gastr_PWM_Channel[au8_Channel].u32_Pwm_Channel_Count = INITIAL ;

			/* pin default value */
			au8_Det = DIO_Write_Pin(gastr_PWM_Channel[au8_Channel].u8_Pwm_Pin, LOW_PIN);

		}
		else
		{
			/* Handling of Start PWM channel before initialize it */
			au8_Det = E_PWM_CHANNEL_NOT_INTIALIZED;
		}
	}
	else
	{
		/* Handling number of channel limit*/
		au8_Det = E_PWM_CHANNELS_NUM ;
	}

	return au8_Det ;
}
