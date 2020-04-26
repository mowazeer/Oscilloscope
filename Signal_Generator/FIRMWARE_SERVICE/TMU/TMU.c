/*
 * TMU.c
 *
 *  Created on: Dec 31, 2019
 *      Author: MO._.Hamdy "Wazeer"
 */


#include "TMU.h"
#include "TMU_PbCfg.h"
#include "Interrupt.h"
#include "DIO_Interface.h"

/*
*	Declaring the structure that will hold the information about certain event
*/
typedef struct
{
	uint32_t u32_TMU_Resolution ;
	uint8_t  u8_Periodicity ;
	uint8_t  u8_Ready ;
	uint8_t  u8_TaskTerminate ;
	u8_pfunc_t u8pfunc_Event ;
}str_TmuEvent_t;

/*
*	Static variable that tells if the TMU module is initialized or not
*/
static uint8_t gu8_TMU_InitFlag = E_TMU_NOT_INTIALIZED ;

/*
 *	Static variables that hold the limits for the resolution
 */
static uint32_t gu32_MinResolution = NULL ;
static uint32_t gu32_MaxResolution = NULL ;

/*
 *	Static variable that will hold the ISR count
 */
static uint8_t gu8_ISR_Count = NULL ;

/*
 *	static variable that will hold the number of ticks needed to achieve the desired resolution
 */
/* todo why it's global not local? */
static uint16_t gu16_TicksCount = NULL ;

/*
*	static variable that will hold the index of the next free element in the events array
*/
static uint8_t gu8_Free_Index = NULL ;

/*
*	static variable that will hold the updated System ticks number
*/
static volatile uint32_t gu32_OVF_Multiple = NULL ;

/*
*	Allocating space for the events configuration
*/
static str_TmuEvent_t gastr_TMU_Events[NUMBER_OF_EVENTS] ;

/***************************************************************************************/
/* brief!  what ISR handling                                                           */
/* param!  void                            			                                   */
/* return! void                                                                        */
/***************************************************************************************/
static void TMU_TIMER_CallBack(void)
{
	Disable_GlobalInterrupt();

	if (gu32_OVF_Multiple < ISR_RESET_FLAG)
	{
		gu32_OVF_Multiple ++ ;
	}
	else
	{
		gu32_OVF_Multiple = 1U ;
	}

/*TODO we already discussed this in the last meeting !! */
	for (gu8_ISR_Count = NULL ; gu8_ISR_Count < NUMBER_OF_EVENTS ; gu8_ISR_Count++)
	{
		if (NOT_YET == gastr_TMU_Events[gu8_ISR_Count].u8_TaskTerminate)
		{
			if (NULL == gu32_OVF_Multiple % gastr_TMU_Events[gu8_ISR_Count].u32_TMU_Resolution)
			{
				gastr_TMU_Events[gu8_ISR_Count].u8_Ready = READY ;
			}
			else
			{
				/*
				 * Do nothing
				 */
			}
		}
		else
		{
			/*
			 * Do nothing The event is not ready
			 */
		}
	}
	Enable_GlobalInterrupt();
}

/***************************************************************************************/
/* brief!  TMU Initialization                                                          */
/* param!  (I/P) desired resolution in microseconds                                    */
/* return! u8 Indication of the execution if it fails or not                           */
/***************************************************************************************/
error_t TMU_Init(uint32_t au32_Resolution)
{
	/*
	 *	Development Error Tracer
	 */
	error_t u8_Det = ERROR_OK ;

	/* A variable that will hold the time per tick for the chosen timer */
	uint32_t au32_TickTime = NULL ;

	/*
	*	Calculating the minimum and maximum resolution for the chosen timer configuration
	*/
	gu32_MinResolution = ( (PRESCALE_VALUE) / FREQ_OVER_MICRO ) ;//todo TMU_Config.u8_PSC

	if (TIMER0 == TMU_Config.u8_Channel)
	{
		gu32_MaxResolution = gu32_MinResolution * TIMER0_MAX_VALUE ;

	}
	else if(TIMER1 == TMU_Config.u8_Channel)
	{
		gu32_MaxResolution = gu32_MinResolution * TIMER1_MAX_VALUE ;
	}
	else if(TIMER2 == TMU_Config.u8_Channel)
	{
		gu32_MaxResolution = gu32_MinResolution * TIMER2_MAX_VALUE ;
	}
	else
	{
		/* Handling of entering wrong timer channel is already done in Timer_Init function in Timer.c */
		u8_Det = E_CHANNEL;
	}

	/*
	*	Checking if the passed resolution is in the allowed range for the resolution
	*/

	if ((au32_Resolution >= gu32_MinResolution) && (au32_Resolution <= gu32_MaxResolution) && (ERROR_OK == u8_Det))
	{
		/*
		*	Initializing the timer with the configuration defined in TMU_cfg.c
		*/
		Timer_Init(&TMU_Config);

		Timer_Get_Tick_Time(TMU_Config.u8_Channel , &au32_TickTime) ; /* Now au32_TickTime holds the value of tick time in nano seconds*/

		//au32_TickTime /= RESOLUTION_IN_MICRO ; /* so we divide it by 1000 to get it in micro sec. */

		gu16_TicksCount = (au32_Resolution * RESOLUTION_IN_MICRO )/ au32_TickTime ;
	}
	else
	{
		/* Handling of entering wrong resolution */
		u8_Det = E_RESOLUTION ;
	}

	if (ERROR_OK == u8_Det)
	{
		gu8_TMU_InitFlag = E_TMU_INTIALIZED ;
		TIMER_SetCallBack(TMU_TIMER_CallBack, TMU_Config.u8_Channel);
		Timer_Start(TMU_Config.u8_Channel , gu16_TicksCount);
	}
	else
	{
			/* Do nothing */
	}

	return u8_Det ;
}

/***************************************************************************************/
/* brief!  TMU Deinitialization                                                        */
/* param!  void                                                                        */
/* return! u8 Indication of the execution if it fails or not                           */
/***************************************************************************************/
error_t TMU_Deinit(void)
{
	/*
	 *	Development Error Tracer
	 */
	error_t u8_Det = ERROR_OK ;

	/*
	*	Making sure that the TMU is Initialized
	*/
	if (E_TMU_INTIALIZED == gu8_TMU_InitFlag)
	{
		u8_Det = Timer_Stop(TMU_Config.u8_Channel);
		gu8_TMU_InitFlag = E_TMU_NOT_INTIALIZED;
	}
	else
	{
		/* Handling of Deinitialize TMU module before initialize it */
		u8_Det = E_TMU_NOT_INTIALIZED;
	}

	return u8_Det ;
}

/***************************************************************************************/
/* brief!  Adds a certain function with a certain interval as an event                 */
/* param!  (I/P) pointer to the function that is desired to be executed                */
/* param!  u32 (I/P) delay time before executing the desired function                  */
/* param!  u8 (I/P) user wants to execute this function periodically or one shot       */
/* return! u8 Indication of the execution if it fails or not                           */
/***************************************************************************************/
error_t TMU_Start(u8_pfunc_t pfun_Timer_App, uint32_t au32_Resolution , uint8_t au8_Periodicity )
{
	/*
	 *	Development Error Tracer
	 */
	error_t u8_Det = ERROR_OK ;

	/*
	*	Making sure that the TMU is Initialized
	*/
	if (E_TMU_INTIALIZED == gu8_TMU_InitFlag)
	{
		/*
		*	Making sure that the passed pointer is not a null one
		*/
		if (NULL != pfun_Timer_App )
		{
			if ((au32_Resolution >= gu32_MinResolution) && (au32_Resolution <= gu32_MaxResolution))//why? todo
			{
				if ((PERIODIC == au8_Periodicity) || (ONE_SHOT == au8_Periodicity))
				{
					/*
					*	Checking if the array o events "buffer" is full or not
					*/
					if(gu8_Free_Index < NUMBER_OF_EVENTS)
					{
						/*
						 *	Passing the event information to the events array
						 */
						gastr_TMU_Events[gu8_Free_Index].u32_TMU_Resolution = au32_Resolution ;
						gastr_TMU_Events[gu8_Free_Index].u8_Periodicity = au8_Periodicity ;
						gastr_TMU_Events[gu8_Free_Index].u8_Ready = NOT_READY ;
						gastr_TMU_Events[gu8_Free_Index].u8_TaskTerminate = NOT_YET ;
						gastr_TMU_Events[gu8_Free_Index].u8pfunc_Event = pfun_Timer_App ;

						gu8_Free_Index ++ ; /* Increment the index to the next free element in the events array */
					}
					else
					{
						/* Handling number of events limit*/
						u8_Det = E_NUMBER_OF_EVENTS ;
					}
				}
				else
				{
					/* Handling of entering wrong periodicity */
					u8_Det = E_PERIODICITY ;
				}
			}
			else
			{
				/* Entering delay doesn't match the defined limits */
				u8_Det = E_RESOLUTION ;
			}
		}
		else
		{
			/* Handling of entering null pointer*/
			u8_Det = E_NULL_PTR ;
		}
	}
	else
	{
		/* Handling of Start TMU module before initialize it */
		u8_Det = E_TMU_NOT_INTIALIZED;
	}
	return u8_Det ;
}

/***************************************************************************************/
/* brief!  Stops a certain event from being executed                                   */
/* param!  (I/P) pointer to function that is desired to be stopped                     */
/* return! u8 Indication of the execution if it fails or not                           */
/***************************************************************************************/
error_t TMU_Stop(u8_pfunc_t pfun_Timer_App)
{
	/*
	 *	Development Error Tracer
	 */
	error_t u8_Det = ERROR_OK ;
	uint8_t au8_Count = NULL ;

	/*
	*	Making sure that the TMU is Initialized
	*/
	if (E_TMU_INTIALIZED == gu8_TMU_InitFlag)
	{
		/*
		*	Making sure that the passed pointer is not a null one
		*/
		if ( NULL != pfun_Timer_App )
		{
			for (au8_Count = NULL ; au8_Count < NUMBER_OF_EVENTS ; au8_Count ++)
			{
				if (pfun_Timer_App == gastr_TMU_Events[au8_Count].u8pfunc_Event)
				{
					gastr_TMU_Events[au8_Count].u8_TaskTerminate = OK ;
				}
				else if((pfun_Timer_App != gastr_TMU_Events[au8_Count].u8pfunc_Event)&&(au8_Count == NUMBER_OF_EVENTS -1U))
				{
					/* Handling Wrong events */
					u8_Det = E_EVENT ;
				}
				else
				{
					/*
					 * Do nothing
					 */
				}
			}
		}
		else
		{
			/* Handling of passing null pointer */
			u8_Det = E_NULL_PTR ;
		}
	}
	else
	{
		/* Handling of Stop TMU module before initialize it */
		u8_Det = E_TMU_NOT_INTIALIZED;
	}

	return u8_Det ;
}

/***************************************************************************************/
/* brief!  Restart a certain event after it has been stopped                           */
/* param!  (I/P) pointer to function that is desired to be restart                     */
/* return! u8 Indication of the execution if it fails or not                           */
/***************************************************************************************/
error_t TMU_Restart(u8_pfunc_t pfun_Timer_App)
{
	/*
	 *	Development Error Tracer
	 */
	error_t u8_Det = ERROR_OK ;
	uint8_t au8_Count = NULL ;

	/*
	*	Making sure that the TMU is Initialized
	*/
	if (E_TMU_INTIALIZED == gu8_TMU_InitFlag)
	{
		/*
		*	Making sure that the passed pointer is not a null one
		*/
		if (NULL != pfun_Timer_App)
		{
			for (au8_Count = NULL ; au8_Count < NUMBER_OF_EVENTS ; au8_Count ++)
			{
				if (pfun_Timer_App == gastr_TMU_Events[au8_Count].u8pfunc_Event)
				{
					gastr_TMU_Events[au8_Count].u8_TaskTerminate = NOT_YET ;
				}
				else if((pfun_Timer_App != gastr_TMU_Events[au8_Count].u8pfunc_Event)&&(au8_Count == NUMBER_OF_EVENTS -1U))
				{
					/* Handling Wrong events */
					u8_Det = E_EVENT ;
				}
				else
				{
					/*
					 * Do nothing
					 */
				}
			}
		}
		else
		{
			/* Handling of passing null pointer */
			u8_Det = E_NULL_PTR ;
		}
	}
	else
	{
		/* Handling of Stop TMU module before initialize it */
		u8_Det = E_TMU_NOT_INTIALIZED;
	}

	return u8_Det ;
}

/***************************************************************************************/
/* brief!  TMU Manager                                                                 */
/* param!  void                                                                        */
/* return! u8 Indication of the execution if it fails or not                           */
/***************************************************************************************/
error_t TMU_Dispatcher(void)
{
	/*
	 *	Development Error Tracer
	 */
	error_t u8_Det = ERROR_OK ;
	uint8_t au8_Count = NULL ;

	/*
	*	Execute Ready Events
	*/
	/*TODO please follow the last session to modifie your dispatcher */
	for (au8_Count = NULL ; au8_Count < NUMBER_OF_EVENTS ; au8_Count++)
	{
		if (READY == gastr_TMU_Events[au8_Count].u8_Ready )
		{
			gastr_TMU_Events[au8_Count].u8pfunc_Event();
			gastr_TMU_Events[au8_Count].u8_Ready = NOT_READY ;

			if (ONE_SHOT == gastr_TMU_Events[au8_Count].u8_Periodicity)
			{
				TMU_Stop(gastr_TMU_Events[au8_Count].u8pfunc_Event);
			}
			/*
			else if ((PERIODIC > gastr_TMU_Events[au8_Count].u8_Periodicity)&&(ONE_SHOT < gastr_TMU_Events[au8_Count].u8_Periodicity))
			{
				(gastr_TMU_Events[au8_Count].u8_Periodicity) -=1;
			}
			*/
			else
			{
				/*
				 * Do nothing
				 */
			}
		}
		else
		{
			/*
			 * Do nothing If Event not Ready
			 */
		}
	}
	return u8_Det ;
}
