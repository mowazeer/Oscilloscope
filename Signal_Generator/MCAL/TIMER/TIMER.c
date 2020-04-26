/*
 * TIMER.c
 *
 *  Created on: Dec 31, 2019
 *      Author: MO._.Hamdy "Wazeer"
 */


#include "TIMER.h"
#include "TIMER_Private.h"
#include "Macros.h"
#include "DIO_Interface.h"
#include "Interrupt.h"

/* global variable that hold the number of over flow count */
uint32_t volatile gu32_T0_OVF_Count = INITIAL;

/*
 * pointer to function for call back function
 */
static pfunc_t pfun_Timer_CallBack[CHANNELS_NUMBER];

/*
 *	Static array store prescaler configuration.
 */
static uint8_t su8_Timer_PSC[CHANNELS_NUMBER] = {NULL} ;

/*
 *	Static array store timers mode configuration "Polling or interrupt"
 */
static uint8_t su8_Timer_InterruptMode[CHANNELS_NUMBER] = {NULL} ;

/*
 *	Static array store tick time values in nano seconds
 */
static uint32_t su32_Tick_Time[CHANNELS_NUMBER] = {NULL} ;


/***************************************************************************************/
/* brief!  A function that takes pointer to struct to configure the desired timer      */
/* param!  (I/P) u8 Timer channel "The desired timer to be started"                    */
/* return! u8 Indication of the execution if it fails or not                           */
/***************************************************************************************/
error_t Timer_Init(Timer_cfg_s *pstr_Timer_cfg)
{
	/*
	 *	Development Error Tracer
	 */
	error_t au8_DET = ERROR_OK ;

	if (NULL != pstr_Timer_cfg ) /* Checking that the passed pointer is not a NULL one */
	{
		if (TIMER0 == pstr_Timer_cfg -> u8_Channel )
		{
			/*
		    *	Calculating the time per tick and passing it to a static variable
		    */
		    if (T0_PSC_0 == (pstr_Timer_cfg -> u8_PSC))
		    {
		    	su32_Tick_Time[TIMER0] = (PRESCALE_0 * 1000U) / FREQ_OVER_MICRO ; /*(= 125 nano) Multiplication by 1000 is to make the time in nano seconds instead of micro*/
		    }
		    else if(T0_PSC_8 == (pstr_Timer_cfg -> u8_PSC))
		    {
		    	su32_Tick_Time[TIMER0] = (PRESCALE_8 * 1000U) / FREQ_OVER_MICRO ; /* Multiplication by 1000 is to make the time in nano seconds instead of micro*/
		    }
		    else if(T0_PSC_64 == (pstr_Timer_cfg -> u8_PSC))
		    {
		    	su32_Tick_Time[TIMER0] = (PRESCALE_64 * 1000U) / FREQ_OVER_MICRO ; /* Multiplication by 1000 is to make the time in nano seconds instead of micro*/
		    }
		    else if(T0_PSC_256 == (pstr_Timer_cfg -> u8_PSC))
		    {
		    	su32_Tick_Time[TIMER0] = (PRESCALE_256 * 1000U) / FREQ_OVER_MICRO ; /* Multiplication by 1000 is to make the time in nano seconds instead of micro*/
		    }
		    else if(T0_PSC_1024 == (pstr_Timer_cfg -> u8_PSC))
		    {
		    	su32_Tick_Time[TIMER0] = (PRESCALE_1024 * 1000U) / FREQ_OVER_MICRO ; /* Multiplication by 1000 is to make the time in nano seconds instead of micro*/
		    }
		    else
		    {
		    	/* Handling of wrong Prescale */
		    	au8_DET = E_PSC ;
		    }
			if(E_PSC != au8_DET)
			{
				/*
				 *	Passing the Timer Prescale to its static variable
				 */
				su8_Timer_PSC[TIMER0] = (pstr_Timer_cfg -> u8_PSC) ;
			}

			/*
			*	Checking the desired Mode if it's polling or interrupt
			*/
			if (INTERRUPT == pstr_Timer_cfg -> u8_Interrupt_Mode )
			{
				Enable_GlobalInterrupt() ;  /*Enable global interrupt*/
				/*
				*	Passing the Timer mode to its static variable
				*/
				su8_Timer_InterruptMode[TIMER0] = INTERRUPT ;
				SET_BIT(TIMSK, OCIE0); /*Enable the interrupt request for timer_0 Output Compare Match*/
			}
			else if(POLLING == pstr_Timer_cfg -> u8_Interrupt_Mode )
			{
				CLEAR_BIT(TIMSK, OCIE0); /*Disable the interrupt request for timer_0 Output Compare Match*/
				/*
				*	Passing the Timer mode to its static variable
				*/
				su8_Timer_InterruptMode[TIMER0] = POLLING ;
			}
			else
			{
				/* Handling of entering wrong Mode */
				au8_DET = E_INTERRUPT_MODE ;
			}
			/*
			*	Activating timer_0 CTC mode
			*/
			SET_BIT(TCCR0, WGM01);
			CLEAR_BIT(TCCR0, WGM00);
		}
		else if (TIMER1 == pstr_Timer_cfg -> u8_Channel)
		{
			/*
		    *	Calculating the time per tick and passing it to a static variable
		    */

		    if (T1_PSC_0 == (pstr_Timer_cfg -> u8_PSC))
		    {
		    	su32_Tick_Time[TIMER1] = (PRESCALE_0 * 1000U) / FREQ_OVER_MICRO ; /* Multiplication by 1000 is to make the time in nano seconds instead of micro*/
		    }
		    else if(T1_PSC_8 == (pstr_Timer_cfg -> u8_PSC))
		    {
		    	su32_Tick_Time[TIMER1] = (PRESCALE_8 * 1000U) / FREQ_OVER_MICRO ; /* Multiplication by 1000 is to make the time in nano seconds instead of micro*/
		    }
		    else if(T1_PSC_64 == (pstr_Timer_cfg -> u8_PSC))
		    {
		    	su32_Tick_Time[TIMER1] = (PRESCALE_64 * 1000U) / FREQ_OVER_MICRO ; /* Multiplication by 1000 is to make the time in nano seconds instead of micro*/
		    }
		    else if(T1_PSC_256 == (pstr_Timer_cfg -> u8_PSC))
		    {
		    	su32_Tick_Time[TIMER1] = (PRESCALE_256 * 1000U) / FREQ_OVER_MICRO ; /* Multiplication by 1000 is to make the time in nano seconds instead of micro*/
		    }
		    else if(T1_PSC_1024 == (pstr_Timer_cfg -> u8_PSC))
		    {
		    	su32_Tick_Time[TIMER1] = (PRESCALE_1024 * 1000U) / FREQ_OVER_MICRO ; /* Multiplication by 1000 is to make the time in nano seconds instead of micro*/
		    }
		    else
		    {
		    	/*Handling of wrong Prescale*/
		    	au8_DET = E_PSC ;
		    }
			if(E_PSC != au8_DET)
			{
				/*
				 *	Passing the Timer Prescale to its static variable
				 */
				su8_Timer_PSC[TIMER1] = (pstr_Timer_cfg -> u8_PSC) ;
			}

			/*
			*	Checking the desired Mode if it's polling or interrupt
			*/
			if (INTERRUPT == pstr_Timer_cfg -> u8_Interrupt_Mode)
			{
				OCR1A = TIMER1_MAX_VALUE ;

				Enable_GlobalInterrupt() ;  /*Enable global interrupt*/

				/*
				*	Passing the Timer mode to its static variable
				*/
				su8_Timer_InterruptMode[TIMER1] = INTERRUPT ;
				SET_BIT(TIMSK, OCIE1A); /*Enable the interrupt request for timer_1 Output Compare A Match*/
			}
			else if(POLLING == pstr_Timer_cfg -> u8_Interrupt_Mode)
			{
				CLEAR_BIT(TIMSK, OCIE1A); /*Disable the interrupt request for timer_1 Output Compare A Match*/

				/*
				*	Passing the Timer mode to its static variable
				*/
				su8_Timer_InterruptMode[TIMER1] = POLLING ;
			}
			else
			{
				/*Handling of entering wrong Mode*/
				au8_DET = E_INTERRUPT_MODE ;
			}

			/*
			*	Activating timer_1 CTC mode "Mode 4"
			*/
			SET_BIT(TCCR1B, WGM12);
		}
		else if(TIMER2 == pstr_Timer_cfg -> u8_Channel)
		{
			/*
		    *	Calculating the time per tick and passing it to a static variable
		    */
		    if (T2_PSC_0 == (pstr_Timer_cfg -> u8_PSC))
		    {
		    	su32_Tick_Time[TIMER2] = (PRESCALE_0 * 1000U) / FREQ_OVER_MICRO ; /* Multiplication by 1000 is to make the time in nano seconds instead of micro*/
		    }
		    else if(T2_PSC_8 == (pstr_Timer_cfg -> u8_PSC))
		    {
		    	su32_Tick_Time[TIMER2] = (PRESCALE_8 * 1000U) / FREQ_OVER_MICRO ; /* Multiplication by 1000 is to make the time in nano seconds instead of micro*/
		    }
		    else if(T2_PSC_32 == (pstr_Timer_cfg -> u8_PSC))
		    {
		    	su32_Tick_Time[TIMER2] = (PRESCALE_32 * 1000U) / FREQ_OVER_MICRO ; /* Multiplication by 1000 is to make the time in nano seconds instead of micro*/
		    }
		    else if(T2_PSC_64 == (pstr_Timer_cfg -> u8_PSC))
		    {
		    	su32_Tick_Time[TIMER2] = (PRESCALE_64 * 1000U) / FREQ_OVER_MICRO ; /* Multiplication by 1000 is to make the time in nano seconds instead of micro*/
		    }
		    else if(T2_PSC_128 == (pstr_Timer_cfg -> u8_PSC))
		    {
		    	su32_Tick_Time[TIMER2] = (PRESCALE_128 * 1000U) / FREQ_OVER_MICRO ; /* Multiplication by 1000 is to make the time in nano seconds instead of micro*/
		    }
		    else if(T2_PSC_256 == (pstr_Timer_cfg -> u8_PSC))
		    {
		    	su32_Tick_Time[TIMER2] = (PRESCALE_256 * 1000U) / FREQ_OVER_MICRO ; /* Multiplication by 1000 is to make the time in nano seconds instead of micro*/
		    }
		    else if(T2_PSC_1024 == (pstr_Timer_cfg -> u8_PSC))
		    {
		    	su32_Tick_Time[TIMER2] = (PRESCALE_1024 * 1000U) / FREQ_OVER_MICRO ; /* Multiplication by 1000 is to make the time in nano seconds instead of micro*/
		    }
		    else
		    {
		    	/*Handling of wrong Prescale*/
		    	au8_DET = E_PSC ;
		    }
			if(E_PSC != au8_DET)
			{
				/*
				 *	Passing the Timer Prescale to its static variable
				 */
				su8_Timer_PSC[TIMER2] = (pstr_Timer_cfg -> u8_PSC) ;
			}

			/*
			*	Checking the desired Mode if it's polling or interrupt
			*/
			if (INTERRUPT == pstr_Timer_cfg -> u8_Interrupt_Mode)
			{
				Enable_GlobalInterrupt() ;  /*Enable global interrupt*/

				/*
				*	Passing the Timer mode to its static variable
				*/
				su8_Timer_InterruptMode[TIMER2] = INTERRUPT ;
				SET_BIT(TIMSK, OCIE2); /*Enable the interrupt request for timer_2 Output Compare Match*/
			}
			else if(POLLING == pstr_Timer_cfg -> u8_Interrupt_Mode)
			{
				CLEAR_BIT(TIMSK, OCIE2); /*Disable the interrupt request for timer_2 Output Compare Match*/

				/*
				*	Passing the Timer mode to its static variable
				*/
				su8_Timer_InterruptMode[TIMER2] = POLLING ;
			}
			else
			{
				/*Handling of entering wrong Mode*/
				au8_DET = E_INTERRUPT_MODE ;
			}
			/*
			*	Activating timer_2 CTC mode
			*/
			SET_BIT(TCCR2, WGM21);
			CLEAR_BIT(TCCR2, WGM20);
		}
		else
		{
			/* Handling of entering wrong channel */
			au8_DET = E_CHANNEL ;
		}
	}
	else
	{
		/*Handling of using null pointer*/
		au8_DET = E_NULL_PTR ;
	}

	return au8_DET ;
}

/***************************************************************************************/
/* brief!  Function that start a chosen timer                                          */
/* param!  (I/P) u8 Timer channel "The desired timer to be started"                    */
/* param!  (I/P) u8 The desired ticks to be counted                                    */
/* return! u8 Indication of the execution if it fails or not                           */
/***************************************************************************************/
error_t Timer_Start(uint8_t u8_Channel, uint16_t u16_Ticks)
{
	/*
	 *	Development Error Tracer
	 */
	error_t au8_DET = ERROR_OK ;

	if (TIMER0 == u8_Channel)
	{
		if (u16_Ticks <= TIMER0_MAX_VALUE)
		{
			/*
			 *	Restarting the desired timer with the predefined prescale
			 */
			CLEAR_MASK(TCCR0, T0_PSC_MASK);
			SET_MASK(TCCR0, su8_Timer_PSC[TIMER0]);

			/*
			 *	Load the desired number of ticks to TCNT register
			 */
			OCR0 = (uint8_t) u16_Ticks ;

		}
		else
		{
			/*Handling of entering tick number more than the maximum allowed*/
			au8_DET = E_TICKS ;
		}
	}
	else if(TIMER1 == u8_Channel)
	{
		if (u16_Ticks <= TIMER1_MAX_VALUE)
		{
			TCNT1 = NULL ;

			/*
			 *	Restarting the desired timer with the predefined prescale
			 */
			CLEAR_MASK(TCCR1B, T1_PSC_MASK);
			SET_MASK(TCCR1B, su8_Timer_PSC[TIMER1]);

			/*
			 *	Load the desired number of ticks to TCNT register
			 */
			OCR1A = u16_Ticks ;
		}
		else
		{
			/*Handling of entering tick number more than the maximum allowed*/
			au8_DET = E_TICKS ;
		}
	}
	else if(TIMER2 == u8_Channel)
	{
		if (u16_Ticks <= TIMER2_MAX_VALUE)
		{
			/*
			*	Restarting the desired timer with the predefined prescale
			*/
			CLEAR_MASK(TCCR2, T2_PSC_MASK);
			SET_MASK(TCCR2, su8_Timer_PSC[TIMER2]);

			/*
			 *	Load the desired number of ticks to TCNT register
			 */
			OCR2 = (uint8_t) u16_Ticks ;
		}
		else
		{
			/*Handling of entering tick number more than the maximum allowed*/
			au8_DET = E_TICKS ;
		}
	}
	else
	{
		/*Handling of entering the wrong channel*/
		au8_DET = E_CHANNEL ;
	}

	/* Return the Development Error Tracer if it's ok or not */
	return au8_DET ;
}

/***************************************************************************************/
/* brief!  Function that stop a chosen timer                                           */
/* param!  (I/P) u8 Timer channel                                                      */
/* return! u8 Indication of the execution if it fails or not                           */
/***************************************************************************************/
error_t Timer_Stop(uint8_t u8_Channel)
{
	error_t au8_DET = ERROR_OK ;

	if (TIMER0 == u8_Channel)
	{
		CLEAR_MASK(TCCR0, su8_Timer_PSC[TIMER0]);

		TCNT0 = NULL ;
	}
	else if(TIMER1 == u8_Channel)
	{
		CLEAR_MASK(TCCR1B, su8_Timer_PSC[TIMER1]);

		TCNT1L = NULL ;
		TCNT1H = NULL ;
	}
	else if(TIMER2 == u8_Channel)
	{
		CLEAR_MASK(TCCR2, su8_Timer_PSC[TIMER0]);

		TCNT2 = NULL ;
	}
	else
	{
		/*Handling of entering a wrong channel*/
		au8_DET = E_CHANNEL ;
	}

	/* Return the Development Error Tracer if it's ok or not */
	return au8_DET ;
}

/***************************************************************************************/
/* brief!  Function that reset a chosen timer                                          */
/* param!  (I/P) u8 Timer channel                                                      */
/* return! u8 Indication of the execution if it fails or not                           */
/***************************************************************************************/
error_t Timer_Reset(uint8_t u8_Channel)
{
	/*
	 *	Development Error Tracer
	 */
	error_t au8_DET = ERROR_OK ;

	if (TIMER0 == u8_Channel)
	{
		TCNT0 = NULL ;
	}
	else if(TIMER1 == u8_Channel)
	{
		TCNT1 = NULL ;
		OCR1A = NULL ;
	}
	else if(TIMER2 == u8_Channel)
	{
		TCNT2 = NULL ;
	}
	else
	{
		/*Handling of entering a wrong channel*/
		au8_DET = E_CHANNEL ;
	}
	/* Return the Development Error Tracer if it's ok or not */
	return au8_DET ;
}

/***************************************************************************************/
/* brief!  function that calculates the time per tick, in nano second                  */
/* param!  (I/P) u8 Timer channel                                                      */
/* param!  (O/P) u32* The value of the time per tick                                   */
/* return! u8 Indication of the execution if it fails or not                           */
/***************************************************************************************/
error_t Timer_Get_Tick_Time(uint8_t u8_Channel, uint32_t *pu32_Timer_Time_ns)
{
	error_t au8_DET = ERROR_OK ;

	/* Checking that the passed pointer is not a null one */
	if ( NULL != pu32_Timer_Time_ns )
	{
		if (TIMER0 == u8_Channel)
		{
			*pu32_Timer_Time_ns = su32_Tick_Time[TIMER0] ;
		}
		else if(TIMER1 == u8_Channel)
		{
			*pu32_Timer_Time_ns = su32_Tick_Time[TIMER1] ;
		}
		else if(TIMER2 == u8_Channel)
		{
			*pu32_Timer_Time_ns = su32_Tick_Time[TIMER2] ;
		}
		else
		{
			/*Handling of entering a wrong channel*/
			au8_DET = E_CHANNEL ;
		}
	}
	else
	{
		/*Handling of using null pointer*/
		au8_DET = E_NULL_PTR ;
	}
	/* Return the Development Error Tracer if it's ok or not */
	return au8_DET ;
}

/***************************************************************************************/
/* brief!  TMU Set the function that will execute in the ISR                           */
/* param!  pointer to function that will execute in the ISR                            */
/* param!  u8 (i/p) Timer channel Number                                               */
/* return! u8 Indication of the execution if it fails or not                           */
/***************************************************************************************/
error_t TIMER_SetCallBack(pfunc_t pfun_Timer_App, uint8_t au8_Channel_Num)
{
	/*
	 *	Development Error Tracer
	 */
	error_t u8_Det = ERROR_OK ;

	if (NULL != pfun_Timer_App)
	{
		switch(au8_Channel_Num)
		{
			/* Timer_0 scenario */
			case TIMER0:
				pfun_Timer_CallBack[TIMER0] = pfun_Timer_App;
			break;

			/* Timer_1 scenario */
			case TIMER1:
				pfun_Timer_CallBack[TIMER1] = pfun_Timer_App;
			break;

			/* Timer_2 scenario */
			case TIMER2:
				pfun_Timer_CallBack[TIMER2] = pfun_Timer_App;
			break;

			/* Handling of passing wrong E_INTERRUPT REQUEST */
			default:
				u8_Det = E_CHANNEL ;
			break;
		}
	}
	else
	{
		/* Handling of passing null pointer */
		u8_Det = E_NULL_PTR ;
	}
	return u8_Det;
}

/***************************************************************************************/
/* brief!  Timer_0 Output Compare Match interrupt handling                             */
/* param!  void                                                                        */
/* return! void                                                                        */
/***************************************************************************************/
ISR(TIMER0_COMP_vect)
{
	if (NULL != pfun_Timer_CallBack[TIMER0])
	{
		pfun_Timer_CallBack[TIMER0]();
	}
}

/***************************************************************************************/
/* brief!  Timer_1 Output Compare A Match interrupt handling                           */
/* param!  void                                                                        */
/* return! void                                                                        */
/***************************************************************************************/
ISR(TIMER1_COMPA_vect)
{
	if (NULL != pfun_Timer_CallBack[TIMER1])
	{
		pfun_Timer_CallBack[TIMER1]();
	}
}

/***************************************************************************************/
/* brief!  Timer_2 Output Compare Match interrupt handling                             */
/* param!  void                                                                        */
/* return! void                                                                        */
/***************************************************************************************/
ISR(TIMER2_COMP_vect)
{
	if (NULL != pfun_Timer_CallBack[TIMER2])
	{
		pfun_Timer_CallBack[TIMER2]();
	}
}

/**************************************************************************************************/
/* I use it in soft ICU todo */
void TIMER0_OVF(void)
{
	CLEAR_BIT(TCCR0,7);///////

	CLEAR_BIT(TCCR0,6); // normal mode
	CLEAR_BIT(TCCR0,3);

	CLEAR_BIT(TCCR0,5); //Normal port operation, OC0 disconnected.
	CLEAR_BIT(TCCR0,4);

	CLEAR_BIT(TCCR0,2); //clk I/O (No prescaling)
	CLEAR_BIT(TCCR0,1);
	SET_BIT  (TCCR0,0);

	TCNT0=0;

	SET_BIT(TIMSK,0);

	SET_BIT(SREG,7);

}

ISR(TIMER0_OVF_vect)
{
	//cli();
	gu32_T0_OVF_Count++;
	//sei();
}
