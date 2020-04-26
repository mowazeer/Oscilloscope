/*
 * ADC_retval.h
 *
 *  Created on: Apr 18, 2020
 *      Author: MO._.Hamdy "Wazeer"
 */

#ifndef __MCAL_ADC_ADC_RETVAL_H__
#define __MCAL_ADC_ADC_RETVAL_H__

#include "Retval.h"

/*
 *	Error macros
 */
#define ADC_ERROR_BASE_CODE       		(error_t)(40U)
#define E_ADC_CHANNEL 					(error_t)(ADC_ERROR_BASE_CODE + 1U )  	/* Wrong Channel */
#define E_ADC_VOLTAGE_REF	  			(error_t)(ADC_ERROR_BASE_CODE + 4U )	/* Wrong Voltage Reference */
#define E_ADC_ADJUST	  				(error_t)(ADC_ERROR_BASE_CODE + 4U )	/* Wrong Adjust */
#define E_ADC_PSC 						(error_t)(ADC_ERROR_BASE_CODE + 2U )  	/* Wrong prescaler */
#define E_ADC_ADC_MODE 					(error_t)(ADC_ERROR_BASE_CODE + 3U )  	/* ADC or counter mode error  */
#define E_ADC_INTERRUPT_MODE  			(error_t)(ADC_ERROR_BASE_CODE + 4U )  	/* Interrupt or Polling mode error   */
#define E_ADC_TRIGGER_MODE  			(error_t)(ADC_ERROR_BASE_CODE + 4U )	/* Wrong Trigger Source */
#define E_ADC_NOT_INTIALIZED 			(error_t)(ADC_ERROR_BASE_CODE + 6U )	/* Init. error */

#endif /* __MCAL_ADC_ADC_RETVAL_H__ */
