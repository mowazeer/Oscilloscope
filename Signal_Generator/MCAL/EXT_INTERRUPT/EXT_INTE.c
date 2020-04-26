/*
 * EXT_INTE.c
 *
 *  Created on: Jan 19, 2020
 *      Author: MO._.Hamdy
 */


#include "EXT_INTE.h"
#include "EXT_INTE_Private.h"
#include "Interrupt.h"
#include "Macros.h"
#include "DIO_Interface.h"

/*
 * pointer to function for call back function
 */
static pfunc_t pfun_Int_CallBack[INTE_INIT_BUFFER];

/*
*	Static variable that tells if the INTE module is initialized or not
*/
static uint8_t gau8_INTE_InitFlag[INTE_INIT_BUFFER] ;

/***************************************************************************************/
/* brief!  function that initialize and the interrupt request                          */
/* param!  u8 (i/p) Interrupt request number                                           */
/* param!  u8 (i/p) Interrupt Sense Control                                            */
/* return! u8 Indication of the execution if it fails or not                           */
/***************************************************************************************/
error_t Ext_Inte_Init(uint8_t au8_Inte_RequestNum, uint8_t au8_InteSense_Control)
{
	/*
	 *	Development Error Tracer
	 */
	error_t au8_Det = ERROR_OK ;
	switch(au8_Inte_RequestNum)
	{
		case INTE_0:
			switch(au8_InteSense_Control)
			{
				case INTE0_LOW_LEVEL:

					CLEAR_MASK(MCUCR, INTE0_SENCE_MASK);
					SET_MASK(MCUCR, INTE0_LOW_LEVEL);
					/* Enable External Interrupt_0 Request */
					SET_BIT(GICR, INT0);
				break;

				case INTE0_LOGICAL_CHANGE:

					CLEAR_MASK(MCUCR, INTE0_SENCE_MASK);
					SET_MASK(MCUCR, INTE0_LOGICAL_CHANGE);
					/* Enable External Interrupt_0 Request */
					SET_BIT(GICR, INT0);
				break;

				case INTE0_FALLING_EDGE:

					CLEAR_MASK(MCUCR, INTE0_SENCE_MASK);
					SET_MASK(MCUCR, INTE0_FALLING_EDGE);
					/* Enable External Interrupt_0 Request */
					SET_BIT(GICR, INT0);
				break;

				case INTE0_RISING_EDGE:

					CLEAR_MASK(MCUCR, INTE0_SENCE_MASK);
					SET_MASK(MCUCR, INTE0_RISING_EDGE);
					/* Enable External Interrupt_0 Request */
					SET_BIT(GICR, INT0);
				break;

				default:
					/* Handling enter wrong interrupt sense control */
					au8_Det = E_INTE0_SENSE_CONTROL;
				break;
			}
		break;

		case INTE_1:
			switch(au8_InteSense_Control)
			{
				case INTE1_LOW_LEVEL:

					CLEAR_MASK(MCUCR, INTE1_SENCE_MASK);
					SET_MASK(MCUCR, INTE1_LOW_LEVEL);
					/* Enable External Interrupt_1 Request */
					SET_BIT(GICR, INT1);
				break;

				case INTE1_LOGICAL_CHANGE:

					CLEAR_MASK(MCUCR, INTE1_SENCE_MASK);
					SET_MASK(MCUCR, INTE1_LOGICAL_CHANGE);
					/* Enable External Interrupt_1 Request */
					SET_BIT(GICR, INT1);
				break;

				case INTE1_FALLING_EDGE:

					CLEAR_MASK(MCUCR, INTE1_SENCE_MASK);
					SET_MASK(MCUCR, INTE1_FALLING_EDGE);
					/* Enable External Interrupt_1 Request */
					SET_BIT(GICR, INT1);
				break;

				case INTE1_RISING_EDGE:

					CLEAR_MASK(MCUCR, INTE1_SENCE_MASK);
					SET_MASK(MCUCR, INTE1_RISING_EDGE);
					/* Enable External Interrupt_1 Request */
					SET_BIT(GICR, INT1);
				break;

				default:
					/* Handling enter wrong interrupt sense control */
					au8_Det = E_INTE1_SENSE_CONTROL;
				break;
			}
		break;

		case INTE_2:
			switch(au8_InteSense_Control)
			{
				case INTE2_FALLING_EDGE:

					CLEAR_MASK(MCUCSR, INTE2_SENCE_MASK);
					SET_MASK(MCUCSR, INTE2_FALLING_EDGE);
					/* Enable External Interrupt_2 Request */
					SET_BIT(GICR, INT2);
				break;

				case INTE2_RISING_EDGE:

					CLEAR_MASK(MCUCSR, INTE2_SENCE_MASK);
					SET_MASK(MCUCSR, INTE2_RISING_EDGE);
					/* Enable External Interrupt_2 Request */
					SET_BIT(GICR, INT2);
				break;

				default:
					/* Handling enter wrong interrupt sense control */
					au8_Det = E_INTE2_SENSE_CONTROL;
				break;
			}
		break;

		default:
			/* Handling enter wrong interrupt request */
			au8_Det = E_INTE_REQUEST;
		break;
	}

	if(ERROR_OK == au8_Det)
	{
		/*
		 *	Raise chosen Interrupt Init. Flag
		 */
		gau8_INTE_InitFlag[au8_Inte_RequestNum] = INTE_IS_INTIALIZED;
		/*
		 *	Enable global interrupt
		 */
		Enable_GlobalInterrupt();
	}
	else
	{
		/* Do Nothing */
	}

	return au8_Det;
}

/***************************************************************************************/
/* brief!  function that deinitialize and the interrupt request                        */
/* param!  u8 (i/p) Interrupt request number                                           */
/* return! u8 Indication of the execution if it fails or not                           */
/***************************************************************************************/
error_t Ext_Inte_Deinit(uint8_t au8_Inte_RequestNum)
{
	/*
	 *	Development Error Tracer
	 */
	error_t au8_Det = ERROR_OK ;

	/* Making sure that the needed interrupt is Initialized */
	if( INTE_IS_INTIALIZED == gau8_INTE_InitFlag[au8_Inte_RequestNum])
	{
		switch(au8_Inte_RequestNum)
		{
			case INTE_0:
				/* Disable External Interrupt_0 Request */
				CLEAR_BIT(GICR, INT0);
			break;

			case INTE_1:
				/* Disable External Interrupt_1 Request */
				CLEAR_BIT(GICR, INT1);
			break;

			case INTE_2:
				/* Disable External Interrupt_2 Request */
				CLEAR_BIT(GICR, INT2);
			break;

			default:
				/* Handling enter wrong interrupt request */
				au8_Det = E_INTE_REQUEST;
			break;
		}
		gau8_INTE_InitFlag[au8_Inte_RequestNum] = INTE_NOT_INTIALIZED;
	}
	else
	{
		au8_Det = E_INTE_NOT_INTIALIZED;
	}

	return au8_Det;
}

/***************************************************************************************/
/* brief!  function that change the interrupt Sense Control                            */
/* param!  u8 (i/p) Interrupt request number                                           */
/* param!  u8 (i/p) Interrupt Sense Control                                            */
/* return! u8 Indication of the execution if it fails or not                           */
/***************************************************************************************/
error_t Ext_Inte_ChangeSense_Control(uint8_t au8_Inte_RequestNum, uint8_t au8_InteSense_Control)
{
	/*
	 *	Development Error Tracer
	 */
	error_t au8_Det = ERROR_OK ;

	/* Making sure that the needed interrupt is Initialized */
	if( INTE_IS_INTIALIZED == gau8_INTE_InitFlag[au8_Inte_RequestNum])
	{
		switch(au8_Inte_RequestNum)
		{
			case INTE_0:
				/* choice the needed interrupt_0 Sense Control */
				switch(au8_InteSense_Control)
				{
					case INTE0_LOW_LEVEL:

						CLEAR_MASK(MCUCR, INTE0_SENCE_MASK);
						SET_MASK(MCUCR, INTE0_LOW_LEVEL);
					break;

					case INTE0_LOGICAL_CHANGE:

						CLEAR_MASK(MCUCR, INTE0_SENCE_MASK);
						SET_MASK(MCUCR, INTE0_LOGICAL_CHANGE);
					break;

					case INTE0_FALLING_EDGE:

						CLEAR_MASK(MCUCR, INTE0_SENCE_MASK);
						SET_MASK(MCUCR, INTE0_FALLING_EDGE);
					break;

					case INTE0_RISING_EDGE:

						CLEAR_MASK(MCUCR, INTE0_SENCE_MASK);
						SET_MASK(MCUCR, INTE0_RISING_EDGE);
					break;

					default:
						/* Handling enter wrong interrupt sense control */
						au8_Det = E_INTE0_SENSE_CONTROL;
					break;
				}
			break;

			case INTE_1:
				/* choice the needed interrupt_1 Sense Control */
				switch(au8_InteSense_Control)
				{
					case INTE1_LOW_LEVEL:

						CLEAR_MASK(MCUCR, INTE1_SENCE_MASK);
						SET_MASK(MCUCR, INTE1_LOW_LEVEL);
					break;

					case INTE1_LOGICAL_CHANGE:

						CLEAR_MASK(MCUCR, INTE1_SENCE_MASK);
						SET_MASK(MCUCR, INTE1_LOGICAL_CHANGE);
					break;

					case INTE1_FALLING_EDGE:

						CLEAR_MASK(MCUCR, INTE1_SENCE_MASK);
						SET_MASK(MCUCR, INTE1_FALLING_EDGE);
					break;

					case INTE1_RISING_EDGE:

						CLEAR_MASK(MCUCR, INTE1_SENCE_MASK);
						SET_MASK(MCUCR, INTE1_RISING_EDGE);
					break;

					default:
						/* Handling enter wrong interrupt sense control */
						au8_Det = E_INTE1_SENSE_CONTROL;
					break;
				}
			break;

			case INTE_2:
				/* choice the needed interrupt_2 Sense Control */
				switch(au8_InteSense_Control)
				{
					case INTE2_FALLING_EDGE:

						/* Disable External Interrupt_2 Request */
						CLEAR_BIT(GICR, INT2);
						/*Clear INTE_1 Flag 1*/
						SET_BIT(GIFR, INTF2);

						CLEAR_MASK(MCUCSR, INTE2_SENCE_MASK);
						SET_MASK(MCUCSR, INTE2_FALLING_EDGE);

						/* Enable External Interrupt_2 Request */
						SET_BIT(GICR, INT2);
					break;

					case INTE2_RISING_EDGE:

						/* Disable External Interrupt_2 Request */
						CLEAR_BIT(GICR, INT2);
						/*Clear INTE_1 Flag 1*/
						SET_BIT(GIFR, INTF2);

						CLEAR_MASK(MCUCSR, INTE2_SENCE_MASK);
						SET_MASK(MCUCSR, INTE2_RISING_EDGE);

						/* Enable External Interrupt_2 Request */
						SET_BIT(GICR, INT2);
					break;

					default:
						/* Handling enter wrong interrupt sense control */
						au8_Det = E_INTE2_SENSE_CONTROL;
					break;
				}
			break;

			default:
				/* Handling enter wrong interrupt request */
				au8_Det = E_INTE_REQUEST;
			break;
		}
	}
	else
	{
		au8_Det = E_INTE_NOT_INTIALIZED;
	}

	return au8_Det;
}

/***************************************************************************************/
/* brief!  Set the function that will execute in the ISR                               */
/* param!  pointer to function that will execute in the ISR                            */
/* param!  u8 (i/p) Interrupt Request Number                                           */
/* return! u8 Indication of the execution if it fails or not                           */
/***************************************************************************************/
error_t Int_SetCallBack(pfunc_t pfun_Int_App, uint8_t au8_Inte_RequestNum)
{
	/*
	 *	Development Error Tracer
	 */
	error_t u8_Det = ERROR_OK ;

	/* Making sure that the passed pointer is not a null pointer */
	if (NULL != pfun_Int_App)
	{
		if( (INTE_0 <= au8_Inte_RequestNum)&&(INTE_2 >= au8_Inte_RequestNum))
		{
			/* Interrupt scenario */
			pfun_Int_CallBack[au8_Inte_RequestNum] = pfun_Int_App;
		}
		else
		{
			/* Handling of passing wrong E_INTERRUPT REQUEST */
			u8_Det = E_INTE_REQUEST ;
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
/* brief!  Interrup_0  handler                                                         */
/* param!  void                                                                        */
/* return! void                                                                        */
/***************************************************************************************/
ISR(INT0_vect)
{
	/* Making sure that the passed pointer is not a null pointer */
	if (NULL != pfun_Int_CallBack[INTE_0])
	{
		pfun_Int_CallBack[INTE_0]();
	}
}

/***************************************************************************************/
/* brief!  Interrup_1  handler                                                         */
/* param!  void                                                                        */
/* return! void                                                                        */
/***************************************************************************************/
ISR(INT1_vect)
{
	/* Making sure that the passed pointer is not a null pointer */
	if (NULL != pfun_Int_CallBack[INTE_1])
	{
		pfun_Int_CallBack[INTE_1]();
	}
}

/***************************************************************************************/
/* brief!  Interrup_2  handler                                                         */
/* param!  void                                                                        */
/* return! void                                                                        */
/***************************************************************************************/
ISR(INT2_vect)
{
	/* Making sure that the passed pointer is not a null pointer */
	if (NULL != pfun_Int_CallBack[INTE_2])
	{
		pfun_Int_CallBack[INTE_2]();
	}
}
