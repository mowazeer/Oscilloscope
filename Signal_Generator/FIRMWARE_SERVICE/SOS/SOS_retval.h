/*
 * SOS_retval.h
 *
 *  Created on: Jan 7, 2020
 *      Author: MO._.Hamdy "Wazeer"
 */

#ifndef __FIRMWARE_SOS_SOS_RETVAL_H__
#define __FIRMWARE_SOS_SOS_RETVAL_H__


#include "Retval.h"

/*
 *	Error macros
 */
#define SOS_ERROR_BASE_CODE       		(error_t)(140U)
#define E_SOS_PERIODICITY 				(error_t)(SOS_ERROR_BASE_CODE + 1U )
#define E_SOS_RESOLUTION				(error_t)(SOS_ERROR_BASE_CODE + 2U )
#define E_SOS_BUFFER_SIZE 				(error_t)(SOS_ERROR_BASE_CODE + 3U )
#define E_SOS_INTIALIZED 				(error_t)(SOS_ERROR_BASE_CODE + 4U )
#define E_SOS_NOT_INTIALIZED 			(error_t)(SOS_ERROR_BASE_CODE + 5U )


#endif /* __FIRMWARE_SOS_SOS_RETVAL_H__ */
