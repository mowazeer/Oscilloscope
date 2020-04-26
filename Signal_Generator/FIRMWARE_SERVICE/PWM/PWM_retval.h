/*
 * PWM_retval.h
 *
 *  Created on: Apr 20, 2020
 *      Author: MO._.Hamdy "Wazeer"
 */

#ifndef __FIRMWARE_PWM_PWM_RETVAL_H__
#define __FIRMWARE_PWM_PWM_RETVAL_H__


#include "Retval.h"

/*
*	Error macros
*/
#define PWM_ERROR_BASE_CODE       		(error_t)(160U)
#define E_PWM_INTIALIZED 				(error_t)(PWM_ERROR_BASE_CODE + 1U )
#define E_PWM_NOT_INTIALIZED 			(error_t)(PWM_ERROR_BASE_CODE + 2U )
#define E_PWM_CHANNEL_INTIALIZED 		(error_t)(PWM_ERROR_BASE_CODE + 3U )
#define E_PWM_CHANNEL_NOT_INTIALIZED 	(error_t)(PWM_ERROR_BASE_CODE + 4U )
#define E_PWM_RESOLUTION 				(error_t)(PWM_ERROR_BASE_CODE + 5U )
#define E_PWM_PIN_NUM 					(error_t)(PWM_ERROR_BASE_CODE + 6U )
#define E_PWM_DUTY_CYCLE 				(error_t)(PWM_ERROR_BASE_CODE + 7U )
#define E_PWM_PERIOD 					(error_t)(PWM_ERROR_BASE_CODE + 8U )
#define E_PWM_CHANNELS_NUM 				(error_t)(PWM_ERROR_BASE_CODE + 9U )

#endif /* __FIRMWARE_PWM_PWM_RETVAL_H__ */
