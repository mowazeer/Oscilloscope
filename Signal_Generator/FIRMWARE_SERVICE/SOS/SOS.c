/*
 * SOS.c
 *
 *  Created on: Jan 7, 2020
 *      Author: MO._.Hamdy "Wazeer"
 */


#include "SOS.h"
#include "SOS_PbCfg.h"
#include "Interrupt.h"
#include "DIO_Interface.h"
#include "MCU_Power.h"

/*
*	Declaring the structure that will hold the information about certain event
*/
typedef struct
{
	uint32_t u32_SOS_Ticks_Num ;
	uint8_t  u8_Priority ;
	uint8_t  u8_Periodicity ;
	uint8_t  u8_TaskState ;
	u8_pfunc_t u8pfunc_Task ;
}str_SOSEvent_t;

/*
*	Static variable that tells if the SOS module is initialized or not
*/
static uint8_t gu8_SOS_InitFlag = E_SOS_NOT_INTIALIZED ;

/*
 *	Static variables that hold the limits for the resolution
 */
static uint32_t gu32_MinResolution = NULL ;
static uint32_t gu32_MaxResolution = NULL ;

/*
 *	static variable that will hold the number of ticks needed to achieve the desired resolution
 */
static uint16_t gu16_TicksCount = NULL ;

/*
*	static variable that will hold the index of the next free element in the events array
*/
static uint8_t gu8_Buffer_Index = NULL ;

/*
*	static variable that will hold the updated System ticks number
*/
static volatile uint32_t gu32_SOS_Ticks_Num = NULL ;

/*
*	Allocating space for the events configuration
*/
static str_SOSEvent_t gastr_SOS_Tasks[SOS_BUFFER_SIZE] ;

/***************************************************************************************/
/* brief!  what ISR handling                                                           */
/* param!  void                            			                                   */
/* return! void                                                                        */
/***************************************************************************************/
static void SOS_TIMER_CallBack(void)
{
	Disable_GlobalInterrupt();
	/*
	 *	variable that will hold the ISR count
	 */
	uint8_t gu8_ISR_Count = NULL ;

	switch(gu32_SOS_Ticks_Num)
	{
		case SOS_ISR_RESET_FLAG:
			gu32_SOS_Ticks_Num = SOS_ISR_RESET_VALUE ;
		break;

		default:
			gu32_SOS_Ticks_Num ++ ;
		break;
	}

	/* loop on the tasks buffer to check if any task become ready */
	for (gu8_ISR_Count = NULL ; gu8_ISR_Count < gu8_Buffer_Index ; gu8_ISR_Count++)
	{
		/* make the task ready if it's meet her time */
		switch(gu32_SOS_Ticks_Num % gastr_SOS_Tasks[gu8_ISR_Count].u32_SOS_Ticks_Num)
		{
			case NULL:
				gastr_SOS_Tasks[gu8_ISR_Count].u8_TaskState = READY ;
			break;

			default:
				/* Do nothing */
			break;
		}
	}
	Enable_GlobalInterrupt();
}

/***************************************************************************************/
/* brief!  SOS Initialization                                                          */
/* param!  (I/P) desired resolution in microseconds                                    */
/* return! u8 Indication of the execution if it fails or not                           */
/***************************************************************************************/
error_t SOS_Init(uint32_t au32_TicksNum)
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
	gu32_MinResolution = ( (SOS_PRESCALE) / FREQ_OVER_MICRO ) ;

	if (TIMER0 == SOS_Config.u8_Channel)
	{
		gu32_MaxResolution = gu32_MinResolution * TIMER0_MAX_VALUE ;

	}
	else if(TIMER1 == SOS_Config.u8_Channel)
	{
		gu32_MaxResolution = gu32_MinResolution * TIMER1_MAX_VALUE ;
	}
	else if(TIMER2 == SOS_Config.u8_Channel)
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

	if ((au32_TicksNum >= gu32_MinResolution) && (au32_TicksNum <= gu32_MaxResolution) && (ERROR_OK == u8_Det))
	{
		/*
		*	Initializing the timer with the configuration defined in SOS_cfg.c
		*/
		Timer_Init(&SOS_Config);

		Timer_Get_Tick_Time(SOS_Config.u8_Channel , &au32_TickTime) ; /* Now au32_TickTime holds the value of tick time in nano seconds*/

		au32_TickTime /= SOS_RESOLUTION_IN_MICRO ; /* so we divide it by 1000 to get it in micro sec. */

		gu16_TicksCount = au32_TicksNum / au32_TickTime ;
	}
	else
	{
		/* Handling of entering wrong resolution */
		u8_Det = E_SOS_RESOLUTION ;
	}

	if (ERROR_OK == u8_Det)
	{
		gu8_SOS_InitFlag = E_SOS_INTIALIZED ;
		TIMER_SetCallBack(SOS_TIMER_CallBack, SOS_Config.u8_Channel);
		Timer_Start(SOS_Config.u8_Channel , gu16_TicksCount);
	}
	else
	{
			/* Do nothing */
	}

	return u8_Det ;
}

/***************************************************************************************/
/* brief!  SOS Deinitialization                                                        */
/* param!  void                                                                        */
/* return! u8 Indication of the execution if it fails or not                           */
/***************************************************************************************/
error_t SOS_Deinit(void)
{
	/*
	 *	Development Error Tracer
	 */
	error_t u8_Det = ERROR_OK ;

	/*
	*	Making sure that the SOS is Initialized
	*/
	if (E_SOS_INTIALIZED == gu8_SOS_InitFlag)
	{
		u8_Det = Timer_Stop(SOS_Config.u8_Channel);
		gu8_SOS_InitFlag = E_SOS_NOT_INTIALIZED;
	}
	else
	{
		/* Handling of Deinitialize SOS module before initialize it */
		u8_Det = E_SOS_NOT_INTIALIZED;
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
error_t SOS_CreatTask(u8_pfunc_t pfun_SosApp, uint32_t au32_TicksNum , uint8_t u8_Priority, uint8_t au8_Periodicity )
{
	/*
	 *	Development Error Tracer
	 */
	error_t u8_Det = ERROR_OK ;

	/*
	*	Making sure that the SOS is Initialized
	*/
	if (E_SOS_INTIALIZED == gu8_SOS_InitFlag)
	{
		/*
		*	Making sure that the passed pointer is not a null one
		*/
		if (NULL != pfun_SosApp )
		{
			if ((au32_TicksNum >= gu32_MinResolution) && (au32_TicksNum <= gu32_MaxResolution))
			{
				if ((PERIODIC >= au8_Periodicity) && (ONE_SHOT <= au8_Periodicity))
				{
					/*
					*	Checking if the array o events "buffer" is full or not
					*/
					if(gu8_Buffer_Index < SOS_BUFFER_SIZE)
					{
						/*
						 *	Passing the event information to the events array
						 */
						gastr_SOS_Tasks[gu8_Buffer_Index].u32_SOS_Ticks_Num = au32_TicksNum ;
						gastr_SOS_Tasks[gu8_Buffer_Index].u8_Priority       = u8_Priority ;
						gastr_SOS_Tasks[gu8_Buffer_Index].u8_Periodicity    = au8_Periodicity ;
						gastr_SOS_Tasks[gu8_Buffer_Index].u8_TaskState      = WAITING ;
						gastr_SOS_Tasks[gu8_Buffer_Index].u8pfunc_Task      = pfun_SosApp ;

						gu8_Buffer_Index ++ ; /* Increment the index to the next free element in the events array */
					}
					else
					{
						/* Handling number of events limit*/
						u8_Det = E_SOS_BUFFER_SIZE ;
					}
				}
				else
				{
					/* Handling of entering wrong periodicity */
					u8_Det = E_SOS_PERIODICITY ;
				}
			}
			else
			{
				/* Entering delay doesn't match the defined limits */
				u8_Det = E_SOS_RESOLUTION ;
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
		/* Handling of Start SOS module before initialize it */
		u8_Det = E_SOS_NOT_INTIALIZED;
	}
	return u8_Det ;
}

/***************************************************************************************/
/* brief!  Delete a certain event from being executed                                  */
/* param!  (I/P) pointer to function that is desired to be stopped                     */
/* return! u8 Indication of the execution if it fails or not                           */
/***************************************************************************************/
error_t SOS_DeleteTask(u8_pfunc_t pfun_SosApp)
{
	/*
	 *	Development Error Tracer
	 */
	error_t u8_Det = ERROR_OK ;
	uint8_t au8_Count = NULL ;

	/*
	*	Making sure that the SOS is Initialized
	*/
	if (E_SOS_INTIALIZED == gu8_SOS_InitFlag)
	{
		/*
		*	Making sure that the passed pointer is not a null one
		*/
		if ( NULL != pfun_SosApp )
		{
			for (au8_Count = NULL ; au8_Count < gu8_Buffer_Index ; au8_Count ++)
			{
				if (pfun_SosApp == gastr_SOS_Tasks[au8_Count].u8pfunc_Task)
				{
					gu8_Buffer_Index --;
					gastr_SOS_Tasks[au8_Count].u8pfunc_Task      = gastr_SOS_Tasks[gu8_Buffer_Index].u8pfunc_Task ;
					gastr_SOS_Tasks[au8_Count].u32_SOS_Ticks_Num = gastr_SOS_Tasks[gu8_Buffer_Index].u32_SOS_Ticks_Num ;
					gastr_SOS_Tasks[au8_Count].u8_Periodicity 	 = gastr_SOS_Tasks[gu8_Buffer_Index].u8_Periodicity ;
					gastr_SOS_Tasks[au8_Count].u8_Priority       = gastr_SOS_Tasks[gu8_Buffer_Index].u8_Priority ;
					gastr_SOS_Tasks[au8_Count].u8_TaskState      = gastr_SOS_Tasks[gu8_Buffer_Index].u8_TaskState ;

					gastr_SOS_Tasks[gu8_Buffer_Index].u8pfunc_Task      = NULL ;
					gastr_SOS_Tasks[gu8_Buffer_Index].u32_SOS_Ticks_Num = NULL;
					gastr_SOS_Tasks[gu8_Buffer_Index].u8_Periodicity    = NULL;
					gastr_SOS_Tasks[gu8_Buffer_Index].u8_Priority       = NULL;
					gastr_SOS_Tasks[gu8_Buffer_Index].u8_TaskState      = NOT_READY;

				}
				else if((pfun_SosApp != gastr_SOS_Tasks[au8_Count].u8pfunc_Task)&&(au8_Count == gu8_Buffer_Index -1U))
				{
					/* Handling Wrong events */
					u8_Det = E_SOS_BUFFER_SIZE ;
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
		/* Handling of Stop SOS module before initialize it */
		u8_Det = E_SOS_NOT_INTIALIZED;
	}

	return u8_Det ;
}

/***************************************************************************************/
/* brief!  SOS Manager                                                                 */
/* param!  void                                                                        */
/* return! u8 Indication of the execution if it fails or not                           */
/***************************************************************************************/
error_t SOS_Run(void)
{
	/*
	 *	Development Error Tracer
	 */
	error_t u8_Det = ERROR_OK ;

	uint8_t au8_Count = NULL ;
	uint8_t au8_Primitive_ReadyTask_index = NULL ;
	uint8_t au8_Is_FirstReadyTask_Flag    = FIRST_READYTASK ;

	/*
	*	Execute Ready Tasks
	*/
	while (1)
	{
		for (au8_Count = NULL ; au8_Count < gu8_Buffer_Index ; au8_Count++)
		{
			switch( gastr_SOS_Tasks[au8_Count].u8_TaskState )
			{
				/* the task is ready */
				case READY:
					switch( au8_Is_FirstReadyTask_Flag )
					{
						case FIRST_READYTASK:

							au8_Primitive_ReadyTask_index = au8_Count ;
							au8_Is_FirstReadyTask_Flag = SECOND_READYTASK ;
						break;

						default:
							/* choosing the highest priority task to be the Primitive task that will be determined */
							if (gastr_SOS_Tasks[au8_Count].u8_Priority > gastr_SOS_Tasks[au8_Primitive_ReadyTask_index].u8_Priority)
							{
								au8_Primitive_ReadyTask_index = au8_Count ;
							}
							else
							{
								/* Do nothing */
							}
						break;
					}
				break;

				case NOT_READY:
					/* Do nothing */
				break;

				case WAITING:
					/* Do nothing */
				break;

				case RUNNING:
					/* Do nothing */
				break;

				default:
					/* Do nothing */
				break;
			}
		}

		/* Task action */
		switch( gastr_SOS_Tasks[au8_Primitive_ReadyTask_index].u8_TaskState )
		{
			/* Run the ready Task */
			case READY:

				gastr_SOS_Tasks[au8_Primitive_ReadyTask_index].u8pfunc_Task();
				gastr_SOS_Tasks[au8_Primitive_ReadyTask_index].u8_TaskState = RUNNING ;

				/* task periodicity decision */
				switch( gastr_SOS_Tasks[au8_Primitive_ReadyTask_index].u8_Periodicity )
				{
					case ONE_SHOT:

						u8_Det = SOS_DeleteTask(gastr_SOS_Tasks[au8_Primitive_ReadyTask_index].u8pfunc_Task);
					break;

					case PERIODIC:

						gastr_SOS_Tasks[au8_Primitive_ReadyTask_index].u8_TaskState = WAITING ;
					break;

					default:

						//gastr_SOS_Tasks[au8_Primitive_ReadyTask_index].u8_Periodicity --;
						//gastr_SOS_Tasks[au8_Primitive_ReadyTask_index].u8_TaskState = WAITING ;
					break;
				}
			break;

			case NOT_READY:
				/* Do nothing */
			break;

			case WAITING:
				/* Do nothing */
			break;

			case RUNNING:
				/* Do nothing */
			break;

			default:
				/* Do nothing */
			break;
		}

		au8_Is_FirstReadyTask_Flag    = FIRST_READYTASK ;
		au8_Primitive_ReadyTask_index = NULL;

		if(ERROR_OK != u8_Det)
		{
			return u8_Det ;
		}
		//CPU_Sleep();
	}
}
