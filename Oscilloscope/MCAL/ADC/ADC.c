/*
 * ADC.c
 *
 *  Created on: Apr 18, 2020
 *      Author: MO._.Hamdy "Wazeer"
 */


#include "ADC_private.h"
#include "Macros.h"
#include "ADC.h"
#include "Interrupt.h"


/*
 * pointer to function for call back function
 */
static pfunc_u8_u8_t pfun_ADC_CallBack;

/*
*	Static variable that tells if the ADC module is initialized or not
*/
static uint8_t gu8_ADC_InitFlag = ADC_NOT_INTIALIZED ;

/*
*	Static variable that hold ADC (Left / Right) Adjust
*/
static uint8_t gu8_LeftRight_Adjust = DUMMY ;

/*
 *	Static variable store UART mode configuration "Polling or interrupt"
 */
static uint8_t u8_ADC_InterruptMode = DUMMY ;

/***************************************************************************************/
/* brief!  ADC Initialization                                                          */
/* param!  (I/P) pointer to structure that hold ADC Configuration                      */
/* return! u8 Indication of the execution if it fails or not                           */
/***************************************************************************************/
error_t ADC_Init(str_ADC_cfg_t *pstr_ADC_cfg)
{
	/*
	 *	Development Error Tracer
	 */
	error_t au8_DET = ERROR_OK ;

	/* Checking that the passed pointer is not a NULL one */
	if (NULL != pstr_ADC_cfg )
	{
		/* configure the used channel to read */
		if((ADC_CH0 <= pstr_ADC_cfg -> u8_Channel)&&(ADC_CH7 >= pstr_ADC_cfg -> u8_Channel))
		{
			/* Initialize ADC pin as input pin */
			DIO_INIT_Pin(pstr_ADC_cfg -> u8_Channel, INPUT_PIN);

			/* Chose Channel to read */
			CLEAR_MASK(ADMUX, ADC_CH_MASK);
			SET_MASK(ADMUX, pstr_ADC_cfg -> u8_Channel);

			/* chose the reference volt */
			switch(pstr_ADC_cfg -> u8_VoltRef)
			{
				case ADC_INTERNAL_VCC:
					CLEAR_MASK(ADMUX, ADC_VCC_MASK);
					SET_MASK(ADMUX, ADC_INTERNAL_VCC);
				break;

				case ADC_EXTERNAL_VCC:
					CLEAR_MASK(ADMUX, ADC_VCC_MASK);
					SET_MASK(ADMUX, ADC_EXTERNAL_VCC);
				break;

				case ADC_INTERNAL_2_56VCC:
					CLEAR_MASK(ADMUX, ADC_VCC_MASK);
					SET_MASK(ADMUX, ADC_INTERNAL_2_56VCC);
				break;

				default:
					au8_DET = E_ADC_VOLTAGE_REF;
				break;
			}

			/* ADC (Left/Right) Adjust Result */
			gu8_LeftRight_Adjust = pstr_ADC_cfg -> u8_LeftRight_Adjust;
			switch(pstr_ADC_cfg -> u8_LeftRight_Adjust)
			{
				case ADC_LEFT_ADJUST:
					SET_BIT(ADMUX, ADLAR);//set left adjust
				break;

				case ADC_RIGHT_ADJUST:
					CLEAR_BIT(ADMUX, ADLAR);//set right adjust
				break;

				default:
					au8_DET = E_ADC_ADJUST;
				break;
			}

			/* ADC prescaler */
			if((ADC_PSC_0 <= pstr_ADC_cfg -> u8_PSC)&&(ADC_PSC_128 >= pstr_ADC_cfg -> u8_PSC))
			{
				CLEAR_MASK(ADCSRA, ADC_PSC_MASK);
				SET_MASK(ADCSRA, pstr_ADC_cfg -> u8_PSC);
			}
			else
			{
				au8_DET = E_ADC_PSC;
			}

			/* ADC Interrupt / Polling Mode */
			u8_ADC_InterruptMode = pstr_ADC_cfg -> u8_Interrupt_Mode;
			if(ADC_INTERRUPT == pstr_ADC_cfg -> u8_Interrupt_Mode)
			{
				/* Enable_Global Interrupt */
				Enable_GlobalInterrupt();
				SET_BIT(ADCSRA, ADIE);
			}
			else if(ADC_POLLING == pstr_ADC_cfg -> u8_Interrupt_Mode)
			{
				CLEAR_BIT(ADCSRA, ADIE);
			}
			else
			{
				au8_DET = E_ADC_INTERRUPT_MODE;
			}

			/* ADC Trigger Mode */
			if((ADC_FREE_RUNNING <= pstr_ADC_cfg -> u8_Trigger_Source)&&(ADC_TIMER_1_CAPTURE >= pstr_ADC_cfg -> u8_Trigger_Source))
			{
				/* Enable ADC Auto Trigger Mode */
				SET_BIT(ADCSRA, ADATE);

				/* ADC Auto Trigger Source */
				CLEAR_MASK(SFIOR, ADC_TRIGGER_MASK);
				SET_MASK(SFIOR, pstr_ADC_cfg -> u8_Trigger_Source);
			}
			else if(ADC_MANUAL_TRIGGER == pstr_ADC_cfg -> u8_Trigger_Source)
			{
				/* Disable ADC Auto Trigger Mode */
				CLEAR_BIT(ADCSRA, ADATE);
			}
			else
			{
				au8_DET = E_ADC_TRIGGER_MODE;
			}

			/* ADC enable */
			if(ERROR_OK == au8_DET)
			{
				SET_BIT(ADCSRA, ADEN);
				gu8_ADC_InitFlag = ADC_IS_INTIALIZED;
			}
			else
			{
				/* return last detected error */
			}
		}
		else
		{
			au8_DET = E_ADC_CHANNEL;
		}
	}
	else
	{
		/*Handling of using null pointer*/
		au8_DET = E_NULL_PTR ;
	}
	/* Return the Development Error Tracer if it's OK or not */
	return au8_DET ;
}

/***************************************************************************************/
/* brief!  ADC Deinitialization                                                        */
/* param!  void                                                                        */
/* return! u8 Indication of the execution if it fails or not                           */
/***************************************************************************************/
error_t ADC_Deinit(void)
{
	/*
	 *	Development Error Tracer
	 */
	error_t au8_DET = ERROR_OK ;

	if(ADC_IS_INTIALIZED == gu8_ADC_InitFlag)
	{
		CLEAR_BIT(ADCSRA, ADEN);  /* ADC Disable */

		gu8_ADC_InitFlag = ADC_NOT_INTIALIZED;
		gu8_LeftRight_Adjust = DUMMY;
		u8_ADC_InterruptMode = DUMMY;
	}
	else
	{
		/* Handling ADC Initialization error */
		au8_DET = E_ADC_NOT_INTIALIZED;
	}

	return au8_DET;
}

/***************************************************************************************/
/* brief!  ADC Change the configuration of the ADC to a certain channel                */
/* param!  u8 (i/p) The desired channel to be changed                                  */
/* return! u8 Indication of the execution if it fails or not                           */
/***************************************************************************************/
error_t ADC_Change_Channel(uint8_t au8_Channel)
{
	/*
	 *	Development Error Tracer
	 */
	error_t au8_DET = ERROR_OK ;

	/* Check ADC Initialization */
	if(ADC_IS_INTIALIZED == gu8_ADC_InitFlag)
	{
		/* Check ADC Channel Range */
		if((ADC_CH0 <= au8_Channel)&&(ADC_CH7 >= au8_Channel))
		{
			/* Initialize ADC pin as input pin */
			DIO_INIT_Pin(au8_Channel, INPUT_PIN);

			/* Chose Channel to read */
			CLEAR_MASK(ADMUX, ADC_CH_MASK);
			SET_MASK(ADMUX, au8_Channel);
		}
		else
		{
			/* Handle Entering Wrong Channel */
			au8_DET = E_ADC_CHANNEL;
		}
	}
	else
	{
		/* Handling ADC Initialization error */
		au8_DET = E_ADC_NOT_INTIALIZED;
	}

	return au8_DET ;
}

/***************************************************************************************/
/* brief!  ADC Start Conversion                                                        */
/* param!  void                                                                        */
/* return! u8 Indication of the execution if it fails or not                           */
/***************************************************************************************/
error_t ADC_Start_Conversion(void)
{
	/*
	 *	Development Error Tracer
	 */
	error_t au8_DET = ERROR_OK ;

	if(ADC_IS_INTIALIZED == gu8_ADC_InitFlag)
	{
		SET_BIT(ADCSRA, ADSC);  /* ADC start conversion */
	}
	else
	{
		/* Handling ADC Initialization error */
		au8_DET = E_ADC_NOT_INTIALIZED;
	}

	return au8_DET;
}

/***************************************************************************************/
/* brief!  ADC Stop Conversion                                                        */
/* param!  void                                                                        */
/* return! u8 Indication of the execution if it fails or not                           */
/***************************************************************************************/
error_t ADC_Stop_Conversion(void)
{
	/*
	 *	Development Error Tracer
	 */
	error_t au8_DET = ERROR_OK ;

	if(ADC_IS_INTIALIZED == gu8_ADC_InitFlag)
	{
		CLEAR_BIT(ADCSRA, ADSC);  /* ADC start conversion */
	}
	else
	{
		/* Handling ADC Initialization error */
		au8_DET = E_ADC_NOT_INTIALIZED;
	}

	return au8_DET;
}

/***************************************************************************************/
/* brief!  ADC Read Value	                                                           */
/* param!  (o/p) pu16 pointer to u16 that hold ADC Value                               */
/* return! u8 Indication of the execution if it fails or not                           */
/***************************************************************************************/
error_t ADC_Read(uint16_t volatile *pu16_Digital_Reading)
{
	/*
	 *	Development Error Tracer
	 */
	error_t au8_DET = ERROR_OK ;

	switch(u8_ADC_InterruptMode)
	{
		case ADC_POLLING:

			while(GET_BIT(ADCSRA, ADIF) == NULL);

			switch(gu8_LeftRight_Adjust)
			{
				case ADC_RIGHT_ADJUST:
					*pu16_Digital_Reading  = ((uint16_t) ADCL) | ((uint16_t)(ADCH << 8U));
				break;

				case ADC_LEFT_ADJUST:
					*pu16_Digital_Reading  = ((uint16_t)(ADCL >> 6U)) | ((uint16_t)(ADCH << 2U));
				break;

				default:
					au8_DET = E_ADC_ADJUST;
					break;
			}
			/* clear ADC Flag */
			SET_BIT(ADCSRA, ADIF);
		break;

		case ADC_INTERRUPT:
			/* do nothing */
		break;

		default :
			au8_DET = E_ADC_INTERRUPT_MODE;
		break;
	}

	return au8_DET;
}

/***************************************************************************************/
/* brief!  ADC Set the function that will execute in the ISR                           */
/* param!  pointer to function that will execute in the ISR                            */
/* return! u8 Indication of the execution if it fails or not                           */
/***************************************************************************************/
error_t ADC_SetCallBack(pfunc_u8_u8_t pfun_ADC_App)
{
	/*
	 *	Development Error Tracer
	 */
	error_t au8_Det = ERROR_OK ;

	if (NULL != pfun_ADC_App)
	{
		pfun_ADC_CallBack = pfun_ADC_App;
	}
	else
	{
		/* Handling of passing null pointer */
		au8_Det = E_NULL_PTR ;
	}
	return au8_Det;
}

/***************************************************************************************/
/* brief!  ADC interrupt handling                                             	       */
/* param!  void                                                                        */
/* return! void                                                                        */
/***************************************************************************************/
ISR(ADC_vect)
{
	if (NULL != pfun_ADC_CallBack)
	{
		pfun_ADC_CallBack(ADCL, ADCH);
	}
}
